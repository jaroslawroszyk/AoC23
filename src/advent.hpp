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
        default:
            std::cout << "ops";
            return nullptr;
    }
}
} // namespace advent
