/* This file contains all recepies regarding STL traits classes (chrono, optional, tuple, smart pointers, random) */

#include <iostream>
#include <chrono>
#include <ratio>
#include <cmath>
#include <iomanip>
#include <optional>

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

void traits_example()
{
    cout << "Traits example! \n\n";

    chrono_with_ratio();
}
