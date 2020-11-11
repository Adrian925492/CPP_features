/* This file contains all recepies regarding queues */

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <set>
#include <iterator>
#include <vector>
#include "queue.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: using priority queue to implement list of things to do

/* In that recepie we will use special type of queue - priority queue.
The priority queue is a set of queues placed in natural order. 

Here we will use priority queue on pairs, in which, the first element will be 
priority, and the second will be task description.

The queu will automatically sort the pairs according to 1st element of pair - its priority.

If we want, we can overload operator >, to affect to how the priorities will be set.

Example
*/

void todolist_example()
{
    cout << "Todolist example \n\n";

    cout << "We will set the list of: \n";

    using item_type = pair<int, string>;
    priority_queue<item_type> list;

    initializer_list<item_type> input_data {
        {0, "task 0"},
        {1, "taks 1"},
        {2, "task2"},
        {1, "taskk1_2"}
    };

    for(const auto &p : input_data)
    {
        cout << p.first << " : " << p.second << "\n";
    }

    for(const auto &p : input_data)
    {
        list.push(p);
    }

    cout << "Sorted list: \n";

    while(!list.empty())
    {
        cout << list.top().first << " : " << list.top().second << "\n";
        list.pop();
    }
    cout << endl;
}

void queue_example()
{
    cout << "Queue recepies examples!  \n\n";

    todolist_example();
}