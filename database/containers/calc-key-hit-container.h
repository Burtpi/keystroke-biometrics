#ifndef CALC_KEY_HIT_CONTAINER_H_
#define CALC_KEY_HIT_CONTAINER_H_

#include <database/models/calc-key-hit.h>

#include <vector>

namespace database::containers {
class CalcKeyHitContainer {
   public:
    const std::vector<database::models::CalcKeyHit>& GetCalcKeyHits();

   private:
    std::vector<database::models::CalcKeyHit> calc_key_hits_;
};
}  // namespace database::containers

#endif