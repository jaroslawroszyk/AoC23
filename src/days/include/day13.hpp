#pragma once

#include <unordered_map>
#include <vector>
#include "../Puzzle.hpp"
#include "Pair.hpp"

struct Day13 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;

private:
    using PairMapVector = std::vector<std::unordered_map<Pair, bool>>;
    using PairVector = std::vector<Pair>;

    auto parse(const std::string&) -> std::pair<PairMapVector, PairVector>;
    auto pointOfIncidence(const std::unordered_map<Pair, bool>&, const Pair&, bool smudge)
        -> std::pair<int64_t, int64_t>;
    auto reflect(const Pair&, double, double) -> Pair;

    auto symmetry(const Pair&, const Pair&) -> std::pair<double, double>;
    auto partOne(const std::string&) -> int64_t;
    auto partTwo(const std::string& input) -> int64_t;
};
