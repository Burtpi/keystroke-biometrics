#include <database/templates/template-container.h>

#include <filesystem>
#include <fstream>
#include <optional>

std::vector<database::models::CalcTemplate>&
database::templates::TemplateContainer::GetCalcTemplate() {
    return calc_templates_;
}

void database::templates::TemplateContainer::LoadTemplates() {
    std::string base_path = "templates";

    for (const std::filesystem::directory_entry& entry :
         std::filesystem::directory_iterator(base_path)) {
        if (entry.is_directory()) {
            std::string folder_name = entry.path().filename().string();
            std::string csv_template_key_hits_path =
                entry.path().string() + "/template_hits.csv";
            std::string csv_template_ngraphs_path =
                entry.path().string() + "/template_hits.csv";
            std::optional<database::containers::CalcKeyHitContainer>
                calc_key_hit_container =
                    LoadAllCalcKeyHitContainers(csv_template_key_hits_path);
            std::optional<database::containers::CalcNgraphContainer>
                calc_ngraph_container =
                    LoadAllCalcNGraphs(csv_template_ngraphs_path);
            if (calc_key_hit_container && calc_ngraph_container) {
                database::models::CalcTemplate calc_template(
                    calc_key_hit_container.value(),
                    calc_ngraph_container.value());
                calc_templates_.push_back(calc_template);
            }
        }
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