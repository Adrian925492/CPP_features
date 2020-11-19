/* This file contains all examples regarding iterators */

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include "iterators.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: Creating own iterable range

/* In STL the iterator is a kid of stndard interface. If we want to have more generic way of
    iterate threw some container / data structure, it is good to use benefits from STL iterators.

    Do do that, we would have to implement iterator class, which will allow access to the user defines
    container. The iterator class, in miniml, has to implement operators:
    * - for dereference, returning value pointed by iterator
    != - to check if iterators are not equal
    And set of increment / decrement operators depending of type of iterator.

    Such created iterator can than be used just like stl - proided, but not for all algorithms.
    Some algorithms needs more information about the iterator. To provide that - see recepie 2.

    Example:
    */

// User defined iterator example
class num_iterator{
    public:
        int counter;
        explicit num_iterator(int initial_position = 0) : counter(initial_position) {}
        
        // Dereference operator if the iterator
        int operator* ()
        {
            return counter;
        }

        // Inequality operator
        bool operator != (const num_iterator& it) const
        {
            return counter != it.counter;
        }

        // As it is forward iterator - increment operator
        num_iterator& operator++ ()
        {
            counter++;
            return *this;
        }

        // Just for recepie 2 - we have to also define == operator
        bool operator== (const num_iterator& it) const
        {
            return counter == it.counter;
        }
};

// User defined data structure definition - that will use user defined iterator
class num_range{
    int a, b;
    public:
    num_range(int from, int to) : a(from), b(to) {}

    // We need to define begin() and end() methods, as for STL - returning proper iterators
    num_iterator begin() const
    {
        return num_iterator(a);
    }
    num_iterator end() const
    {
        return num_iterator(b);
    }
};

