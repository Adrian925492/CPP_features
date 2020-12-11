/* This file contains all recepies regarding STL algorithms */

#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <locale>
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

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 6: Stream formatting

/* In the recepie we will present examples of string formattings */

//Helper function
void print_aligned_demo(int val, size_t width, char fill_char = ' ')
{
    cout << "=============================\n";
    cout << setfill(fill_char); //Sets nr of chars to fill align
    cout << left << setw(width) << val << endl;
    cout << right << setw(width) << val << endl;
    cout << internal << setw(width) << val << endl;
}

void string_formatting_example()
{
    cout << "String_formatting_example\n\n";
    
    // Print alignment
    print_aligned_demo(123456, 15);
    print_aligned_demo(123456, 15, '_');

    // Data type print
    cout << hex << showbase;        // Will stear if print value as hex with base (0x), as oct or dec
    print_aligned_demo(0x123abc, 15);

    cout << oct;
    print_aligned_demo(123456, 15);

    cout << "Hex with capital letters: " << hex << uppercase << 0x123abc << endl;

    cout << "Liczba: " << 100 << endl;
    cout << dec;
    cout << "Dec type: liczba: " << 100 << endl;

    // True ansd false boolean
    cout << "True and false bollen: " << false << " " << true << endl;
    cout << "True and false ascii: " << boolalpha << false << " " << true << endl;  // Will print boolean as ascii true/false

    //Double numbers
    cout << "Double numbers: " 
    << 12.3 << ", " 
    << 12.0 << ", "
    << showpoint << 12.0 << endl;   //Showpoint will show fraction even if it is 0

    // Notation
    cout << "Double in scientific notation: " << scientific << 123.000000000003 << endl;    // Will print as 123e...
    cout << "Double in normal notation: " << fixed << 123.000000000003 << endl;

    // Number precision
    cout << "Precision number to 10: " << setprecision(10) << 0.0000000001 << endl;
    cout << "Precision number to 1: " << setprecision(1) << 0.0000000001 << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 7: Stream operator overload

/* In the example we will overload stream operator to obtain ability of 
in/out user defined data structures */

struct cities
{
    string name;
    int population;
    int size;
};

ostream& operator << (ostream& os, cities data)
{
    cout << "City name: " << data.name << ", pop: " << data.population << " ,size: " << data.size << endl;
    return os;
}   

void stream_overload_example()
{
    cout << "Stream overload example\n\n";

    vector<cities> c{
        {"Warszawa", 300000, 12500},
        {"Wroclaw", 342304, 1233},
        {"Gdansk" ,12300, 123000}
    };

    // Cout overloaded
    for (auto& v : c) cout << v;
}


void strings_example()
{
    cout << "Strings example! \n\n";

    basics_example();

    white_letters_remove_example();

    white_letters_remove_example_SV();

    cin_example();

    counting_words_example();

    string_formatting_example();

    stream_overload_example();
}
