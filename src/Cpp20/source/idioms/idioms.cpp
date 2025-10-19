#include "idioms.hpp"
#include <iostream>
#include <utility> // for std::swap
#include <vector>
#include <concepts>
#include <ranges>
#include <functional> // for std::invoke
#include <tuple>
#include <variant>
#include <array>
#include <memory>

//1. RAII idiom - usage of constructors and destructors to manage resource allocation and deallocation. Based on calling destructor automatically when an object goes out of scope.
class RAII {
public:
    RAII() { std::cout << "Resource acquired\n"; }
    ~RAII() { std::cout << "Resource released\n"; }
};

void raii_example() {
    {
        std::cout << "1. RAII example:\n";
        RAII resource; // Resource is acquired here
    } // Resource is released automatically when going out of scope
}

//2. Non-copyable idiom - prevent copying of objects by deleting copy constructor and copy assignment operator.
class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete; // Delete copy constructor
    NonCopyable& operator=(const NonCopyable&) = delete; // Delete copy assignment
    NonCopyable(NonCopyable&&) = default; // Allow move constructor
    NonCopyable& operator=(NonCopyable&&) = default; // Allow move assignment
};

void non_copyable_example() {
    std::cout << "2. Non-Copyable example:\n";
    NonCopyable obj1;
    // NonCopyable obj2 = obj1; // Error: copy constructor is deleted
    NonCopyable obj3 = std::move(obj1); // OK: move constructor is allowed
};

//3. Hidden friend idiom - allows a class to declare another class or function as a friend without exposing the friendship in the public interface.
class HiddenFriend {
public:
    int value;
    HiddenFriend(int v) : value(v) {}
private:
    friend void reveal_value(const HiddenFriend& hf);   // Declare friend function - as private.
};

void reveal_value(const HiddenFriend& hf) {     // Friend function definition - out of scope of class
    std::cout << "HiddenFriend value: " << hf.value << std::endl;
}

//ADL usage example - Argument Dependent Lookup
// When a function is called, the compiler looks for the function in the namespaces of its arguments
// This is useful for operator overloading and functions that are closely related to a class
// In this example, reveal_value is found via ADL because it is a friend of HiddenFriend.

//ADL will look for function in following order:
//1. Global namespace
//2. Namespace of the class of the first argument (if any)
//3. Namespace of the class of the second argument (if any)
//... and so on for all arguments
//In case of swap function, if we use using std::swap; inside the function, it will first look for swap in the namespace of the arguments (which could be a custom swap function for that type), and if not found, it will fall back to std::swap.

class CustomType; // Forward declaration for ADL example

//Example of simple array class with usage of HiddenFriend idiom.
template <typename T>
class Array {
public:
    Array(T* array, int size) : array_{array}, size_{size} {}  //Constructor
    ~Array() { delete[] array_; }  //Destructor

    T& operator[](int index) { return array_[index]; }  //Indexing operator
    int size() const { return size_; }  //Size getter

    friend void swap(Array& a1, Array& a2) noexcept {  //Friend function to swap two arrays
        using std::swap; //Enable ADL for swap function - in case T has a custom swap implementation that should be used. Otherwise, in next lines std::swap would be used.
        std::swap(a1.array_, a2.array_);
        std::swap(a1.size_, a2.size_);
    }

private:
    T* array_;
    int size_;
};

class CustomType {
public:
    CustomType(int v) : value(v) {}
    int getValue() const { return value; }

    friend void swap(CustomType& c1, CustomType& c2) { //Custom swap function for CustomType
        std::cout << "Custom swap called\n";
        std::swap(c1.value, c2.value);
    }

private:
    int value;
};

