/* This file contains all recepies regarding unordered maps */

#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <cassert>
#include "unordered_map.h"

using namespace std;

static void print_map(const map<int, int>& m)
{
    cout << "Map elements: { ";
    for_each(m.begin(), m.end(), [](auto it){cout << it.first << " : " << it.second << ", ";});
    cout << " }\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: 




void unordered_map_example()
{
    cout << "Unordered map recepies examples!  \n\n";

}