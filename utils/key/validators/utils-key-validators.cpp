#include <config/config-manager.h>
#include <database/database.h>
#include <utils/key/validators/utils-key-validators.h>

#include <algorithm>
#include <iterator>

void utils::key::validators::CheckIfExit(
    database::models::KeyBuffer &key_state) {
    if (key_state.hid == global_config_manager.GetAppConfig().GetExitHid()) {
        global_config_manager.GetAppConfig().SetKeyLogging(false);
    }
}

utils::key::validators::KeyHitIterator utils::key::validators::CheckIfExists(
    database::models::KeyBuffer key_state,
    std::vector<database::models::KeyHit> &key_hits) {
    // Check whether the data from buffer refers to any existing object of the
    // currently pressed keys
    KeyHitIterator key =
        std::find_if(key_hits.begin(), key_hits.end(),
                     [key_state](database::models::KeyHit &key_hit) {
                         return key_hit.GetHid() == key_state.hid &&
                                key_hit.GetIsPressed() == true;
                     });
    return key;
}

bool utils::key::validators::CheckIfSpecialChar(int hid) {
    const std::vector<database::models::KeyHit> &modifier_keys =
        database_manager.GetModifierKeyHitContainer().GetEntries();

    const std::map<int, std::string> &special_chars_ascii =
        global_config_manager.GetLanguageConfig().GetSpecialCharsAscii();

    // Check if Right Alt key is currently pressed
    std::vector<database::models::KeyHit>::const_iterator ralt = std::find_if(
        modifier_keys.begin(), modifier_keys.end(),
        [](const database::models::KeyHit &key_hit) {
            return key_hit.GetHid() == 230 && key_hit.GetIsPressed() == true;
        });
    std::_Tree<std::map<int, std::string>>::const_iterator special_char =
        special_chars_ascii.find(hid);

    return special_char != special_chars_ascii.end() &&
           ralt != modifier_keys.end();
}

bool utils::key::validators::CheckIfBigChar() {
    const std::vector<database::models::KeyHit> &modifier_keys =
        database_manager.GetModifierKeyHitContainer().GetEntries();

    // Check if any Shift key is currently pressed
    std::vector<database::models::KeyHit>::const_iterator shift = std::find_if(
        modifier_keys.begin(), modifier_keys.end(),
        [](const database::models::KeyHit &key_hit) {
            return (key_hit.GetHid() == 225 || key_hit.GetHid() == 229) &&
                   key_hit.GetIsPressed() == true;
        });
    return shift != modifier_keys.end();
}

bool utils::key::validators::CheckIfModifierKey(int hid) {
    const std::map<int, std::string> &modifier_keys =
        global_config_manager.GetLanguageConfig().GetModifierKeys();

    // Check if pressed key is a modifier key (any Shift, Right Alt)
    std::_Tree<std::map<int, std::string>>::const_iterator modifier_key =
        modifier_keys.find(hid);
    return modifier_key != modifier_keys.end();
}

void utils::key::validators::CheckIfNgraph() {
    const std::vector<database::models::KeyHit> &key_hits =
        database_manager.GetKeyHitContainer().GetEntries();

    if (key_hits.size() <= 3) return;

    database::models::KeyHit key_hit = key_hits.back();

    const config::LanguageConfig &language_config =
        global_config_manager.GetLanguageConfig();

    // Get mapped char value depending on whether the key hit is special
    auto get_char = [&](database::models::KeyHit key_hit) -> std::string {
        return key_hit.GetIsSpecial() ? language_config.GetSpecialCharsAscii()
                                            .find(key_hit.GetHid())
                                            ->second
                                      : language_config.GetHidToAscii()
                                            .find(key_hit.GetHid())
                                            ->second;
    };

    // Check if n-graph
    auto process_n_graph = [&](const std::string &ngraph_str, int n) {
        const std::vector<std::string> &ngraph_size =
            n == 2 ? language_config.GetDigraph()
                   : language_config.GetTrigraph();

        std::vector<std::string>::const_iterator ngraph_find =
            std::find(ngraph_size.begin(), ngraph_size.end(), ngraph_str);

        if (ngraph_find != ngraph_size.end()) {
            std::vector<int> time_stamps = {
                key_hits[key_hits.size() - n].GetTimeStamp(),
                key_hit.GetTimeStamp()};

            global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
                "Adding new ngraph entry.");

            database_manager.GetNgraphContainer().AddEntry(ngraph_str,
                                                           time_stamps);

            // Add new n-graph to the merged objects container for easier
            // calculation
            database_manager.GetMergedObjectsContainer().AddEntry(
                database_manager.GetNgraphContainer().GetEntries().back());

            global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
                "Successfully added new ngraph entry.");
        }
    };

    std::string digraph_str =
        get_char(key_hits[key_hits.size() - 2]) + get_char(key_hit);
    process_n_graph(digraph_str, 2);

    if (key_hits.size() > 4) {
        std::string trigraph_str = get_char(key_hits[key_hits.size() - 3]) +
                                   get_char(key_hits[key_hits.size() - 2]) +
                                   get_char(key_hit);
        process_n_graph(trigraph_str, 3);
    }
}

void utils::key::validators::CheckIfKeyIsPressed(
    database::models::KeyBuffer &key_state) {
    std::vector<database::models::KeyHit> &key_hits =
        utils::key::validators::CheckIfModifierKey(key_state.hid)
            ? database_manager.GetModifierKeyHitContainer().GetEntries()
            : database_manager.GetKeyHitContainer().GetEntries();

    if (key_state.pressure == 0) {
        for (database::models::KeyHit &key_hit : key_hits) {
            if (key_hit.GetHid() == key_state.hid && key_hit.GetIsPressed()) {
                utils::key::validators::CheckIfKeyWasPressed(key_hit);

                // Calculate descriptors only if key was pressed
                if (key_hit.GetWasPressed()) {
                    key_hit.SetIsPressed(false);
                    key_hit.Calculate();
                    database_manager.GetMergedObjectsContainer().AddEntry(
                        key_hit);
                }
                break;
            }
        }
    }
}

void utils::key::validators::CheckIfKeyWasPressed(
    database::models::KeyHit &key_hit) {
    // Proceed only if there is enough pressure data for interpolation
    if (key_hit.GetPressures().size() > 8) {
        // Check if any pressure value was above the minimum actuation point set
        // in config
        for (float pressure : key_hit.GetPressures()) {
            if (pressure >
                global_config_manager.GetAppConfig().GetActuationPoint())
                return;
        }
    }
    key_hit.SetWasPressed(false);
}