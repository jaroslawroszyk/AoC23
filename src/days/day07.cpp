#include "include/day07.hpp"
#include <algorithm>
#include <cassert>
#include <compare>
#include <vector>
#include "include/day07.hpp"
#include "utilities.hpp"

namespace part1
{
/*
sequence:
// kolejnosc: A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2.
Every hand is exactly one type. From strongest to weakest, they are:

Five of a kind, where all five cards have the same label: AAAAA
Four of a kind, where four cards have the same label and one card has a different label: AA8AA
Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other
card in the hand: TTT98 Two pair, where two cards share one label, two other cards share a second label, and the
remaining card has a third label: 23432 One pair, where two cards share one label, and the other three cards have a
different label from the pair and each other: A23A4 High card, where all cards' labels are distinct: 23456
*/
struct Hand
{
    std::vector<char> cards{};
    int64_t bid{};
};
auto value(const Hand& hand, int64_t i) -> int64_t
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
    return 0;
}

auto rank(const Hand& hand) -> int64_t
{
    std::map<char, int64_t> unique{};
    for (const auto& item : hand.cards)
    {
        unique[item]++;
    }

    auto repeats = [](const std::map<char, int64_t>& unique) -> int64_t
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

auto compare(const Hand& a, const Hand& b) -> int64_t
{
    int64_t rankOrder = (rank(a) < rank(b)) ? -1 : ((rank(b) < rank(a)) ? 1 : 0);
    if (rankOrder != 0)
    {
        return rankOrder;
    }

    for (int64_t i = 0; i < 5; i++)
    {
        int64_t valueOrder = (value(a, i) < value(b, i)) ? -1 : ((value(b, i) < value(a, i)) ? 1 : 0);
        if (valueOrder != 0)
        {
            return valueOrder;
        }
    }

    return 0;
}

auto solvePartOne(const std::string& input) -> int64_t
{
    std::vector<std::string> lines = utils::lines(input);

    std::vector<Hand> hand;
    std::transform(
        lines.begin(),
        lines.end(),
        std::back_inserter(hand),
        [](const std::string& str) {
            return Hand{.cards = {str[0], str[1], str[2], str[3], str[4]}, .bid = utils::parse<int64_t>(str.substr(6))};
        });

    std::sort(hand.begin(), hand.end(), [](const Hand& a, const Hand& b) { return compare(a, b) < 0; });

    int64_t winnings = 0;
    for (size_t n = 0; n < hand.size(); n++)
    {
        winnings += hand[n].bid * (n + 1);
    }
    return winnings;
}
} // namespace part1

namespace part2
{
struct Hand
{
    std::vector<char> cards{};
    int64_t bid{};
};

auto value(const Hand& hand, int64_t i) -> int64_t
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

auto rank(const Hand& hand) -> int64_t
{
    std::map<char, int64_t> unique;
    for (char card : hand.cards)
    {
        unique[card]++;
    }

    auto repeats = [](const std::map<char, int64_t>& unique) -> int64_t
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

auto compare(const Hand& a, const Hand& b) -> int64_t
{
    int64_t order = (rank(a) < rank(b)) ? -1 : ((rank(b) < rank(a)) ? 1 : 0);
    if (order != 0)
    {
        return order;
    }

    for (int64_t i = 0; i < 5; i++)
    {
        order = (value(a, i) < value(b, i)) ? -1 : ((value(b, i) < value(a, i)) ? 1 : 0);
        if (order != 0)
        {
            return order;
        }
    }

    return 0;
}

auto solvePartTwo(const std::string& input) -> int64_t
{
    auto lines = utils::lines(input);
    std::vector<Hand> hand;
    for (const std::string& str : lines)
    {
        hand.push_back({std::vector<char>(str.begin(), str.begin() + 5), std::stoi(str.substr(6))});
    }

    std::sort(hand.begin(), hand.end(), [](const Hand& a, const Hand& b) { return compare(a, b) < 0; });

    int64_t winnings = 0;
    for (size_t n = 0; n < hand.size(); n++)
    {
        winnings += hand[n].bid * (n + 1);
    }
    return winnings;
}
} // namespace part2

auto Day07::part_one(const std::string& input) -> std::string // 249726565
{
    auto result = part1::solvePartOne(input);
    auto expectedResult{249726565};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day07::part_two(const std::string& input) -> std::string // 251135960
{
    auto result = part2::solvePartTwo(input);
    auto expectedResult{251135960};
    assert(result == expectedResult);
    return std::to_string(result);
}
