#include "utilities.hpp"

#include <algorithm>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace helper
{
auto rtrim(std::string_view sv) -> std::string_view
{
    auto isNotWhitespace = [](unsigned char c) { return not std::isspace(c); };

    auto lastNonWhitespace = std::ranges::find_if(sv.rbegin(), sv.rend(), isNotWhitespace).base();

    return {sv.begin(), lastNonWhitespace};
}
} // namespace helper

namespace utils
{
auto lines(const std::string& s) -> std::vector<std::string>
{
    auto lines = std::vector<std::string>{};
    auto ss = std::stringstream(s);

    for (std::string line; std::getline(ss, line);)
    {
        lines.emplace_back(helper::rtrim(line));
    }
    return lines;
}

auto split(const std::string& s, char delimeter) -> std::vector<std::string>
{
    auto lines = std::vector<std::string>{};
    auto ss = std::stringstream(s);

    for (std::string line; std::getline(ss, line, delimeter);)
    {
        lines.emplace_back(helper::rtrim(line));
    }
    return lines;
}

auto print(std::ostream& os, const auto&... args)
{
    pprint::PrettyPrinter(os).print(args...);
}

auto print(const auto&... args)
{
    utils::print(std::cout, args...);
}
} // namespace utils
