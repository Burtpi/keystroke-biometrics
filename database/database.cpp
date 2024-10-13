#include <database/database.h>

database::DatabaseManager database_manager;

database::containers::KeyHitContainer&
database::DatabaseManager::GetKeyHitContainer() {
    return key_hit_container_;
}

database::containers::NgraphContainer&
database::DatabaseManager::GetNgraphContainer() {
    return ngraph_container_;
}

database::containers::CalcKeyHitContainer&
database::DatabaseManager::GetCalcKeyHitContainer() {
    return calc_key_hit_container_;
}
database::containers::CalcNgraphContainer&
database::DatabaseManager::GetCalcNgraphContainer() {
    return calc_ngraph_container_;
}
database::containers::KeyHitContainer&
database::DatabaseManager::GetModifierKeyHitContainer() {
    return modifier_key_hit_container_;
}
