#ifndef CALC_TEMPLATE_H_
#define CALC_TEMPLATE_H_

#include <database/containers/calc-key-hit-container.h>
#include <database/containers/calc-ngraph-container.h>

#include <string>
#include <vector>

namespace database::models {
struct CalcTemplate {
    CalcTemplate(database::containers::CalcKeyHitContainer calc_key_hit,
                 database::containers::CalcNgraphContainer calc_ngraph,
                 std::string language)
        : calc_key_hit_container(calc_key_hit),
          calc_ngraph_container(calc_ngraph),
          score(100),
          language(language) {};
    database::containers::CalcKeyHitContainer calc_key_hit_container;
    database::containers::CalcNgraphContainer calc_ngraph_container;
    std::string language;
    double score;
};
}  // namespace database::models

#endif
