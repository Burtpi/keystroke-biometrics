#include <database/models/calc-key-hit.h>
#include <utils/math/utils-math.h>

database::models::CalcKeyHit::CalcKeyHit(std::tuple<int, bool, bool> key_hit,
                                         std::vector<KeyHit>& key_hit_data) {
    hid_ = std::get<0>(key_hit);
    is_special_ = std::get<1>(key_hit);
    is_big_ = std::get<2>(key_hit);
    Calculate(key_hit_data);
}

void database::models::CalcKeyHit::Calculate(
    std::vector<KeyHit>& key_hit_data) {
    std::vector<int> dwell_times;
    std::vector<float> magnitudes;
    std::vector<double> total_energy;
    for (const auto& key_hit : key_hit_data) {
        dwell_times.emplace_back(key_hit.GetDwellTime());
        magnitudes.emplace_back(key_hit.GetMagnitude());
        total_energy.emplace_back(key_hit.GetTotalEnergy());
    }

    if (dwell_times.size() > 0 && magnitudes.size() > 0 &&
        total_energy.size() > 0) {
        dwell_time_ = utils::math::CalculateDescriptor(dwell_times);
        total_energy_ = utils::math::CalculateDescriptor(total_energy);
        magnitude_ = utils::math::CalculateDescriptor(magnitudes);
    }
}