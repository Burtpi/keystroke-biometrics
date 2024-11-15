#include <config/config-manager.h>
#include <database/containers/key-hit-container.h>
#include <utils/key/validators/utils-key-validators.h>

void database::containers::KeyHitContainer::AddEntry(int hid, int elapsed_time,
                                                     float pressure) {
    bool is_big = utils::key::validators::CheckIfBigChar();
    bool is_special = utils::key::validators::CheckIfSpecialChar(hid);
    entries_.emplace_back(hid, elapsed_time, pressure, is_big, is_special);
}

void database::containers::KeyHitContainer::AddModifierEntry(int hid,
                                                             int elapsed_time,
                                                             float pressure) {
    entries_.emplace_back(hid, elapsed_time, pressure, false, false);
}

void database::containers::KeyHitContainer::SaveToFile() {
    std::string date_folder =
        global_config_manager.GetLoggerConfig().GetDateFolder();

    std::ofstream file_key_hits(date_folder + "/key_hits.csv");

    file_key_hits << "hid,is_special_char,is_big_char,dwell_time,total_energy,"
                     "magnitude,time_stamps,pressure\n";
    for (const database::models::KeyHit& key_hit : entries_) {
        key_hit.SaveKeyHitToCsv(file_key_hits);
    }
    file_key_hits.close();
}

void database::containers::KeyHitContainer::LoadFromFile(
    std::string base_path) {
    std::ifstream csv_key_hits(base_path);

    if (csv_key_hits.is_open()) {
        std::string line;
        std::getline(csv_key_hits, line);

        while (std::getline(csv_key_hits, line)) {
            std::stringstream ss(line);
            database::models::KeyHit key_hit;
            int hid, dwell_time;
            bool is_special, is_big;
            double total_energy;
            float magnitude;

            char comma;
            ss >> hid >> comma >> is_special >> comma >> is_big >> comma >>
                dwell_time >> comma >> total_energy >> comma >> magnitude >>
                comma >> comma;

            key_hit.SetHid(hid);
            key_hit.SetIsSpecial(is_special);
            key_hit.SetIsBig(is_big);
            key_hit.SetDwellTime(dwell_time);
            key_hit.SetTotalEnergy(total_energy);
            key_hit.SetMagnitude(magnitude);

            std::string other_str;

            std::getline(ss, other_str, '}');
            std::stringstream time_stamps_ss(other_str);
            int time_stamp;

            // Load all timestamps
            while (time_stamps_ss >> time_stamp) {
                key_hit.PushBackTimeStamp(time_stamp);
                time_stamps_ss >> comma;
            }

            std::getline(ss, other_str, '}');
            std::stringstream pressures_ss(other_str);
            float pressure;
            pressures_ss >> comma >> comma;

            // Load all pressures
            while (pressures_ss >> pressure) {
                key_hit.PushBackPressure(pressure);
                pressures_ss >> comma;
            }

            key_hit.Interpolate();

            entries_.emplace_back(key_hit);
        }
        csv_key_hits.close();
    }
}