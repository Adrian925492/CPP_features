#include "spaceship.hpp"

#include <iostream>
#include <string>
#include <compare>

//Example of default spaceship operator
class A {
public:

    auto operator<=>(const A&) const = default;

    int x1{};
    float f1{};
    std::string s1{};
};

//Own implementation of spaceship operator
class B : public A {
public:
    std::strong_ordering operator<=>(const B& obj) const {
        if (f1 < obj.f1) {
            return std::strong_ordering::less;
        }
        if (f1 > obj.f1) {
            return std::strong_ordering::greater;
        }
        return std::strong_ordering::equal;
    }
};

void spaceship_main() {
    std::cout << "--------- Spaceship ---------\n";

    auto res = (A{1, 1.0, "b"} <=> A{1, 1.1, "b"});
    std::cout << "Default spaceship: A{1, 1.0, b} less A{1, 1.1, b} " << (res == std::strong_ordering::less) << "\n";
    std::cout << "Default spaceship: generate sub-operator < A{1, 1.0, b} < A{1, 1.1, b} " << (A{1, 1.0, "b"} < A{1, 1.1, "b"}) << "\n";
    std::cout << "User defined spaceship:compare only 2nd argument < B{2, 1.0, b} < B{1, 1.1, b} " << (B{2, 1.0, "b"} < B{1, 1.1, "b"}) << "\n";
}