/* Ways of initialization:

In cpp we have general 3 ways of initializations:
-> By "= value", ex:      auto a = 2 or int a = 2
    Here no changes were applied between C++17 and older standards. The compiler will use assignment operator to assign variable value.
    In that situation we will get int variable (auto used). Moreover, if we explicitly define type of the variable, we have also implicit conversion.
    For example, int a = 1.3 will give 1 in a variable, beacouse compiler will implicitly convert tve value. In case of containers,
    copy assignment operator will be used.

-> By "= {}", ex. auto a = {2}

    Here we have some changes.
    Explicit type:
        If we have explicit type and one variable, like int a = {2}, the compiler in old and new standards will assign it as int with 2.
        If we initialize container, we will have different behavior in old and new standard. vector<int> a = {1, 2} will gove vector of ints with elements
        1 and 2.

    Implicit type:
        If we have implicit type and one variable, in old standard initializer_list<int> would be used with only one elment. If we type auto a = {1.1} in old
        standard, we will get int. In cpp17, compilwe will find proper type and act like initialization by assignmnet or (). For example, auto a = {1.1} will
        give float of value 1.1.

        If we have container, in old standard we will get initializer_list<T>, where T is class of container. In case of auto, type of container
        elements will be assumed as int (in old standard). In new standard, it will be type of all elements in the list. If we have no same type for all
        elements, we will get an error.    
    
    
    In case of vector<int> a = {1, 2, 3} we will get
    vector of 3 elements. However, if we would like to assign more than one element in such way with auto, we will get an error, ex. auto a = {1, 2, 3} will not
    work as compiler cannot assume any type.

-> By {}, ex:       auto a{2}
    Here we have some changes. We can do it with type auto or with explicit type.
    Explicit type:
        We will get explicit initializer list of the variable, ex. int a{2} will give int a of value 2; and vector<int> a {1,2} will give 2-element
        vector of int. Here we have no implicit type conversion, so if we give int a{1.2} we will get an error.

    Implicit type (with auto)
        We can only use for 1 element in {}. For example, if we use auto a{2} we will get int with value of 2. Moreover, in that case, there is no 
        implicit type conversion. Initialization more than one elent in that way is forbidden with auto.

-> By (), ex:       auto a(2)
    Here we have some changes as well:
        Constructor will be used.

*/

#include <iostream>
#include <vector>

using namespace std;

void way_of_initialization_example()
{
    //Explicit types
    int a1 = 1;         // Copy assignment used
    int a2 = {1};       // cpp17: will find proper constructor for type given in rvalue (int); in cpp11 it will we initialize_list<int>
    int a3{1};          // explicit type int init. No implicit type conversion, so a3{1.2} will give error
    int a4(1);          // Constructor used

    vector<int> v1 = {1, 2, 3};    //3 - element vector if ints, std initializer_list used
    vector<int> v2{1, 2, 3};       // Like above
    vector<int> v3(2, 3);          // Fit constructor, here we will get 2 element vector of 3

    cout << "Ways of initialization \n\n";
    cout << "Explicit types: \n\n";
    cout << "int a1 = 1 gives: " << a1 << endl << "int a2 = {1} gives " << a2 << endl << "int a3{1} gives: " << a3 << endl << "int a4(1) gives :" << a4 << endl;
    
       //Implicit types
    auto b1 = 1;         // Copy assignment used, int assumed by r-value type
    auto b2 = {1};       // cpp17: will find proper constructor for type given in rvalue (int); in cpp11 it will we initialize_list<int>
    auto b3{1};          // explicit type int init by r-value type
    auto b4(1);          // Constructor used, int assumed by r-value type

    auto w1 = {1, 2, 3};    //3 - element vector if ints, std initializer_list used
    //auto v2{1, 2, 3};       // Forbidden
    //auto w3(2, 3);          // Forbidden, no known type

    cout << "Ways of initialization \n\n";
    cout << "Implicit types: \n\n";
    cout << "int b1 = 1 gives: " << b1 << endl << "int b2 = {1} gives initializer_list<>" << endl << "int b3{1} gives: " << b3 << endl << "int b4(1) gives :" << b4 << endl;
   }

