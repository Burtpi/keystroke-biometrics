#include <config/config-manager.h>
#include <database/containers/ngraph-container.h>

void database::containers::NgraphContainer::AddEntry(
    std::string ngraph, std::vector<int>& time_stamps) {
    entries_.emplace_back(ngraph, time_stamps);
}

void database::containers::NgraphContainer::SaveToFile() {
    std::string date_folder =
        global_config_manager.GetLoggerConfig().GetDateFolder();

    std::ofstream file_ngraphs(date_folder + "/ngraphs.csv");

    file_ngraphs << "chars,flight_time,time_stamps\n";
    for (const database::models::Ngraph& ngraph : entries_) {
        ngraph.SaveNgraphToCsv(file_ngraphs);
    }
    file_ngraphs.close();
}

void database::containers::NgraphContainer::LoadFromFile(
    std::string base_path) {
    std::ifstream csv_ngraphs(base_path);

    if (csv_ngraphs.is_open()) {
        std::string line;
        std::getline(csv_ngraphs, line);

        while (std::getline(csv_ngraphs, line)) {
            std::stringstream ss(line);
            database::models::Ngraph ngraph;
            std::string chars;
            int flight_time;

            char comma;
            std::getline(ss, chars, ',');
            ss >> flight_time >> comma >> comma;

            ngraph.SetChars(chars);
            ngraph.SetFlightTime(flight_time);

            std::string other_str;

            std::getline(ss, other_str, '}');
            std::stringstream time_stamps_ss(other_str);
            std::string time_stamp;

            // Read all timestamps
            while (time_stamps_ss >> time_stamp) {
                ngraph.PushBackTimeStamp(stoi(time_stamp));
                time_stamps_ss >> comma;
            }

            entries_.push_back(ngraph);
        }

        csv_ngraphs.close();
    }
}