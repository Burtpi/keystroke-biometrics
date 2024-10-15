#ifndef UTILS_KEY_H_
#define UTILS_KEY_H_

#include <database/models/key-buffer.h>

#include <algorithm>
#include <vector>

namespace utils::key {
std::vector<database::models::KeyBuffer> SortKeyStates(
    std::vector<database::models::KeyBuffer> key_states);
void LogKeyStates(std::vector<database::models::KeyBuffer> key_states);
void CreateKeyHits(database::models::KeyBuffer &key_state);
void RemoveNotPressedHits();
void LogAllHits();
void LoadAllHits();
}  // namespace utils::key

#endif