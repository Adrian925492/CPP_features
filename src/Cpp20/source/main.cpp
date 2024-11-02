#include <constant_expressions.hpp>
#include <move_semantic.hpp>

#include <iostream>

int main(void)
{
    std::cout << "CPP20 features \n\n";

    constexpr_main();
    move_main();
}