#ifndef UTILS_CALC_H_
#define UTILS_CALC_H_

#include <database/database.h>
#include <database/models/calc-template.h>

namespace utils::calc {
void CalculateCurrentObjects(
    std::vector<float> weights = {1, 1, 1, 1},
    database::containers::MergedObjectsContainer& merged_objects_container =
        database_manager.GetMergedObjectsContainer(),
    database::templates::TemplateContainer& calc_templates_container =
        database_manager.GetTemplateContainer());
void CalculateKeyHit(
    database::models::KeyHit& key_hit,
    std::vector<database::models::CalcTemplate>& calc_templates,
    std::vector<float> weights, std::string language);
void CalculateKeyHitTemplateScore(database::models::CalcTemplate& calc_template,
                                  database::models::KeyHit& key_hit,
                                  std::vector<float> weights);
void CalculateNgraph(
    database::models::Ngraph& ngraph,
    std::vector<database::models::CalcTemplate>& calc_templates,
    std::vector<float> weights, std::string language);
void CalculateNgraphTemplateScore(database::models::CalcTemplate& calc_template,
                                  database::models::Ngraph& ngraph,
                                  std::vector<float> weights);
std::optional<double> CalculateScore(double score);
void CalculateZScores(std::vector<double> z_scores,
                      database::models::CalcTemplate& calc_template);
}  // namespace utils::calc

#endif