#ifndef UTILS_KEY_H_
#define UTILS_KEY_H_

#include <models/key-buffer.h>
#include <vector>
#include <algorithm>

namespace utils::key
{
    std::vector<KeyBuffer> SortKeyStates(std::vector<KeyBuffer> key_states);
}

#endif