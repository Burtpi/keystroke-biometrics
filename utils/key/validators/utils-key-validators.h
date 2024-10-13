#ifndef UTILS_KEY_VALIDATORS_H_
#define UTILS_KEY_VALIDATORS_H_

#include <config/config-manager.h>
#include <database/models/key-buffer.h>
#include <database/models/key-hit.h>

#include <vector>

namespace utils::key::validators {

typedef std::vector<database::models::KeyHit>::iterator KeyHitIterator;

void CheckIfExit(database::models::KeyBuffer& key_state);
KeyHitIterator CheckIfExists(database::models::KeyBuffer key_state,
                             std::vector<database::models::KeyHit>& key_hits);
bool CheckIfBigChar();
bool CheckIfSpecialChar(int hid);
bool CheckIfModifierKey(int hid);
void CheckIfNgraph();
void CheckIfKeyIsPressed(database::models::KeyBuffer& key_state);
void CheckIfKeyWasPressed(database::models::KeyHit& key_hit);
}  // namespace utils::key::validators

#endif