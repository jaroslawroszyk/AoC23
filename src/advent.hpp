#include <cassert>
#include <iostream>
#include <memory>

#include "days/Puzzle.hpp"
#include "inc/days.inc"

namespace advent
{
auto puzzle(int day) -> std::unique_ptr<Puzzle>
{
    assert(0 < day and day < 26);

    switch (day)
    {
        case 1:
            return std::make_unique<Day01>(Day01());
        case 2:
            return std::make_unique<Day02>(Day02());
        case 3:
            return std::make_unique<Day03>(Day03());
        case 4:
            return std::make_unique<Day04>(Day04());
        case 5:
            return std::make_unique<Day05>(Day05());
        case 6:
            return std::make_unique<Day06>(Day06());
        case 7:
            return std::make_unique<Day07>(Day07());
        case 8:
            return std::make_unique<Day08>(Day08());
        case 9:
            return std::make_unique<Day09>(Day09());
        case 10:
            return std::make_unique<Day10>(Day10());
        case 11:
            return std::make_unique<Day11>(Day11());
        case 13:
            return std::make_unique<Day13>(Day13());
        case 14:
            return std::make_unique<Day14>(Day14());
        case 15:
            return std::make_unique<Day15>(Day15());
        case 16:
            return std::make_unique<Day16>(Day16());
        case 18:
            return std::make_unique<Day18>(Day18());
        case 21:
            return std::make_unique<Day21>(Day21());
        // case 22:
        //     return std::make_unique<Day22>(Day22());
        case 23:
            return std::make_unique<Day23>(Day23());
        default:
            std::cout << "ops";
            return nullptr;
    }
}
} // namespace advent
