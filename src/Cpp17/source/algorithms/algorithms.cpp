/* This file contains all recepies regarding STL algorithms */

#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <iterator>
#include <map>
#include <random>

using namespace std;

//Simple helper function - print the vector content
static void print(const vector<int> &v)
{
    copy(v.begin(), v.end(), ostream_iterator<int>{cout, ", "});
    cout << endl;
}


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
The recepie presents sorting algorithms examples. Depending on type of container, there are
several algorithms implemented (choosing sort, merging sort, insert sort etc...). Compilse chooses 
best autoamtically.
*/

void sort_example()
{
    cout << "Sort example! \n\n";

    vector<int> v{1,2,3,4,5,6,7,8,9};   //source vetor

    random_device rd;
    mt19937 g {rd()};                   // Random generator init

    cout << "Input container: ";
    print(v);
    cout << "Sorted: " << is_sorted(v.begin(), v.end()) << endl;

    shuffle(v.begin(), v.end(), g);     //Shuffle vector

    cout << "\nShuffled vector: ";
    print(v);
    cout << "Sorted: " << is_sorted(v.begin(), v.end()) << endl;

    // Sort
    sort(v.begin(), v.end());
    cout << "\nSort() called: Sorted: " << is_sorted(v.begin(), v.end()) << "vector: ";
    print(v);

    // Partition
    shuffle(v.begin(), v.end(), g);    // Shuffle vector
    partition(v.begin(), v.end(), [](int e){return e<5;});   //Partition - all less than 5 elements on the beginning
    
    cout << "\nPartitioned vector: ";
    print(v);

    // Partial sort
    shuffle(v.begin(), v.end(), g);    // Shuffle vector
    auto middle(next(v.begin(), int(v.size() / 2)));    //Find middle element of a vector
    partial_sort(v.begin(), middle, v.end());

    cout << "\nPartial sorted (to the middle) vector: ";
    print(v);

    //Sort in opposite way - by passing compare fcn
    shuffle(v.begin(), v.end(), g);    // Shuffle vector
    sort(v.begin(), v.end(), [](int& lhs, int& rhs){return rhs < lhs;});
    cout << "\nOpposite sorted vector: ";
    print(v);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 3: Filter (erase) example

/* 
The recepie presents filter algorithms examples. The algorithms mahe removin or copying
filtered elements from input to output range.
*/

void filter_example()
{
    cout << "Filter example! \n\n";

    vector<int> v{1,2,3,4,5,6,7,8,9};   //source vetor

    cout << "Input container: ";
    print(v);

    // Remove all 2-s:
    const auto new_end(remove(v.begin(), v.end(), 2));  //Not erases, just moves searched element to the end of container
    v.erase(new_end, v.end());

    cout << "\nErased all 2s vector: ";
    print(v);

    // Now erase all odd numbers
    auto odd ([](int i){return i%2 != 0;});
    const auto new_end2(remove_if(v.begin(), v.end(), odd));
    v.erase(new_end2, v.end());

    cout << "\nErased all odd values in vector: ";
    print(v);

    // Replace all 4-s to 16
    replace(v.begin(), v.end(), 4, 16);

    cout << "\nReplaced all 4 values to 16 in vector: ";
    print(v);

    // Copy only odd numbers
    vector<int> w{1,2,3,4,5,6,7,8,9};   //source vetor
    vector<int> w1;
    vector<int> w2;

    auto odd_val ( [](int i){ return i % 2 != 0;});
    auto even_val ( [](int i){ return i % 2 == 0;});

    remove_copy_if(w.begin(), w.end(), back_inserter(w1), odd_val);
    copy_if(w.begin(), w.end(), back_inserter(w2), even_val);

    cout << "Copied only even values in 2 ways: ";
    print(w1);
    cout << "\n";
    print(w2);
    cout << endl;
}

void algorithms_example()
{
    cout << "Algorithms example! \n\n";

    copy_example();

    sort_example();

    filter_example();

}
