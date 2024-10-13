#include <config/config-manager.h>
#include <database/containers/calc-ngraph-container.h>
#include <database/database.h>
#include <utils/biometric_template/utils-template.h>
#include <utils/time/utils-time.h>

#include <fstream>
#include <string>

void database::containers::CalcNgraphContainer::AddEntry(
    std::string ngraph, std::vector<database::models::Ngraph> ngraph_data) {
    entries_.emplace_back(ngraph, ngraph_data);
}

void database::containers::CalcNgraphContainer::SaveToFile() {
    std::string date_folder =
        global_config_manager.GetLoggerConfig().GetDateFolder();
    std::ofstream file_ngraphs(date_folder + "/template_ngraph.csv");

    file_ngraphs << "ngraph,flight_time_mean,flight_time_std_deviation\n";

    for (database::models::CalcNgraph calc_ngraph : entries_) {
        calc_ngraph.SaveCalcNgraphToCsv(file_ngraphs);
    }
    file_ngraphs.close();
}

void database::containers::CalcNgraphContainer::LoadFromFile(
    std::string csv_file_path) {
    std::ifstream csv_calc_ngraphs(csv_file_path);
    std::string line;

    std::getline(csv_calc_ngraphs, line);

    while (std::getline(csv_calc_ngraphs, line)) {
        std::vector<std::string> row =
            utils::biometric_template::SplitLine(line, ',');

        if (row.size() == 3) {
            entries_.emplace_back(row);
        }
    }
}