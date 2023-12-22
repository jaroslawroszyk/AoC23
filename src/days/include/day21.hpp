#pragma once
#include <functional>
#include <utility>
#include "../Puzzle.hpp"
#include "utilities.hpp"

struct Day21 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
