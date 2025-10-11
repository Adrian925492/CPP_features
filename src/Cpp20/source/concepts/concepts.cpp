#include "concepts.hpp"

#include <iostream>
#include <cstdint>
#include <concepts>

#include <vector>
#include <iterator>

//Some part of default concepts are provided by std lib. Full list of concepts that are able to be used are in https://en.cppreference.com/w/cpp/concepts.

//Example struct using default defined in std

//same - as
template <std::same_as<uint32_t> T>
struct SameAsU32 {
    T a;
};

//Convertibel to float
template <std::convertible_to<float> T>
struct ConvertibleToFloat {
    T a;
};

//Common type - The concept common_with<T, U> specifies that two types T and U share a common type (as computed by std::common_type_t) to which both can be converted.
template <std::common_with<int> T>
struct HasCommonType {
    T a;
};

//Common reference - specifies that two types share a common reference type
template <std::common_reference_with<int> T>
struct HasCommonRef {
    T a;
};

//Can be assigned from other type
template <std::assignable_from<int> T>
struct AssignableFromInt {
    T a;
};

//Can be swapped with other type (can also use std::swapable_with<T> - checks if type is swapable with given type.)
template <std::swappable T>
struct SwappableT {
    T a;
};

//For constructors and destructors - checks if is destructible, copy constructible by int and can be default initialized.
template <typename T>
requires std::destructible<T> && std::constructible_from<T, int> && std::default_initializable<T>
struct ConstructDestructConcept {
    T a;
};

//For constructors and 2 template args - if is move and copy constructible
template <typename T, typename W>
requires std::move_constructible<T> && std::copy_constructible<W>
struct MoveAndCopyConstructible {
    T a;
    W b;
};

//For integral and fractional  type (non fraction)
template<std::integral T>
struct Integral {
    T a;
};

template<std::unsigned_integral T>
struct IntegralUnsigned {
    T a;
};

template<std::signed_integral T>
struct IntegralSigned {
    T a;
};

template<std::floating_point T>
struct Floating {
    T a;
};

//Example struct using default defined in std callable predictate concept
template <typename T>
requires std::predicate<T, int>
struct Predictate {
    T pred;
};

struct Pred {
    bool operator() (int x) {
        return static_cast<bool>(x);
    }
};

//Own concept
template <typename T>
concept NotAPointer = !std::is_pointer_v<T>;

template <typename T>
concept HasFooMethod = requires(T some_type, int x) {
    {some_type.foo(x)} -> std::same_as<int>; //Has callable foo(int) that returns void.
};

template <NotAPointer T>
requires HasFooMethod<T> 
struct MyClass
{
    T cls;
};

struct HasFooBar {
    int foo(int x)
    {
        return x;
    }

    int bar()
    {
        return 112;
    }
};

//In-place comcept - possible, but BAD PRACTICE
template <typename T>
requires requires(T type) { {type.bar()}; } //Checks if type T has method foo()
struct InPlaceConcept {
    T cls;
};

//Concept example - checks if type is container
template <typename S>
concept IsContainer = requires(S _s) {
    { _s.begin() } -> std::input_or_output_iterator;
    { _s.end() } -> std::input_or_output_iterator;
   
};

template <IsContainer T>
struct Cont {
    T _cont{};
};

//Function concept based overload - we provide 2 implementations of tempalte functions fcn1 with 2 diferrent concepts.
template <std::same_as<uint32_t> T>
int fcn1(T x)
{
    std::cout << "u32: ";
    return static_cast<int>(x);
}

template <std::same_as<uint16_t> T>
int fcn1(T x)
{
    std::cout << "u16: ";
    return static_cast<int>(x);
}


void concepts_main()
{
    std::cout << "-------- Concepts --------\n";
    int x{3};
    std::cout << "Default concepts: Only uint32_t: " << SameAsU32<uint32_t>{42}.a << "\n";
    std::cout << "Default concepts: Convertible to float: " << ConvertibleToFloat<double>{42.22}.a << "\n";
    std::cout << "Default concepts: Common type is int: " << HasCommonType<long int>{6}.a << "\n";
    std::cout << "Default concepts: Common ref is int&: " << HasCommonType<long int>{6}.a << "\n";
    std::cout << "Default concepts: Assignable from int: " << AssignableFromInt<int&>{x}.a << "\n";
    std::cout << "Default concepts: Swappable: " << SwappableT<float>{2.22}.a << "\n";
    std::cout << "Default concepts: Integral: " << Integral<int>{4}.a << "\n";
    std::cout << "Default concepts: Integral unsigned: " << IntegralUnsigned<unsigned long>{4}.a << "\n";
    std::cout << "Default concepts: Integral signed: " << IntegralSigned<int16_t>{-42}.a << "\n";
    std::cout << "Default concepts: Floating: " << Floating<float>{-4.23}.a << "\n";
    std::cout << "Default concepts: Constructible default or by int, destructible: " << ConstructDestructConcept<unsigned int>{23}.a << "\n";
    std::cout << "Default concepts: Move and copy constructible, 2 template params: " << MoveAndCopyConstructible<unsigned int, int8_t>{23, 12}.a << "\n";

    std::cout << "Default concepts: Is predictate: " << Predictate<Pred>{}.pred(2) << "\n";

    std::cout << "Own concept - checks if type is not a pointer and has callable foo method " << MyClass<HasFooBar>{}.cls.foo(23) << "\n";
    std::cout << "Own in-place concept - checks if type has callable foo method " << InPlaceConcept<HasFooBar>{}.cls.bar() << "\n";
    
    std::cout << "Own concept - checks if type is a container " << Cont<std::vector<int>>{{1, 2, 3}}._cont.at(0) << "\n";

    uint16_t u16{16};
    uint32_t u32{32};
    std::cout << "Concept overload: fcn1() for uint16_t " << fcn1(u16) << " and for uint32_t " << fcn1(u32) << "\n";
}