#ifndef CALC_NGRAPH_H_
#define CALC_NGRAPH_H_

#include <database/models/ngraph.h>
#include <database/models/statistics.h>

#include <fstream>
#include <string>

namespace database::models {
class CalcNgraph {
   public:
    CalcNgraph(std::string ngraph, std::vector<Ngraph>& ngraph_data);
    void SaveCalcNgraphToCsv(std::ofstream& file);

   private:
    std::string ngraph_;
    database::models::Statistics flight_time_;
    void Calculate(std::vector<Ngraph>& ngraph_data);
};
}  // namespace database::models

#endif