#ifndef UTILS_KEY_VALIDATORS_H_
#define UTILS_KEY_VALIDATORS_H_

#include <config/config-manager.h>
#include <database/models/key-buffer.h>

#include <vector>

namespace utils::key::validators {
void CheckIfExit(std::vector<database::models::KeyBuffer> key_states);
}

#endif