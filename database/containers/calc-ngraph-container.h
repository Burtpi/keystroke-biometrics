#ifndef CALC_NGRAPH_CONTAINER_H_
#define CALC_NGRAPH_CONTAINER_H_

#include <database/containers/container.h>
#include <database/models/calc-ngraph.h>

namespace database::containers {
class CalcNgraphContainer : public Container<database::models::CalcNgraph> {
   public:
    void AddEntry(std::string ngraph,
                  std::vector<database::models::Ngraph> ngraph_data);
    void SaveToFile();
};
}  // namespace database::containers

#endif