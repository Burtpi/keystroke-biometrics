#include <database/containers/calc-key-hit-container.h>

void database::containers::CalcKeyHitContainer::AddEntry(
    std::tuple<int, bool, bool> key_hit,
    std::vector<database::models::KeyHit> key_hit_data) {
    entries_.emplace_back(key_hit, key_hit_data);
}