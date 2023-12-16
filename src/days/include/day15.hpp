#pragma once
#include "../Puzzle.hpp"

struct Day15 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;

private:
    auto part1(const std::string& input) -> int64_t;
};
/*
    // int64_t sum{0};
    // for (const auto& lens : sequence)
    // {
    //     sum += hash(lens);
    // }
*/
