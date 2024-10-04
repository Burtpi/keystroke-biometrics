#ifndef KEY_HIT_CONTAINER_H_
#define KEY_HIT_CONTAINER_H_

#include <database/models/key-hit.h>

#include <vector>

namespace database::container {
struct KeyHitContainer {
    std::vector<database::models::KeyHit> key_hits;

    void AddKeyHit(database::models::KeyHit hit);
    void PushBackTimeStamp(int time_stamp);
    void PushBackPressure(float pressure);
};
}  // namespace database::container

extern database::container::KeyHitContainer key_hit_container;

#endif