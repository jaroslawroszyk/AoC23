#include "include/day21.hpp"
#include <cassert>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include "Point.hpp"

namespace
{
std::vector<Point> orthogonal()
{
    return {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
}

std::vector<std::vector<char>> elements(const std::string& input)
{
    std::vector<std::vector<char>> result{};
    std::istringstream iss(input);
    std::string line{};

    while (std::getline(iss, line))
    {
        std::vector<char> element(line.begin(), line.end());
        result.push_back(element);
    }

    return result;
}
struct PointHash
{
    std::size_t operator()(const Point& p) const { return std::hash<int>()(p.x) ^ std::hash<int>()(p.y); }
};

Point translate(const Point& pos, const Point& bounds)
{
    Point alt = pos;
    if (alt.x < 0)
    {
        alt.x = bounds.x + alt.x % bounds.x;
    }
    if (alt.x > bounds.x - 1)
    {
        alt.x = alt.x % bounds.x;
    }
    if (alt.y < 0)
    {
        alt.y = bounds.y + alt.y % bounds.y;
    }
    if (alt.y > bounds.y - 1)
    {
        alt.y = alt.y % bounds.y;
    }
    return alt;
}
} // namespace

auto walk(const std::vector<std::vector<char>>& garden, int steps) -> int64_t
{
    Point bounds = {static_cast<int>(garden.size()), static_cast<int>(garden[0].size())};
    Point start = bounds.div(2);

    std::unordered_set<Point, PointHash> plots{{start}};
    for (int s = 0; s < steps; s++)
    {
        std::unordered_set<Point, PointHash> newPlots;
        for (const auto& pos : plots)
        {
            for (const auto& dir : orthogonal())
            {
                Point next = pos.add(dir);
                Point alt = translate(next, bounds);
                if (garden[alt.y][alt.x] != '#')
                {
                    newPlots.insert(next);
                }
            }
        }
        plots = newPlots;
    }
    return plots.size();
}

auto Day21::part_one(const std::string& line) -> std::string
{
    auto garden = elements(line);
    int64_t result = walk(garden, 64);
    auto expectedResult{3542};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day21::part_two(const std::string&) -> std::string
{
    return "part two";
}