void array_usage_example() {
    std::cout << "Array usage example with ADL and Hidden Friend idiom:\n";
    Array<int> arr1(new int[3]{1, 2, 3}, 3);
    Array<int> arr2(new int[3]{4, 5, 6}, 3);

    std::cout << "Before swap:\n";
    for (int i = 0; i < arr1.size(); ++i) {
        std::cout << arr1[i] << " "; // Outputs: 1 2 3
    }
    std::cout << std::endl;
    for (int i = 0; i < arr2.size(); ++i) {
        std::cout << arr2[i] << " "; // Outputs: 4 5    6
    }
    std::cout << std::endl; 
    swap(arr1, arr2); // Calls the friend swap function

    std::cout << "After swap:\n";
    for (int i = 0; i < arr1.size(); ++i) {
        std::cout << arr1[i] << " "; // Outputs: 4 5 6
    }
    std::cout << std::endl;
    for (int i = 0; i < arr2.size(); ++i) {
        std::cout << arr2[i] << " "; // Outputs: 1 2 3
    }
    std::cout << std::endl;

    std::cout << "Array with CustomType and custom swap usage example:\n";
    Array<CustomType> carr1(new CustomType[2]{CustomType(1), CustomType(2)}, 2);
    Array<CustomType> carr2(new CustomType[2]{CustomType(10), CustomType(20)}, 2);
    std::cout << "Before swap:\n";
    for (int i = 0; i < carr1.size(); ++i) {
        std::cout << carr1[i].getValue() << " "; // Outputs: 1 2
    }
    std::cout << std::endl;
    for (int i = 0; i < carr2.size(); ++i) {
        std::cout << carr2[i].getValue() << " "; // Outputs: 10 20
    }
    std::cout << std::endl;

    swap(carr1, carr2); // Calls the friend swap function, which in turn calls CustomType's custom swap
    std::cout << "After swap:\n";
    for (int i = 0; i < carr1.size(); ++i) {
        std::cout << carr1[i].getValue() << " "; // Outputs: 10 20
    }
    std::cout << std::endl;
    for (int i = 0; i < carr2.size(); ++i) {
        std::cout << carr2[i].getValue() << " "; // Outputs: 1 2
    }
    std::cout << std::endl;

    std::cout << "Custom type swap example:\n";
    CustomType ct1(100);
    CustomType ct2(200);
    std::cout << "Before swap: ct1 = " << ct1.getValue() << ", ct2 = " << ct2.getValue() << std::endl;
    swap(ct1, ct2); // Calls CustomType's custom swap
    std::cout << "After swap: ct1 = " << ct1.getValue() << ", ct2 = " << ct2.getValue() << std::endl;
}

void hidden_friend_example() {
    std::cout << "3. Hidden Friend idiom example:\n";
    HiddenFriend hf(42);
    reveal_value(hf); // Accessing private member via friend function
    array_usage_example();
}

//4. Copy - and-swap idiom - provides strong exception safety by implementing copy assignment operator using copy constructor and a swap function.

template <typename T>
class Array_2 {
public:
    Array_2(T* array, int size) : array_{array}, size_{size} {}  //Constructor
    ~Array_2() { delete[] array_; }  //Destructor

    Array_2(const Array_2& other) : array_{new T[other.size_]}, size_{other.size_} { //Copy constructor - follow rule of 5
        for (int i = 0; i < size_; ++i) {
            array_[i] = other.array_[i];
        }
    }

    Array_2(Array_2&& other) noexcept : array_{other.array_}, size_{other.size_} { //Move constructor - follow rule of 5
        other.array_ = nullptr;
        other.size_ = 0;
    }

    T& operator[](int index) { return array_[index]; }  //Indexing operator
    int size() const { return size_; }  //Size getter

    friend void swap(Array_2& a1, Array_2& a2) noexcept {  //Friend function to swap two arrays
        using std::swap; //Enable ADL for swap function - in case T has a custom swap implementation that should be used. Otherwise, in next lines std::swap would be used.
        std::swap(a1.array_, a2.array_);
        std::swap(a1.size_, a2.size_);
    }

    Array_2& operator=(Array_2 other) noexcept {  //Copy-and-swap idiom - handles copy and move assignment operators at once. Provides exception free level of safety.
        swap(*this, other); //Swap the contents
        return *this;
    }

private:
    T* array_;
    int size_;
};

void copy_and_swap_example() {
    std::cout << "4. Copy-and-Swap idiom example:\n";
    Array_2<int> arr1(new int[3]{1, 2, 3}, 3);
    Array_2<int> arr2(new int[3]{4, 5, 6}, 3);

    std::cout << "Before assignment:\n";
    for (int i = 0; i < arr1.size(); ++i) {
        std::cout << arr1[i] << " "; // Outputs: 1 2 3
    }
    std::cout << std::endl;
    for (int i = 0; i < arr2.size(); ++i) {
        std::cout << arr2[i] << " "; // Outputs: 4 5 6
    }
    std::cout << std::endl;

    arr1 = arr2; // Uses copy-and-swap idiom

    std::cout << "After assignment:\n";
    for (int i = 0; i < arr1.size(); ++i) {
        std::cout << arr1[i] << " "; // Outputs: 4 5 6
    }
    std::cout << std::endl;
}

//5. Nebloids - a way to create function objects that can be used like regular functions, often used in conjunction with templates and type deduction.
// Example: A simple nebloid that adds two values

