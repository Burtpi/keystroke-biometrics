#include <database/containers/key-hit-container.h>

std::vector<database::models::KeyHit>
database::containers::KeyHitContainer::GetKeyHits() {
    return key_hits_;
}

database::models::KeyHit
database::containers::KeyHitContainer::GetFirstKeyHit() {
    return key_hits_.front();
}

database::models::KeyHit
database::containers::KeyHitContainer::GetLastKeyHit() {
    return key_hits_.back();
}

void database::containers::KeyHitContainer::AddKeyHit(
    database::models::KeyHit hit) {
    key_hits_.emplace_back(hit);
}

void database::containers::KeyHitContainer::PushBackTimeStamp(int time_stamp) {
    key_hits_.back().PushBackTimeStamp(time_stamp);
}

void database::containers::KeyHitContainer::PushBackPressure(float pressure) {
    key_hits_.back().PushBackPressure(pressure);
}