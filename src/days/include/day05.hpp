#pragma once
#include <ostream>
#include "../Puzzle.hpp"

struct Range
{
    int64_t destination{};
    int64_t source{};
    int64_t length{};
    friend std::ostream& operator<<(std::ostream& os, const Range& range)
    {
        os << "{" << range.destination << " " << range.source << " " << range.length << "}";
        return os;
    }
};

struct Day05 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;

private:
    auto parse(const std::string&);
    auto closest_coordinate(const std::string&) -> int64_t;
};
