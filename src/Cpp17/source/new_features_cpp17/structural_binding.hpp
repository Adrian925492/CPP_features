/* Structural binding

In other languages it it names unpacking. Structural binding is semantic issue, that allows
to explicitly give names of variables for elements returned from method as pair, array, c-style array, structure or tuple.

Using structural binding produces more human readable code.

Syntax:

Assume that foo returns std::pair<int,int>

auto [element1, element2] = foo();

and now we have access to pair elements like it would be standard variable, like:
element1 = ...
cout << element 2

Restrictions:
-> In the brackets, You have to apply exactly as many elements as the function returns. If not, compiler will give an error.
-> In case of structure, no element can be static, and all ements has to be defined in the same base class. 
    First declared element  in the structure will be assigned to first variable, second to second etc.
-> The type of syntax can be auto, const auto, const auto& or const auto && (no any other)

It is an example of syntatic sugar

Curiosities:
-> In modern compilers we have feature line RVO - return value optimization, which prevents from
coping variable returned by method/function if we assign it to, for ex. a variable (like in that example). Instead of that, compiler
will assign the variable content directly, and we have not to worry about copying (efficiency).

*/

#include <iostream>
#include <utility>
#include <list>
#include <tuple>

// EXAMPLE 1: pair

std::pair<int, int> divide_reminder(int divident, int divisior);

std::pair<int, int> divide_reminder(int divident, int divisior)
{
    return std::make_pair<int, int>(divident/divisior, divident%divisior);
}

// EXAMPLE 2: tuple

std::tuple<std::string, int> get_ages();

std::tuple<std::string, int> get_personal_info()
{
    return std::make_tuple("Adam", 22);
}

// EXAMPLE 3: structure

typedef struct data{
    std::string name;
    int age;
    int salary;
}data_t;

using namespace std;

void structural_binding_example()
{
    cout << "Structural binding example\n\n";
    
    // Old - style binding
    auto result = divide_reminder(16, 3);
    auto result2 = get_personal_info();
    data_t employee{"marek", 40, 2000};

    cout << "1. Old style: \n\n";
    cout << "Division 16/6 gives: " << result.first << " and rest of " << result.second << "\n";
    cout << "Name is: " << get<0>(result2) << " and age is: " << get<1>(result2) << "\n";  
    cout << "Employee name is: " << employee.name << " age is: " << employee.age << " and salary is: " << employee.salary << "\n";

     // New - style binding
    auto [fraction, remainder] = divide_reminder(16, 3);        // pair
    auto [name, age] = get_personal_info();                     // tuple
    auto [e_name, e_age, e_salary] = employee;                  // Struct

    cout << "2. New style: \n\n";
    cout << "Division 16/6 gives: " << fraction << " and rest of " << remainder << "\n";   
    cout << "Name is: " << name << " and age is: " << age << "\n";  
    cout << "Employee name is: " << e_name << " age is: " << e_age << " and salary is: " << e_salary << "\n"; 


}

