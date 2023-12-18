#pragma once
#include "../Puzzle.hpp"

using namespace std;

template <typename T>
struct GridHash;

template <typename T>
class Grid
{
public:
    explicit Grid(const std::vector<std::string>& lines)
    {
        std::transform(
            lines.begin(),
            lines.end(),
            std::back_inserter(data),
            [](const auto& line) { return std::vector<T>(line.begin(), line.end()); });
    }
    T& operator()(int64_t x, int64_t y) { return data[y][x]; }
    const T& operator()(int64_t x, int64_t y) const { return data[y][x]; }
    auto operator==(const Grid<T>& other) const -> bool { return data == other.data; }
    auto operator!=(const Grid<T>& other) const -> bool { return !(*this == other); }

    auto getData() const -> const std::vector<std::vector<T>>& { return data; }
    auto width() const -> int64_t { return data.empty() ? 0 : data[0].size(); }
    auto height() const -> int64_t { return data.size(); }

private:
    std::vector<std::vector<T>> data;
};

template <>
struct GridHash<char>
{
    auto operator()(const Grid<char>& grid) const -> size_t
    {
        size_t result = 0;
        for (const auto& row : grid.getData())
        {
            for (const auto& elem : row)
            {
                result ^= std::hash<char>()(elem) + 0x9e3779b9 + (result << 6) + (result >> 2);
            }
        }
        return result;
    }
};

struct Day14 : Puzzle
{
public:
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;

private:
    std::unordered_map<Grid<char>, int64_t, GridHash<char>> seen;
    auto parse(const std::string&) -> Grid<char>;
    auto load(const Grid<char>&) -> int64_t;
    auto findCycle(Grid<char>& input) -> std::pair<int, int>;

    auto north(Grid<char>& grid) -> void;
    auto west(Grid<char>& grid) -> void;
    auto south(Grid<char>& grid) -> void;
    auto east(Grid<char>& grid) -> void;

    auto part1(Grid<char>&) -> int64_t;
    auto part2(Grid<char>&) -> int64_t;
};
