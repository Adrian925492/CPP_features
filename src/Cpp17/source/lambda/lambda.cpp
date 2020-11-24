/* This file contains all recepies regarding lambda function */

#include <iostream>

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

    // Example 5: carrying function
    auto plus_ten ( [=](int x) -> int {return x + 10;} );
    cout << "Carrying example: plus 10 fcn: plus_ten(3) = " << plus_ten(3) << endl << endl;
}

void lambda_example()
{
    cout << "Lambda example! \n\n";

    simple_lambda();
}