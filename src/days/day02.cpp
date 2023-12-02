#include "include/day02.hpp"
#include <charconv>
#include <chrono>
#include <format>
#include <iostream>
#include <optional>
#include <ranges>
#include <sstream>
#include <string>
#include "utilities.hpp"

// using std::operator""sv;

struct CubeBag
{
    int red;
    int green;
    int blue;
};

constexpr auto MAX_RED = 12;
constexpr auto MAX_GREEN = 13;
constexpr auto MAX_BLUE = 14;

static constexpr std::optional<int> svtoi(std::string_view const& sv)
{
    int value;
    if (std::from_chars(sv.data(), sv.data() + sv.size(), value).ec == std::errc{})
    {
        return value;
    }
    return std::nullopt;
}

constexpr bool tryAddCubes(std::string_view const& cubeColor, int const cubeCount, CubeBag& bag)
{
    if (cubeColor == "red")
    {
        bag.red += cubeCount;
        return bag.red <= MAX_RED;
    }
    if (cubeColor == "green")
    {
        bag.green += cubeCount;
        return bag.green <= MAX_GREEN;
    }
    if (cubeColor == "blue")
    {
        bag.blue += cubeCount;
        return bag.blue <= MAX_BLUE;
    }
    return false;
}

constexpr bool parseAndCheckGame(std::string_view const& setInfosToken)
{
    size_t pos = 0;
    while (pos != std::string_view::npos)
    {
        size_t semicolonPos = setInfosToken.find(';', pos);
        auto const setToken = setInfosToken.substr(pos, semicolonPos - pos);

        auto bag = CubeBag{};
        size_t cubePos = 0;
        while (cubePos != std::string_view::npos)
        {
            size_t commaPos = setToken.find(',', cubePos);
            auto const cubeToken = setToken.substr(cubePos, commaPos - cubePos);

            auto const cubeTokenSv = std::string_view(cubeToken);
            auto const whitespacePos = cubeTokenSv.find(' ');
            auto const cubeCount = svtoi(cubeTokenSv.substr(0, whitespacePos)).value_or(0);
            auto const cubeColor = cubeTokenSv.substr(whitespacePos + 1);
            if (!tryAddCubes(cubeColor, cubeCount, bag))
            {
                return false;
            }

            if (commaPos == std::string_view::npos)
            {
                break;
            }

            cubePos = commaPos + 2;
        }

        if (semicolonPos == std::string_view::npos)
        {
            break;
        }

        pos = semicolonPos + 2;
    }

    return true;
}

auto Day02::part_one(const std::string& input) -> std::string
{
    int answer = 0;
    for (auto const& line : utils::lines(input))
    {
        auto const colonPos = line.find(':');
        auto const gameToken = line.substr(0, colonPos);
        auto const setInfosToken = line.substr(colonPos + 2);
        if (parseAndCheckGame(setInfosToken))
        {
            auto const gameId = stoi(gameToken.substr(5));
            answer += gameId;
        }
    }
    return std::to_string(answer);
}

auto Day02::part_two(const std::string& input) -> std::string
{
    return "part two";
}
