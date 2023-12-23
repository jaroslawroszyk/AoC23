#include "include/day13.hpp"
#include <cassert>
#include "utilities.hpp"

namespace
{
auto verticalSymmetry(const Pair& a, const Pair& b) -> std::pair<double, double>
{
    int64_t minJ = std::min(a.j, b.j);
    int64_t maxJ = std::max(a.j, b.j);
    int64_t deltaJ = maxJ - minJ;

    return (deltaJ % 2 == 0) ? std::make_pair(-1.0, -1.0) : std::make_pair(0.0, minJ + deltaJ / 2.0);
}

auto horizontalSymmetry(const Pair& a, const Pair& b) -> std::pair<double, double>
{
    int64_t minI = std::min(a.i, b.i);
    int64_t maxI = std::max(a.i, b.i);
    int64_t deltaI = maxI - minI;

    return (deltaI % 2 == 0) ? std::make_pair(-1.0, -1.0) : std::make_pair(minI + deltaI / 2.0, 0.0);
}
} // namespace

auto Day13::symmetry(const Pair& a, const Pair& b) -> std::pair<double, double>
{
    if (a.i == b.i)
    {
        return verticalSymmetry(a, b);
    }

    if (a.j == b.j)
    {
        return horizontalSymmetry(a, b);
    }

    return {-1.0, -1.0};
}

auto Day13::reflect(const Pair& p, double symmetryRow, double symmetryColumn) -> Pair
{
    if (symmetryRow == 0)
    {
        double dj = symmetryColumn - static_cast<double>(p.j);
        return {p.i, p.j + static_cast<int64_t>(dj * 2)};
    }
    double di = symmetryRow - static_cast<double>(p.i);
    return {p.i + static_cast<int64_t>(di * 2), p.j};
}

auto Day13::pointOfIncidence(const std::unordered_map<Pair, bool>& mirrors, const Pair& bounds, bool smudge)
    -> std::pair<int64_t, int64_t>
{
    auto points = utils::keys(mirrors);

    for (size_t n = 0; n < points.size(); ++n)
    {
        for (size_t m = n + 1; m < points.size(); ++m)
        {
            auto [ir, jr] = symmetry(points[n], points[m]);
            if (ir == -1 || jr == -1)
            {
                continue;
            }

            bool found = true;
            bool smudgeFlag = smudge;
            for (const auto& p : points)
            {
                auto pp = reflect(p, ir, jr);
                if (!(0 <= pp.i && pp.i < bounds.i) || !(0 <= pp.j && pp.j < bounds.j))
                {
                    continue;
                }

                if (mirrors.find(pp) == mirrors.end())
                {
                    if (smudgeFlag)
                    {
                        smudgeFlag = false;
                        continue;
                    }
                    found = false;
                    break;
                }
            }

            if (found && !smudgeFlag)
            {
                return {static_cast<int64_t>(ir + 0.5), static_cast<int64_t>(jr + 0.5)};
            }
        }
    }

    return {0, 0};
}

auto Day13::parse(const std::string& input) -> std::pair<Day13::PairMapVector, Day13::PairVector>
{
    auto lines = utils::lines(input);

    std::vector<int64_t> sep = {-1};
    for (size_t n = 0; n < lines.size(); ++n)
    {
        if (lines[n].empty())
        {
            sep.push_back(n);
        }
    }
    sep.push_back(lines.size());

    std::vector<std::unordered_map<Pair, bool>> maps{};
    std::vector<Pair> bounds{};

    for (size_t n = 0; n < sep.size() - 1; ++n)
    {
        auto local = std::vector<std::string>(lines.begin() + sep[n] + 1, lines.begin() + sep[n + 1]);
        std::unordered_map<Pair, bool> mirrors;

        for (size_t i = 0; i < local.size(); ++i)
        {
            for (size_t j = 0; j < local[i].length(); ++j)
            {
                if (local[i][j] == '#')
                {
                    mirrors[{static_cast<int64_t>(i), static_cast<int64_t>(j)}] = true;
                }
            }
        }

        maps.push_back(mirrors);
        bounds.push_back({static_cast<int64_t>(local.size()), static_cast<int64_t>(local[0].length())});
    }

    return {maps, bounds};
}

auto Day13::partOne(const std::string& input) -> int64_t
{
    int64_t sum = 0;
    auto [maps, bounds] = parse(input);

    for (size_t n = 0; n < maps.size(); ++n)
    {
        auto [nrows, ncols] = pointOfIncidence(maps[n], bounds[n], false);
        sum += nrows * 100 + ncols;
    }

    return sum;
}

auto Day13::part_one(const std::string& input) -> std::string
{
    auto result = partOne(input);
    // auto expectedResult{41859};
    // assert(result == expectedResult);
    return std::to_string(result);
}

auto Day13::partTwo(const std::string& input) -> int64_t
{
    int64_t sum = 0;
    auto [maps, bounds] = parse(input);

    for (size_t n = 0; n < maps.size(); ++n)
    {
        auto [nrows, ncols] = pointOfIncidence(maps[n], bounds[n], true);
        sum += nrows * 100 + ncols;
    }

    return sum;
}

auto Day13::part_two(const std::string& input) -> std::string
{
    auto result = partTwo(input);
    // auto expectedResult{30842};
    // assert(result == expectedResult);
    return std::to_string(result);
}
