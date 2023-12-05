#pragma once

#include <algorithm>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include "../../libs/pprint.hh"

namespace helper
{
auto rtrim(std::string_view sv) -> std::string_view;
} // namespace helper

namespace utils
{
auto lines(const std::string& s) -> std::vector<std::string>;
auto split(const std::string& s, char delimeter) -> std::vector<std::string>;

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

// auto print2DVec()
// {
//         for(const auto& x : maps)
//     {
//         utils::printVec(x);
//     }
// }

template <typename T>
inline auto parse(const std::string& str) -> T
{
    T i{};
    std::istringstream(str) >> i;
    return i;
}
} // namespace utils
