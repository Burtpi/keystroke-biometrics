#ifndef CALC_NGRAPH_H_
#define CALC_NGRAPH_H_

#include <database/models/ngraph.h>
#include <database/models/statistics.h>

#include <fstream>
#include <string>

namespace database::models {
class CalcNgraph {
    // -----------------------------------------------------------
    // Model for Ngraph templates
    // Used by CalcNgraphContainer
    //
    // Data about each n-graph's (chars) flight time is
    // stored for calculation in the identification scenario
    //
    // For flight time, the mean and standard deviation are stored
    // -----------------------------------------------------------
   public:
    CalcNgraph(std::string ngraph, std::vector<Ngraph>& ngraph_data);
    CalcNgraph(std::vector<std::string> row);
    std::string GetNgraph() const;
    database::models::Statistics GetFlightTime();
    void SaveCalcNgraphToCsv(std::ofstream& file);

   private:
    std::string ngraph_;
    database::models::Statistics flight_time_;
    void Calculate(std::vector<Ngraph>& ngraph_data);
};
}  // namespace database::models

#endif