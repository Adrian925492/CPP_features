/* This file contains all recepies regarding maps */

#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <cassert>
#include "map.h"

using namespace std;

void print_map(const map<int, int>& m)
{
    cout << "Map elements: { ";
    for_each(m.begin(), m.end(), [](auto it){cout << it.first << " : " << it.second << ", ";});
    cout << " }\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: using effective way of adding elements to a map

/* 
    Adding to a map can be succeed if key is not already in a map, or failed if it is. We can
    use emplace() or insert() methods and check retval to see if the inserting succeeds, but during
    that operation the stl will create map node and than try to emplace it.

    Instead of that, in cpp17 we can use try_emplace() method, which is more effectove. Firstl, it will
    check if the key is not already in a map, and than, if not, it will emplace the element.

    Signature:

    pair<it, bool> try_emplace(key, value)


    it - iterator of emplaced map node or iterator to map node existing in a map with given key
    bool - true if emplacing succeed

EXAMPLE
*/

void add_to_map_recipie()
{
        cout << "Add to map recepie \n\n";
        cout << "Map at the beginning:\n";

    map<int, int> mapa{make_pair(1,1), make_pair(2,2), make_pair(3,3)};

        print_map(mapa);

        cout << "Add element to map by try_emplace\n";
        
    auto p = mapa.try_emplace(1, 2);

        cout << "Map after adding 1:2 (existing key): \n";
        print_map(mapa);

    auto p2 = mapa.try_emplace(4, 4);

        cout << "Map after adding 4:3 (new key): \n";
        print_map(mapa);
}       

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 2: Insert with tip

/* If we want to insert element into map, the algorithm has
go threw a map and find proper place to insert it. Sometiles it has to
rebalance map (maps are usually implemented as binary tree).

It is possible to add additional parameter to insers function, which is iterator
to one after element that shall be after inserted element (before cpp11 it was one
last that shall be before). Works for old and cpp 17 standards.

If the tip wil be fine, the insertion will take much less complexity ( O(1)). Of it
becomes false, the map will use standard insertion algorithm.

*/
void insert_with_tip()
{
    cout << "Insert with tip to the map \n";
    cout << "Map at the beginning:\n";

    map<int, int> mapa{make_pair(1,1), make_pair(2,2)};

        print_map(mapa);

        cout << "Add element to map with tpi:\n";

    auto tip_iterator = mapa.end();
    auto it = mapa.insert(tip_iterator, {3,3});
        print_map(mapa);
}


void map_example()
{
    cout << "Map recepies examples!  \n\n";
    add_to_map_recipie();   
    insert_with_tip();
}