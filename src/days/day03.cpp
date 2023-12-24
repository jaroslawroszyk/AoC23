#include "include/day03.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <string>
#include "utilities.hpp"

namespace
{
static auto isdigit(char c) -> bool
{
    return '0' <= c && c <= '9';
}

static auto inbounds(const std::vector<std::string>& lines, int x, int y) -> bool
{
    return 0 <= y && y < lines.size() && 0 <= x && x < lines[y].size();
}

static auto expand(const std::string& line, int start) -> std::pair<int, int>
{
    int s = start, e = start;
    for (; s >= 0 && isdigit(line[s]); --s)
    {
    }
    for (; e < line.size() && isdigit(line[e]); ++e)
    {
    }
    return {s + 1, e};
}

auto isSpecial(const std::vector<std::string>& lines)
{
    return [lines](int64_t row, int64_t col)
    {
        if (row < 0 || col < 0) return false;
        if (row >= std::ssize(lines) || col >= std::ssize(lines[row])) return false;
        return not std::isdigit(lines[row][col]) && lines[row][col] != '.';
    };
}
} // namespace

namespace std
{
template <>
struct hash<std::array<int, 3>>
{
    size_t operator()(const std::array<int, 3>& arr) const
    {
        size_t hashValue = 0;
        for (int value : arr)
        {
            hashValue ^= std::hash<int>()(value) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
        }
        return hashValue;
    }
};
} // namespace std

auto Day03::part1(const std::string& input) -> int
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

auto Day03::part2(const std::string& input) -> int
{
    auto lines = utils::lines(input);
    std::vector<std::array<int, 2>> gears;

    for (int y = 0; y < lines.size(); ++y)
    {
        const std::string& str = lines[y];
        for (int x = 0; x < str.size(); ++x)
        {
            if (str[x] == '*')
            {
                gears.push_back({x, y});
            }
        }
    }

    const std::array<std::array<int, 2>, 8> neighbours = {
        {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}}};

    int sum = 0;

    for (const auto& pt : gears)
    {
        std::unordered_set<std::array<int, 3>> numbers;
        int x = pt[0], y = pt[1];

        for (const auto& neighbour : neighbours)
        {
            int dx = neighbour[0], dy = neighbour[1];

            if (inbounds(lines, x + dx, y + dy) && isdigit(lines[y + dy][x + dx]))
            {
                auto [s, e] = expand(lines[y + dy], x + dx);
                numbers.insert({s, e, y + dy});
            }
        }

        if (numbers.size() == 2)
        {
            int product = 1;
            for (const auto& n : numbers)
            {
                int s = n[0], e = n[1], y = n[2];
                product *= utils::parse<int>(lines[y].substr(s, e - s));
            }
            sum += product;
        }
    }

    return sum;
}

auto Day03::part_one(const std::string& input) -> std::string
{
    auto result = part1(input);
    auto expectedResult{553079};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day03::part_two(const std::string& input) -> std::string
{
    auto result = part2(input);
    auto expectedResult{84363105};
    assert(result == expectedResult);
    return std::to_string(result);
}
