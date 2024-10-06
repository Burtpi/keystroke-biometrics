#include <config/config-manager.h>
#include <database/database.h>
#include <utils/key/validators/utils-key-validators.h>

#include <algorithm>
#include <iterator>

void utils::key::validators::CheckIfExit(
    database::models::KeyBuffer &key_state) {
    if (key_state.hid == global_config_manager.GetAppConfig().GetExitHid())
        global_config_manager.GetAppConfig().SetKeyLogging(false);
}

utils::key::validators::KeyHitIterator utils::key::validators::CheckIfExists(
    database::models::KeyBuffer key_state,
    std::vector<database::models::KeyHit> key_hits) {
    KeyHitIterator key =
        std::find_if(key_hits.begin(), key_hits.end(),
                     [key_state](database::models::KeyHit &key_hit) {
                         return key_hit.GetHid() == key_state.hid &&
                                key_hit.GetIsPressed() == true;
                     });
    return key;
}

bool utils::key::validators::CheckIfSpecialChar(int hid) {
    KeyHitIterator ralt = std::find_if(
        database_manager.GetKeyHitContainer().GetModifierKeys().begin(),
        database_manager.GetKeyHitContainer().GetModifierKeys().end(),
        [](database::models::KeyHit &key_hit) {
            return key_hit.GetHid() == 230 && key_hit.GetIsPressed() == true;
        });
    auto special_char =
        global_config_manager.GetLanguageConfig().GetSpecialCharsAscii().find(
            hid);

    return special_char != global_config_manager.GetLanguageConfig()
                               .GetSpecialCharsAscii()
                               .end() &&
           ralt !=
               database_manager.GetKeyHitContainer().GetModifierKeys().end();
}

bool utils::key::validators::CheckIfBigChar() {
    KeyHitIterator shift = std::find_if(
        database_manager.GetKeyHitContainer().GetModifierKeys().begin(),
        database_manager.GetKeyHitContainer().GetModifierKeys().end(),
        [](database::models::KeyHit &key_hit) {
            return (key_hit.GetHid() == 225 || key_hit.GetHid() == 229) &&
                   key_hit.GetIsPressed() == true;
        });
    return shift !=
           database_manager.GetKeyHitContainer().GetModifierKeys().end();
}

bool utils::key::validators::CheckIfModifierKey(
    database::models::KeyBuffer key_state) {
    auto modifier_key =
        global_config_manager.GetLanguageConfig().GetModifierKeys().find(
            key_state.hid);
    return modifier_key !=
           global_config_manager.GetLanguageConfig().GetModifierKeys().end();
}

void utils::key::validators::CheckIfNgraph(database::models::KeyHit key_hit) {
    std::vector<database::models::KeyHit> key_hits =
        database_manager.GetKeyHitContainer().GetKeyHits();

    if (key_hits.size() <= 3) return;

    config::LanguageConfig language_config =
        global_config_manager.GetLanguageConfig();

    auto get_char = [&](database::models::KeyHit key_hit) -> std::string {
        return key_hit.GetIsSpecial() ? language_config.GetSpecialCharsAscii()
                                            .find(key_hit.GetHid())
                                            ->second
                                      : language_config.GetHidToAscii()
                                            .find(key_hit.GetHid())
                                            ->second;
    };

    auto process_n_graph = [&](const std::string &ngraph_str, int n) {
        std::vector<std::string> ngraph_size =
            n == 2 ? language_config.GetDigraph()
                   : language_config.GetTrigraph();
        std::vector<std::string>::iterator ngraph_find =
            std::find(ngraph_size.begin(), ngraph_size.end(), ngraph_str);
        if (ngraph_find != ngraph_size.end()) {
            database_manager.GetNgraphContainer().GetNgraphs().emplace_back(
                ngraph_str);
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
    std::vector<database::models::KeyHit> key_hits_ =
        utils::key::validators::CheckIfModifierKey(key_state)
            ? database_manager.GetKeyHitContainer().GetModifierKeys()
            : database_manager.GetKeyHitContainer().GetKeyHits();
    if (key_state.pressure == 0) {
        for (database::models::KeyHit &key_hit : key_hits_) {
            if (key_hit.GetHid() == key_state.hid && key_hit.GetIsPressed()) {
                key_hit.SetIsPressed(false);
                key_hit.Calculate();
                break;
            }
        }
    }
}