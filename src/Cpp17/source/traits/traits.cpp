/* This file contains all recepies regarding STL traits classes (chrono, optional, tuple, smart pointers, random) */

#include <iostream>
#include <chrono>
#include <ratio>
#include <cmath>
#include <iomanip>
#include <optional>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <any>
#include <list>
#include <variant>

#include "traits.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: Using ratio to convert between time types

/* std::ration<X, Y = 1> is a type that defines fraction value. We can use it to specify
one of chrono types (in the example duration) to have a types oh seconds (default), miliseconds and
microseconds.

chrono::duration<T, Ratio> is a type for storing period of time. T is type of value in which period will
be held (default long long int), and Ratio is a multiplicator of second (SI). For example, if we want to
have miliseconds, we have to specify type duration with ratio of std::ratio<1, 1000>.

*/

void chrono_with_ratio()
{
    cout << "Chrono with ratio example! \n\n";

    //Define time period types
    using seconds = chrono::duration<double, std::ratio<1>>; //std::ratio is optional here. It is 1 by default.
    using miliseconds = chrono::duration<double, std::ratio<1, 1000>>;
    using microseconds = chrono::duration<double, std::ratio<1, 1000000>>;

    //Get time stamp before wait (some loop)
    const auto t1 = chrono::steady_clock::now();

    string x;
    cout << "Print some data: ";
    cin >> x;

    const auto t2 = chrono::steady_clock::now();    //Get 2nd timestamp

    const auto time_elapsed = t2 - t1;

    cout << "Time in seconds: " << seconds(time_elapsed).count() << endl;
    cout << "Time in miliseconds: " << miliseconds(time_elapsed).count() << endl;
    cout << "Time in microseconds: " << microseconds(time_elapsed).count() << endl;

}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 2: Using chrono

/*
In that recepie we will use chrono libray with system clock. The time from system clock allows to
convert the results to time_t type (structure known from C). If we have that, we can easily print 
current days, hours, seconds etc.

We can also use literals to convert between subtypes (minutes, hours etc), and modify time (ex.
add minutes to hours)
*/

ostream& operator<<(ostream& os, const chrono::time_point<chrono::system_clock> &t)
{
    const auto tt (chrono::system_clock::to_time_t(t)); //System time allows to convert to time_t structure
    const auto loct (std::localtime(&tt));              
    return os << put_time(loct, "%c");      //Will print the time with standard formatting way (hh mm ss)
}

using days = chrono::duration<chrono::hours::rep, ratio_multiply<chrono::hours::period, ratio<24>>>;    //Define days type - 1 day = 24 hours

//Define _days literal
constexpr days operator ""_days(unsigned long long h)
{
    return days{h};
}

