#include <constant_expressions.hpp>
#include <move_semantic.hpp>
#include <multilang_string.hpp>
#include <spaceship.hpp>
#include <modules.hpp>
#include <concepts.hpp>
#include <idioms.hpp>

#include <iostream>

int main(void)
{
    std::cout << "CPP20 features \n\n";

    constexpr_main();
    move_main();
    multilang_string_main();
    spaceship_main();
    modules_main();
    concepts_main();
    idioms_main();
}