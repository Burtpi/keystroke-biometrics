#include <database/models/calc-ngraph.h>
#include <utils/math/utils-math.h>

database::models::CalcNgraph::CalcNgraph(std::string ngraph,
                                         std::vector<Ngraph>& ngraph_data) {
    ngraph_ = ngraph;
    Calculate(ngraph_data);
}

database::models::CalcNgraph::CalcNgraph(std::vector<std::string> row) {
    ngraph_ = row[0];
    flight_time_.mean = stod(row[1]);
    flight_time_.std_deviation = stod(row[2]);
}

void database::models::CalcNgraph::Calculate(std::vector<Ngraph>& ngraph_data) {
    std::vector<int> flight_times;

    // Store flight time data from grouped n-graphs
    for (const auto& ngraph : ngraph_data) {
        flight_times.emplace_back(ngraph.GetFlightTime());
    }

    if (!flight_times.empty()) {
        flight_time_ = utils::math::CalculateDescriptor(flight_times);
    }
}

void database::models::CalcNgraph::SaveCalcNgraphToCsv(std::ofstream& file) {
    if (flight_time_.mean > 0 && flight_time_.std_deviation > 0) {
        file << ngraph_ << "," << flight_time_.mean << ","
             << flight_time_.std_deviation << "\n";
    }
}

std::string database::models::CalcNgraph::GetNgraph() const { return ngraph_; }
database::models::Statistics database::models::CalcNgraph::GetFlightTime() {
    return flight_time_;
}