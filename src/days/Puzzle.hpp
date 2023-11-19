#pragma once
#include <string>

struct Puzzle
{
    virtual ~Puzzle() = default;
    auto solve(const std::string& input) -> std::pair<std::string, std::string>
    {
        return {part_one(input), part_two(input)};
    }
    virtual auto part_one(const std::string&) -> std::string { return ""; };
    virtual auto part_two(const std::string&) -> std::string { return ""; };
};
