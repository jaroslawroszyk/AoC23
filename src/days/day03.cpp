#include "include/day03.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include "utilities.hpp"

namespace part1
{
auto isSpecial(const std::vector<std::string>& lines)
{
    return [lines](int64_t row, int64_t col)
    {
        if (row < 0 || col < 0) return false;
        if (row >= std::ssize(lines) || col >= std::ssize(lines[row])) return false;
        return not std::isdigit(lines[row][col]) && lines[row][col] != '.';
    };
}

auto sumSchemantic(const std::string& input) -> int
{
    std::vector<std::string> lines = utils::lines(input);

    auto isspecial = isSpecial(lines);

    int64_t sum{0};
    for (int64_t row = 0; row < std::ssize(lines); ++row)
    {
        bool lastSpecial = false;

        int64_t currentParsedNumber = 0;
        bool valid = false;

        for (int64_t col = 0; col < std::ssize(lines[row]); ++col)
        {
            bool current = isspecial(row, col) || isspecial(row - 1, col) || isspecial(row + 1, col);

            if (isdigit(lines[row][col]))
            {
                valid |= lastSpecial || current;
                currentParsedNumber *= 10;
                currentParsedNumber += lines[row][col] - '0';
            }
            else if (currentParsedNumber != 0)
            {
                valid |= current;
                if (valid)
                {
                    sum += currentParsedNumber;
                }

                currentParsedNumber = 0;
                valid = false;
            }

            lastSpecial = current;
        }
        if (currentParsedNumber != 0 && valid)
        {
            sum += currentParsedNumber;
        }
    }
    return sum;
}
} // namespace part1

auto Day03::part_one(const std::string& input) -> std::string
{
    return std::to_string(part1::sumSchemantic(input));
}

auto Day03::part_two(const std::string& input) -> std::string
{
    return "part_two";
}
