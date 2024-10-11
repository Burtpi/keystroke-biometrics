#ifndef UTILS_TEMPLATE_
#define UTILS_TEMPLATE_

#include <database/models/key-hit.h>
#include <database/models/ngraph.h>

namespace utils::biometric_template {
using KeyHitType = std::tuple<int, bool, bool>;
using GroupedKeyHits =
    std::unordered_map<KeyHitType, std::vector<database::models::KeyHit>>;
using GroupedNgraphs =
    std::unordered_map<std::string, std::vector<database::models::Ngraph>>;

void CreateTemplate();
void ProcessKeyHits();
void ProcessNgraphs();
GroupedKeyHits GroupKeyHits();
GroupedNgraphs GroupNgraphs();
}  // namespace utils::biometric_template

#endif