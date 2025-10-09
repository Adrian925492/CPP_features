/* This file contains all recepies regarding maps */

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>
#include "map.h"

using namespace std;

static void print_map(const map<int, int>& m)
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

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 3: Exctract map node

/* In older standards, to get map node, we could for example access it by iterator. To
get extracted vesrion of a node, we had to copy the node pointed by iterator, and than erase node from
the map. 

From cpp17 we have new method that allows to do it in more effective way - extract(). No copy and erase will be
done here, the method just unlinks the node from a map, links neighbour nodes together if needed, and
makes rebalancing of the map if needed. The method has 2 variants - with iterator argument, returns node handler, and
is faster, beacouse does not need to look for a node by key, and other one, that accepts a key. The method looks map
for finding a key, and if it is present, it returns node of the element. If key is not present, it will return empty
node.

We can check if node is empty by .empty() method call (true = empty)

With such extracted node we can do something, like swapping, modyfying etc.

Next we can insert such modified node to any map by insert() method.

Example usage:

*/

void extract_node_example()
{
        cout << "Extract node example! \n\n";
        cout << "Map at the begining: ";

    map<int, int> mapa{make_pair(1,1), make_pair(2,2)};

        print_map(mapa);

        cout << "Extract element by key 2:\n";

    auto node = mapa.extract(2);

        cout << "Map after extract: ";
        print_map(mapa);    

        cout << "Extracted element: key: " << node.key() << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 4: Using map to count occurence of elements in series

/* Sometimes we want to count number of occurences of some elements in a series
in a good way. Here we have example of how to du it by map.

1. Create empty map - key will be series element, and value will be occurence counter
2. For each element, increment value and if key does not exists, add key

Example:
*/

void occurence_counter_example()
{
        cout << "Occurence counter example \n\n";
        cout << "We will count occurences of separate letters in the following list: {";
    vector<int> input{1, 2, 3, 4, 5, 6, 6, 3, 4, 2, 6, 1};
        for_each(input.begin(), input.end(), [](auto& it){cout << " " << it << ",";});
        cout << "}" << endl << endl;

    map<int, int> counter;
    for_each(input.begin(), input.end(), [&counter](auto it){
        counter[it]++;
    });

        cout << "Map after counting (unordered): \n";
        print_map(counter);

    vector<pair<int, int>> ordered_count;
    ordered_count.reserve(counter.size());
    move(counter.begin(), counter.end(), back_inserter(ordered_count));
    sort(ordered_count.begin(), ordered_count.end(), [](auto& a, auto&b){return a.second > b.second;});

        cout << "Sorted counter: { ";
        for_each(ordered_count.begin(), ordered_count.end(), [](auto& it){cout << " " << it.first << " : " << it.second << ",";});
        cout << "}\n\n";
}


void map_example()
{
    cout << "Map recepies examples!  \n\n";
    add_to_map_recipie();   
    insert_with_tip();
    extract_node_example();
    occurence_counter_example();
}