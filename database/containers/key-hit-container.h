#ifndef KEY_HIT_CONTAINER_H_
#define KEY_HIT_CONTAINER_H_

#include <database/models/key-hit.h>

#include <vector>

namespace database::containers {
class KeyHitContainer {
   public:
    std::vector<database::models::KeyHit> GetKeyHits();
    database::models::KeyHit GetFirstKeyHit();
    database::models::KeyHit GetLastKeyHit();
    void AddKeyHit(database::models::KeyHit hit);
    void PushBackTimeStamp(int time_stamp);
    void PushBackPressure(float pressure);

   private:
    std::vector<database::models::KeyHit> key_hits_;
};
}  // namespace database::containers

#endif