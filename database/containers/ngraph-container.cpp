#include <database/containers/ngraph-container.h>

std::vector<database::models::Ngraph>
database::containers::NgraphContainer::GetNgraphs() {
    return ngraphs_;
}

void database::containers::NgraphContainer::AddNgraph(
    std::string ngraph, std::vector<int>& time_stamps) {
    ngraphs_.emplace_back(ngraph, time_stamps);
}