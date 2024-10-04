#include <database/containers/key-hit-container.h>

database::container::KeyHitContainer key_hit_container;

void database::container::KeyHitContainer::AddKeyHit(
    database::models::KeyHit hit) {
    key_hits.emplace_back(hit);
}

void database::container::KeyHitContainer::PushBackTimeStamp(int time_stamp) {
    key_hits.back().PushBackTimeStamp(time_stamp);
}

void database::container::KeyHitContainer::PushBackPressure(float pressure) {
    key_hits.back().PushBackPressure(pressure);
}