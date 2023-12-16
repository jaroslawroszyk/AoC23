#include "include/day07.hpp"
#include <algorithm>
#include <cassert>
#include "include/day07.hpp"
#include "utilities.hpp"

auto compare(const Hand& a, const Hand& b, IPart& part) -> int64_t
{
    int64_t order = (part.rank(a) < part.rank(b)) ? -1 : ((part.rank(b) < part.rank(a)) ? 1 : 0);
    if (order != 0)
    {
        return order;
    }

    for (int64_t i = 0; i < 5; i++)
    {
        order = (part.value(a, i) < part.value(b, i)) ? -1 : ((part.value(b, i) < part.value(a, i)) ? 1 : 0);
        if (order != 0)
        {
            return order;
        }
    }

    return 0;
}

auto FirstPart::value(const Hand& hand, int64_t i) -> int64_t
{
    switch (hand.cards[i])
    {
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'J':
            return 11;
        case 'T':
            return 10;
        default:
            return hand.cards[i] - '0';
    }
}

auto FirstPart::rank(const Hand& hand) -> int64_t
{
    std::unordered_map<char, int64_t> unique{};
    for (const auto& item : hand.cards)
    {
        unique[item]++;
    }

    auto repeats = [](const std::unordered_map<char, int64_t>& unique) -> int64_t
    {
        int64_t max = 0;
        for (const auto& item : unique)
        {
            if (max < item.second)
            {
                max = item.second;
            }
        }
        return max;
    };

    switch (unique.size())
    {
        case 5:
            return 0;
        case 4:
            return 1;
        case 3:
            return repeats(unique);
        case 2:
            return repeats(unique) + 1;
        default:
            return 6;
    }
}

auto SecondPart::value(const Hand& hand, int64_t i) -> int64_t
{
    switch (hand.cards[i])
    {
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'J':
            return 1;
        case 'T':
            return 10;
        default:
            return hand.cards[i] - '0';
    }
}

auto SecondPart::rank(const Hand& hand) -> int64_t
{
    std::unordered_map<char, int64_t> unique;
    for (char card : hand.cards)
    {
        unique[card]++;
    }

    auto repeats = [](const std::unordered_map<char, int64_t>& unique) -> int64_t
    {
        int64_t max = 0;
        for (const auto& item : unique)
        {
            if (max < item.second)
            {
                max = item.second;
            }
        }
        return max;
    };

    switch (unique.size())
    {
        case 5:
            return 0 + unique['J'];
        case 4:
            switch (unique['J'])
            {
                case 0:
                    return 1;
                default:
                    return 3;
            }
        case 3:
            switch (unique['J'])
            {
                case 0:
                    return repeats(unique);
                case 1:
                    return repeats(unique) + 2;
                default:
                    return 5;
            }
        case 2:
            switch (unique['J'])
            {
                case 0:
                    return repeats(unique) + 1;
                default:
                    return 6;
            }
        default:
            return 6;
    }
}

auto Day07::part1(const std::string& input) -> int64_t
{
    FirstPart first;
    std::vector<std::string> lines = utils::lines(input);

    std::vector<Hand> hand;
    std::transform(
        lines.begin(),
        lines.end(),
        std::back_inserter(hand),
        [](const std::string& str) {
            return Hand{.cards = {str[0], str[1], str[2], str[3], str[4]}, .bid = utils::parse<int64_t>(str.substr(6))};
        });

    std::sort(
        hand.begin(), hand.end(), [this, &first](const Hand& a, const Hand& b) { return compare(a, b, first) < 0; });

    int64_t winnings = 0;
    for (size_t n = 0; n < hand.size(); n++)
    {
        winnings += hand[n].bid * (n + 1);
    }
    return winnings;
}

auto Day07::part2(const std::string& input) -> int64_t
{
    SecondPart second;
    auto lines = utils::lines(input);
    std::vector<Hand> hand;
    for (const std::string& str : lines)
    {
        hand.push_back({std::vector<char>(str.begin(), str.begin() + 5), std::stoi(str.substr(6))});
    }

    std::sort(
        hand.begin(), hand.end(), [this, &second](const Hand& a, const Hand& b) { return compare(a, b, second) < 0; });

    int64_t winnings = 0;
    for (size_t n = 0; n < hand.size(); n++)
    {
        winnings += hand[n].bid * (n + 1);
    }
    return winnings;
}

auto Day07::part_one(const std::string& input) -> std::string
{
    auto result = part1(input);
    auto expectedResult{249726565};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day07::part_two(const std::string& input) -> std::string
{
    auto result = part2(input);
    auto expectedResult{251135960};
    assert(result == expectedResult);
    return std::to_string(result);
}
