#pragma once
#include <cstdint>
#include <functional>

struct Pair
{
    int64_t i{};
    int64_t j{};

    friend auto operator==(const Pair& lhs, const Pair& rhs) -> bool { return lhs.i == rhs.i && lhs.j == rhs.j; }
};

namespace std
{
template <>
struct hash<Pair>
{
    std::size_t operator()(const Pair& p) const { return std::hash<int64_t>()(p.i) ^ std::hash<int64_t>()(p.j); }
};
} // namespace std
