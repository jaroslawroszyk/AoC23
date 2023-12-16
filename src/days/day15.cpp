#include "include/day15.hpp"
#include <cassert>
#include <numeric>
#include "utilities.hpp"

auto hash(const std::string& lens) -> int64_t
{
    int64_t current{0};
    for (size_t i = 0; i < lens.size(); ++i)
    {
        current += static_cast<int64_t>(lens[i]);
        current *= 17;
        current %= 256;
    }

    return current;
}

auto Day15::part1(const std::string& input) -> int64_t
{
    auto sequence = utils::split(input, ',');
    auto hashView = sequence | std::views::transform(hash);

    return std::accumulate(hashView.begin(), hashView.end(), int64_t{0}, std::plus<>());
}

auto Day15::part_one(const std::string& input) -> std::string
{
    auto result = part1(input);

    auto expectedResult{516070};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day15::part_two(const std::string&) -> std::string
{
    return "part_two";
}
