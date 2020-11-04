/* 
if constexpr is new syntax, that works like standard if ... else, but on compile time.

As it works on compile time, it has to operate on elements kniwn in compile time. It can be for example types
given by template (or values)

Using it we can selectivly use blocks of code without any extra runtime code basing on type given to template.

Just like okd #if ... #endif syntax, byt with syntax check on compile time.

*/

#include <iostream>
#include <vector>

using namespace std;

// Exmaple

template<typename T>        //generic addable class
class addable
{
public:
    T val;
    template <typename U>
    T add(U x) const
    {
        if constexpr (std::is_same_v<T, std::vector<U>>) {  //If T is vector
            auto copy(val);     // copy val variable (container)
            for (auto &n : copy)
            {
                n += x;     //add x to each element of container
            }  
            return copy;    // And return elements with added values
        } else {
            return x + val;
        }
    }
};

void constexpr_if_example()
{
    cout << "COnstexpr if example\n\n";

    addable<int> a{2};
    int a1 = a.add(3);
    cout << "Add int to int: result 2 + 3 = " << a1 << endl;

    vector<int> vec = {3, 6};
    addable<vector<int>> v{vec};
    vector<int> v1 = v.add(2);
    cout << "Add int to vector: result 2 + [ 3, 6] = ";
    for(auto& el : v1) cout << el << " ";
    cout << endl;

}