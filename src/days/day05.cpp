#include "include/day05.hpp"
#include "utilities.hpp"
#include <algorithm>
#include <numeric>
#include <regex>
#include <string>

struct Range
{
    int64_t destination{};
    int64_t source{};
    int64_t length{};
    friend std::ostream& operator<<(std::ostream& os, const Range& range)
    {
        os << "{" << range.destination << " " << range.source << " " << range.length << "}";
        return os;
    }
};

auto findPattern(std::string& pattern, std::string& text) -> std::vector<std::string>
{
    std::vector<std::string> result{};
    std::regex regex(pattern);

    auto words_begin = std::sregex_iterator(text.begin(), text.end(), regex);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator it = words_begin; it != words_end; ++it)
    {
        std::smatch match = *it;
        std::string match_str = match.str();
        result.push_back(match_str);
    }

    return result;
}

auto parse(const std::string& line)
{
    auto lines = utils::split(line, ':');

    std::string pattern = "[0-9]+";
    auto seeds = findPattern(pattern, lines[1]);
    std::vector<int64_t> seedsMap{};
    std::transform(seeds.begin(), seeds.end(), std::back_inserter(seedsMap), utils::parse<int64_t>);

    std::vector<std::vector<Range>> maps{};
    for (int i = 2; i < lines.size(); ++i)
    {
        auto givenMap = lines[i];
        auto nums = findPattern(pattern, givenMap);

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

auto closest_coordinate(const std::string& line) -> int64_t
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

auto Day05::part_one(const std::string& line) -> std::string // 226172555
{
    return std::to_string(closest_coordinate(line));
}

// auto closest_range_location(const std::string& input) -> int64_t

auto Day05::part_two(const std::string&) -> std::string
{
    return "part-two";
}
