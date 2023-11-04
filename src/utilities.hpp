#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "../libs/pprint.hh"

namespace utils
{
    inline auto rtrim(std::string&& s) -> std::string
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return not std::isspace(ch); }).base(), s.end());
        return s;
    }

    auto lines(const std::string& s) -> std::vector<std::string>
    {
        auto lines = std::vector<std::string>{};
        auto ss = std::stringstream(s);

        for (std::string line; std::getline(ss, line);)
        {
            lines.push_back(rtrim(std::move(line)));
        }
        return lines;
    }

    inline auto print(std::ostream& os, const auto&... args) { pprint::PrettyPrinter(os).print(args...); }

    inline auto print(const auto&... args) { utils::print(std::cout, args...); }

    template<typename Container>
    auto printVec(const Container& container)
    {
        for (auto& el : container)
        {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }

} // namespace utils
