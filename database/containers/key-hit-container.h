#ifndef KEY_HIT_CONTAINER_H_
#define KEY_HIT_CONTAINER_H_

#include <database/containers/container.h>
#include <database/models/key-hit.h>

#include <vector>

namespace database::containers {
class KeyHitContainer : public Container<database::models::KeyHit> {
   public:
    void AddEntry(int hid, int elapsed_time, float pressure);
    void AddModifierEntry(int hid, int elapsed_time, float pressure);
};
}  // namespace database::containers

#endif