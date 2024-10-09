#ifndef KEY_HIT_CONTAINER_H_
#define KEY_HIT_CONTAINER_H_

#include <database/models/key-hit.h>

#include <vector>

namespace database::containers {
class KeyHitContainer {
   public:
    const std::vector<database::models::KeyHit>& GetKeyHits();
    const std::vector<database::models::KeyHit>& GetModifierKeys() const;
    void AddKeyHit(bool is_modifier, int hid, int elapsed_time, float pressure);
    std::vector<database::models::KeyHit>::const_iterator RemoveKeyHit(
        std::vector<database::models::KeyHit>::const_iterator key_hit);

   private:
    std::vector<database::models::KeyHit> key_hits_;
    std::vector<database::models::KeyHit> modifier_key_hits_;
};
}  // namespace database::containers

#endif