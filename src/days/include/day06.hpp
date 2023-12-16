#pragma once
#include "../Puzzle.hpp"

struct Day06 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;

private:
    auto partOne(const std::string&) -> int64_t;
    auto partTwo(const std::string&) -> int64_t;
};
