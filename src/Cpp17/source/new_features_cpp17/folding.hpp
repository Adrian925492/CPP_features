/*
Folding - ability of cpp17 language to handle wariadic number of arguments.

For example, if we want to do the same operation (like sum) on variadic number of arguments we can use fold.

Fold is in fact shortened sign of recursive call of the operation on elements from variadic list, up to
the end of the list.

Fold syntax:

( <sth to do> ... ) - is the right fold.
( ... <sth to do> ) - is the lef fold.

For example if we have sum of variadic number of elements, and we will call:

sum(1, 2, 3)

the right fold will expand it to:

((1 + 2) + 3)

and the left fold to:
(1 + (2 + 3))

It may sometimes have manner.

In fold we can use almost all logicam, mathematica, boolean or stream operators.

*/

#include <iostream>
using namespace std;

template<typename ... Ts>
auto suma(Ts ... args)
{
    return (args + ...);    //Rifgt fold example
}

// And in old-style manner

//We need specialization template for last element of variadic chain !
template<typename T>
T suma_old(T arg)
{
    return arg;
}

//And rest of it with recursive call
template<typename T, typename ... Ts>
T suma_old(T arg, Ts ... args)
{
    return arg + suma_old(args ...);
}

void fold_example()
{
    cout << "Fold example \n\n";

    cout << "Fold of sum of 1, 2, 3, 4 = " << suma(1, 2, 3, 4) << endl;
    cout << "Fold of sum of 2, 3, 4 = " << suma(2, 3, 4) << endl;

    cout << "Old - style recursive manner: sum of 1, 2, 3, 4 = " << suma_old(1, 2, 3, 4) << endl;
}