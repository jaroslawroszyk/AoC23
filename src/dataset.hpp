#include <cassert>
#include <fstream>
#include <string>

namespace dataset
{
auto input(int day, bool example) -> std::string
{
    assert(day > 0 and day < 26);

    auto path = std::string("../dataset/");
    path += example ? "example" : "puzzle";
    path += (day < 10 ? "0" : "") + std::to_string(day) + ".txt";

    auto file = std::ifstream(path);
    if (not file.is_open())
    {
        std::cerr << "Unable to open file: " << path << std::endl;
        return "";
    }

    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}
}; // namespace dataset
