#include "include/day11.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
#include "utilities.hpp"

auto parse11(const std::string& input) -> std::vector<std::vector<char>>
{
    std::vector<std::vector<char>> result;
    auto lines = utils::lines(input);

    std::transform(
        lines.begin(),
        lines.end(),
        std::back_inserter(result),
        [](const std::string& line) { return std::vector<char>(line.begin(), line.end()); });

    return result;
}

auto expand(const std::vector<std::vector<char>>& skymap, int64_t coefficient)
    -> std::vector<std::pair<int64_t, int64_t>>
{
    std::map<std::pair<int64_t, int64_t>, std::pair<int64_t, int64_t>> galaxyMap;

    int64_t ei = 0;
    for (int64_t i = 0; i < skymap.size(); ++i)
    {
        bool empty = true;
        for (int j = 0; j < skymap[i].size(); ++j)
        {
            if (skymap[i][j] == '#')
            {
                empty = false;
                galaxyMap[{i, j}] = {ei, j};
            }
        }
        if (empty)
        {
            ei += coefficient - 1;
        }
        ++ei;
    }

    int64_t ej = 0;
    for (int j = 0; j < skymap[0].size(); ++j)
    {
        bool empty = true;
        for (int64_t i = 0; i < skymap.size(); ++i)
        {
            if (auto it = galaxyMap.find({i, j}); it != galaxyMap.end())
            {
                empty = false;
                galaxyMap[{i, j}] = {it->second.first, ej};
            }
        }
        if (empty)
        {
            ej += coefficient - 1;
        }
        ++ej;
    }

    std::vector<std::pair<int64_t, int64_t>> galaxies;
    for (const auto& g : galaxyMap)
    {
        galaxies.emplace_back(g.second);
    }
    return galaxies;
}

auto distance(const std::vector<std::pair<int64_t, int64_t>>& galaxies) -> int64_t
{
    int64_t sum = 0;
    for (size_t i = 0; i < galaxies.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < galaxies.size(); ++j)
        {
            int64_t idist = std::abs(galaxies[i].first - galaxies[j].first);
            int64_t jdist = std::abs(galaxies[i].second - galaxies[j].second);
            sum += idist + jdist;
        }
    }
    return sum;
}

auto Day11::part_one(const std::string& input) -> std::string
{
    auto skymap = parse11(input);
    auto galaxies = expand(skymap, 2);
    auto result = distance(galaxies);
    auto expectedResult{9799681};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day11::part_two(const std::string& input) -> std::string
{
    auto skymap = parse11(input);
    auto galaxies = expand(skymap, 1000000);
    auto result = distance(galaxies);
    auto expectedResult{513171773355};
    assert(result == expectedResult);
    return std::to_string(result);
}
