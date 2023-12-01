#include "include/day01.hpp"
#include <algorithm>
#include <concepts>
#include <fstream>
#include <iostream>
#include <list>
#include <numeric>
#include <ranges>
#include <vector>
#include "../utilities.hpp"

auto sumOfCalibrationValues(const std::string& input) -> int
{ // 54951

    auto lines = utils::lines(input);
    int sum = 0;

    for (const std::string& line : lines)
    {
        std::vector<int> digits;
        for (char c : line)
        {
            if (std::isdigit(c))
            {
                digits.push_back(c - '0');
            }
        }
        sum += digits.front() * 10 + digits.back();
    }

    return sum;
}

auto sumOfCalibrationValuesPart2(const std::string& input)->int
{
    
}

auto Day01::part_one(const std::string& input)->std::string
{
    int result = sumOfCalibrationValues(input);
    return std::to_string(result);
}

auto Day01::part_two(const std::string& input)->std::string
{
    // int result = sumOfCalibrationValuesPart2(input);
    // return std::to_string(result);
    return "foo";
}
