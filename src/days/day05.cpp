#include "include/day05.hpp"
#include <algorithm>
#include <numeric>
#include <string>
#include "include/day04.hpp"
#include "utilities.hpp"

auto Day05::part_one(const std::string& line) -> std::string
{
    auto lines = utils::lines(line);
    utils::printVec(lines);
    return "part-one";
}

auto Day05::part_two(const std::string&) -> std::string
{
    return "part-two";
}
