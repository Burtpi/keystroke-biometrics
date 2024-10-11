#ifndef NGRAPH_CONTAINER_H_
#define NGRAPH_CONTAINER_H_

#include <database/containers/container.h>
#include <database/models/ngraph.h>

#include <string>
#include <vector>

namespace database::containers {
class NgraphContainer : public Container<database::models::Ngraph> {
   public:
    void AddEntry(std::string ngraph, std::vector<int>& time_stamps);
};
}  // namespace database::containers

#endif