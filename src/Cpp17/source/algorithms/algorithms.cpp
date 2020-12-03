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

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 4: Transform example

/* Transform function ach similarly to copy finction - it copies
elements from one range to anothe, but allows to chenge it during copy by provided transform 
function */

void transform_example()
{
    cout << "Transform example\n\n";

    vector<int> v{1,2,3,4,5};
    cout << "Initial vector: ";
    print(v);

    cout << endl << "Transformed elements - element^2: ";
    transform(v.begin(), v.end(), ostream_iterator<int>{cout, ", "},
        [](int x){return x*x;}
    );

    cout << endl << endl;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 5: Find example

/* The recepie shows example of using find algorithms.

Some containers has its own imlementation of find algorithms, which is usually more
efficient than general one from algorithms. However, algorithms gives little bit more
flexibility. Two major ways of searching are implemented: linear search, and binary search which
needs input range to be sorted.

*/

struct city{
    string name;
    int population;
};

bool operator==(const city& lhs, const city& rhs)
{
    return lhs.name == rhs.name && lhs.population == rhs.population;
}

ostream& operator<<(ostream& os, const city& data)
{
    return os << data.name << " : " << data.population;
}

template<typename T>        //Implement function for printing that will prevent accesing to end iterator of container
static auto opt_print (const T &container)
{
    return [end_it (container.end())] (const auto& item)
    {
        if(item != end_it)
        {
            cout << *item << endl;
        }else{
            cout << "<end>" << endl;
        }
    };
}

void find_example()
{
    cout << "Find example\n\n";
    
    vector<int> v{1,2,3,4,5,6,7,8,9};
    cout << "Initial vector: ";
    print(v);

    //Find - uses linear algorithm
    cout << "Find element 3: " << *(find(v.begin(), v.end(), 3)) << endl;

    //Search - check if element exists
    cout << "Element 4 is in vector?: " << binary_search(v.begin(), v.end(), 4) << endl;

    //Search in list of cities example
    const vector<city> w{
        {"Warszawa", 30000},
        {"Wroclaw", 6000},
        {"Gdansk", 4000}
    };

    auto found_wroclaw {find(w.begin(), w.end(), city{"Wroclaw", 6000})};
    cout << "Wroclaw found: " << *found_wroclaw << endl;

    //Search with predictate
    cout << "Gdansk found with predictate: " << *(find_if(w.begin(), w.end(), [](const city& c){return c.name == "Gdansk";})) << endl;

    //Search range
    auto range = equal_range(v.begin(), v.end(), 2);
    cout << "Elements around 2 (less and more) in vector: min: " << *range.first << " max: " << *range.second << endl;

    //Search bounds
    auto lb = lower_bound(v.begin(), v.end(), 3);
    auto hb = upper_bound(v.begin(), v.end(), 5);

    cout << "Bounds elements of range 3-5: min: " << *lb << " max: " << *hb << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 6: Clamp example

/* In the recepie we will show clamp function that will change input value
to clamp value if it is grater than clamp value. We will also present procedure of 
normalizing vector elements */

//Normalization function example
static auto norm(int min, int max, int new_max)
{
    const double diff = max-min;
    return [=](int val){
        return int((val - min)/diff*new_max);
    };
}

void clamp_example()
{
    cout << "Clamp example\n\n";

    vector<int> v{122,245,344,434,511,644,711,84,95};
    cout << "Initial vector: ";
    print(v);

    //Clamp
    cout << "\nClamped to 0-100 vector: ";
    transform(v.begin(), v.end(), ostream_iterator<int>{cout, ", "}, [](int x){return clamp(x, 0, 100);});

    //Normalize
    cout << "\nNormalized vector 0-100: ";
    const auto [min_it, max_it] = minmax_element(v.begin(), v.end());
    vector<int> v_norm;
    v_norm.reserve(v.size());
    transform(v.begin(), v.end(), back_inserter(v_norm), norm(*min_it, *max_it, 100));
    print(v_norm);
    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 7: Searching for substring

/* In that recepie we will search for substring in string using search algorithm. However,
the string class has already well optimized find() method that will do the same.

Here we use algorithm from <algorithms> to show its flexibility.

*/

//Substring print helper function
template<typename T>
static void print(T it, size_t chars)
{
    copy_n(it, chars, ostream_iterator<char>{cout});
    cout << endl;
}

void substring_example()
{
    cout << "Search for substring example\n";

    string s = "Hello world, eweryone stay healthly!";
    cout << "Input string: " << s << endl;
    const string pat = "stay";
    cout << "We will look for " << pat << " in strings." << endl;

    {
    //Old style (before CPP17) search - linear search
    auto match = search(s.begin(), s.end(), pat.begin(), pat.end());
    cout << "Before cpp17 style search: ";
    print(match, 4);
    }

    {
    //Cpp17 style search - default searcher
    auto match = search(s.begin(), s.end(), default_searcher(pat.begin(), pat.end()));
    cout << "Default searcher: ";
    print(match, 4);
    }

    {
    //Cpp17 style search - boyer moore searcher
    auto match = search(s.begin(), s.end(), boyer_moore_searcher(pat.begin(), pat.end()));
    cout << "Boyer moore searcher: ";
    print(match, 4);
    }

    {
    //Cpp17 style search - boyer moore horspool searcher
    auto match = search(s.begin(), s.end(), boyer_moore_horspool_searcher(pat.begin(), pat.end()));
    cout << "Boyer moore horspool searcher: ";
    print(match, 4);
    }
}

void algorithms_example()
{
    cout << "Algorithms example! \n\n";

    copy_example();

    sort_example();

    filter_example();

    transform_example();

    find_example();

    clamp_example();

    substring_example();
}
