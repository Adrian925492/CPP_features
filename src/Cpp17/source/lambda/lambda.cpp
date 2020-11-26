/* This file contains all recepies regarding lambda function */

#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <iterator>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: Basic lambda examples

/* Lambda function is in fact functor object that has simplified initializaion. 

Properties:
-> Lambda can be assigned to a variable, and the variable can be used like a function
-> Lambda can be, as well, used in place of decalration
-> Lambda can be constexpr
-> Lambda supports several types of capturing variable. Most comon are by copy [=], and by reference [&]. Vars captured by copy are implicitly const (non mutable).
To make it mutable we have to use mutable keyword after lambda []
-> In [] we can define lambda object atributes. The type of atribute is deducted from assigned init value.
-> By "-> T" we can specify explicitly return value of a lambda
-> By except attribute we can allow to throw exceptions by the lambda

*/

void simple_lambda()
{
    cout << "Simple lambda examples: ";

    // Example 1: basic simple lambda
    auto just_one ([](){return 1;});
    auto just_two ([]{return 2;});

    cout << "Lambda reutrning 1: " << just_one() << " Lambda returning 2: " << just_two() << endl << endl;

    // Example 2: Lambda called in declaration place
    cout << "Lambda returning result of 1 + 2 called in declaration place: " << [](int a, int b){return a+b;}(1, 2) << endl << endl;

    // Example 3: Lambda with lambda object variable
    auto var_labd = [var = 7](){return var+1;};
    cout << "Lambda with lambda object variable = 7, returning the variable + 1: " << var_labd() << endl << endl;

    // Example 4: Lambda capturing value from scope
    {
        int a = 2;

        auto lbd1 = [a](){return a;};
        auto lbd2 ([a]() mutable {return ++a;});
        auto lbd3 = [&a](){return ++a;};
        auto lbd4 = [=](){return a;};
        auto lbd5 = [&](){return a;};

        cout << "Lambda capturing value 2 by copy and returning it: " << lbd1() << endl;
        
        cout << "Lambda capturing value 2 by mutable copy, increment and returning it: " << lbd2() << endl;
        
        cout << "Lambda capturing value 2 by reference, increment and returning it: " << lbd3() << endl;
        
        cout << "Lambda capturing var a from scope by copy and return it (2): " << lbd4() << endl;          
            // Notice, that here expected value is 2, as init (capturing) is done like in constructor - before incrementing reference value
        
        cout << "Lambda capturing var a from scope by reference and return it (3): " << lbd5() << endl;
    }

    // Example 5: carrying function and explicitly give return type
    auto plus_ten ( [=](int x) -> int {return x + 10;} );
    cout << "Carrying example: plus 10 fcn: plus_ten(3) = " << plus_ten(3) << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 2: Using std::function to pack functor/lambda into more polimorphic object

/* If we have functors with the same operator() ret vaulue and the same arguments types, we could use it 
    in polymorphic way. However, 2 functors containing to 2 different class cannot be used that way.

    Similarly, 2 lambda functions with 2 different capture lists cannot be treated as polymorphic, despite
    its call signature is the same.

    Sometimes we could want to use it in polymorphic way, like when putting it to the vector (example).

    To do that, we can pack such functors/lambdas into std::function object.

    Std::function creates polymorphic pack for functors, lambdas and functions which has same argument types list
    and returnd the same retval.

*/

void foo(int x)
{
    cout << " ::Function! " << x;
}

void polimorphic_lambda_example()
{
    cout << "Example of use std::function to pack lambdas into polymorphic way\n\n";

    auto lb1 = [](int x){cout << " ::Lambda1! " << x;};
    auto lb2 = [&](int x){cout << " ::Lambda2! " << x;};

    vector<std::function<void(int)>> v{std::function<void(int)>(foo), std::function<void(int)>(lb1), std::function<void(int)>(lb2)};

    for (auto& x : v)
    {
        x(1);
    }
    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 3: Merging functions using concatenation

/* Concatenation of functions is a technique used in function paradigmat programming.
It is not natevly supported in C++, but allows to easy and generic way create functions
of other functions. For example

auto foo = a . b . c (param)

Will create function foo() that will be concatenation of a, b, and c with param, like a(b(c(param))).

Usage of such constructs increase flexibility and redability.

With C++ we can use lambda to define concat punction, that will do similar thing for us.

Example:

*/

template <typename T, typename ... Ts>
auto concat(T head_function, Ts ... tail_functions)
{
    if constexpr (sizeof ...(tail_functions) > 0) {     //If there are any arguments in a variable list to expand (any functions)
        return [=](auto ...parameters){                 // Create lambda function aith parameters as argument and return it
            return head_function(concat(tail_functions...)(parameters...));     // Call recursive: head_function( ... result of concatenation as lambda)(call the lambda with parameters....)
        };
    } else {
        return head_function;
    }
}

void concat_example()
{
    cout << "Concat example \n\n";

    auto twice = [](int i){return 2*i;};
    auto trice = [](int i){return 3*i;};

    auto combined = concat(twice, trice, std::plus<int>{});

    cout << "Combined function result: combined(2,3) = 2 * 3 * (2+3) = 30 : " << combined(2,3) << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 4: Using lambda to create combined predictates

/* Predictate is a function that checks validity of input dta and returns true if it is valid.
Sometimes we need to have some predictate that woul be combination of existing ones, connecting
together by logical or/and expression. The example shows how we can produce such combined predictate
using lambda in elegant way.

*/

template<typename F, typename A, typename B>
auto combine(F logical_operator, A a, B b)
{
    return [=](auto param){return logical_operator(a(param), b(param));};
}

void combined_predictate_example()
{
    cout << "Combined predictate example \n\n";
    auto pred1 = [](int x){return x > 10;};
    auto pred2 = [](int x){return x < 15;};

    auto combined_pred = combine(logical_and<>{}, pred1, pred2);

    cout << "Combined predictate of: x> 10 and x < 15 for x == 14: ";

    if (combined_pred(14)) cout << "TRUE";

    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 5: Using lambda to create package of functions

/* The recepie allows us to create function that will pack for us many other functions
and call it one by one. Such packaged function can be than called many times, reducing
number of repetitions in the code.

*/

static auto multicall (auto ... functions)
{
    return [=](auto x){
        (void)(initializer_list<int>{ ((void)functions(x), 0)...});     //Cast to void forces ignore retval
    };
}

void pack_example()
{
    cout << "Function pack example\n\n";
    auto f1 = [](int x){cout << " Fcn1 " << x;};
    auto f2 = [](int x){cout << " Fcn2 " << x;};
    auto f3 = [](int x){cout << " Fcn3 " << x;};

    auto mcf = multicall(f1, f2, f3);       // Create multicall function

    cout << "Multicall fcn: ";
    mcf(1);

    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 6: Creating transform_if function

/* Transform_if is a mix of std::transform, which transforms
all emements from input range using transform function, and if clause, which will add
predictate to transform function, that will decide if the element will be transformed or not.

Example:
*/

//Step 1: define mapping function
template <typename T>
auto map(T fn)
{
    return [=](auto reduce_fn){     // The mapping function returns functor that accepts reduce function
        return [=](auto accum, auto input){     // Which returns functor in general form
            return reduce_fn(accum, fn(input));     //Which in its implementation calls transform_fn and returns its output
        };
    };
}


// Step 2: define filter function to handle predictate. The function will filter out all 
//      elements not fit to the predictate, and if fits it will call reduce_fn on it.
template <typename T>
auto filter(T predictate)
{
    return [=](auto reduce_fn){     //The filter function will return functor, which accepts reduce function
        return [=](auto accum, auto input)      // And in its implementation returns function which checks predictate
        {
            if (predictate(input)){
                return reduce_fn(accum, input);     // And calls reduce fn if predictate is true
            }else{
                return accum;                       // Or returns unmodified value
            }
        };
    };
}

// Step 3: define helper function - that will copy and move iterator
auto copy_and_advance = [](auto it, auto input){
    *it = input;
    return ++it;
};

void transform_if_example()
{
    cout << "Transform if example! \n\n";

    auto pred_even = [](int i){return i%2;};    //Define predictate
    auto accum_twice = [](int i){return i*2;};  //Define transformfunction

    vector<int> v{1,2,3,4,5};                   //Define input data

    cout << "The transform_if will take elements from vector v: {1,2,3,4,5}, and for each even element will return its multiplication to stdout. \n Result:\n";

    std::accumulate(
        v.begin(),
        v.end(),
        std::ostream_iterator<int>{std::cout, ", "},
        filter(pred_even)(
            map(accum_twice)(
                copy_and_advance
            )
        )
    );

    // Here we just rely on thick, that both map, filter and reduce_fcn returns functor that has the same signature - fitting to std::accumulate.
    // We can forex. use just copy_and_advance

    // If we type: filter(pred)(a), in fact the filter will return lambda accepting reduce_fn, but 2nd () will call it in place.
    // Such call will return lambda which signature fits to copy_and_replace. The "a" is here hext function to do, and we can create such chain in that way.
    cout << "Just copy_and_advance usage example\n:"
    std::accumulate(
        v.begin(),
        v.end(),
        std::ostream_iterator<int>{std::cout, ", "},
        copy_and_advance
    );


    cout << endl << endl;
}

void lambda_example()
{
    cout << "Lambda example! \n\n";

    simple_lambda();

    polimorphic_lambda_example();

    concat_example();

    combined_predictate_example();

    pack_example();

    transform_if_example();
}

// auto haming = Hamming(1, 1.2, ...)
// auto average = Average()
// auto minmax = MinMax()
// 
// auto filter = hamming << average << minmax;
// auto sensor_value = filter(raw_value);
// or just...
// auto sensor_value = hamming(raw_value);