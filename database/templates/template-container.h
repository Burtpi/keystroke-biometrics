#ifndef TEMPLATE_CONTAINER_H_
#define TEMPLATE_CONTAINER_H_

#include <database/models/calc-template.h>

#include <optional>
#include <vector>

namespace database::templates {
class TemplateContainer {
    // -----------------------------------------------------------
    // Container for templates (CalcTemplate)
    // 
    // Used for easier access to variety of templates
    // -----------------------------------------------------------
   public:
    TemplateContainer();
    TemplateContainer(std::string template_name) : name_(template_name) {}
    std::vector<database::models::CalcTemplate>& GetCalcTemplate();
    std::string GetName();
    void LoadTemplates(std::string base_path);
    void LogScores();

   private:
    std::string name_;
    std::vector<database::models::CalcTemplate> calc_templates_;
    std::optional<database::containers::CalcKeyHitContainer>
    LoadAllCalcKeyHitContainers(std::string csv_file_path);
    std::optional<database::containers::CalcNgraphContainer> LoadAllCalcNGraphs(
        std::string csv_file_path);
};
}  // namespace database::templates

#endif