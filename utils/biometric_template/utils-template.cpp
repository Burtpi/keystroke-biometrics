#include <config/config-manager.h>
#include <database/database.h>
#include <database/models/calc-key-hit.h>
#include <database/models/calc-ngraph.h>
#include <database/models/key-hit.h>
#include <database/models/ngraph.h>
#include <utils/biometric_template/utils-template.h>
#include <utils/time/utils-time.h>

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void utils::biometric_template::CreateTemplate() {
    ProcessKeyHits();
    ProcessNgraphs();
}

void utils::biometric_template::ProcessKeyHits() {
    std::unordered_map<KeyHitType, std::vector<database::models::KeyHit>>
        grouped_key_hits = GroupKeyHits();

    for (const auto& grouped_key_hit : grouped_key_hits) {
        database_manager.GetCalcKeyHitContainer().AddEntry(
            grouped_key_hit.first, grouped_key_hit.second);
    }
}

void utils::biometric_template::ProcessNgraphs() {
    std::unordered_map<std::string, std::vector<database::models::Ngraph>>
        grouped_ngraphs = GroupNgraphs();

    for (const auto& grouped_ngraph : grouped_ngraphs) {
        database_manager.GetCalcNgraphContainer().AddEntry(
            grouped_ngraph.first, grouped_ngraph.second);
    }
}

utils::biometric_template::GroupedKeyHits
utils::biometric_template::GroupKeyHits() {
    utils::biometric_template::GroupedKeyHits grouped_key_hits;
    const std::vector<database::models::KeyHit>& key_hits =
        database_manager.GetKeyHitContainer().GetEntries();
    const std::vector<database::models::KeyHit>& modifier_keys =
        database_manager.GetModifierKeyHitContainer().GetEntries();
    std::vector<database::models::KeyHit> merged_key_hits;

    merged_key_hits.insert(merged_key_hits.end(), key_hits.begin(),
                           key_hits.end());

    merged_key_hits.insert(merged_key_hits.end(), modifier_keys.begin(),
                           modifier_keys.end());

    for (const database::models::KeyHit& key_hit : merged_key_hits) {
        utils::biometric_template::KeyHitType key = std::make_tuple(
            key_hit.GetHid(), key_hit.GetIsSpecial(), key_hit.GetIsBig());
        grouped_key_hits[key].push_back(key_hit);
    }
    return grouped_key_hits;
}

utils::biometric_template::GroupedNgraphs
utils::biometric_template::GroupNgraphs() {
    utils::biometric_template::GroupedNgraphs grouped_ngraphs;
    const std::vector<database::models::Ngraph>& ngraphs =
        database_manager.GetNgraphContainer().GetEntries();

    for (const database::models::Ngraph& ngraph : ngraphs) {
        grouped_ngraphs[ngraph.GetChars()].push_back(ngraph);
    }
    return grouped_ngraphs;
}

void utils::biometric_template::SaveToFile() {
    database_manager.GetCalcKeyHitContainer().SaveToFile();
    database_manager.GetCalcNgraphContainer().SaveToFile();
}