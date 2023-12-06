#include "include/day04.hpp"
#include "utilities.hpp"
#include <algorithm>
#include <numeric>
#include <string>

struct Card
{
    int id;
    std::vector<int> winningNumbers;
    std::vector<int> numbersOnCard;
    std::size_t copies;
};

namespace helper
{
inline auto extractNumber(const std::string& line) -> std::vector<int>
{
    std::vector<int> numbers;
    std::size_t start = 0;
    std::size_t end = line.find(' ');
    for (int i = 0; i < line.size(); i += 3)
    {
        if (line[i] == ' ')
        {
            numbers.push_back(std::stoi(line.substr(i + 1, i + 2)));
        }
        else
        {
            numbers.push_back(std::stoi(line.substr(i, i + 2)));
        }
    }
    return numbers;
}

inline auto updateCopiesBasedOnWinningNumbers(std::vector<Card>& cards) -> void
{
    for (const auto& card : cards)
    {
        int count = 0;
        for (const auto& cardId : card.numbersOnCard)
        {
            if (std::find(std::begin(card.winningNumbers), std::end(card.winningNumbers), cardId) !=
                std::end(card.winningNumbers))
            {
                count++;
            }
        }
        for (int i = card.id + 1 - 1; i < std::min(cards.size(), std::size_t(card.id + count)); i++)
        {
            cards[i].copies += card.copies;
        }
    }
}
} // namespace helper

auto total_score(const std::string& input)
{
    auto lines = utils::lines(input);
    std::size_t totalPoints{0};
    for (auto& line : lines)
    {
        std::size_t start = 0;
        std::size_t end = line.find(":");
        start = end + 2;
        end = line.find('|', start);
        const auto winningNumbers = helper::extractNumber(line.substr(start, end - start));
        const auto card_numbers = helper::extractNumber(line.substr(end + 2, line.size() - end));
        int cnt{0};
        for (const auto& cardId : card_numbers)
        {
            if (std::find(std::begin(winningNumbers), std::end(winningNumbers), cardId) != std::end(winningNumbers))
                ++cnt;
        }
        if (cnt > 0) totalPoints += std::pow(2, cnt - 1);
    }
    return totalPoints;
}

auto total_scratchcards(const std::string& input)
{
    auto lines = utils::lines(input);
    std::size_t totalPoints{0};
    std::vector<Card> cards{};
    for (auto& line : lines)
    {
        Card card;
        std::size_t start = 0;
        std::size_t end = line.find(":");
        card.id = std::stoi(line.substr(5, end - 5));
        start = end + 2;
        end = line.find('|', start);

        card.winningNumbers = helper::extractNumber(line.substr(start, end - start));
        card.numbersOnCard = helper::extractNumber(line.substr(end + 2, line.size() - end));
        card.copies = 1;
        cards.push_back(card);
    }

    helper::updateCopiesBasedOnWinningNumbers(cards);
    return std::accumulate(
        std::begin(cards), std::end(cards), 0, [](std::size_t total, const Card& card) { return total + card.copies; });
}

auto Day04::part_one(const std::string& input) -> std::string // // 20855
{
    return std::to_string(total_score(input));
}

auto Day04::part_two(const std::string& input) -> std::string // 5489600
{
    return std::to_string(total_scratchcards(input));
}
