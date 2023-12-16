#pragma once
#include "../Puzzle.hpp"
struct Card
{
    int id;
    std::vector<int> winningNumbers;
    std::vector<int> numbersOnCard;
    std::size_t copies;
};

struct Day04 : Puzzle
{
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
