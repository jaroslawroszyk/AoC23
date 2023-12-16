#include "include/day05.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <string>
#include "utilities.hpp"

auto Day05::parse(const std::string& line)
{
    auto lines = utils::split(line, ':');

    std::string pattern = "[0-9]+";
    auto seeds = utils::findPattern(pattern, lines[1]);
    std::vector<int64_t> seedsMap{};
    std::transform(seeds.begin(), seeds.end(), std::back_inserter(seedsMap), utils::parse<int64_t>);

    std::vector<std::vector<Range>> maps{};
    for (int i = 2; i < lines.size(); ++i)
    {
        auto givenMap = lines[i];
        auto nums = utils::findPattern(pattern, givenMap);

        std::vector<Range> ranges{};
        for (int j = 0; j < nums.size(); j += 3)
        {
            Range range{0, 0, 0};
            range.destination = utils::parse<int64_t>(nums[j]);
            range.source = utils::parse<int64_t>(nums[j + 1]);
            range.length = utils::parse<int64_t>(nums[j + 2]);
            ranges.push_back(range);
        }
        maps.push_back(ranges);
    }

    return std::make_pair(seedsMap, maps);
}

auto Day05::closest_coordinate(const std::string& line) -> int64_t
{
    auto [seeds, maps] = parse(line);

    for (const auto& map : maps)
    {
        auto copySeed = seeds;
        for (int i = 0; i < seeds.size(); i++)
        {
            for (const auto& range : map)
            {
                if (range.source <= seeds[i] && seeds[i] < range.source + range.length)
                {
                    copySeed[i] = range.destination + (seeds[i] - range.source);
                    break;
                }
            }
        }
        seeds = copySeed;
    }

    return *std::min_element(seeds.begin(), seeds.end());
}

auto Day05::part_one(const std::string& input) -> std::string
{
    auto result = closest_coordinate(input);
    auto expectedResult{226172555};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day05::part_two(const std::string&) -> std::string
{
    // TODO: implement that
    return "part-two";
}
