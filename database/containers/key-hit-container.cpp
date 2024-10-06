#include <database/containers/key-hit-container.h>
#include <utils/key/validators/utils-key-validators.h>

std::vector<database::models::KeyHit>
database::containers::KeyHitContainer::GetKeyHits() {
    return key_hits_;
}

std::vector<database::models::KeyHit>
database::containers::KeyHitContainer::GetModifierKeys() {
    return modifier_key_hits_;
}

database::models::KeyHit
database::containers::KeyHitContainer::GetFirstKeyHit() {
    return key_hits_.front();
}

database::models::KeyHit
database::containers::KeyHitContainer::GetLastKeyHit() {
    return key_hits_.back();
}

void database::containers::KeyHitContainer::AddKeyHit(bool is_modifier, int hid,
                                                      int elapsed_time,
                                                      float pressure) {
    if (is_modifier == true) {
        modifier_key_hits_.emplace_back(hid, elapsed_time, pressure);
    } else {
        bool is_big = utils::key::validators::CheckIfBigChar();
        bool is_special = utils::key::validators::CheckIfSpecialChar(hid);
        key_hits_.emplace_back(hid, elapsed_time, pressure, is_big, is_special);
    }
}