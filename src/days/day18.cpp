#include "include/day18.hpp"
#include <cassert>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.hpp"

namespace
{
auto toDir(char c) -> Point
{
    switch (c)
    {
        case 'R':
        case '0':
            return {1, 0};
        case 'D':
        case '1':
            return {0, 1};
        case 'L':
        case '2':
            return {-1, 0};
        case 'U':
        case '3':
            return {0, -1};
    }
    return {0, 0};
}
} // namespace

auto Day18::parse(const std::string& input, Callback callback) -> std::vector<Point>
{
    auto lines = utils::lines(input);
    std::vector<Point> points = {{0, 0}};

    for (const auto& line : lines)
    {
        Point last = points.back();
        auto [direction, length] = callback(line);

        Point next = {last.i + direction.i * length, last.j + direction.j * length};
        points.push_back(next);
    }

    return points;
}

auto Day18::shoelaceFormula(const std::vector<Point>& set) -> int64_t
{
    auto partial = [](const Point& a, const Point& b)
    {
        int64_t triangle = a.i * b.j - b.i * a.j;
        return triangle + std::abs(b.i - a.i) + std::abs(b.j - a.j);
    };

    int64_t area{0};
    for (size_t n = 0; n < set.size() - 1; n++)
    {
        area += partial(set[n], set[n + 1]);
    }
    area += partial(set.back(), set[0]);
    return std::abs(area / 2) + 1;
}

auto Day18::partOne(const std::string& input) -> int64_t
{
    auto points = parse(
        input,
        [this](const std::string& line)
        {
            auto fields = utils::split(line, ' ');
            auto direction = fields[0][0];
            auto length = std::stoi(fields[1]);
            return std::make_pair(toDir(direction), length);
        });

    return shoelaceFormula(points);
}

auto Day18::partTwo(const std::string& input) -> int64_t
{
    auto points = parse(
        input,
        [this](const std::string& line)
        {
            auto fields = utils::split(line, ' ');
            auto color = fields[2].substr(2, fields[2].size() - 3);

            char direction = color.back();
            int length = std::stoi(color.substr(0, color.size() - 1), nullptr, 16);

            return std::make_pair(toDir(direction), length);
        });

    return shoelaceFormula(points);
}

auto Day18::part_one(const std::string& input) -> std::string
{
    auto result = partOne(input);
    auto expectedResult{49061};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day18::part_two(const std::string& input) -> std::string
{
    auto result = partTwo(input);
    auto expectedResult{92556825427032};
    assert(result == expectedResult);
    return std::to_string(result);
}
