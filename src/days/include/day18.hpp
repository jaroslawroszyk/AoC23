#pragma once
#include <functional>
#include <utility>
#include "../Puzzle.hpp"
#include "utilities.hpp"

struct Day18 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;

private:
    using Callback = std::function<std::pair<Point, int>(const std::string&)>;
    auto parse(const std::string&, Callback) -> std::vector<Point>;
    auto shoelaceFormula(const std::vector<Point>&) -> int64_t;
    auto partOne(const std::string&) -> int64_t;
    auto partTwo(const std::string&) -> int64_t;
};
