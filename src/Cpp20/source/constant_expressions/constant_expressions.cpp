#include <cstddef>
#include <array>
#include <iostream>

//Standard compile-time constexpr literal type [c++11]
constexpr size_t array_size = 6;

//constexpr function [c++11]
constexpr size_t is_size_ok(size_t s)
{
    if (s > 5)
        return 5;
    return s;
}

//constexpr class [c++17]
class ArraySize {
public:
    constexpr ArraySize(size_t s) : _s(s) {}
    constexpr size_t get_size() {
        return _s;
    }
private:
    int _s;
};



void constexpr_main() {
    std::cout << "Constant expressions \n";

    std::cout << "Standard const expressions: " << array_size << "\n";
}