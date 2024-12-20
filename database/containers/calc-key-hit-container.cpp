#include <config/config-manager.h>
#include <database/containers/calc-key-hit-container.h>
#include <database/database.h>
#include <utils/biometric_template/key-hit-type-hash.h>
#include <utils/biometric_template/utils-template.h>
#include <utils/time/utils-time.h>

#include <fstream>
#include <optional>
#include <string>

void database::containers::CalcKeyHitContainer::AddEntry(
    std::tuple<int, bool, bool> key_hit,
    std::vector<database::models::KeyHit> key_hit_data) {
    entries_.emplace_back(key_hit, key_hit_data);
}

void database::containers::CalcKeyHitContainer::SaveToFile(std::string path) {
    std::filesystem::path directory = std::filesystem::path(path).parent_path();
    std::filesystem::create_directories(directory);
    std::ofstream file_key_hits(path);

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

void database::containers::CalcKeyHitContainer::GenerateCalcKeyHitHashMap() {
    // Generate hashmap for the key (hid, is_special, is_big)
    for (database::models::CalcKeyHit& calc_key_hit : entries_) {
        std::tuple<int, bool, bool> key =
            std::make_tuple(calc_key_hit.GetHid(), calc_key_hit.GetIsSpecial(),
                            calc_key_hit.GetIsBig());
        calc_key_hit_hash_map_[key] = calc_key_hit;
    }
}

std::optional<database::models::CalcKeyHit>
database::containers::CalcKeyHitContainer::FindEntry(
    database::models::KeyHit key_hit) const {
    // Find if there is a calc template for the key (hid, is_special, is_big)
    std::tuple<int, bool, bool> key = std::make_tuple(
        key_hit.GetHid(), key_hit.GetIsSpecial(), key_hit.GetIsBig());
    auto it = calc_key_hit_hash_map_.find(key);
    if (it != calc_key_hit_hash_map_.end()) {
        return it->second;
    } else {
        return std::nullopt;
    }
}