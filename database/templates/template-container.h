#ifndef TEMPLATE_CONTAINER_H_
#define TEMPLATE_CONTAINER_H_

#include <database/models/calc-template.h>

#include <vector>

namespace database::templates {
class TemplateContainer {
   public:
    std::vector<database::models::CalcTemplate>& GetCalcTemplate();
    void LoadTemplates();

   private:
    std::vector<database::models::CalcTemplate> calc_templates_;
    database::containers::CalcKeyHitContainer LoadAllCalcKeyHitContainers(
        std::string csv_file_path);
    database::containers::CalcNgraphContainer LoadAllCalcNGraphs(
        std::string csv_file_path);
};
}  // namespace database::templates

#endif