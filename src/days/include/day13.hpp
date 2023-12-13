#pragma once
#include "../Puzzle.hpp"

struct MyPair
{
    int64_t i;
    int64_t j;
};

namespace std
{
template <>
struct hash<MyPair>
{
    std::size_t operator()(const MyPair& p) const { return std::hash<int64_t>()(p.i) ^ std::hash<int64_t>()(p.j); }
};
} // namespace std

struct Day13 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;

private:
    using MyPairMapVector = std::vector<std::unordered_map<MyPair, bool>>;
    using MyPairVector = std::vector<MyPair>;

    auto parse(const std::string&) -> std::pair<MyPairMapVector, MyPairVector>;
    auto pointOfIncidence(const std::unordered_map<MyPair, bool>&, const MyPair&, bool smudge)
        -> std::pair<int64_t, int64_t>;
    auto reflect(const MyPair&, double, double) -> MyPair;

    auto symmetry(const MyPair&, const MyPair&) -> std::pair<double, double>;
    auto partOne(const std::string&) -> int64_t;
    auto partTwo(const std::string& input) -> int64_t;
};