//Standard add function (defined in equivalent of std namespace)
namespace myStd {
    class A{};
    class B{};
    template <typename T>
    void add(T&a, T&b) {
        std::cout << "Standard add() called\n";
    }
}

//Range add function (defined in equivalent of std::ranges namespace)
namespace myRanges {
    namespace addImpl {
        struct _add {
            template <typename T, typename = std::enable_if_t< std::is_same<T, myStd::A>::value >>
            void operator()(T& a, T& b) const {
                std::cout << "MyRange add() called\n";
            }
        };
    }
    inline constexpr addImpl::_add add{};    //Nebloid example
}

void standard_nebloid() {
    std::cout << "Standard nebloid example:\n";

    myStd::A a, b;  //Explicit give type of argument
    add(a, b);      //Calls myStd::add

    using namespace myRanges;   //Brings myRanges::add into scope - ADL is not used as a, b are type from myStd
    myStd::A c, d;
    add(c, d);      //Calls myRanges::add
}

//Example of usage of concepts and nebloids to create a contains function that checks if a value exists in a range. Supports std::ranges.
namespace detail {
    struct contains_fn final {  //Final type - informs compiler that this type will not be inherited from. Helps with optimization.

        //std::identity - a projection that returns its argument unchanged. Useful as a default projection.
        //std::indirect_binary_predicate - concept that checks if a binary predicate can be applied to the results of two projections.
        //std::projected - a type that represents the result of applying a projection to an iterator's value type.
        //std::ranges::equal_to - a standard equality comparison function object.

        // Using C++20 concepts to constrain the template parameters. Default signature of customized point object.
        //It - input iterator type
        //Sent - sentinel type (end iterator or sentinel)
        //T - type of the value to search for
        //Proj - projection function type (defaults to identity function)
        //Function object for operation on iterators.
        template <std::input_iterator It, std::sentinel_for<It> Sent, typename T, typename Proj = std::identity>
        requires std::indirect_binary_predicate<std::ranges::equal_to, std::projected<It, Proj>, const T*>
        constexpr bool operator()(It first, Sent last, const T& value, Proj proj = {}) const 
        {
            while(first != last && std::invoke(proj, *first) != value) {
                ++first;
            }
            return first != last;
        }

        // Overload for ranges - allows passing a range directly instead of begin and end iterators.
        template <std::ranges::input_range Rng, typename T, typename Proj = std::identity>
        requires std::indirect_binary_predicate<std::ranges::equal_to, std::projected<std::ranges::iterator_t<Rng>, Proj>, const T*>
        constexpr bool operator()(Rng&& rng, const T& value, Proj proj = {}) const {
            return (*this)(std::ranges::begin(rng), std::ranges::end(rng), value, std::move(proj)); // Forward to the iterator-based overload
        }
    };
}

inline constexpr detail::contains_fn contains{}; // Inline variable - ensures single instance across translation units. Constexpr - can be evaluated at compile time. Nebloid instantioation. Explicit instantiation of contains_fn type. 
// Blocks ADL for contains function, as defined explicitly in the global namespace.

void nebloid_example() {
    std::cout << "5. Nebloid example:\n";

    standard_nebloid();

    std::cout << "Extended nebloid example:\n";
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "Contains 3 in vec {1, 2, 3, 4, 5}: " << (contains(vec, 3) ? "true" : "false") << std::endl; // Outputs: true
    std::cout << "Contains 6 in vec {1, 2, 3, 4, 5}: " << (contains(vec, 6) ? "true" : "false") << std::endl; // Outputs: false
    //Usage of contains with projection
    std::cout << "Contains 5 in vec {1, 2, 3, 4, 5} with projection (value = 5 * 2): " 
              << (contains(vec, 5, [](int v) { return 2 * v; }) ? "true" : "false") << std::endl; // Outputs: true

    //Usage with iterators
    std::cout << "Contains 4 in vec {1, 2, 3, 4, 5} using iterators: " 
              << (contains(vec.begin(), vec.end(), 4) ? "true" : "false") << std::endl; // Outputs: true
}

//6. Policy based design

struct NoPrint {
    template <typename... Args>
    void operator()(Args&&...) const {}
};

struct PrintToConsole {
    template <typename... Args>
    void operator()(Args&&... args) const {
        (std::cout << ... << args) << std::endl;
    }
};

template <typename T, typename PrintPolicy = NoPrint>
class MyClass {
public:
    MyClass() {
        PrintPolicy{}("MyClass constructor");
    }

