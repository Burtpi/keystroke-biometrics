#ifndef UTILS_CALC_H_
#define UTILS_CALC_H_

namespace utils::calc {
void CalculateCurrentObjects();
void CalculateKeyHits(std::vector<database::models::KeyHit>& key_hits);
void CalculateKeyHit(
    database::models::KeyHit& key_hit,
    std::vector<database::models::CalcTemplate>& calc_templates);
void CalculateKeyHitTemplateScore(database::models::CalcTemplate& calc_template,
                                  database::models::KeyHit& key_hit);

void CalculateNgraphs();
void CalculateNgraph(
    database::models::Ngraph& ngraph,
    std::vector<database::models::CalcTemplate>& calc_templates);
void CalculateNgraphTemplateScore(database::models::CalcTemplate& calc_template,
                                  database::models::Ngraph& ngraph);
double CalculateScore(double score);
void CalculateZScores(std::vector<double> z_scores,
                      database::models::CalcTemplate& calc_template);
}  // namespace utils::calc

#endif