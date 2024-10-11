#include <database/models/ngraph.h>

database::models::Ngraph::Ngraph(std::string chars,
                                 std::vector<int> time_stamps) {
    chars_ = chars;
    time_stamps_ = time_stamps;
    flight_time_ = CalculateFlightTime();
}

int database::models::Ngraph::GetFlightTime() const { return flight_time_; }

int database::models::Ngraph::CalculateFlightTime() {
    return time_stamps_.back() - time_stamps_.front();
}