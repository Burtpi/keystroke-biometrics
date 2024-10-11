#include <database/containers/calc-key-hit-container.h>

const std::vector<database::models::CalcKeyHit>&
database::containers::CalcKeyHitContainer::GetCalcKeyHits() {
    return calc_key_hits_;
}