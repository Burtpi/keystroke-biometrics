#ifndef NGRAPH_CONTAINER_H_
#define NGRAPH_CONTAINER_H_

#include <database/models/ngraph.h>

#include <string>
#include <vector>

namespace database::containers {
class NgraphContainer {
   public:
    std::vector<database::models::Ngraph> GetNgraphs();
    void AddNgraph(std::string ngraph, std::vector<int>& time_stamps);

   private:
    std::vector<database::models::Ngraph> ngraphs_;
};
}  // namespace database::containers

#endif