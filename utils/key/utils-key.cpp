#include <database/database.h>
#include <logger/logger.h>
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

    std::map<int, std::string> hid_to_ascii =
        global_config_manager.GetLanguageConfig().GetHidToAscii();

    for (database::models::KeyBuffer key : sorted_key_states) {
        row << "{Key: ";
        auto it = hid_to_ascii.find(key.hid);
        if (it != hid_to_ascii.end()) {
            row << hid_to_ascii.find(key.hid)->second;
        } else {
            row << key.hid;
        }
        row << ", Pressure: " << key.pressure << "}, ";
    }
    row << "]";
    logger::GetHitLogger()->info(row.str());
}

void utils::key::CreateKeyHits(
    std::vector<database::models::KeyBuffer> key_states) {
    int elapsed_time =
        stoi(global_config_manager.GetAppConfig().GetElapsedTime());

    for (database::models::KeyBuffer key_state : key_states) {
        bool is_modifier =
            utils::key::validators::CheckIfModifierKey(key_state);

        std::vector<database::models::KeyHit> key_hits =
            is_modifier
                ? database_manager.GetKeyHitContainer().GetModifierKeys()
                : database_manager.GetKeyHitContainer().GetKeyHits();

        utils::key::validators::KeyHitIterator existing_key =
            utils::key::validators::CheckIfExists(key_state, key_hits);

        if (existing_key != key_hits.end()) {
            existing_key->PushBackTimeStamp(elapsed_time);
            existing_key->PushBackPressure(key_state.pressure);
        } else {
            database_manager.GetKeyHitContainer().AddKeyHit(
                is_modifier, key_state.hid, elapsed_time, key_state.pressure);
        }
    }
}