/* This file contains all recepies regarding STL traits classes (chrono, optional, tuple, smart pointers, random) */

#include <iostream>
#include <chrono>
#include <ratio>
#include <cmath>
#include <iomanip>
#include <optional>
#include <tuple>

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

void traits_example()
{
    cout << "Traits example! \n\n";

    chrono_with_ratio();

    using_chrono();

    optional_example();

    tuple_exampel();
}
