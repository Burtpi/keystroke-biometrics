#include <config/config-manager.h>
#include <database/containers/key-hit-container.h>
#include <database/containers/merged-objects-container.h>
#include <database/containers/ngraph-container.h>
#include <utils/optimizer/utils-optimizer.h>

#include <filesystem>
std::vector<database::templates::TemplateContainer>
utils::optimizer::LoadTemplatesWithNames() {
    std::string base_path = "optimizer/templates";
    std::vector<database::templates::TemplateContainer> template_containers;

    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Loading templates with names.");

    for (const std::filesystem::directory_entry& entry :
         std::filesystem::directory_iterator(base_path)) {
        if (entry.is_directory()) {
            std::string folder_name = entry.path().filename().string();
            database::templates::TemplateContainer template_container(
                folder_name);
            template_container.LoadTemplates(entry.path().string());
            template_containers.emplace_back(template_container);
        }
    }
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Successfully loaded the templates with names.");

    return template_containers;
}

std::vector<database::containers::MergedObjectsContainer>
utils::optimizer::LoadAllOptimizationData() {
    std::string base_path = "optimizer/data";
    std::vector<database::containers::MergedObjectsContainer>
        merged_objects_containers;

    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Loading optimization data.");

    for (const std::filesystem::directory_entry& entry :
         std::filesystem::directory_iterator(base_path)) {
        if (entry.is_directory()) {
            std::string folder_name = entry.path().filename().string();
            for (const std::filesystem::directory_entry& entry_sub :
                 std::filesystem::directory_iterator(base_path + "/" +
                                                     folder_name)) {
                if (entry_sub.is_directory()) {
                    merged_objects_containers.emplace_back(
                        LoadAllOptimizationMergedData(entry_sub.path().string(),
                                                      folder_name));
                }
            }
        }
    }
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Successfully loaded the optimizatin data.");

    return merged_objects_containers;
}

database::containers::MergedObjectsContainer
utils::optimizer::LoadAllOptimizationMergedData(std::string base_path,
                                                std::string name) {
    database::containers::KeyHitContainer key_hit_container;
    key_hit_container.LoadFromFile(base_path + "/key_hits.csv");
    database::containers::NgraphContainer ngraph_container;
    ngraph_container.LoadFromFile(base_path + "/ngraphs.csv");
    std::string language = LoadLanguage(base_path + "/language.txt");
    database::containers::MergedObjectsContainer merged_objects_container(
        name, language);
    merged_objects_container.SetMergedObjects(key_hit_container.GetEntries(),
                                              ngraph_container.GetEntries());
    return merged_objects_container;
}

std::string utils::optimizer::LoadLanguage(std::string txt_file_path) {
    if (std::filesystem::exists(txt_file_path)) {
        std::ifstream language_file(txt_file_path);
        std::string line;

        std::getline(language_file, line);

        return line;
    } else {
        return global_config_manager.GetLanguageConfig().GetModelLanguage();
    }
}

void utils::optimizer::SaveLanguage() {
    std::string path = global_config_manager.GetLoggerConfig().GetDateFolder();
    std::ofstream language_file(path + "/language.txt");

    language_file
        << global_config_manager.GetLanguageConfig().GetModelLanguage();
    language_file.close();
}
