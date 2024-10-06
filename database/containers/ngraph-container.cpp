#include <database/containers/ngraph-container.h>

std::vector<database::models::Ngraph>
database::containers::NgraphContainer::GetNgraphs() const {
    return ngraphs_;
}