    ~MyClass() {
        PrintPolicy{}("MyClass destructor");
    }
};

void print_example()
{
    std::cout << "6. Print example:\n";
    std::cout << "No print policy class instantiation: \n";
    MyClass<int> obj1;
    std::cout << "Print policy class instantiation: \n";
    MyClass<int, PrintToConsole> obj2;
}

// 7. CRTP - Curiously Recurring Template Pattern idiom example - a technique where a class template derives from itself instantiated with a derived class.

//Base class:
template <typename Item>
class Base {
public:
    void foo() {
        static_cast<Item*>(this)->implementation(); // Calls derived class implementation
    }
};

class Item1 : public Base<Item1> {
public:
    void implementation() {
        std::cout << "Item1 implementation\n";
    }
};

class Item2 : public Base<Item2> {
public:
    void implementation() {
        std::cout << "Item2 implementation\n";
    }
};

//CRTP idiom and organization elements in container.
//Example 1 - use tuple
//Example 2 - use std::variant type
//Exmaple 3 - use inheritance from common base class with virtual functions.

//Exmple 3:
class CommonBase {
public:
    template <typename T> requires std::is_base_of_v<Base<T>, T>
    explicit CommonBase(T&& item) : item_{std::forward<T>(item)} {}

    void foo() {
        std::visit([] <typename U> (Base<U>& arg) { arg.foo(); }, item_);
    }
private:
    std::variant<Item1, Item2> item_;
};



void crtp_container_example() {
    // Example 1 - use tuple
    std::cout << "CRTP container example using std::tuple:\n";
    std::tuple<Item1, Item2> items; //Contianier implementation
    std::apply([] <typename... T> (Base<T>... args) { (args.foo(), ...); }, items);    //Call method over container elemnts.

    // Example 2 - use std::variant type
    std::cout << "CRTP container example using std::variant:\n";
    using ItemVariant = std::variant<Item1, Item2>;
    auto items_var = std::array{ItemVariant{Item1{}}, ItemVariant{Item2{}}};
    for(const auto& el : items_var) {
        std::visit([] <typename T> (Base<T> arg) { arg.foo(); }, el);
    }

    // Example 3 - use inheritance from common base class with virtual functions.
    std::cout << "CRTP container example using common base class:\n";
    auto items3 = std::array<CommonBase, 2>{CommonBase{Item1{}}, CommonBase{Item2{}}};
    for(auto& el : items3) {
        el.foo();
    }
}

void crtp_example() {
    std::cout << "7. CRTP example:\n";
    Item1 item1;
    item1.foo(); // Calls Item1 implementation

    Item2 item2;
    item2.foo(); // Calls Item2 implementation

    crtp_container_example();
}

//8. Type erased idiom - allows storing and using objects of different types that share a common interface without exposing their concrete types. This is often achieved using a base class with virtual functions and storing pointers to the base class.

//Interface
struct TypeErasedBase {
    virtual ~TypeErasedBase() = default;
    virtual void foo() = 0;
};

//Template wrapper class that derives from TypeErasedBase
template <typename T>
class TypeErasedWrapper : public TypeErasedBase {
public:
    explicit TypeErasedWrapper(T t) : item_{std::move(t)} {}
    void foo() override {
        item_.foo();
    }
private:
    T item_;
};

//Item supporting type erasure
class ItemErasedCommon {
public:
    template <typename T>
    explicit ItemErasedCommon(T t)
        : item_{std::make_unique<TypeErasedWrapper<T>>(std::move(t))} {}
    void foo() {
        item_->foo();
    }
private:
    std::unique_ptr<TypeErasedBase> item_;  //T concrete type not used (type erased)
};

class ErasedItem1 {     //No info about common IF !
public:
    void foo() {
        std::cout << "ErasedItem1 implementation\n";
    }
};

class ErasedItem2 {     //No info about common IF !
public:
    void foo() {
        std::cout << "ErasedItem2 implementation\n";
    }
};

void type_erased_example() {
    std::cout << "Type Erased example:\n";
    auto items = std::array{ItemErasedCommon{ErasedItem1{}}, ItemErasedCommon{ErasedItem2{}}};
    for (auto& item : items) {
        item.foo();
    }
}

void idioms_main()
{
    std::cout << "------ CPP20 Idioms ------ \n\n";
    raii_example();
    non_copyable_example();
    hidden_friend_example();
    copy_and_swap_example();
    nebloid_example();
    print_example();
    crtp_example();
    type_erased_example();
    std::cout << "\n-------------------------- \n";
}