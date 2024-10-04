#ifndef UTILS_KEY_VALIDATORS_H_
#define UTILS_KEY_VALIDATORS_H_

#include <vector>
#include <models/key-buffer.h>
#include <config/config-manager.h>

namespace utils::key::validators
{
    void CheckIfExit(std::vector<KeyBuffer> key_states);
}

#endif