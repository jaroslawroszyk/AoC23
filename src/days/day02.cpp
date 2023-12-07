#include "include/day02.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "utilities.hpp"

namespace
{
constexpr auto MAX_RED = 12;
constexpr auto MAX_GREEN = 13;
constexpr auto MAX_BLUE = 14;
} // namespace

namespace parser
{
enum class Type
{
    RED,
    GREEN,
    BLUE
};

struct Cube
{
    Type type;
    int64_t count;
    friend std::istream& operator>>(std::istream&, Cube&);
};

struct Game
{
    int64_t id;
    std::unordered_map<Type, int64_t> max;
    friend std::istream& operator>>(std::istream&, Game& game);
    auto power() const -> int64_t { return max.at(Type::RED) * max.at(Type::GREEN) * max.at(Type::BLUE); }
};

std::istream& operator>>(std::istream& is, Game& game)
{
    if (is.peek() != 'G' or not is.ignore(5))
    {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    if (not(is >> game.id))
    {
        return is;
    }
    is.ignore(1);

    game.max.clear();
    Cube cube{};
    while (is >> cube)
    {
        game.max[cube.type] = std::max(game.max[cube.type], cube.count);

        auto delim = is.get();
        if (delim == ',' or delim == ';') continue;
        if (delim == '\n') break;
        if (delim == EOF)
        {
            is.clear();
            break;
        }
    }
    return is;
}

std::istream& operator>>(std::istream& is, Cube& cube)
{
    if (not(is >> cube.count)) return is;
    while (is.peek() == ' ')
        is.get();
    switch (is.peek())
    {
        case 'b':
            cube.type = Type::BLUE;
            is.ignore(4);
            break;
        case 'g':
            cube.type = Type::GREEN;
            is.ignore(5);
            break;
        case 'r':
            cube.type = Type::RED;
            is.ignore(3);
            break;
        default:
            throw std::runtime_error("parsing error");
    }
    return is;
}
} // namespace parser

auto isGameValid(parser::Game& game)
{
    using namespace parser;
    return game.max[Type::RED] <= MAX_RED && game.max[Type::GREEN] <= MAX_GREEN && game.max[Type::BLUE] <= MAX_BLUE;
}

// part 1
auto possible_games(const std::string& input) -> int64_t
{
    int64_t sum{0};

    for (const auto& line : utils::lines(input))
    {
        parser::Game game{};
        std::istringstream iss(line);
        iss >> game;

        if (isGameValid(game))
        {
            sum += game.id;
        }
    }

    return sum;
}

// part 2
auto game_powah(const std::string& input) -> int64_t
{
    int64_t total_power = 0;

    for (const auto& line : utils::lines(input))
    {
        parser::Game game{};
        std::istringstream iss(line);
        iss >> game;

        total_power += game.power();
    }

    return total_power;
}

auto Day02::part_one(const std::string& input) -> std::string // 2449
{
    auto result = possible_games(input);
    auto expectedResult{2449};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day02::part_two(const std::string& input) -> std::string // 63981
{
    auto result = game_powah(input);
    auto expectedResult{63981};
    assert(result == expectedResult);
    return std::to_string(result);
}
