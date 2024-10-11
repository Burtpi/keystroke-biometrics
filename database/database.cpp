#include <database/database.h>

database::DatabaseManager database_manager;

database::containers::KeyHitContainer
database::DatabaseManager::GetKeyHitContainer() const {
    return key_hit_container_;
}

database::containers::NgraphContainer
database::DatabaseManager::GetNgraphContainer() const {
    return ngraph_container_;
}

database::containers::CalcKeyHitContainer
database::DatabaseManager::GetCalcKeyHitContainer() const {
    return calc_key_hit_container_;
}
database::containers::CalcNgraphContainer
database::DatabaseManager::GetCalcNgraphContainer() const {
    return calc_ngraph_container_;
}
database::containers::KeyHitContainer
database::DatabaseManager::GetModifierKeyHitContainer() const {
    return modifier_key_hit_container_;
}
