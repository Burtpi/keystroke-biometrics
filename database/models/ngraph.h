#ifndef NGRAPH_H_
#define NGRAPH_H_

#include <fstream>
#include <string>
#include <vector>

namespace database::models {
class Ngraph {
   public:
    Ngraph(std::string chars, std::vector<int> time_stamps);
    Ngraph();
    std::string GetChars() const;
    bool GetIsCalculated();
    void SetIsCalculated(bool is_calculated);
    int GetFlightTime() const;
    void SetChars(std::string chars);
    void SetFlightTime(int flight_time);
    void PushBackTimeStamp(int time_stamp);
    void SaveNgraphToCsv(std::ofstream &file) const;

   private:
    std::string chars_;
    std::vector<int> time_stamps_;
    bool is_calculated_;
    int flight_time_;
    int CalculateFlightTime();
};
}  // namespace database::models
#endif