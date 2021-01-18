/* This file contains all recepies regarding parallell processing */

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
//#include <execution>
#include "parallell_processing.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: Policies example

/*
Execution poliy is a new feature added in C++17. It allows to set if algorithm provided by
STL would be run in sequential way (default), or parallel way. We can say it by adding 1st argumrnt
of execution policy type (optional)
*/

//Helper function
static bool odd(int n) {return n % 2;}

void using_policies()
{
    cout << "Processing policies usage example \n\n";

    vector<int> v(50000000);

    // Add function for random generating number
    mt19937 rd;
    uniform_int_distribution<int> dis(0, 100000);
    auto rand_num ([=] () mutable {return dis(rd);});

    cout << "Using generate sequentially! " << endl;
    const auto t11 = chrono::steady_clock::now();
    generate(v.begin(), v.end(), rand_num);
    const auto t12 = chrono::steady_clock::now();
    cout << "FINISH! in " << (t12 - t11).count() << " seconds" << endl;

    cout << "Using generate parallel!" << endl;
    const auto t21 = chrono::steady_clock::now();
    //generate(execution::par, v.begin(), v.end(), rand_num);
    const auto t21 = chrono::steady_clock::now();
    cout << "FINISH! in " << (t22 - t21).count() << " seconds" << endl;
}

void parallell_processing_example()
{
    using_policies();
}