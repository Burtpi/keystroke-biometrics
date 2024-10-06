#include <database/containers/ngraph-container.h>

std::vector<database::models::Ngraph>
database::containers::NgraphContainer::GetNgraphs() {
    return ngraphs_;
}