/* This file contains all recepies regarding vectors */

#include <iostream>
#include <vector>
#include <algorithm>
#include "vector.h"

using namespace std;

void print_vector(vector<int> v)
{
    cout << "Vecotr elements: { ";
    for_each(v.begin(), v.end(), [](auto it){cout << it << ", ";});
    cout << " }\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: using style erase - remove in vectors

/* STD vector provides mechanism for erasing and removing and resizing its size, even if we want to remove element in
    the middle of vetor. Thus, the user should not do it on his own (like by loop), beacouse vector - provided
    feature has better performance.

    How to:

    <algorithm>
    1) new_end = std::remove(begin(v), end(v), value) <- The remove funstion will find all "values" variables in the vector and move it at
            the end of vector (sort it). It will return iterator to one - past last element of vector, from which the elemnts
            has been moved out. The elements moved out will be corrupted, but not erased yet.

    1') new_end = std::remove_if(begin(v), end(v), predictate) <- The method will move all elements that passes the predictate to right side
            of the vector. The elements can be corrupted, and the method will return iterator to one-past the last element left in the vector.
            The vector will not be shortened yet. Predictate can be function or lambda that returns boolean, basic on vector value (iterator as input)
    
    ! Remove and Remove-if methods works also for other containers, as it just moves and not really erases elements, can be used for ex. for array.

    2) v.erase(new_end, end(v)) - the method will erase values from iterator new_end to end(v). That will result clearing rubish values left
            after erasing, the vector will be resized.

    2') If we remove element from the middle of vector and has left blnk space, we can fit the vector size to new needed space by
        v.shrink_to_fit() method. During that, the vector will allocate new set of memory, enough for the data, copy the data and deallocate old memory.

EXAMPLE
*/

void erase_remove_recipie()
{
        cout << "Erase - remove recepie \n\n";
        cout << "Vector at the beginning:\n";
    
    vector<int> v{1, 2, 3, 2, 5, 2, 7, 8};
        
        print_vector(v);
        cout << "We will erase all 2\n";

    auto new_end = remove(v.begin(), v.end(), 2);

        print_vector(v);

    v.erase(new_end, end(v));

        cout << "Erase elements: \n";
        print_vector(v);

        cout << "We will erase all element > 5 \n";
        print_vector(v);

    auto new_end2 = remove_if(v.begin(), v.end(), [](auto it){return((it) > 5);});
        cout << "After remove_if: \n";
        print_vector(v);

    v.erase(new_end2, v.end());
        cout << "After erase\n: ";
        print_vector(v);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 2: Fast remove elemnt

/* Normally removing element from the middle of a vector is costly - beacouse we need to reallocae memory and vector
    has to copy data. However, if we do not care of the element sorder, we can remove any (one) element 
    in the middle of vector just by overriding it by last element of the vector and removing last
    element of a vector, which is much more effective (we just move the end pointer, no need to copy and realocate anythink).

    What can be costly is copying last element of the vector to the plase of removed. If the vector contains 
    large elements, we can use std::move instead of copy to save some resources.

    EXAMPLE:
*/

void quick_remove_at(vector<int> &v, vector<int>::iterator it)
{
    if (it != end(v))
    {
        *it = move(v.back());
        v.pop_back();
    }
}

void quick_erase_example()
{
        cout << "Quick erase recepie \n\n";
        cout << "Vector at the beginning:\n";
    
    vector<int> v{1, 2, 3, 2, 5, 2, 7, 8};
        
        print_vector(v);
        cout << "We will erase number 3\n";

    auto it = find(v.begin(), v.end(), 3);
    quick_remove_at(v, it);

        cout << "After erase elements: \n";
        print_vector(v);
}


void vector_example()
{
    cout << "Vector recepies examples!  \n\n";
    erase_remove_recipie();
    quick_erase_example();
}