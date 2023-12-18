#pragma once

#include <algorithm>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include "../../libs/pprint.hh"

struct Point
{
    int64_t x{};
    int64_t y{};

    Point(int64_t x, int64_t y) : x(x), y(y) {}
    Point() = default;

};

namespace helper
{
auto rtrim(std::string_view) -> std::string_view;
} // namespace helper

namespace utils
{
auto lines(const std::string&) -> std::vector<std::string>;
auto split(const std::string&, char delimeter) -> std::vector<std::string>;

auto print(std::ostream& os, const auto&... args);

auto print(const auto&... args);

template <typename Container>
auto printVec(const Container& container)
{
    for (auto& el : container)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

template <typename Container>
auto print2D(const Container& container)
{
    for (auto& el : container)
    {
        printVec(el);
    }
    std::cout << std::endl;
}

template <typename T>
inline auto parse(const std::string& str) -> T
{
    T i{};
    std::istringstream(str) >> i;
    return i;
}
template <typename K, typename V>
std::vector<K> keys(const std::unordered_map<K, V>& map)
{
    std::vector<K> result{};
    for (const auto& pair : map)
    {
        result.push_back(pair.first);
    }

    return result;
}

/*
template <typename K, typename V>
std::vector<K> keys(const std::unordered_map<K, V>& map)
{
    std::vector<K> result{};
    result.reserve(map.size());

    std::transform(map.begin(), map.end(), std::back_inserter(result), [](const auto& pair) { return pair.first; });

    return result;
}


*/
auto findPattern(std::string&, std::string&) -> std::vector<std::string>;
} // namespace utils
