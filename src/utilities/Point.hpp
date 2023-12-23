#pragma once

#include <cstdint>

struct Point
{
    int64_t x{};
    int64_t y{};

    Point(int64_t x, int64_t y) : x(x), y(y) {}
    Point() = default;

    Point operator+(const Point& other) const { return {x + other.x, y + other.y}; }

    Point operator-(const Point& other) const { return {x - other.x, y - other.y}; }

    Point operator*(int scalar) const { return {x * scalar, y * scalar}; }

    bool operator==(const Point& other) const { return x == other.x && y == other.y; }

    bool operator!=(const Point& other) const { return !(*this == other); }

    Point add(const Point& other) const { return {x + other.x, y + other.y}; }

    Point div(int divisor) const { return {x / divisor, y / divisor}; }
};
