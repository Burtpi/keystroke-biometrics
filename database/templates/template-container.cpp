#include <config/config-manager.h>
#include <database/database.h>
#include <database/templates/template-container.h>
#include <utils/optimizer/utils-optimizer.h>

#include <filesystem>
#include <fstream>
#include <optional>

database::templates::TemplateContainer::TemplateContainer() {}

std::vector<database::models::CalcTemplate>&
database::templates::TemplateContainer::GetCalcTemplate() {
    return calc_templates_;
}

std::string database::templates::TemplateContainer::GetName() { return name_; }

void database::templates::TemplateContainer::LoadTemplates(
    std::string base_path) {
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Loading templates.");

    // Iterating through all directories with template files
    for (const std::filesystem::directory_entry& entry :
         std::filesystem::directory_iterator(base_path)) {
        if (entry.is_directory()) {
            std::string folder_name = entry.path().filename().string();
            std::string csv_template_key_hits_path =
                entry.path().string() + "/template_hits.csv";
            std::string csv_template_ngraphs_path =
                entry.path().string() + "/template_ngraph.csv";
            std::string language_path = entry.path().string() + "/language.txt";

            std::string language =
                utils::optimizer::LoadLanguage(language_path);
            std::optional<database::containers::CalcKeyHitContainer>
                calc_key_hit_container =
                    LoadAllCalcKeyHitContainers(csv_template_key_hits_path);
            std::optional<database::containers::CalcNgraphContainer>
                calc_ngraph_container =
                    LoadAllCalcNGraphs(csv_template_ngraphs_path);
            if (calc_key_hit_container && calc_ngraph_container) {
                database::models::CalcTemplate calc_template(
                    calc_key_hit_container.value(),
                    calc_ngraph_container.value(), language);
                calc_templates_.push_back(calc_template);
            }
        }
    }
    if (calc_templates_.size() > 0) {
        global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
            "Successfully loaded the templates.");
    } else {
        global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
            "No templates were loaded. Switching to template init mode");

        global_config_manager.GetCalcConfig().SetIsTemplateInit(true);
    }
}

std::optional<database::containers::CalcKeyHitContainer>
database::templates::TemplateContainer::LoadAllCalcKeyHitContainers(
    std::string csv_file_path) {
    if (std::filesystem::exists(csv_file_path)) {
        database::containers::CalcKeyHitContainer calc_key_hit_container;

        calc_key_hit_container.LoadFromFile(csv_file_path);
        calc_key_hit_container.GenerateCalcKeyHitHashMap();
        return calc_key_hit_container;
    } else {
        return std::nullopt;
    }
}

std::optional<database::containers::CalcNgraphContainer>
database::templates::TemplateContainer::LoadAllCalcNGraphs(
    std::string csv_file_path) {
    if (std::filesystem::exists(csv_file_path)) {
        database::containers::CalcNgraphContainer calc_ngraph_container;

        calc_ngraph_container.LoadFromFile(csv_file_path);
        return calc_ngraph_container;
    } else {
        return std::nullopt;
    }
}

void database::templates::TemplateContainer::LogScores() {
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Logging all scores.");

    std::string date_folder =
        global_config_manager.GetLoggerConfig().GetDateFolder();

    std::ofstream file_scores(date_folder + "/scores.txt");

    for (auto calc_template : calc_templates_) {
        file_scores << calc_template.score << std::endl;
    }
    file_scores.close();

    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Successfully logged all scores.");
}
