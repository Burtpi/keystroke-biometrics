#ifndef CALC_KEY_HIT_CONTAINER_H_
#define CALC_KEY_HIT_CONTAINER_H_

#include <database/containers/container.h>
#include <database/models/calc-key-hit.h>

#include <vector>

namespace database::containers {
class CalcKeyHitContainer : public Container<database::models::CalcKeyHit> {};
}  // namespace database::containers

#endif