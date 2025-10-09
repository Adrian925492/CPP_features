/* In cpp17 we have ability to leave deduction of template arguments basing on constructor types given.

For example, if we want to use pari, in old standards we would have to instantiate it by

std::pair<int, float> a(2, 3.14);

With givinf int and float types explicitly.

From cpp17 we can leave it to automatic deduction, like:

std::pair a(2, 3.14) without need to give template arguments.

If a class has to be able to use it, it has to have construtor that 
will use all template types, like

template <typename X, typename Y>
class A {
    A(X x, Y y) {...}
}

so the compiler would be able to deduct all template types from types of variables given to the constructor.

! Sometimes we cannot use it, for example, when we have some implicit constraint for input types.

Let assuem we have to add elements of variadic templates. Here, we have implicit assumption, that 
all elemens has to be implicitly castable to one of the types. Output type is explicitly given by template. 

However, if we want to still use automatic type deduction we can use construction:

template<typename T...>
sum(Ts&& .. ts) -> sum<std::common_type_t<Ts ...>>;

common_type_t will deduct common type of arguments givet (Ts ...) for us, and here e can still use auto type deduction.

*/

#include <iostream>
#include <utility>

using namespace std;

// Auto type deduction example

// With that we cannoct use auto typing:
template <typename T>
struct sum {
    T value;

    template <typename ... Ts>
    sum(Ts&& ... values) : value{(values + ...)} {}         //fold used in constructor
};

template <typename ... Ts>
sum(Ts&& ... ts) -> sum<std::common_type_t<Ts...>>;         // Special syntax - to tell compiler explicitly how to deduct type

void automatic_template_types_deduction_example()
{
    cout << "Automatic template types deduction example! \n\n";

    pair<int, float> A(1, 2.13);    //Old style
    pair B(2, 4.14);                //Cpp17 style

    cout << "with given std::pair<int, float> with old init style we get elements: [ " << A.first << " " << A.second << " ] \n";
    cout << "with given std::pair with init new style we get elements: [ " << B.first << " " << B.second <<" ] \n\n";


    sum<int> S(1, 2.13, 3);     //Here ouput type is explicitly given
    cout << "sum with explicit type of 1 + 2.13 + 3 is: " << S.value << endl;

    sum M(1, 2.13, 3);     //Here ouput type is explicitly given
    cout << "sum with explicit type of 1 + 2.13 + 3 is: " << S.value << endl;

}
