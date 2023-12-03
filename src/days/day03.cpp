#include "include/day03.hpp"
#include "utilities.hpp"
#include <iostream>

auto Day03::part_one(const std::string& input) -> std::string
{
    auto lines = utils::lines(input);
    for(const auto& line : lines)
    {
        std::cout << line << std::endl;
    }
    return "DAY 3";
}

auto Day03::part_two(const std::string& input) -> std::string
{
    return "DAY 3";
}
