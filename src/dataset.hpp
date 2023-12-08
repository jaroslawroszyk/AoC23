#include <cassert>
#include <format>
#include <fstream>
#include <string>

namespace dataset
{

inline auto load_input(int day) -> std::string
{
    auto zero = (day < 10 ? "0" : "");
    auto path = "../dataset/inputs/puzzle08.txt";
    // auto path = "../dataset/inputs/puzzle04.txt";

    auto f = std::ifstream(path);
    return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

inline auto load_example(int day) -> std::string
{
    auto zero = (day < 10 ? "0" : "");
    // auto path = std::format("../dataset/examples/day{}{}.txt", zero, day);
    auto path = "../dataset/examples/day08.txt";

    auto f = std::ifstream(path);
    return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

inline auto load(int day, bool example) -> std::string
{
    return example ? load_example(day) : load_input(day);
}
}; // namespace dataset
