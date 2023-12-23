#pragma once
#include <sstream>
#include <unordered_map>
#include "../Puzzle.hpp"

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
} // namespace parser

struct Day02 : Puzzle
{
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
