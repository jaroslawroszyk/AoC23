#include "include/day06.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <regex>
#include <string>
#include <vector>
#include "utilities.hpp"

namespace parser
{
auto parseInputFirstPart(const std::string& input)
{
    auto lines = utils::lines(input);
    std::string pattern = "\\d+";
    auto time = utils::findPattern(pattern, lines[0]);
    auto distance = utils::findPattern(pattern, lines[1]);

    std::vector<std::pair<int, int>> raceData;
    for (size_t i = 0; i < time.size(); ++i)
    {
        raceData.emplace_back(utils::parse<int>(time[i]), utils::parse<int>(distance[i]));
    }
    return raceData;
}

auto parseInputSecondPart(const std::string& input)
{
    auto lines = utils::lines(input);

    auto timeCombined = std::regex_replace(lines[0], std::regex("\\D+"), "");
    auto distCombined = std::regex_replace(lines[1], std::regex("\\D+"), "");

    int64_t time = utils::parse<int64_t>(timeCombined);
    int64_t distance = utils::parse<int64_t>(distCombined);

    return std::make_pair(time, distance);
}
} // namespace parser

auto partOne(const std::string& input) -> int64_t
{
    auto raceData = parser::parseInputFirstPart(input);
    int64_t margin = 1;

    for (const auto& race : raceData)
    {
        int64_t records = std::ranges::count_if(
            std::ranges::views::iota(1, race.first), [&](int t) { return (race.first - t) * t > race.second; });

        margin *= records;
    }
    return margin;
}

auto partTwo(const std::string& input) -> int64_t
{
    auto [time, distance] = parser::parseInputSecondPart(input);

    int64_t records = 0;
    for (int64_t t = 1; t < time; ++t)
    {
        if ((time - t) * t > distance)
        {
            ++records;
        }
    }

    return records;
}

auto Day06::part_one(const std::string& input) -> std::string // 505494
{
    auto result = partOne(input);
    auto expectedResult{505494};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day06::part_two(const std::string& input) -> std::string // 23632299
{
    auto result = partTwo(input);
    auto expectedResult{23632299};
    assert(result == expectedResult);
    return std::to_string(result);
}
