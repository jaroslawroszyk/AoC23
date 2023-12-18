#pragma once
#include "../Puzzle.hpp"

struct Day16 : Puzzle
{
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
/*
    // int64_t sum{0};
    // for (const auto& lens : sequence)
    // {
    //     sum += hash(lens);
    // }
*/
