#include "include/day10.hpp"
#include <algorithm>
#include <cassert>
#include <functional>
#include <numeric>
#include <ranges>
#include <vector>
#include "utilities.hpp"

constexpr int DIM = 140;
constexpr auto validN = std::array{'|', 'F', '7'};
constexpr auto validO = std::array{'-', 'J', '7'};
constexpr auto validS = std::array{'|', 'L', 'J'};
constexpr auto validW = std::array{'-', 'F', 'L'};

enum Direction
{
    N,
    E,
    S,
    W
};

inline int getIndex(int const i, int const j)
{
    return i * (DIM + 1) + j;
}

inline std::pair<int, int> getPos(int const index)
{
    return {index / (DIM + 1), index % (DIM + 1)};
}

std::pair<int, Direction> traverse(std::string const& input, int const current, Direction from)
{
    auto const [i, j] = getPos(current);
    switch (input[current])
    {
        case '|':
            return from == N ? std::make_pair(getIndex(i - 1, j), N) : std::make_pair(getIndex(i + 1, j), S);
        case '-':
            return from == E ? std::make_pair(getIndex(i, j + 1), E) : std::make_pair(getIndex(i, j - 1), W);
        case 'L':
            return from == S ? std::make_pair(getIndex(i, j + 1), E) : std::make_pair(getIndex(i - 1, j), N);
        case 'J':
            return from == S ? std::make_pair(getIndex(i, j - 1), W) : std::make_pair(getIndex(i - 1, j), N);
        case '7':
            return from == N ? std::make_pair(getIndex(i, j - 1), W) : std::make_pair(getIndex(i + 1, j), S);
        case 'F':
            return from == N ? std::make_pair(getIndex(i, j + 1), E) : std::make_pair(getIndex(i + 1, j), S);
        default:
            throw std::invalid_argument("no pipe at given position");
    }
}

std::pair<char, Direction> getStartPipe(std::string const& input, int start)
{
    auto const [si, sj] = getPos(start);
    auto const north = std::ranges::contains(validN, input[getIndex(si - 1, sj)]);
    auto const east = std::ranges::contains(validO, input[getIndex(si, sj + 1)]);
    auto const south = std::ranges::contains(validS, input[getIndex(si + 1, sj)]);
    auto const west = std::ranges::contains(validW, input[getIndex(si, sj - 1)]);

    if (north && south) return {'|', N};
    if (east && west) return {'-', E};
    if (north && east) return {'L', S};
    if (north && west) return {'J', S};
    if (south && west) return {'7', N};
    if (south && east) return {'F', N};

    throw std::invalid_argument("start position cannot be a pipe");
}

auto Day10::part_one(const std::string& input) -> std::string
{
    auto lines = utils::lines(input);

    auto inputCopy = input;
    auto const startIndex = inputCopy.find('S');
    auto const [pipe, startDirection] = getStartPipe(inputCopy, startIndex);
    inputCopy[startIndex] = pipe;

    auto length = 0;
    auto currentIndex = startIndex;
    auto currentDirection = startDirection;
    do
    {
        auto const [newIndex, newDirection] = traverse(inputCopy, currentIndex, currentDirection);
        currentIndex = newIndex;
        currentDirection = newDirection;
        ++length;
    } while (currentIndex != startIndex);

    auto const answer = length / 2;

    return std::to_string(answer);
}

char getIntersectionChar(Direction const from, Direction const to)
{
    if (from == N)
    {
        return 'N';
    }

    if (to == S)
    {
        return 'S';
    }

    return 'X';
}

auto Day10::part_two(const std::string& input) -> std::string
{
    auto lines = utils::lines(input);

    auto inputCopy = input;
    auto const startIndex = inputCopy.find('S');
    auto const [pipe, startDirection] = getStartPipe(inputCopy, startIndex);
    inputCopy[startIndex] = pipe;

    auto [currentIndex, currentDirection] = traverse(inputCopy, startIndex, startDirection);
    while (currentIndex != startIndex)
    {
        auto const [newIndex, newDirection] = traverse(inputCopy, currentIndex, currentDirection);
        inputCopy[currentIndex] = getIntersectionChar(currentDirection, newDirection);
        currentIndex = newIndex;
        currentDirection = newDirection;
    }

    auto const [newIndex, newDirection] = traverse(inputCopy, currentIndex, currentDirection);
    inputCopy[currentIndex] = getIntersectionChar(currentDirection, newDirection);

    auto answer = 0;
    for (auto line = 0; line < DIM; line++)
    {
        auto windings = 0;
        auto const limit = line * (DIM + 1) + DIM;
        for (auto current = line * (DIM + 1); current < limit; current++)
        {
            if (inputCopy[current] == 'N')
            {
                --windings;
            }
            else if (inputCopy[current] == 'S')
            {
                ++windings;
            }
            else if (inputCopy[current] != 'X')
            {
                if (windings != 0)
                {
                    ++answer;
                }
            }
        }
    }

    return std::to_string(answer);
}
