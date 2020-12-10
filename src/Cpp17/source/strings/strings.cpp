/* This file contains all recepies regarding STL algorithms */

#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>
#include "strings.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: String basics

/* In the recepie concatenation an creation of strings will be shown */


void basics_example()
{
    cout << "Basics example\n\n";

    // String init
    string s1 {"abc"s};
    string_view sw1 {"swq"sv};  //New cpp17 type - string view. This will not copy all char chain, only the reference to it.

    cout << "String: " << s1 << "String view: " << sw1 << endl;

    //Concat
    string sc = s1 + "qqw";
    string scw = s1 + string{sw1};  //To concat string view we have to make string on it first. We cannot just concat - beacouse it has no chars inside.

    cout << "Concat string: " << sc << " Concat string view: " << scw << endl;

    //Convert small to upper letters
    cout << "Capital letters conversion: ";
    transform(sc.begin(), sc.end(), ostream_iterator<char>{cout}, ::toupper);
    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 2: White signs remover

/* In that recepie we will implement function that removes white signs from beggining and end of string
*/

string white_signs_removal(string s)
{
    const auto white_signs {" \t\n"};
    const auto first = s.find_first_not_of(white_signs);
    if (first == string::npos) {return {};}
    auto last = s.find_last_not_of(white_signs);
    if (last == string::npos) {last = s.size();};
    return s.substr(first, last - first + 1);
}

void white_letters_remove_example()
{
    cout << "WHite letters remove example\n\n";
    string s {"         Hello world         "};
    cout << "Initial string: {" << s << "}\n";
    string s2 = white_signs_removal(s);
    cout << "After remove: {" << s2 << "}\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 3: White signs remover - string view

/* String view class - provides string interface without need of keeping copy
of string inside string object. String view keeps only reference to c-style string chain. It can be 
used in all elements that accepts string interface (or iterators), but uses it
like c style char array.

*/

string_view white_signs_removal_SV(string_view s)
{
    const auto white_signs {" \t\n"};
    const auto first = s.find_first_not_of(white_signs);
    s.remove_prefix(min(s.size(), first));  //As first, if not found is sting_view::nops, which is -1, maped to int will be very large number, we can use min().
    const auto last = s.find_last_not_of(white_signs);
    if (last != string_view::npos)
    {
        s.remove_suffix(s.size() - last - 1);
    }
    return s;
}

void white_letters_remove_example_SV()
{
    cout << "White letters with string view remove example\n\n";
    string_view s {"         Hello world         "sv};
    cout << "Initial string: {" << s << "}\n";
    string_view s2 = white_signs_removal_SV(s);
    cout << "After remove: {" << s2 << "}\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 4: String cin example

/* In the recepie we will show cin usage example and error handling */

void cin_example()
{
    cout << "Cin example\n";
    cout << "Type 2 numbers: int and double: ";
    int x;
    double y;
    if(cin >> x >> y)   // Cast cin to bool will return true if last operation succeed
    {
        cout << "Fine. Your numbers are: int: " << x << " and y: " << y << endl;
    }else{
        cout << "You have typed wrong data! " << endl;
        cin.clear();    // Will reset error state of cin
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //Will clear cin buffer untill last '\n' sign.
    }

    cout << "Type name and surname: ";
    string name;
    getline(cin >> ws, name, ',');  //Getline will set up separator, and cin >> ws will remove spaces around name and surname
    if (name.empty())
    {
        cout << "You typed wrong name and surname data! ";
    }else{
        cout << "Name and surname: " << name << endl;
    }
    cout << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 5: Counting words in input data

/* In the recepie we will count words in input data using stream */

template <typename T>
size_t num_of_words(T& is)
{
    return distance(istream_iterator<string>{is}, {});
}

void counting_words_example()
{
    cout << "Counting words example\n";
    string s {"Ala ma kota, kot ma ale"};
    cout << "We will count nr of words in sentence: " << s << endl;
    istringstream ss{s};
    cout << "Number of words: " << num_of_words(ss) << endl;
}

void strings_example()
{
    cout << "Strings example! \n\n";

    basics_example();

    white_letters_remove_example();

    white_letters_remove_example_SV();

    cin_example();

    counting_words_example();
}
