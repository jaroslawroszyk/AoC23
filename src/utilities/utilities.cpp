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

auto findPattern(std::string& pattern, std::string& text) -> std::vector<std::string>
{
    std::vector<std::string> result{};
    std::regex regex(pattern);

    auto words_begin = std::sregex_iterator(text.begin(), text.end(), regex);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator it = words_begin; it != words_end; ++it)
    {
        std::smatch match = *it;
        std::string match_str = match.str();
        result.push_back(match_str);
    }

    return result;
}
} // namespace utils
