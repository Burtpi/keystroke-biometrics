#ifndef CALC_NGRAPH_CONTAINER_H_
#define CALC_NGRAPH_CONTAINER_H_

#include <database/containers/container.h>
#include <database/models/calc-ngraph.h>
#include <database/models/ngraph.h>

#include <optional>
#include <vector>

namespace database::containers {
class CalcNgraphContainer : public Container<database::models::CalcNgraph> {
   public:
    void AddEntry(std::string ngraph,
                  std::vector<database::models::Ngraph> ngraph_data);
    void SaveToFile(std::string path);
    void LoadFromFile(std::string csv_file_path);
    std::optional<database::models::CalcNgraph> FindEntry(
        database::models::Ngraph ngraph) const;
};
}  // namespace database::containers

#endif