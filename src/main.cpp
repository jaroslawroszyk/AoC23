#include <iostream>

#include "advent.hpp"
#include "args.hpp"
#include "dataset.hpp"
#include "days/Puzzle.hpp"

auto main(int argc, char** argv) -> int
{
    auto [day, example] = args::parse(argc, argv);
    auto input = dataset::input(day, example);
    auto puzzle = advent::puzzle(day);

    std::cout << "Advent of Code 2023 - Day " << day << "\n";
    auto [part_one, part_two] = puzzle->solve(input);
    std::cout << "Part One: " << part_one << std::endl;
    std::cout << "Part Two: " << part_two << std::endl;

    return 0;
}
