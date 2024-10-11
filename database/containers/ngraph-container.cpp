#include <database/containers/ngraph-container.h>

void database::containers::NgraphContainer::AddEntry(
    std::string ngraph, std::vector<int>& time_stamps) {
    entries_.emplace_back(ngraph, time_stamps);
}