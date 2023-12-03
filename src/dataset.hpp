#include <cassert>
#include <fstream>
#include <string>
#include <format>
namespace dataset
{

inline auto load_input(int day) -> std::string {
    auto zero = (day < 10 ? "0" : "");
    auto path = std::format("../dataset/inputs/puzzle{}{}.txt", zero, day);

    auto f = std::ifstream(path);
    return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

inline auto load_example(int day) -> std::string {
    auto zero = (day < 10 ? "0" : "");
    auto path = std::format("../dataset/examples/day{}{}.txt", zero, day);

    auto f = std::ifstream(path);
    return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

inline auto load(int day, bool example) -> std::string {
    return example ? load_example(day) : load_input(day);
}
}; // namespace dataset
