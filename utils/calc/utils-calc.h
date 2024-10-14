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
double CalculateScore(double score);
}  // namespace utils::calc

#endif