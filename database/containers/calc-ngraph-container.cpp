#include <config/config-manager.h>
#include <database/containers/calc-ngraph-container.h>
#include <database/database.h>
#include <utils/time/utils-time.h>

void database::containers::CalcNgraphContainer::AddEntry(
    std::string ngraph, std::vector<database::models::Ngraph> ngraph_data) {
    entries_.emplace_back(ngraph, ngraph_data);
}

void database::containers::CalcNgraphContainer::SaveToFile() {
    std::chrono::time_point<std::chrono::system_clock> date =
        global_config_manager.GetAppConfig().GetStartDate();
    std::string dateFolder = "logs/" + utils::time::GetDateInString(date);
    std::ofstream file_ngraphs(dateFolder + "/template_ngraph.csv");

    file_ngraphs << "ngraph,flight_time_mean,flight_time_std_deviation\n";

    for (database::models::CalcNgraph calc_ngraph : entries_) {
        calc_ngraph.SaveCalcNgraphToCsv(file_ngraphs);
    }
    file_ngraphs.close();
}