// And example of usage
void iterable_range_example()
{
    cout << "Iterable range example \n\n";
    cout << "Print range 1 to 4 using iterators: { ";

    for (auto element : num_range(1, 5))    // This loop - style works only with iterable class!
    {
        cout << element << ", ";
    }
    cout << "}\n\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 2: Creating STL-style iterator class

/* That recepie is an extention to recepie 1. If we want to have more fancy iterator, and use more stuffs
from STL lib, we need to provide some informations required by some STL algorithms so it could work properly.

The informations can be provided by specialization template structure named iterator_traits<iterator_type>. 

In the structure we have several typedefs that would be used y iterators.

In that example we will extend recepie1 iterator by providing the desired informations.

Example:
*/

// Info struct specialization
template <>
struct std::iterator_traits<num_iterator>
{
    using iterator_category = std::forward_iterator_tag;        //Defines category of the iterator
    using value_type = int;                                     // Defines type of value returned by iterator dereference
    using difference_type = void;                               // Type of it2 - it1. 
    using pointer = int*;                                       // Type of pointer to referee object
    using reference = int&;                                     // Type of reference to referee object
};

// And example of usage
void stl_style_iterator_example()
{
    cout << "STL - style iterator example \n\n";
    cout << "Print min and max of range 1 to 5 using stl minmax algorithm: range: {";

    num_range range(1,5);

    for (auto element : range)    // This loop - style works only with iterable class!
    {
        cout << element << ", ";
    }
    cout << "}\n\n";

    auto [min, max] = (minmax_element(range.begin(), range.end()));

    cout << "And min: " << *min << " max: " << *max << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 3: Using iterator adapters

/* Iterator adapters are stl provided objects that allows to adapt interface of source of the data, 
and container in which the data shall be puted. As an example, stream can be treated as data source, and 
vector as a container for data.

We can adapt such using iterator adapters.

Example */

void iterator_adapters_example()
{
    cout << "Iterator adapters example \n\n";

    vector<int> a{1,2,3,4};

    cout << "At the beginning we have a vector (destination container): {";
    for (auto &i : a) {cout << i << ", ";}
    cout << "}\n\n";

    //Example 1: adapt stream iterator - to add to back
    istringstream ss{"12 13"};
    istream_iterator<int> it11{ss};
    istream_iterator<int> it12{};
    copy(it11, it12, back_inserter(a));

    cout << "We pass data from string stream (12,13) at the end of v. Result: {";
    for (auto &i : a) {cout << i << ", ";}
    cout << "}\n\n";

    //Example 2: adapt stream iterator - to add to the middle of container
    istringstream ss2{"-12 -13"};
    istream_iterator<int> it21{ss2};
    istream_iterator<int> it22{};
    auto a_middle (next(a.begin(), static_cast<int>(a.size()/2)));
    copy(it21, it22, inserter(a, a_middle));

    cout << "We pass data from string stream (-12,-13) at the middle of v. Result: {";
    for (auto &i : a) {cout << i << ", ";}
    cout << "}\n\n";

    // Example 3 (descr only) front_inserter - adds to the front of the container. Container must handle push_front() method.
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 4: Using iterator for implementing algorithms

/* Iterator can be used to sequentially access containers, but, as well, we can use it to implement
algorithms, in which we have to save some state (or should). If we have an algorithm, on which its next state
depends on previous state, we can make it recursive. However, sometimes, recursive manner can be very memory consuming
and may crash our application. So, we can also implement it in iterative way, but thus will have impact on
lenght of computing for some cases.

In case if we want tu sequentially use next values of such kind of algorithm, we can use iterators as kind
of storage, for values computed in a previous step. With that, we do not have to calculate all sequence each time we want
to use the algorithm.

As an example - fibonacci calculator. All new values are calculaed basing on calculated in old step.

Example */

//Fibonacci iterator class
class fibit{
    size_t i {0};
    size_t a {0};
    size_t b {1};
public:
    fibit() = default;
    explicit fibit(size_t _i) : i(_i) {}

    fibit& operator++()
    {
        const size_t old_b {b};
        b += a;
        a = old_b;  //Here we have fibonacci algorithm
        ++i;
        return *this;
    }

    bool operator!= (const fibit &o) const
    {
        return i != o.i;
    }

    size_t operator*()
    {
        return b;
    }
};

// Fibonacci iterator container - like style - just to make it possible to use in range for loop
class fib_range
{
    size_t end_n;   //Max fibonacci iteration definition
public:
    fib_range(size_t end_n_) : end_n(end_n_) {}
    fibit begin() const {return fibit{};}       //And implementations of begin() and end() of a range
    fibit end() const {return fibit{end_n};}
};

void iterator_for_algorithm_example()
{
    cout << "Example of usage iterator for implementing algorithm. Here - fobonacci \n\n";
    cout << "Fibonacci numbers in range up to 10: {";
    for (auto element : fib_range(10))
    {
        cout << element << ", ";
    }
    cout << "}\n\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 5: Reverse iterator

/* Reverse iterators are in fact standard iterators decorated with algorithm that converts
incrementation to decrementation. That allows to use containers with algorithms naturally
working only in forward way to work with opposite way - iterate from end to beginning.

Reverse iterator can be applied only on containers that allows to iterate back (decrement iterator).

STL containers has already methods that returns reverse iterators: rend() and rbegin().
If we have container that does not provides rbegin and rend, we can use make_reverse_iterator() function,
that converts standard iterator to reverse one. The container has to be able to iterate backward.

Example:
*/

void reverse_iterator_example()
{
    cout << "Reverse iteration example \n\n";
    cout << "We have a list: {1, 2, 3, 4, 5}. Reverse list is: \n";
    list<int>  l{1, 2, 3, 4, 5};

    copy(l.rbegin(), l.rend(), ostream_iterator<int>{cout, ", "});

    cout << "\n\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 6: Using iterator guard

/* Iterator guard is an empty object, which fits to iterator interface, but has different type
than standard iterator. In cpp17 we can have different types for begin and end iterators when
iterating by loop. Although, we can use different type for begin and end iterator of a range.

It is usable if we want to iterate threw range, in which we do not know end iterator placement
before we get to it, and we do not want to iterate threw whole range to find it before
we start loop iteration. Example of such situation can be iterating threw stream.

If we have guard iterator which has different type than standard iterator, we can overload != operator of standard iterator
to check if we reached end of range (ex. for c-style char chain we can check if char is '\0')

The compiler will automatiaclly chose right != operator for us to compare iterator with guard.

The iterated range has to return standard iterator in begin(), and guard iterator type in end().

Example */

// Iterator guard type
class it_guard {};

// Standard iterator
class it{
    const char *s {nullptr}; //The iterator will iterate threw c-style char chain
public:
    explicit it(const char *str) : s(str) {}
    char operator* () const 
    {
        return *s;
    }
    it& operator++()
    {
        ++s;
        return *this;
    }
    bool operator!= (const it_guard) const
    {
        return s != nullptr && *s != '\0';
    }
};

//Range to iteration definition
class cstring_range{
    const char *s {nullptr};
    public:
    cstring_range(const char* str) : s(str) {}
    it begin() const
    {
        return it{s};
    }
    it_guard end() const
    {
        return {};
    }
};

// And example function
void iterator_guardian_example()
{
    cout << "Iterator guardian example \n\n";
    cout << "We will iterate c-style string: a, d, b, v, c: \n\n";

    cstring_range c{"adbvc"};

    for (char x : c)
    {
        cout << x << ", ";
    }
    cout << "\n\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 7: Automatic check of iterator code

/* Iterators acts like standard pointers. That means, the iterators can be affected by some 
errors hard to discover, like dereference to point out of range.

In the recepie we will cause such mistake and check if compiler will be able to find it out.

Example:
*/

void iterator_error_example()
{
    cout << "Iterator mistake example. Dereference element of vector by iterator: ";
    vector<int> v{1,2,3};
    v.shrink_to_fit();
    const auto it = v.begin();
    cout << *it << "\n";
    cout << "And now dereference iterator that points wrongly. Vector has been moved. *it = ";
    v.push_back(8); //As 4th element cannot be fitted to 3-element memory slot, the vector will be moved to new memory slot
    cout << *it << endl << endl;
}

void iterators_example()
{
    cout << "Iterators examples! " << endl << endl;

    iterable_range_example();

    stl_style_iterator_example();

    iterator_adapters_example();

    iterator_for_algorithm_example();

    reverse_iterator_example();

    iterator_guardian_example();

    iterator_error_example();
}