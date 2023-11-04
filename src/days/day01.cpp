#include "../utilities.hpp"
#include "include/day01.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <ranges>
#include <concepts>
#include <list>
#include <ranges>
#include <vector>

auto sonar_sweep(const std::string& input) -> std::string
{
    auto lines = utils::lines(input);
    std::vector<int> report{};

    for (const std::string& line : lines)
    {
        int value = utils::parse<int>(line);
        report.push_back(value);
    }

    utils::print(report);

    return "sonar_sweep";
}

auto Day01::part_one(const std::string& input) -> std::string
{
    return sonar_sweep(input);
}

auto Day01::part_two(const std::string&)->std::string
{
    return "part_two";
}
