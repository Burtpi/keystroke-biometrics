#ifndef NGRAPH_H_
#define NGRAPH_H_

#include <string>
#include <vector>

namespace database::models {
class Ngraph {
   public:
    Ngraph(std::string chars, std::vector<int> time_stamps);
    std::string GetChars() const;
    bool GetIsCalculated();
    void SetIsCalculated(bool is_calculated);
    int GetFlightTime() const;

   private:
    std::string chars_;
    std::vector<int> time_stamps_;
    bool is_calculated_;
    int flight_time_;
    int CalculateFlightTime();
};
}  // namespace database::models
#endif