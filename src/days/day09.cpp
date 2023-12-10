#include "include/day09.hpp"
#include <cassert>
#include <numeric>
#include "utilities.hpp"

auto extrapolateForward(const std::vector<int>& history)
{
    if (std::all_of(history.begin(), history.end(), [](int val) { return val == 0; }))
    {
        return 0;
    }

    std::vector<int> diff{};
    diff.reserve(history.size() - 1);

    for (size_t i = 0; i < history.size() - 1; ++i)
    {
        diff.push_back(history[i + 1] - history[i]);
    }

    return history.back() + extrapolateForward(diff);
}

auto extrapolateBackward(const std::vector<int>& history)
{
    if (std::all_of(history.begin(), history.end(), [](int val) { return val == 0; }))
    {
        return 0;
    }

    std::vector<int> diff{};
    diff.reserve(history.size() - 1);

    for (size_t i = 0; i < history.size() - 1; ++i)
    {
        diff.push_back(history[i + 1] - history[i]);
    }

    return history.front() - extrapolateBackward(diff);
}

using Callback = std::function<int(const std::vector<int>&)>;
auto process(const std::string& input, const Callback callback)
{
    auto data = utils::lines(input);
    std::vector<int> values{};

    for (const auto& line : data)
    {
        std::vector<int> numbers;
        std::istringstream line_stream(line);
        int number;

        while (line_stream >> number)
        {
            numbers.push_back(number);
        }

        values.push_back(callback(numbers));
    }
    auto sum = std::accumulate(values.begin(), values.end(), 0);

    return std::to_string(sum);
}

auto Day09::part_one(const std::string& input) -> std::string
{
    auto result = process(input, extrapolateForward);
    auto expectedResult{1743490457};
    assert(std::stoi(result) == expectedResult);
    return result;
}

auto Day09::part_two(const std::string& input) -> std::string
{
    auto result = process(input, extrapolateBackward);
    auto expectedResult{1053};
    assert(std::stoi(result) == expectedResult);
    return result;
}
