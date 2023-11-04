#include "days/include/day01.hpp"
#include "days/Puzzle.hpp"
#include <cassert>
#include <iostream>
#include <memory>

namespace advent
{
    auto puzzle(int day) -> std::unique_ptr<Puzzle>
    {
        assert(0 < day and day < 26);

        switch (day)
        {
        case 1: return std::make_unique<Day01>(Day01());
        default:
            std::cout << "ops";
            return nullptr;
        }
    }
} // namespace advent
