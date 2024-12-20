#include <database/models/ngraph.h>

database::models::Ngraph::Ngraph(std::string chars,
                                 std::vector<int> time_stamps) {
    chars_ = chars;
    time_stamps_ = time_stamps;
    is_calculated_ = false;
    flight_time_ = CalculateFlightTime();
}

database::models::Ngraph::Ngraph() { is_calculated_ = false; }

std::string database::models::Ngraph::GetChars() const { return chars_; }

int database::models::Ngraph::GetFlightTime() const { return flight_time_; }

bool database::models::Ngraph::GetIsCalculated() { return is_calculated_; }

void database::models::Ngraph::SetIsCalculated(bool is_calculated) {
    is_calculated_ = is_calculated;
}
int database::models::Ngraph::GetTimeStamp() const {
    return time_stamps_.back();
}
int database::models::Ngraph::CalculateFlightTime() {
    return time_stamps_.back() - time_stamps_.front();
}

void database::models::Ngraph::SaveNgraphToCsv(std::ofstream &file) const {
    if (flight_time_ > 0 && flight_time_ <= 1000) {
        file << chars_ << "," << flight_time_ << ",{";
        bool first_iter = true;
        for (const int &time_stamp : time_stamps_) {
            if (!first_iter) {
                file << ",";
            }
            file << time_stamp;
            first_iter = false;
        }
        file << "}\n";
    }
}

void database::models::Ngraph::SetChars(std::string chars) { chars_ = chars; }

void database::models::Ngraph::SetFlightTime(int flight_time) {
    flight_time_ = flight_time;
}

void database::models::Ngraph::PushBackTimeStamp(int time_stamp) {
    time_stamps_.emplace_back(time_stamp);
}