#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include "../Puzzle.hpp"
#include "utilities.hpp"

struct Coord
{
    int64_t row;
    int64_t col;
    auto operator<=>(const Coord&) const = default;
    Coord operator+(const Coord& other) const { return {row + other.row, col + other.col}; }
};

template <>
struct std::hash<Coord>
{
    std::size_t operator()(const Coord& c) const noexcept
    {
        std::size_t h1 = std::hash<int64_t>{}(c.row);
        std::size_t h2 = std::hash<int64_t>{}(c.col);
        return h1 ^ (h2 << 1);
    }
};

struct Day23 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;

private:
    using ExploreFunction = std::function<void(Coord, int64_t)>;
    using Distance = int64_t;
    using State = int64_t;

    auto maxPath(std::vector<std::string>, Coord, Coord) -> int64_t;
    auto longestRoute(const std::string&) -> int64_t;
    auto exploreGraph(const ExploreFunction&, Coord) -> int64_t;

    std::unordered_set<Coord> visited;

    std::vector<std::tuple<Coord, Distance, State>> dfs;
};
