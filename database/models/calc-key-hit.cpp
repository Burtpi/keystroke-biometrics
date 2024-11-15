#include <database/models/calc-key-hit.h>
#include <utils/math/utils-math.h>

#include <sstream>
#include <string>

database::models::CalcKeyHit::CalcKeyHit(std::tuple<int, bool, bool> key_hit,
                                         std::vector<KeyHit>& key_hit_data) {
    hid_ = std::get<0>(key_hit);
    is_special_ = std::get<1>(key_hit);
    is_big_ = std::get<2>(key_hit);
    Calculate(key_hit_data);
}

database::models::CalcKeyHit::CalcKeyHit() {}

database::models::CalcKeyHit::CalcKeyHit(std::vector<std::string> row) {
    hid_ = stoi(row[0]);
    std::istringstream(row[1]) >> is_special_;
    std::istringstream(row[2]) >> is_big_;
    dwell_time_.mean = stod(row[3]);
    dwell_time_.std_deviation = stod(row[4]);
    total_energy_.mean = stod(row[5]);
    total_energy_.std_deviation = stod(row[6]);
    magnitude_.mean = stod(row[7]);
    magnitude_.std_deviation = stod(row[8]);
}

void database::models::CalcKeyHit::Calculate(
    std::vector<KeyHit>& key_hit_data) {
    std::vector<int> dwell_times;
    std::vector<float> magnitudes;
    std::vector<double> total_energy;

    // Store all of the descriptors data from grouped key hits
    for (const auto& key_hit : key_hit_data) {
        dwell_times.emplace_back(key_hit.GetDwellTime());
        magnitudes.emplace_back(key_hit.GetMagnitude());
        total_energy.emplace_back(key_hit.GetTotalEnergy());
    }

    if (!dwell_times.empty() && !magnitudes.empty() && !total_energy.empty()) {
        dwell_time_ = utils::math::CalculateDescriptor(dwell_times);
        total_energy_ = utils::math::CalculateDescriptor(total_energy);
        magnitude_ = utils::math::CalculateDescriptor(magnitudes);
    }
}

void database::models::CalcKeyHit::SaveCalcKeyHitToCsv(std::ofstream& file) {
    if (dwell_time_.mean > 0 && dwell_time_.std_deviation > 0 &&
        total_energy_.mean > 0 && total_energy_.std_deviation > 0 &&
        magnitude_.mean > 0 && magnitude_.std_deviation > 0) {
        file << hid_ << "," << is_special_ << "," << is_big_ << ","
             << dwell_time_.mean << "," << dwell_time_.std_deviation << ","
             << total_energy_.mean << "," << total_energy_.std_deviation << ","
             << magnitude_.mean << "," << magnitude_.std_deviation << "\n";
    }
}

int database::models::CalcKeyHit::GetHid() { return hid_; }
bool database::models::CalcKeyHit::GetIsSpecial() { return is_special_; }
bool database::models::CalcKeyHit::GetIsBig() { return is_big_; }
database::models::Statistics database::models::CalcKeyHit::GetDwellTime() {
    return dwell_time_;
}
database::models::Statistics database::models::CalcKeyHit::GetTotalEnergy() {
    return total_energy_;
}
database::models::Statistics database::models::CalcKeyHit::GetMagnitude() {
    return magnitude_;
}