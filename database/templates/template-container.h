#ifndef TEMPLATE_CONTAINER_H_
#define TEMPLATE_CONTAINER_H_

#include <database/models/calc-template.h>

#include <vector>

namespace database::templates {
class TemplateContainer {
   public:
    database::models::CalcTemplate& GetCalcTemplate();
    void LoadTemplates();

   private:
    database::models::CalcTemplate calc_template_;
    void LoadAllCalcKeyHitContainers(std::string csv_file_path);
    void LoadAllCalcNGraphs(std::string csv_file_path);
};
}  // namespace database::templates

#endif