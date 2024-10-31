#ifndef UTILS_CALC_H_
#define UTILS_CALC_H_

#include <database/models/calc-template.h>

namespace utils::calc {
void CalculateCurrentObjects(std::vector<float> weights = {1, 1, 1, 1});
void CalculateKeyHit(
    database::models::KeyHit& key_hit,
    std::vector<database::models::CalcTemplate>& calc_templates,
    std::vector<float> weights);
void CalculateKeyHitTemplateScore(database::models::CalcTemplate& calc_template,
                                  database::models::KeyHit& key_hit,
                                  std::vector<float> weights);
void CalculateNgraph(
    database::models::Ngraph& ngraph,
    std::vector<database::models::CalcTemplate>& calc_templates,
    std::vector<float> weights);
void CalculateNgraphTemplateScore(database::models::CalcTemplate& calc_template,
                                  database::models::Ngraph& ngraph,
                                  std::vector<float> weights);
std::optional<double> CalculateScore(double score);
void CalculateZScores(std::vector<double> z_scores,
                      database::models::CalcTemplate& calc_template);
}  // namespace utils::calc

#endif