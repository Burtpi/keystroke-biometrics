#include <database/models/calc-ngraph.h>
#include <utils/math/utils-math.h>

database::models::CalcNgraph::CalcNgraph(std::string ngraph,
                                         std::vector<Ngraph>& ngraph_data) {
    ngraph_ = ngraph;
    Calculate(ngraph_data);
}

void database::models::CalcNgraph::Calculate(std::vector<Ngraph>& ngraph_data) {
    std::vector<int> flight_times;
    for (const auto& ngraph : ngraph_data) {
        flight_times.emplace_back(ngraph.GetFlightTime());
    }

    if (!flight_times.empty()) {
        flight_time_ = utils::math::CalculateDescriptor(flight_times);
    }
}

void database::models::CalcNgraph::SaveCalcNgraphToCsv(std::ofstream& file) {
    file << ngraph_ << "," << flight_time_.mean << ","
         << flight_time_.std_deviation << "\n";
}