#include <cstddef>
#include <array>
#include <iostream>

/* Constexpr - keyword saying, that the expression shall be (if can be) resolved in compile time rather than runtime.
As constexpr we can use:
- variables [since C++11]
- functions [since C++11]
- class methods, contructor [since C++17]
- inherit over classes [since C++17]

*/

//consteval function and constinit variable
constinit size_t total_max_size = 5;

consteval size_t absolute_max_size(size_t s)
{
    if (s > 20)
        return 20;
    return s;
}

//Standard compile-time constexpr literal type [c++11]
constexpr size_t array_size = 6;

//constexpr function [c++11]. Since [c++14] the functions may use local variables and loops. The cpp14 stardard also allow more than one return statements from constexpr functions (methods).
constexpr size_t is_size_ok(size_t s)
{
    if (s > total_max_size)
        return total_max_size;
    return s;
}


//constexpr class [c++17]
class ArrayMaxSize {
public:

    //Constexpr constructor
    constexpr ArrayMaxSize(size_t s) : _s(s) {}

    //Constexpr method
    constexpr size_t get_size() const          //"const" this - since C++17 the constexpr methods are not default :"const".
    {
        if (_s > max_size)
            return max_size;    
        return _s;
    }

    virtual constexpr size_t getLimit() const //"virtual" constexpr methods - valid since C++20
    {
        return max_size;
    }
private:
    const size_t _s;                           //Member variable const
    constexpr static size_t max_size = 5;      //Constexpr member variable shall be static! - only statically instantiated can be constexpr.
};

//Constexpr inheritance
class ArrayMinMaxSize : public ArrayMaxSize
{
public:
    //Constexpr constructor
    constexpr ArrayMinMaxSize(size_t s) : _s(s), ArrayMaxSize(_s) {}

    //Constexpr method
    constexpr size_t get_size() const          //"const" this - since C++17 the constexpr methods are not default :"const".
    {
        if (_s < min_size)
            return min_size;
        return ArrayMaxSize::get_size();
    }

    virtual constexpr size_t getLimit() const //"virtual" constexpr methods - valid since C++20
    {
        return min_size;
    }
private:
    const size_t _s;
    constexpr static size_t min_size = 1;
};

void constexpr_main() {
    std::cout << "-------- Constant expressions --------\n";

    //COnstexpr lambda [since C++20]
    constexpr auto arraySize_l = [](){
        return 14;
    };

    std::cout << "Standard const expressions: " << array_size << "\n";
    std::cout << "Consteval method call: " << absolute_max_size(128) << "\n";
    std::cout << "Constexpr function: " << is_size_ok(14) << "\n";
    std::cout << "Class constant expression: " << ArrayMaxSize{4}.get_size() << "\n";
    std::cout << "Inherrited class constant expression: " << ArrayMinMaxSize{4}.get_size() << "\n";
    std::cout << "Constexpr lambda: " << arraySize_l() << "\n";
    std::cout << "Constexpr virtual methods: classA: " << ArrayMaxSize{4}.getLimit() << " classB: " << ArrayMinMaxSize{4}.getLimit() << "\n";
}