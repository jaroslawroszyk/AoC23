#include "include/day14.hpp"
#include <cassert>
#include "utilities.hpp"

auto Day14::parse(const std::string& input) -> Grid<char>
{
    auto lines = utils::lines(input);
    return Grid<char>(lines);
}

auto Day14::load(const Grid<char>& grid) -> int64_t
{
    int64_t load = 0;

    for (int64_t x = 0; x < grid.width(); ++x)
    {
        for (int64_t y = 0; y < grid.height(); ++y)
        {
            Point p(x, y);
            if (grid(p.x, p.y) == 'O')
            {
                load += grid.height() - y;
            }
        }
    }

    return load;
}

auto Day14::north(Grid<char>& grid) -> void
{
    for (int x = 0; x < grid.width(); ++x)
    {
        int fixed = 0;

        for (int y = 0; y < grid.height(); ++y)
        {
            if (grid(x, y) == 'O')
            {
                if (y > fixed)
                {
                    grid(x, y) = '.';
                    grid(x, fixed) = 'O';
                }
                fixed += 1;
            }
            else if (grid(x, y) == '#')
            {
                fixed = y + 1;
            }
        }
    }
}

auto Day14::west(Grid<char>& grid) -> void
{
    for (int y = 0; y < grid.height(); ++y)
    {
        int fixed = 0;

        for (int x = 0; x < grid.width(); ++x)
        {
            if (grid(x, y) == 'O')
            {
                if (x > fixed)
                {
                    grid(x, y) = '.';
                    grid(fixed, y) = 'O';
                }
                fixed += 1;
            }
            else if (grid(x, y) == '#')
            {
                fixed = x + 1;
            }
        }
    }
}

auto Day14::south(Grid<char>& grid) -> void
{
    for (int x = 0; x < grid.width(); ++x)
    {
        int fixed = grid.height() - 1;

        for (int y = grid.height() - 1; y >= 0; --y)
        {
            if (grid(x, y) == 'O')
            {
                if (y < fixed)
                {
                    grid(x, y) = '.';
                    grid(x, fixed) = 'O';
                }
                fixed -= 1;
            }
            else if (grid(x, y) == '#')
            {
                fixed = y - 1;
            }
        }
    }
}

auto Day14::east(Grid<char>& grid) -> void
{
    for (int y = 0; y < grid.height(); ++y)
    {
        int fixed = grid.width() - 1;

        for (int x = grid.width() - 1; x >= 0; --x)
        {
            if (grid(x, y) == 'O')
            {
                if (x < fixed)
                {
                    grid(x, y) = '.';
                    grid(fixed, y) = 'O';
                }
                fixed -= 1;
            }
            else if (grid(x, y) == '#')
            {
                fixed = x - 1;
            }
        }
    }
}

auto Day14::findCycle(Grid<char>& grid) -> std::pair<int, int>
{
    seen.insert({grid, 0});

    int64_t start{};
    int64_t end{};
    do
    {
        north(grid);
        west(grid);
        south(grid);
        east(grid);

        auto it = seen.find(grid);
        if (it != seen.end())
        {
            start = it->second;
            end = seen.size();
            break;
        }
        else
        {
            seen.insert({grid, seen.size()});
        }
    } while (true);

    return {start, end};
}

auto Day14::part1(Grid<char>& input) -> int64_t
{
    Grid<char> grid = input;

    // North
    for (int64_t x = 0; x < grid.width(); ++x)
    {
        for (int64_t y = 0; y < grid.height(); ++y)
        {
            Point p(x, y);
            if (grid(p.x, p.y) == 'O')
            {
                int64_t newY = y;
                while (newY > 0)
                {
                    if (grid(p.x, newY - 1) == '.')
                    {
                        grid(p.x, newY - 1) = 'O';
                        grid(p.x, newY) = '.';
                        newY -= 1;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    return load(grid);
}

auto Day14::part_one(const std::string& input) -> std::string
{
    Grid<char> inputGrid = parse(input);
    int64_t result = part1(inputGrid);

    auto expectedResult{107053};
    assert(result == expectedResult);
    return std::to_string(result);
}

auto Day14::part2(Grid<char>& grid) -> int64_t
{
    auto [start, end] = findCycle(grid);
    int64_t last = (1'000'000'000 - start) % (end - start) + start;
    auto it = std::find_if(seen.begin(), seen.end(), [last](const auto& entry) { return entry.second == last; });

    return load(it->first);
}

auto Day14::part_two(const std::string& input) -> std::string
{
    Grid<char> inputGrid = parse(input);
    int64_t result = part2(inputGrid);

    auto expectedResult{88371};
    assert(result == expectedResult);
    return std::to_string(result);
}
