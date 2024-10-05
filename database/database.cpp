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
