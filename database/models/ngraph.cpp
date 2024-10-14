#include <database/models/ngraph.h>

database::models::Ngraph::Ngraph(std::string chars,
                                 std::vector<int> time_stamps) {
    chars_ = chars;
    time_stamps_ = time_stamps;
    flight_time_ = CalculateFlightTime();
}

std::string database::models::Ngraph::GetChars() const { return chars_; }
int database::models::Ngraph::GetFlightTime() const { return flight_time_; }
bool database::models::Ngraph::GetIsCalculated() { return is_calculated_; }
void database::models::Ngraph::SetIsCalculated(bool is_calculated) {
    is_calculated_ = is_calculated;
}

int database::models::Ngraph::CalculateFlightTime() {
    return time_stamps_.back() - time_stamps_.front();
}