#include <database/containers/calc-ngraph-container.h>

void database::containers::CalcNgraphContainer::AddEntry(
    std::string ngraph, std::vector<database::models::Ngraph> ngraph_data) {
    entries_.emplace_back(ngraph, ngraph_data);
}