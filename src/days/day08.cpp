#include "include/day08.hpp"
#include <cassert>
#include <numeric>
#include <unordered_map>
#include "utilities.hpp"

namespace
{
using Graph = std::unordered_map<std::string, std::array<std::string, 2>>;
} // namespace

auto hauntedWasteland(const std::string& instructions, const Graph& graph, std::string node) -> int64_t
{
    int64_t steps = 0;
    for (size_t i = 0; node[2] != 'Z'; i = (i + 1) % instructions.length())
    {
        steps += 1;

        auto it = graph.find(node);
        if (it == graph.end())
        {
            break;
        }

        if (instructions[i] == 'R')
        {
            node = it->second[1];
        }
        else if (instructions[i] == 'L')
        {
            node = it->second[0];
        }
    }
    return steps;
}

auto regexCapture(const std::regex& re, const std::string& s) -> std::vector<std::string>
{
    std::smatch matches;
    std::regex_match(s, matches, re);
    return {matches[1], matches[2], matches[3]};
}

auto parseGraphFromLines(std::vector<std::string>& lines) -> Graph
{
    std::regex re(R"((\w+) = \((\w+), (\w+)\))");

    Graph graph{};
    for (size_t i = 2; i < lines.size(); ++i)
    {
        auto captures = regexCapture(re, lines[i]);
        std::string node = captures[0];
        std::string left = captures[1];
        std::string right = captures[2];
        graph[node] = {left, right};
    }

    return graph;
}

auto hauntedWastelandPartOne(const std::string& input) -> int64_t
{
    std::vector<std::string> lines = utils::lines(input);
    auto instructions = lines[0];

    auto graph = parseGraphFromLines(lines);

    std::string startNode = "AAA";
    return hauntedWasteland(instructions, graph, startNode);
}

auto hauntedWastelandPartTwo(const std::string& input) -> int64_t
{
    std::vector<std::string> lines = utils::lines(input);

    auto graph = parseGraphFromLines(lines);
    auto instructions = lines[0];

    std::unordered_map<std::string, int64_t> cache{};
    int64_t result = 1;
    for (const auto& entry : graph)
    {
        if (entry.first.size() > 2 && entry.first[2] == 'A')
        {
            if (cache.find(entry.first) == cache.end())
            {
                cache[entry.first] = hauntedWasteland(instructions, graph, entry.first);
            }
            result = std::lcm(result, cache[entry.first]);
        }
    }

    return result;
}

auto Day08::part_one(const std::string& input) -> std::string
{
    auto result = hauntedWastelandPartOne(input);
    auto expectedResult{19783};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day08::part_two(const std::string& input) -> std::string
{
    auto result = hauntedWastelandPartTwo(input);
    auto expectedResult{9177460370549};
    assert(result == expectedResult);
    return std::to_string(result);
}
