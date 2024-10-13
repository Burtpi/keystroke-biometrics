#include <database/templates/template-container.h>

#include <filesystem>
#include <fstream>

database::models::CalcTemplate&
database::templates::TemplateContainer::GetCalcTemplate() {
    return calc_template_;
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
            LoadAllCalcKeyHitContainers(csv_template_key_hits_path);
            LoadAllCalcNGraphs(csv_template_ngraphs_path);
        }
    }
}

void database::templates::TemplateContainer::LoadAllCalcKeyHitContainers(
    std::string csv_file_path) {
    if (std::filesystem::exists(csv_file_path)) {
        database::containers::CalcKeyHitContainer calc_key_hit_container;

        calc_key_hit_container.LoadFromFile(csv_file_path);
        calc_template_.calc_key_hit_containers_.push_back(
            calc_key_hit_container);
    }
}

void database::templates::TemplateContainer::LoadAllCalcNGraphs(
    std::string csv_file_path) {
    if (std::filesystem::exists(csv_file_path)) {
        database::containers::CalcNgraphContainer calc_ngraph_container;

        calc_ngraph_container.LoadFromFile(csv_file_path);
        calc_template_.calc_ngraph_containers_.push_back(calc_ngraph_container);
    }
}