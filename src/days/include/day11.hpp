#pragma once
#include <vector>
#include "../Puzzle.hpp"

struct Day11 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;

private:
    auto parse(const std::string&) -> std::vector<std::vector<char>>;
};
