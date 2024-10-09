#include <database/containers/key-hit-container.h>
#include <utils/key/validators/utils-key-validators.h>

const std::vector<database::models::KeyHit>&
database::containers::KeyHitContainer::GetKeyHits() {
    return key_hits_;
}

const std::vector<database::models::KeyHit>&
database::containers::KeyHitContainer::GetModifierKeys() const {
    return modifier_key_hits_;
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

std::vector<database::models::KeyHit>::const_iterator
database::containers::KeyHitContainer::RemoveKeyHit(
    std::vector<database::models::KeyHit>::const_iterator key_hit) {
    return utils::key::validators::CheckIfModifierKey(key_hit->GetHid())
               ? modifier_key_hits_.erase(key_hit)
               : key_hits_.erase(key_hit);
}