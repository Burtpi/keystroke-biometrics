#ifndef NGRAPH_H_
#define NGRAPH_H_

#include <string>
#include <vector>

namespace database::models {
class Ngraph {
   public:
    Ngraph(std::string chars);
    void SetIsCalculated(bool is_calculated);
    void Calculate();

   private:
    std::string chars_;
    std::vector<int> time_stamps_;
    bool is_calculated_;
    int flight_time_;
    void CalculateFlightTime();
};
}  // namespace database::models
#endif