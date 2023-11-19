#pragma once
#include <algorithm>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "../libs/pprint.hh"

namespace utils
{
auto rtrim(std::string_view sv) -> std::string_view
{
    auto isNotWhitespace = [](unsigned char c) { return not std::isspace(c); };

    auto lastNonWhitespace = std::ranges::find_if(sv.rbegin(), sv.rend(), isNotWhitespace).base();

    return {sv.begin(), lastNonWhitespace};
}

auto lines(const std::string& s) -> std::vector<std::string>
{
    auto lines = std::vector<std::string>{};
    auto ss = std::stringstream(s);

    for (std::string line; std::getline(ss, line);)
    {
        lines.emplace_back(rtrim(line));
    }
    return lines;
}

inline auto print(std::ostream& os, const auto&... args)
{
    pprint::PrettyPrinter(os).print(args...);
}

inline auto print(const auto&... args)
{
    utils::print(std::cout, args...);
}

template <typename Container>
auto printVec(const Container& container)
{
    for (auto& el : container)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

template <typename T>
inline auto parse(const std::string& str) -> T
{
    return static_cast<T>(std::stof(str));
}
} // namespace utils
