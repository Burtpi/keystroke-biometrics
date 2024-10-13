#include <database/templates/template-container.h>

const std::vector<database::containers::CalcKeyHitContainer>&
database::templates::TemplateContainer::GetCalcKeyHitContainer() {
    return calc_key_hit_containers_;
}

const std::vector<database::containers::CalcNgraphContainer>&
database::templates::TemplateContainer::GetNgraphContainer() {
    return calc_ngraph_containers_;
}