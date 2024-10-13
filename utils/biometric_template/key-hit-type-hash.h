#ifndef KEY_HIT_TYPE_HASH_H
#define KEY_HIT_TYPE_HASH_H

#include <functional>
#include <tuple>

namespace std {
template <>
struct hash<std::tuple<int, bool, bool>> {
    std::size_t operator()(const std::tuple<int, bool, bool>& key) const {
        auto [a, b, c] = key;
        std::size_t hash1 = std::hash<int>{}(a);
        std::size_t hash2 = std::hash<bool>{}(b);
        std::size_t hash3 = std::hash<bool>{}(c);
        return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
    }
};
}  // namespace std

#endif