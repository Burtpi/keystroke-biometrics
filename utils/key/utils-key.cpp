#include <database/database.h>
#include <utils/key/utils-key.h>
#include <utils/key/validators/utils-key-validators.h>
#include <utils/time/utils-time.h>

#include <string>

std::vector<database::models::KeyBuffer> utils::key::SortKeyStates(
    std::vector<database::models::KeyBuffer> key_states) {
    std::vector<database::models::KeyBuffer> sorted_key_states = key_states;
    std::sort(sorted_key_states.begin(), sorted_key_states.end());
    return sorted_key_states;
}

void utils::key::LogKeyStates(
    std::vector<database::models::KeyBuffer> key_states) {
    std::vector<database::models::KeyBuffer> sorted_key_states =
        utils::key::SortKeyStates(key_states);

    std::stringstream row;

    row << "Elapsed Time: "
        << global_config_manager.GetAppConfig().GetElapsedTime()
        << ", Size: " << std::to_string(sorted_key_states.size())
        << ", Keys: [";

    const std::map<int, std::string>& hid_to_ascii =
        global_config_manager.GetLanguageConfig().GetHidToAscii();

    for (database::models::KeyBuffer key : sorted_key_states) {
        row << "{Key: ";
        std::_Tree<std::map<int, std::string>>::const_iterator it =
            hid_to_ascii.find(key.hid);
        if (it != hid_to_ascii.end()) {
            row << hid_to_ascii.find(key.hid)->second;
        } else {
            row << key.hid;
        }
        row << ", Pressure: " << key.pressure << "}, ";
    }
    row << "]";
    global_config_manager.GetLoggerConfig().GetHitLogger()->info(row.str());
}

void utils::key::CreateKeyHits(database::models::KeyBuffer& key_state) {
    int elapsed_time =
        stoi(global_config_manager.GetAppConfig().GetElapsedTime());
    bool is_modifier =
        utils::key::validators::CheckIfModifierKey(key_state.hid);

    // Use different key hits container depending on whether the key is a
    // modifier
    std::vector<database::models::KeyHit>& key_hits =
        is_modifier ? database_manager.GetModifierKeyHitContainer().GetEntries()
                    : database_manager.GetKeyHitContainer().GetEntries();

    utils::key::validators::KeyHitIterator existing_key =
        utils::key::validators::CheckIfExists(key_state, key_hits);

    // Update existing key hit or create a new one
    if (existing_key != key_hits.end()) {
        existing_key->UpdateKeyHit(elapsed_time, key_state.pressure);
    } else {
        global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
            "Adding new key hit entry.");

        // Add key hits to different containers depending on whether the key is
        // a modifier
        if (is_modifier) {
            database_manager.GetModifierKeyHitContainer().AddModifierEntry(
                key_state.hid, elapsed_time, key_state.pressure);
        } else {
            database_manager.GetKeyHitContainer().AddEntry(
                key_state.hid, elapsed_time, key_state.pressure);

            // After adding a new key hit, check whether the key is a part of an
            // n-graph
            utils::key::validators::CheckIfNgraph();
        }
        global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
            "Successfully added new key hit entry.");
    }
}

void utils::key::RemoveNotPressedHits() {
    try {
        // Remove all not pressed hits from modifier keys container
        const std::vector<database::models::KeyHit>& modifier_keys =
            database_manager.GetModifierKeyHitContainer().GetEntries();

        auto modifier_key = modifier_keys.begin();
        int counter = 0;

        while (modifier_key != modifier_keys.end()) {
            if (!modifier_key->GetWasPressed()) {
                modifier_key =
                    database_manager.GetModifierKeyHitContainer().RemoveEntry(
                        modifier_key);
                counter++;
            } else {
                ++modifier_key;
            }
        }

        // Remove all not pressed hits from key hits container
        const std::vector<database::models::KeyHit>& key_hits =
            database_manager.GetKeyHitContainer().GetEntries();
        auto key_hit = key_hits.begin();
        while (key_hit != key_hits.end()) {
            if (!key_hit->GetWasPressed()) {
                key_hit =
                    database_manager.GetKeyHitContainer().RemoveEntry(key_hit);
                counter++;
            } else {
                ++key_hit;
            }
        }

        // Log only if any objects were removed
        if (counter > 0)
            global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
                "Successfully removed {} entries.", counter);
    } catch (const std::exception& e) {
        global_config_manager.GetLoggerConfig().GetGeneralLogger()->error(
            "Error occured: {}", e.what());
    }
}

void utils::key::LogAllHits() {
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Logging all hits to files.");

    database_manager.GetKeyHitContainer().SaveToFile();
    database_manager.GetNgraphContainer().SaveToFile();

    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Successfully logged all hits to files.");
}

void utils::key::LoadAllHits() {
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Loading all hits from files.");

    database_manager.GetKeyHitContainer().LoadFromFile();
    database_manager.GetNgraphContainer().LoadFromFile();

    // Merge key hit and ngraph containers for proper calculation
    database_manager.GetMergedObjectsContainer().SetMergedObjects(
        database_manager.GetKeyHitContainer().GetEntries(),
        database_manager.GetNgraphContainer().GetEntries());

    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Successfully loaded all hits from files.");
}