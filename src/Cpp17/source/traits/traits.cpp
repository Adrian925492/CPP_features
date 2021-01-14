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
#include <vector>
#include <map>
#include <random>
#include <variant>
#include <limits>
#include <memory>

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

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 8: Unique pointer example

/* Unique pointer is introduced in C++11 type of smart pointer. It allows to handle dynamic memor allocation
with automatic release object, when it is abandoned. That means, that user has not to remember of resources
and risk of memory leaks is minimal with that.

Moreover, unique pointer can be only one that provides access to an object. That means it cannot be copied, but
can be moved.

Moreover, unique pointer can be null, and can be used as standerd pointer.

Unique pointers needs no additional resources compairng with standard pointers to work with.

*/

//Helper class
class Foo
{
    public:
    string name;
    Foo(string n) : name(n) {
        cout << "CTOR " << name << endl;
    }
    ~Foo() {
        cout << "DTOR " << name << endl;
    }
};

void process_item(unique_ptr<Foo> p)
{
    if (!p) {return;}   //Return if p is empty
    cout << "Processing " << p->name << endl;
}

void unique_ptr_example()
{
    cout << "Unique pointer example\n\n";

    // 2 ways of init unique ptr - by make_unique and directly
    {
        unique_ptr<Foo> p1 {new Foo("foo1")};
        auto p2 = make_unique<Foo>("foo2");
    }   //Here both foo1 and foo2 will be automatically deleted - exiting the scope

    //Using proces item helper function
    process_item(make_unique<Foo>("foo3")); //foo3 given to function, so will be deleted when exiting function

    //Move pointer
    auto p1 (make_unique<Foo>("foo4"));
    auto p2 (make_unique<Foo>("foo5"));
    process_item(move(p1));     //Here only foo5 will be deleted exiting function
    cout << "End of function " << endl;
    //Foo 4 will be deleted here - exiting of scope
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 9: Shared pointer example

/*
Shared_prt is type of smart pointers that allows to be copiable. Shared pointers has control block.
One control block exists for each copy of shared pointer. Each shared pointer referee to object and to control block.
The control block has counter infirming how many copies of shared pointers we have, and has also reference to object
pointed. If the counter reaches 0, the control block deletes referee object and otself. Each copyiong of shared_ptr 
increases the counter.

In the example we will use classes from unique_ptr.
*/

//Helper function
void f_shared(shared_ptr<Foo> p)
{
    cout << "p: pointer counter is: " << p.use_count() << endl;
}

void shared_ptr_example()
{
    cout << "Shared ptr example \n\n";

    shared_ptr<Foo> p1; //Null shared ptr
    {
        cout << "Beginning of interior scope. " << endl;
        shared_ptr<Foo> p2 {new Foo{"foo1"}};
        auto p3 {make_shared<Foo>("foo2")};
        cout << "Use count of foo1 is: " << p2.use_count() << endl; //Use count will be 1
        p1 = p2;    //Copy
        cout << "Use count of foo1 is: " << p2.use_count() << endl; //Use count will be 2
    }   //Here foo1 will be kept, foo2 deleted
    cout << "Return to main scope" << endl;
    cout << p1.use_count() << endl;

    cout << "First call of f_shared() " << endl;
    f_shared(p1);   //Here function will have copy of shared_ptr. Only for life time of function, shared_ptr counter will be 2.
    cout << "Second call of f_shared()" << endl;
    f_shared(move(p1)); //Give control of p1 to function, remove p1 content after function scope return
    cout << "End of scope" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 10: Weak pointer example

/* Weak pointer is a type of smart pointer that keeps only information about pointed object, but does not allows
to directly access it. It has to be converted to shared_ptr by lock method before accesing the object. Beacouse it
does not allows to access directly, making weak pointer dies not increments reference_counter of control block. Moreover, object
refered by weak pointer can be deleted even if weak pointer still exists. Weak pointer allows to check if object pointed
is still accesible.

In the example we will use classes from unique_ptr.
*/

//Heper function
void weak_ptr_info(const weak_ptr<Foo> &p)
{
    cout << "-------------" << boolalpha
    << "Expired: " << p.expired() << endl       //Informs if object pointed is still accesible
    << "Use count: " << p.use_count() << endl   //Returns use counter - like for shared_ptr
    << "Content: " ;
    if (const auto sp (p.lock()); sp)
    {
        cout << sp->name << endl;
    }else{
        cout << "nullptr" << endl;
    }
}

void weak_pointer_example()
{
    cout << "Weak pointer example \n\n";

    weak_ptr<Foo> p1;
    weak_ptr_info(p1);

    {
        auto shared_foo (make_shared<Foo>("foo1"));
        p1 = shared_foo;
        weak_ptr_info(p1);
    }   //Leave scope - foo1 will be deleted by shared ptr, but p1 still exists
    weak_ptr_info(p1);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 11: Non standard smart pointers example

/* Assume we have class that cannot be initialized by standard new and delete function (ex. has
only private constructors and is created by creation methods). In that case it will not be possible to 
instantiate it by smart pointers.

In the recepie workaround for that is showed.
*/

//Example class
class Foo2{
    string name;
    Foo2(string n) : name(n) 
    { 
        cout << "CTOR " << name << endl;
    }
    ~Foo2() 
    {
        cout << "DTOR " << name << endl;
    }
    public:
    static Foo2* create_foo2(string s)
    {
        return new Foo2{move(s)};
    }
    static void destroy_foo2(Foo2* p)
    {
        delete p;
    }
};

//Create wrapper for making shared and unique Foo2
// Here we use constructor of shared/unique ptr of type shared_ptr<F> (F*, Delete_function_t)
// The F* is returned by creatr_foo2 method call. Other arg is just a pointer to function.
static shared_ptr<Foo2> make_shared_foo2(string s)
{
    return {Foo2::create_foo2(move(s)), Foo2::destroy_foo2};
}

static unique_ptr<Foo2, void(*)(Foo2*)> make_unique_foo2(string s)
{
    return {Foo2::create_foo2(move(s)), Foo2::destroy_foo2};
}

void non_standards_smart_pointers_usage_example()
{
    cout << "Non standard smart pointers usage example \n\n";
    auto sp (make_shared_foo2("Shared foo2 instance"));
    auto up (make_unique_foo2("Unique foo2 instance"));
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 12: Shared pointer to atribute of larger object

/* In the recepie we will hve large object stored by shared pointer, ant we want to 
have access to the attribute of that object by shared pointer, but we want that shared ptr
of the attribute to point to the same control block as object shared pointer. It is possible by
usage special form of shared_ptr constructor. In that way, if object shared_ptr will be out of scope,
the large object itself will not be deleted untill its attribute shared_ptr exists.
*/

struct example_data
{
    int a;
    string b;
    example_data(int aa, string bb) : a(aa), b(bb) {cout << "CTOR " << a << b << endl;}
    ~example_data() {cout << "DTOR " << a << b << endl;}
};

void large_object_attribute_shared_ptr_example()
{
    cout << "Large object attribute shared pointer example \n";

    //Prepare shared ptrs
    shared_ptr<int> p1;
    shared_ptr<string> p2;    

    //Prepare object
    {
        auto p = make_shared<example_data>(2, "example_class");
        p1 = shared_ptr<int>(p, &p->a);
        p2 = shared_ptr<string>(p, &p->b);
    }   //Here scope ends, so object pointed by p would be destroyed, but p1 and p2 prevents from it!
    cout << "After scope attributes ob object: p1 is " << *p1 << " and p2 is: " << *p2 << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 13: Random number generator usage

/* From C++11 standard the STL provides set of random number generator engines for generating PRNG 
values (and one engine for TRNG if available).

The recepie shows example of using it.
*/

//Function for generating histogram of values
template<typename T>
void histogram(size_t partitions, size_t samples)
{
    using rand_t = typename T::result_type;     //Create an alias to rand num generated type
    partitions = max<size_t>(partitions, 10);   //Limit given amount of partitions to max 10

    T rd;   //Instantiate random number generator
    rand_t div ((double(T::max()) + 1) / partitions);   //That value will be used for generating normalization (max val of generator per partitions amount)
    vector<size_t> v (partitions);                 //Instantiate vector for histogram data
    for (size_t i {0}; i < samples; ++i)
    {
        ++v[rd() / div];    //Increment element of vector of id randomly choosen from range 0 - partitions (max 10)
    }

    rand_t max_elem (*max_element(v.begin(), v.end()));
    rand_t max_div  (max(max_elem / 100, rand_t(1)));   //Scalling histogram value

    // Print histogram
    for (size_t i {0}; i < partitions; ++i)
    {
        cout << setw(2) << i << ":"
        << string(v[i] / max_div, '*') << endl;
    }
}

void random_number_generator_usage()
{
    cout << "Random number generator usage example \n\n";

    //Define nr of samples and partitions
    size_t partitions {10};
    size_t samples {1000000};

    //Use engines:
    cout << "Random device engine: " << endl;
    histogram<random_device>(partitions, samples);

    cout << "Default random engine: " << endl;
    histogram<default_random_engine>(partitions, samples);

    cout << "minstd_rand device engine: " << endl;
    histogram<minstd_rand0>(partitions, samples);

    cout << "minstd_rand0 device engine: " << endl;
    histogram<minstd_rand>(partitions, samples);

    cout << "mt19937 device engine: " << endl;
    histogram<mt19937>(partitions, samples);

    cout << "mt19937_64 device engine: " << endl;
    histogram<mt19937_64>(partitions, samples);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 14: Random number generation with given distribution

/* The STL has defined set of engines that if used with random number generator can
give a random value with defined distribution of propability. The following example shows 
couple of commonly used distributions given by STL.
*/

//Print function - will print distribution of generating given amount of samples
template<typename T>
void print_distro(T distro, size_t samples)
{
    default_random_engine e;        //Instantiate random engine firts
    map<int, size_t> m;
    for (size_t i {0}; i < samples; ++i)
    {
        m[distro(e)] += 1;          //Just like in above example - increment amount of generated samples for given value from range
    }

    size_t max_elem (max_element(m.begin(), m.end(), 
        [](const auto &a, const auto &b)
        {
            return a.second < b.second;
        })->second);                // Will give max element of generated elements for scalling histogram
    
    size_t max_div (max(max_elem/100, size_t(1)));

    //Print results
    for (const auto [randval, count] : m)
    {
        if (count < max_elem / 200) {continue;}      //Counters with very small values will be skipped - to increase readability
        cout << setw(3) << randval << ":"
        << string(count / max_div, '*') << endl;
    }
}

void distribution_example()
{
    cout << "Distribution example \n\n";

    //Define nr of samples and partitions
    size_t partitions {10};
    size_t samples {1000000};    

    // Print distributed random elements for different distributions
    cout << "uniform_int_distribution: " << endl;
    print_distro(uniform_int_distribution<int>{0, 9}, samples);

    cout << "normal_distribution: " << endl;
    print_distro(normal_distribution<double>{0.0, 2.0}, samples);

    cout << "bernoulli_distribution: " << endl;
    print_distro(bernoulli_distribution{0.75}, samples);

    cout << "discrete_distribution: " << endl;
    print_distro(discrete_distribution<int>{{1, 2, 4, 8}}, samples);

    cout << "piecewise_constant_distribution: " << endl;
    initializer_list<double> intervals {0, 5, 10, 30};
    initializer_list<double> weights {0.2, 0.3, 0.5};
    print_distro(piecewise_constant_distribution<double>{begin(intervals), end(intervals), begin(weights)}, samples);

    cout << "piecewise_linear_distribution: " << endl;
    initializer_list<double> weights2 {0, 1, 1, 0};
    print_distro(piecewise_linear_distribution<double>{begin(intervals), end(intervals), begin(weights2)}, samples);
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

    unique_ptr_example();

    shared_ptr_example();

    weak_pointer_example();

    non_standards_smart_pointers_usage_example();

    large_object_attribute_shared_ptr_example();

    random_number_generator_usage();

    distribution_example();
}