void using_chrono()
{
    cout << "Chrono example \n\n";

    // Get time stamp
    auto now = chrono::system_clock::now();

    cout << "Current time: " << now << endl;

    chrono::hours chrono_12h {12};
    cout << "12 hours later will be: " << (now + chrono_12h) << endl;

    //And with namespace chrono literals
    using namespace chrono_literals;

    cout << "12 hour and 15 min later will be: " << (now + 12h + 15min) << endl;
    cout << "A week ago was: " << (now -7_days) << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 3: Optional type example

/* From C++17 we have additional optional type. Optional can pack any type (including structs, it has
overloaded -> operator) and can stroe value of packed type or can be empty. We shaould check, before getting the value, 
if optional is not empty. If we try to get vlue of empty optional, logit_error exception will be thrown.

*/

// Define optional value of int
using oint = optional<int>;

//Helper function - will return optional value of int i
oint read_int()
{
    int i;
    if (cin >> i) {return {i};}
    return {};
}

//Helper functions additions
oint operator+(oint a, oint b)
{
    if (!a || !b) {return {};}  //If a or b is empty return none
    return *a + *b; //Else return sum of values of optionals a and b
}

//Helper functions additions
oint operator+(oint a, int b)
{
    if (!a) {return {};}  //If a or b is empty return none
    return *a + b; //Else return sum of values of optionals a and b
}
void optional_example()
{
    cout << "Optional example \n\n";

    cout << "Type 2 int numbers: ";
    auto a = read_int();
    auto b = read_int();
    auto sum (a + b + 10);

    if (sum) {
        cout << *a << " + " << *b << " + 10 = " << *sum << endl;
    }else{
        cout << "You have typed wrong numbers!" << endl;
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 4: Tuple example

/* In the recepie we will show how to use tuple for pack and unpack data */

//Helper function
static void print_student(size_t id, const string& name, double gpa)
{
    cout << "Student: " << quoted(name) << ", ID: " << id << ", GPA: " << gpa << endl;
}


void tuple_exampel()
{
    cout << "Tuple example\n\n";

    using student_t = tuple<size_t, string, double>;
    
    //Exmple 1 - just one tuple
    student_t john {123, "John", 3.7};

    {
        const auto &[id, name, gpa] = john; //Unpack single tuple
        print_student(id, name, gpa);
    }
    cout << "-------\n";

    //Example 2: collection of tuples
    auto students = {
        make_tuple(234, "Jan", 2.34),
        make_tuple(345, "Mark", 3.45),
        make_tuple(456, "Adam", 4.56)
    };

    for(const auto &[id, name, gpa] : students)
    {
        print_student(id, name, gpa);   //Iterate threw collection and print out students
    }
    cout << "-------\n";

    //And print using apply()
    for(const auto& args : students)
    {
        apply(print_student, args); //Apply will call print_students with args
    }
    cout << "-------\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 5: Tuple manipulation example

/* In takt recepie we will show advanced tricks of tupe manipulation (concat, counting min, max, average, 
printing, concat zipping)

One new method will be used: std::tuple_cat(X, Y...) which produces single tuple of tuples X, Y, ... by concating
it.

*/

//EXAMPLE 1: Printing any tuple
template<typename T, typename ...Ts>
void print_tuple(ostream& os, T& v1, Ts& ...vs)
{
    os << v1;   //Print 1st element alone (without ", ")
    (void)initializer_list<int>{((os << ", " << vs),0)...}; //Expand eaxh element of vs (...) to initialize list of elements "os << ", " << vs)"
}

template<typename ... Ts>
ostream& operator<< (ostream& os, const tuple<Ts...> &t)
{
    auto print_to_os = [&os](const auto &...xs) {
        print_tuple(os, xs...);     //That lambda will expand tuple t to elements xs and print it to stream os (we will not need to give stream name)
    };
    os << "(";
    apply(print_to_os, t);          //That will call print_to_os with tuple args
    return os << ")" << endl;
}

// EXAMPLE 2: MIN, MAX and AVERAGE of tuple
template <typename T>
tuple<double, double, double, double>
sum_min_max_ave(const T& data)
{
    auto min_max = minmax_element(data.begin(), data.end());
    auto sum = accumulate(data.begin(), data.end(), 0.0);
    return {sum, *min_max.first, *min_max.second, sum / data.size()};
}

// EXAMPLE 3: ZIP TUPLES
template<typename Ta, typename Tb>
static auto zip(const Ta& a, const Tb& b)
{
    auto z ([](auto ...xs){     //This lambda will unpack t1 tuple to elements (xs)
        return [xs...](auto ...ys) {    //This lambda will unpack t2 tuple to elements (ys)
            return tuple_cat(make_tuple(xs, ys)...);    //Here we have access to each element of t1 and t2 in variadic way
        };
    });

    return apply(apply(z, a), b);
}

void advanced_tuple_example()
{
    cout << "Advanced tuple examples \n\n";

    using student_t = tuple<size_t, string, double>;
    
    student_t john {123, "John", 3.7};
    tuple<string, string, string> header {"id", "name", "gid"};

    // Example 1 - printing tuple
    cout << "Example 1: printing tuples: \n" << header << john;

    //Exmaple 2 - min max ave elemnt
    auto i = {1.0, 2.0, 3.0, 4.0};
    cout << "Min max element of the elements {1, 2, 3, 4} [sum, min, max, ave] is: " << sum_min_max_ave(i);

    //Exmaple 3 - zipped tuple
    cout << "Ziped tuple of " << header << " and " << john << " is " << zip(header, john);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 6: Using std::any

/* From C++17 standard new type std::any was introduced to replace old style void*, used when
we want to pass argument of any type. STD::any is more safe.
*/

ostream& operator<<(ostream& os, const any& data)
{
    if(!data.has_value())
    {
        return os << "Empty value has been passed. Nothing to display. ";
    }
    else if (data.type() == typeid(string))
    {
        return os << "String passed: " << any_cast<string>(data);
    }
    else if (data.type() == typeid(int))
    {
        return os << "Int passed: " << any_cast<int>(data);
    }
    else if (data.type() == typeid(list<int>))
    {
        os << "List of ints passed: "; 
        auto l = any_cast<list<int>>(data);
        for (auto& el : l)
        {
            os << el << ", ";
        }
        return os;
    }
    else {
        return os << "Type not recognized.";
    }
}

void any_example()
{
    cout << "Std::any example \n\n";
    
    //Prepare data
    string s = "string";
    int i = 2;
    list<int> l{1, 2, 3};
    double d = 2.3;
    
    any a1(s);
    any a2(i);
    any a3(d);
    any a4(l);
    any a5{};   //Empty any

    cout << "String: " << a1 << endl;
    cout << "Int: " << a2 << endl;
    cout << "Double (not recognized): " << a3 << endl;
    cout << "List: " << a4 << endl;
    cout << "Empty any: " << a5 << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 7: Variant example

/* In the recepie we will show usage of std::variant type introduced in C++17. It can hold
elements of one of defined types (like union), but also provides mechanisms for accesing the data
and checking what exactly type of element is in variant continer. 
*/

// We will define 2 semantically similar classes, but not connected to each other (no inheritance, common interface etc.)
class cat{
    string name;
public:
    cat(string n) : name{n} {}
    void meow() const {
        cout << name << " mouws!" << endl;
    }
};

class dog{
    string name;
public:
    dog(string n) : name{n} {}
    void woof() const {
        cout << name << " woofs!" << endl;
    }
};

//We will define functor - helper for visitor 
struct animal_voice
{
    void operator() (const dog& x) {x.woof();}
    void operator() (const cat& x) {x.meow();}    
};

//Define variant type
using animal = variant<dog, cat>;

void variant_example()
{
    cout << "Variant example \n\n";

    // Define data
    list<animal> l {cat{"Cat1"}, dog{"Dog1"}, cat{"cat2"}};

    //Usage exmaple 1 - using index()
    cout << "Printing using index(): " << endl;
    for (const animal& a : l)
    {
        switch (a.index())
        {
        case 0:
            get<dog>(a).woof();
            break;
        case 1:
            get<cat>(a).meow();
        default:
            break;
        }
    }

    //Usage example 2 - using get if
    cout << "Printing using get_if(): " << endl;
    for (const animal& a : l)
    {
        if (const auto d (get_if<dog>(&a)); d)
        {
            d->woof();
        } else if (const auto c (get_if<cat>(&a)); c)
        {
            c->meow();
        }
    }   

    //Usage example 3 - using visit()
    cout << "Printing using visit(): " << endl;
    for (const animal& a : l)
    {
        visit(animal_voice{}, a);
    }   
}

void traits_example()
{
    cout << "Traits example! \n\n";

    chrono_with_ratio();

    using_chrono();

    optional_example();

    tuple_exampel();

    advanced_tuple_example();

    any_example();

    variant_example();
}
