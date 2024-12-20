#include <config/config-manager.h>
#include <database/database.h>
#include <database/models/calc-key-hit.h>
#include <database/models/calc-ngraph.h>
#include <database/models/key-hit.h>
#include <database/models/ngraph.h>
#include <utils/biometric_template/utils-template.h>
#include <utils/time/utils-time.h>

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

void utils::biometric_template::CreateTemplate() {
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Creating templates.");

    ProcessKeyHits();
    ProcessNgraphs();

    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Successfully created the templates");
}

void utils::biometric_template::ProcessKeyHits() {
    std::unordered_map<KeyHitType, std::vector<database::models::KeyHit>,
                       utils::biometric_template::TupleHash,
                       utils::biometric_template::TupleEqual>
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
    // Merge key hits and modifier key hits containers
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

    // Group all merged key hits by their key (hid, is_special, is_big)
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

    // Group all n-graphs
    for (const database::models::Ngraph& ngraph : ngraphs) {
        grouped_ngraphs[ngraph.GetChars()].push_back(ngraph);
    }
    return grouped_ngraphs;
}

void utils::biometric_template::SaveToFile() {
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Saving the templates to files.");

    std::string date = utils::time::GetDateInString(
        global_config_manager.GetLoggerConfig().GetStartDate());

    std::string date_folder =
        global_config_manager.GetLoggerConfig().GetDateFolder();

    database_manager.GetCalcKeyHitContainer().SaveToFile(date_folder +
                                                         "/template_hits.csv");
    database_manager.GetCalcNgraphContainer().SaveToFile(
        date_folder + "/template_ngraph.csv");

    database_manager.GetCalcKeyHitContainer().SaveToFile("templates/" + date +
                                                         "/template_hits.csv");
    database_manager.GetCalcNgraphContainer().SaveToFile(
        "templates/" + date + "/template_ngraph.csv");

    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Successfully saved the templates to files.");
}

std::vector<std::string> utils::biometric_template::SplitLine(
    const std::string& line, char delimiter) {
    std::vector<std::string> strings;
    std::string string;
    std::istringstream string_stream(line);
    while (getline(string_stream, string, delimiter)) {
        strings.push_back(string);
    }
    return strings;
}