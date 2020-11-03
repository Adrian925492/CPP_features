/* Variable range limitation, allows to make more clear code if we want to define
explicit scope (for ex. for some variable) which is not being scope of current finction, like
for lock_guard.

It is good practice to define such scopes (encapsulation).

Only foe limiting scope of variable to if or switch blocks.

syntax:

if (variable = initializer; condition) {...}
switch (variable = initializer; condition) {...}

inside {...} variable is accesible (only)

It is also type of syntatic sugar

 */

#include <iostream>
using namespace std;

void varaible_range_limitation_example()
{
    cout << "Variable range limitations example\n\n";

    cout << "Old style \n\n";
    // Old style
    {   //define extra scope
        int a = 2;
        cout << "Variable inside scope: " << a << endl;  //accesible
    }
    //cout << "Variable outside scope: " << a << endl;  //inaccesible

    cout << "New style\n\n";

    bool condition = true;
    if (int a = 2; condition)
    {
        cout << "Variable inside scope of if: " << a << endl;  //accesible
    }
    switch (int a = 2; condition)
    {
        case true:
            cout << "Variable inside scope of if: " << a << endl;  //accesible
            break;
        
        case false:
            break;
    }

}