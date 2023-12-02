#include "include/day01.hpp"
#include "utilities.hpp"
#include <algorithm>
#include <concepts>
#include <fstream>
#include <iostream>
#include <list>
#include <numeric>
#include <ranges>
#include <vector>

namespace
{
const std::unordered_map<std::string, int> valuesToNumber = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };
} // namespace

auto trebuchetPartOne(const std::string& input) -> int // correct Answer: = 54951
{
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

auto trebuchetPartTwo(const std::string& input) -> int // correct Answer = 55218
{
    auto lines = utils::lines(input);

    auto isLetter = [&valuesToNumber = valuesToNumber](const std::string& line, int index) -> int
    {
        for (const auto& [key, value] : valuesToNumber)
        {
            if (key == line.substr(index, key.size()) || line[index] - '0' == value)
            {
                return value;
            }
        }
        return -1;
    };

    int sum{0};
    for (const std::string& line : lines)
    {
        int first = -1;
        int last = -1;
        int sizeOfLine = static_cast<int>(line.size());
        for (int i = 0; i < sizeOfLine; i++)
        {
            int letterValue = isLetter(line, i);
            if (letterValue != -1)
            {
                if (first == -1) first = letterValue;
                last = letterValue;
            }
        }
        assert(first != -1);
        sum += first * 10 + last;
    }

    return sum;
}
/*
second Solution for part2
    std::vector<std::string> numbers{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for (const std::string& line : lines)
    {
        std::vector<int> digits{};
        for (int i = 0; i < static_cast<int>(line.size()); ++i)
        {
            if (std::isdigit(line[i]))
            {
                digits.push_back(line[i] - '0');
            }
            else if (std::isalpha(line[i]))
            {
                for (size_t j = 0; j < numbers.size(); ++j)
                {
                    const auto& word = numbers[j];
                    if (line.size() >= i + word.size() && line.substr(i, word.size()) == word)
                    {
                        digits.push_back(j + 1);
                        break;
                    }
                }
            }
        }

        if (not digits.empty())
        {
            sum += digits.front() * 10 + digits.back();
        }
    }
*/

auto Day01::part_one(const std::string& input) -> std::string
{
    int result = trebuchetPartOne(input);
    return std::to_string(result);
}

auto Day01::part_two(const std::string& input) -> std::string
{
    int result = trebuchetPartTwo(input);
    return std::to_string(result);
}
