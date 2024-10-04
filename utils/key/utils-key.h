#ifndef UTILS_KEY_H_
#define UTILS_KEY_H_

#include <models/key-buffer.h>

#include <algorithm>
#include <vector>

namespace utils::key {
std::vector<KeyBuffer> SortKeyStates(std::vector<KeyBuffer> key_states);
void LogKeyStates(std::vector<KeyBuffer> key_states);
}  // namespace utils::key

#endif