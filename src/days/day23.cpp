#include "include/day23.hpp"
#include <cassert>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include "utilities.hpp"

/*
paths (.)
forest (#)
steep slopes (^, >, v, and <).
*/

auto Day23::exploreGraph(const ExploreFunction& try_explore, Coord exit) -> int64_t
{
    int64_t max{0};
    while (not dfs.empty())
    {
        auto& [coord, distance, state] = dfs.back();
        if (coord == exit)
        {
            max = std::max(max, distance);
            dfs.pop_back();
            visited.erase(coord);
        }
        switch (state)
        {
            case 0: // Exploration Initialization
                ++state;
                try_explore({coord.row - 1, coord.col}, distance + 1);
                break;
            case 1: //  Upward Node Exploration
                ++state;
                try_explore({coord.row + 1, coord.col}, distance + 1);
                break;
            case 2: // Downward Node Exploration
                ++state;
                try_explore({coord.row, coord.col + 1}, distance + 1);
                break;
            case 3: // Exploring the Right Node
                ++state;
                try_explore({coord.row, coord.col - 1}, distance + 1);
                break;
            case 4: // Explore Node Left
                dfs.pop_back();
                visited.erase(coord);
                break;
        }
    }

    return max;
}

auto Day23::maxPath(std::vector<std::string> map, Coord start, Coord exit) -> int64_t
{
    ExploreFunction try_explore = [&](Coord coord, int64_t distance)
    {
        if (coord.row < 0 || coord.row >= std::ssize(map) || coord.col < 0 || coord.col >= std::ssize(map[coord.row]) ||
            map[coord.row][coord.col] == '#')
        {
            return;
        }

        if (map[coord.row][coord.col] == '>')
        {
            try_explore({coord.row, coord.col + 1}, distance + 1);
            return;
        }
        if (map[coord.row][coord.col] == '<')
        {
            try_explore({coord.row, coord.col - 1}, distance + 1);
            return;
        }
        if (map[coord.row][coord.col] == 'v')
        {
            try_explore({coord.row + 1, coord.col}, distance + 1);
            return;
        }
        if (map[coord.row][coord.col] == '^')
        {
            try_explore({coord.row - 1, coord.col}, distance + 1);
            return;
        }
        if (visited.contains(coord)) return;
        dfs.push_back({coord, distance, 0});
        visited.insert(coord);
    };

    try_explore(start, 0);

    return exploreGraph(try_explore, exit);
}

auto Day23::longestRoute(const std::string& input) -> int64_t
{
    auto lines = utils::lines(input);
    std::vector<std::string> grid(lines.begin(), lines.end());

    Coord start = {0, 1};
    Coord exit = {std::ssize(grid) - 1, std::ssize(grid[0]) - 2};
    return maxPath(grid, start, exit);
}

auto Day23::part_one(const std::string& line) -> std::string
{
    auto result = longestRoute(line);
    auto expectedResult{2354};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day23::part_two(const std::string&) -> std::string
{
    return "part_two";
}
