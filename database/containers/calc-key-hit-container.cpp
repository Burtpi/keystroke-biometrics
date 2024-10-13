#include <config/config-manager.h>
#include <database/containers/calc-key-hit-container.h>
#include <database/database.h>
#include <utils/biometric_template/utils-template.h>
#include <utils/time/utils-time.h>

#include <fstream>
#include <string>

void database::containers::CalcKeyHitContainer::AddEntry(
    std::tuple<int, bool, bool> key_hit,
    std::vector<database::models::KeyHit> key_hit_data) {
    entries_.emplace_back(key_hit, key_hit_data);
}

void database::containers::CalcKeyHitContainer::SaveToFile() {
    std::string date_folder =
        global_config_manager.GetLoggerConfig().GetDateFolder();

    std::ofstream file_key_hits(date_folder + "/template_hits.csv");

    file_key_hits << "hid,is_special,is_big,dwell_time_mean,dwell_time_std_"
                     "deviation,total_energy_mean,total_energy_std_deviation,"
                     "magnitude_mean,magnitude_std_deviation\n";
    for (database::models::CalcKeyHit calc_key_hit : entries_) {
        calc_key_hit.SaveCalcKeyHitToCsv(file_key_hits);
    }
    file_key_hits.close();
}

void database::containers::CalcKeyHitContainer::LoadFromFile(
    std::string csv_file_path) {
    std::ifstream csv_calc_key_hits(csv_file_path);
    std::string line;

    std::getline(csv_calc_key_hits, line);

    while (std::getline(csv_calc_key_hits, line)) {
        std::vector<std::string> row =
            utils::biometric_template::SplitLine(line, ',');

        if (row.size() == 9) {
            entries_.emplace_back(row);
        }
    }
}