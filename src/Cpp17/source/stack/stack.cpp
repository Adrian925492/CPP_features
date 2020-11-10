/* This file contains all recepies regarding unordered maps */

#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <vector>
#include "stack.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: Using stack for simple RPN calculator

/* In that recepie we will use stack in simple RPN calculator

The calculator will accept elements to its input. For element mapable to
operend type (ex. double), the program will map it to operend type and put into the stack.

If the operend could not be mapable, the program will treat it as operator and
try to execute operation on last 2 operends from the stack.

*/

// Executable operations map
map<string, double (*)(double, double)> operations {
    {"+", [](double a, double b){return a+b;}},
    {"-", [](double a, double b){return a-b;}},
    {"*", [](double a, double b){return a*b;}},
    {"/", [](double a, double b){return a/b;}},
};

template <typename T>
double evaluate_rpn(T it, T end)
{
    // create value stack
    stack<double> val_stack{};

    // stack populate helper function
    auto pop_stack([&](){
        auto r (val_stack.top());
        val_stack.pop();
        return r;
    });

    for(; it != end; ++it)
    {
        stringstream ss {*it};
        if (double val; ss >> val)  // If element is operend
        {
            val_stack.push(val);    //Add operend to the stack
        }
        else    // If element is not operend - it can be operator, than
        {
            const auto r = pop_stack();     //Get last 2 operends from the stack
            const auto l = pop_stack();

            //try - catch block, in case if operations is not implemented
            try{
                const auto & op {operations.at(*it)};   // Try to find operaions in operation map
                const double result = op(l, r);     //Execute the operation
                val_stack.push(result);     //Push the reult of the operation to stack top
            }catch(const out_of_range&)
            {
                throw invalid_argument(*it);    // If the operend was not in operations map - throw exception (can be cached by function that uses calculator)
            }

        }
    }
    return val_stack.top();  // Return result - as top of the stack
}

void rpn_calculator_example()
{
        cout << "RPN calculator example \n\n";
        cout << "Let assume we want to calculate expression: 1 2 + 3 *, which will give result of 9.\n\n";

    vector<string> operation = {"1",  "2",  "+",  "3", "*"};

    
    auto result = evaluate_rpn(operation.begin(), operation.end());

    cout << "result is: " << result << endl << endl;

}

void stack_example()
{
    cout << "Stack recepies examples!  \n\n";
    rpn_calculator_example();
}