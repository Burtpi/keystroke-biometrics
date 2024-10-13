#ifndef TEMPLATE_CONTAINER_H_
#define TEMPLATE_CONTAINER_H_

#include <database/containers/calc-key-hit-container.h>
#include <database/containers/calc-ngraph-container.h>

#include <vector>

namespace database::templates {
class TemplateContainer {
   public:
    const std::vector<database::containers::CalcKeyHitContainer>&
    GetCalcKeyHitContainer();
    const std::vector<database::containers::CalcNgraphContainer>&
    GetNgraphContainer();

   private:
    std::vector<database::containers::CalcKeyHitContainer>
        calc_key_hit_containers_;
    std::vector<database::containers::CalcNgraphContainer>
        calc_ngraph_containers_;
};
}  // namespace database::templates

#endif