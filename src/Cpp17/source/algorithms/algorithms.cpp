/* This file contains all recepies regarding STL algorithms */

#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: Copy algorithm example

/* The recepie presents copy and move algorithm usage example. What is benefitial here, the
compiler will choose automatically the most optimized copy/move algorithm for the problem.

*/

//Trick: overload shell cout operator to allow it to handle pair<int, string>
namespace std{
    ostream& operator<<(ostream& os, const pair<int, string> &p)
    {
        return os << "( " << p.first << ", " << p.second << ") ";
    }
}


void copy_example()
{
    cout << "Copy example! \n\n";

    vector<pair<int, string>> src{
        {1, "jeden"},
        {2, "dwa"},
        {3, "trzy"},
        {4, "cztery"}
    };

    map<int, string> dest;

    copy_n(src.begin(), 2, inserter(dest, dest.begin()));    // Copy 2 first elements to map

    auto shell_it (ostream_iterator<pair<int, string>>{cout, "; "});

    copy(dest.begin(), dest.end(), shell_it);       // Print the content of destination map - by copying elements to range pointed by stream iterator mapped to cout

    cout << endl << endl;

    dest.clear();       //Clear output map

    move(src.begin(), src.end(), inserter(dest, dest.begin()));   // Move instead of copy

    cout << "After move: destination: ";
    copy(dest.begin(), dest.end(), shell_it); 

    cout << "\nAfter move: source: ";
    copy(src.begin(), src.end(), shell_it);     
//! Notice, thart strings are not availabel any more. 
// That is beacouse copy algorithm assigned strings, which lays in different place in memory, to dest container instead of copying it.

    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 2: Sort algorithm example

/* 

*/

void sort_example()
{
    cout << "Sort example! \n\n";
}

void algorithms_example()
{
    cout << "Algorithms example! \n\n";

    copy_example();

    sort_example();

}
