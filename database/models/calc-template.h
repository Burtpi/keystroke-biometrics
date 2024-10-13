#ifndef CALC_TEMPLATE_H_
#define CALC_TEMPLATE_H_

#include <database/containers/calc-key-hit-container.h>
#include <database/containers/calc-ngraph-container.h>

#include <vector>

namespace database::models {
struct CalcTemplate {
    std::vector<database::containers::CalcKeyHitContainer>
        calc_key_hit_containers_;
    std::vector<database::containers::CalcNgraphContainer>
        calc_ngraph_containers_;
};
}  // namespace database::models

#endif
