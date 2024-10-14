
#ifndef KEY_HIT_TYPE_HASH_H
#define KEY_HIT_TYPE_HASH_H

#include <functional>
#include <tuple>

namespace utils::biometric_template {
struct TupleHash {
    std::size_t operator()(const std::tuple<int, bool, bool>& key) const {
        auto [a, b, c] = key;
        std::size_t hash1 = std::hash<int>{}(a);
        std::size_t hash2 = std::hash<bool>{}(b);
        std::size_t hash3 = std::hash<bool>{}(c);
        return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
    }
};

struct TupleEqual {
    bool operator()(const std::tuple<int, bool, bool>& left_hash,
                    const std::tuple<int, bool, bool>& right_hash) const {
        return left_hash == right_hash;
    }
};
}  // namespace utils::biometric_template

#endif