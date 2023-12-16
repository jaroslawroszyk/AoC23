#pragma once
#include <string>
#include <vector>
#include "../Puzzle.hpp"

struct Day03 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;

private:
    auto part1(const std::string&) -> int;
    auto part2(const std::string& input) -> int;
};
