#ifndef KEY_HIT_TYPE_HASH_H
#define KEY_HIT_TYPE_HASH_H

#include <functional>
#include <tuple>

namespace std {
template <>
struct hash<std::tuple<int, bool, bool>> {
    std::size_t operator()(const std::tuple<int, bool, bool>& key) const {
        auto [a, b, c] = key;
        std::size_t h1 = std::hash<int>{}(a);
        std::size_t h2 = std::hash<bool>{}(b);
        std::size_t h3 = std::hash<bool>{}(c);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};
}  // namespace std

#endif