/* This file contains all recepies regarding unordered maps */

#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <set>
#include <iterator>
#include <vector>
#include "set.h"

using namespace std;

static void print_set(set<string>& s)
{
    cout << "{ ";
    for (const auto element : s)
    {
        cout << " " << element << " ,";
    }
    cout << "}\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: Using set for filter duplicates and sort elements from some group

/*
Set acts like a map, in which key is a value. Set cannot have a duplicates and is organized as a tree - 
sorted. That means, that it can be used to automatically sort and filter duplicates of some group.

! In example You can see usage of istream_iterator class.

The class returns iterator object to given stream.

We create 2 iterators here. One is for stream iterator. Other is empty iterator, named as end.
If elements in the stream will be all handled, the iterator will be empty, so as end iterator, and
the method using it shall see it Empty iterator shall not be dereferred.

In the copy method inserter class is used. The inserter class creates insert_iterator, which is used for empty containers. 
If the iterator is incremented, it does nothing, but if it is used by dereferee and assign the value, it 
will put the value into the container (as new value) and increment.

The inserter accepts container instance and iterator on place, when new element shall be placed. IN that ase it is
one past end of the container, so end iterator.
*/

void filter_duplicates_and_sort_inputs_by_set()
{
    cout << "Filter duplicates and sort inputs by set example \n\n";
    cout << "Lets filter duplicates of an input stream and sort it in alphabetic order.\n";

    set<string> s;
    string input_string {"a a b c f g a x s g d f s"};
    stringstream ss{input_string};

    cout << "Input string data: " << input_string << endl << endl;

    istream_iterator<string> it {ss};
    istream_iterator<string> end;

    copy(it, end, inserter(s, s.end()));

    cout << "Set content: \n";
    print_set(s);
}

void set_example()
{
    cout << "Set recepies examples!  \n\n";
    filter_duplicates_and_sort_inputs_by_set();
}