#pragma once
#include "../Puzzle.hpp"

struct Hand
{
    std::vector<char> cards{};
    int64_t bid{};
};

struct IPart
{
    virtual ~IPart() = default;
    virtual auto value(const Hand&, int64_t i) -> int64_t = 0;
    virtual auto rank(const Hand&) -> int64_t = 0;
};

struct FirstPart : public IPart
{
    auto value(const Hand&, int64_t i) -> int64_t override;
    auto rank(const Hand&) -> int64_t override;
    virtual ~FirstPart() = default;
};

struct SecondPart : public IPart
{
    auto value(const Hand&, int64_t i) -> int64_t override;
    auto rank(const Hand&) -> int64_t override;
    virtual ~SecondPart() = default;
};

struct Day07 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;

private:
    auto part1(const std::string&) -> int64_t;
    auto part2(const std::string&) -> int64_t;
};
