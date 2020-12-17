/* This file contains all recepies regarding STL algorithms */

#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <locale>
#include <map>
#include <utility>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <regex>
#include <system_error>
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

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 8: Map parsing example

/* In the recepie we will produce map serializer using streams */

struct citydata
{
    int size;
    string department;
};
// Input stream operator for citydata - to able to add each cotudata
istream& operator >> (istream& is, citydata &d)
{
    return is >> d.size >> quoted(d.department);
}

// Input stream operator for map node - here p.second is citydata, so here we use previously defined operator >>
istream& operator >> (istream& is, pair<string, citydata> &p)
{
    return is >> quoted(p.first) >> p.second;
}

void map_serializer_example()
{
    cout << "Map serializer example\n\n";

    cout << "Data taken from text file. \n";
    map<string, citydata> m;
    ifstream ifs;
    ifs.open("/repo/CPP_features/src/Cpp17/source/strings/city_database.txt");
    copy(istream_iterator<pair<string, citydata>>{ifs}, {}, inserter(m, end(m)));   //Here we can fill in map by cin
    auto max_func ([](size_t old_max, const auto &b){return max(old_max, b.first.length());});  //Here we will find element of longest name
    size_t width {accumulate(begin(m), end(m), 0u, max_func)};   
    ifs.close();        

    // And printing
    cout << "Deserialized data: \n";
    for (const auto &[name, data] : m) {
        const auto &[size, department] = data;
        cout << left << setw(width) << name << ": " << size << ": " << department << endl;
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 9: Using output stream iterator example

/* In the recepie we will use output stream iterators for displaying data */

//Helper function - translate int to string number
string word_num(int i)
{
    unordered_map<int, string> m {
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}
    };
    auto match = m.find(i);
    if (match == m.end()) return "unexisting";
    return match -> second;
}

//Helper datatype
struct bork {
    int borks;
    bork(int i) : borks(i) {}

    void print(ostream& os) const{
        fill_n(ostream_iterator<string>{os, " "}, borks, "bork!"s);
        cout << endl;
    }
};

//Ostream operator for bork implementation
ostream& operator<<(ostream& os, const bork &b)
{
    b.print(os);
    return os;
}

void ostream_example()
{
    cout << "Ostream example \n\n";

    //Input data vector
    const vector<int> v{1,2,3,4,5};

    // Using ostream iterator for printing
    ostream_iterator<int> oit {cout};
    for (int i : v) {*oit = i;}
    cout << endl;

    ostream_iterator<int> oit_comma {cout, ", "};
    for (int i : v) {*oit_comma = i;}
    cout << endl;

    // Using ostream with algorithm
    copy(begin(v), end(v), oit);
    cout << endl;
    copy(begin(v), end(v), oit_comma);
    cout << endl;

    //Implicit conversion to ostream iterator:
    copy(begin(v), end(v), ostream_iterator<bork>{cout, ", "});

}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 10: Reirecting cout buffer

/* Each standars steam (cin, cout, cerr) object has its own data buffer which acts like
an frontend for the stream. Such buffer sor stringstream would be assigned string, and for
file strim - the file. For cout it is standard output. We can reassign such buffer if needed to
change direction of outputs. It can be usabel for example when we want not to show any infos
from library which we have to use byt we have no sources.
*/

class redirect_cout_region{
    using buftype = decltype(cout.rdbuf()); //That will get type of cout buffer
    ofstream ofs;
    buftype buffer_backup;

    public:
    explicit redirect_cout_region(const string &filename) : 
        ofs{filename}, buffer_backup{cout.rdbuf(ofs.rdbuf())} {}
    
    redirect_cout_region() : ofs{}, buffer_backup{cout.rdbuf(ofs.rdbuf())} {}

    ~redirect_cout_region() {
        cout.rdbuf(buffer_backup);  //Retirve buffer to previous version (backuped)
    }
};

void redirect_buffer_example()
{
    cout << "Redirect buffer example! \n\n";    //We will redirect outputs to a file

    cout << "Before redirect...." << endl;
    {
        redirect_cout_region _ ("cout_file.txt");
        cout << "Redirected data 1...." << endl;
        cout << "Redirected data 2...." << endl;
        cout << "Redirected data 3...." << endl;
    }
    {
        redirect_cout_region _;
        cout << "That data will not be shown at all! " << endl;
    }
    cout << "Retivered to cout." << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 11: Own string example

/* In the recepie we will create own string class basing on overrided char_traits class. The char_traits
is one of types provided for std::string. In fact, steing is just specialization of basic_string<char> class.

We can extend the specialization to: string = basic_string<char, char_traits<char>, allocator<char>>.

Char defines type of single element, char_traits class gives all algorithms needed to string (like
compaison strings), and allocator gives mechanisms for allocation and deallocation the memory.

By inheritence, we can extend char_traits class, override some mechanisms in it and use our implementation
to configure new, user defined string class.

*/

//Redefining tolow function - just to have it constexpr
static constexpr char tolow(char c)
{
    switch(c){
        case 'A'...'Z': return c - 'A' + 'a';
        default: return c;
    }
}

//LC string class will create strings with lovercase only, even if we init it hy uppercase
class lc_traits : public char_traits<char> {
    public:
    //Override method that will assign chars to its place in memory - to convert all char to lover case
        static constexpr void assign(char_type& r, const char_type& a)
        {
            r = tolow(a);
        }

    // That function will copy char chain to memory
        static char_type* copy(char_type* dest, const char_type* src, size_t count)
        {
            transform(src, src + count, dest, tolow);
            return dest;
        }
};

//CI traits class will compare strings without case sensitivity
class ci_traits : public char_traits<char> {
    public:
    // Override comparison method
        static constexpr bool eq(char_type a, char_type b) 
        {
            return tolow(a) == tolow(b);
        }
    // Override less than method
        static constexpr bool lt(char_type a, char_type b) 
        {
            return tolow(a) < tolow(b);
        }
    //Override compare method
        static constexpr int compare(const char_type* s1, const char_type* s2, size_t count)
        {
            for(; count; ++s1, ++s2, --count) {
                const char_type diff (tolow(*s1) - tolow(*s2));
                if (diff < 0) {return -1;}
                else if (diff > 0) {return 1;}
            }
            return 0;
        }
    //Override find method
        static constexpr const char_type* find(const char_type* p, size_t count, const char_type& ch) 
        {
            const char_type find_c {tolow(ch)};
            for(; count != 0; --count, ++p)
            {
                if (find_c == tolow(*p)) {return p;}
            }
            return nullptr;
        }
};

//Define string types basing on defined char traits types
using lc_string = basic_string<char, lc_traits>;
using ci_string = basic_string<char, ci_traits>;

//Define stream operators so we cound print the strings
ostream& operator<< (ostream& os, const lc_string& str)
{
    return os.write(str.data(), str.size());
}

ostream& operator<< (ostream& os, const ci_string& str)
{
    return os.write(str.data(), str.size());
}

void own_string_example()
{
    cout << "Own string example\n\n";

    cout << "string: " << string{"AlA Ma Kota"} << endl;
    cout << "lc_string: " << lc_string{"AlA Ma Kota"} << endl;
    cout << "ic_string: " << ci_string{"AlA Ma Kota"} << endl;    

    // Case sensitivity comparison check
    ci_string s1 {"Ala Ma Kota"};
    ci_string s2 {"ala ma kota"};
    if (s1 == s2)
    {
        cout << "CI string compares case insensitive! " << endl;
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 12: Regex usage example

/* In the example we will use regex to find desired elements - http links from html page 
    Regex are available from Cpp11 standard.
*/

//Heler function for printing
template<typename It>
void print(It it, It end)
{
    while(it != end)
    {
        const string link (*it++);
        if(it == end) {break;}
        const string desc (*it++);
        cout << left << setw(4) << "Link: " << setw(86) << link << " Destination: " << desc << endl;
    }
}

void regex_example()
{
    cout << "Regex example\n\n";
    cout << "We will parse file.html to find all http links. Links found: \n";

    ifstream ifs("/repo/CPP_features/src/Cpp17/source/strings/file.html");
    ifs >> noskipws;
    string input;
    copy(istream_iterator<char>{ifs}, {}, inserter(input, input.end()));
    
    //Define egex pattern
    const regex link_re {"<a href=\"([^\"]*)\"[^<]*>([^<]*)</a>"};

    // Create regex token iterator - will return next match untill no more matches. The iterator do not know its end untill reached.
    sregex_token_iterator it {begin(input), end(input), link_re, {1, 2}};
    
    print(it, {});
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 13: Format guard example

/* In the recepie we will define special class which will act as format guard. Untill
scope will be ended, it will keep streams formatted according to needs.
*/

class format_guard{
    decltype(cout.flags()) f {cout.flags()};    //Save old flags of cout - to retierve it afterwards
    public:
    ~format_guard() {cout.flags(f);}            //Set old flags in destructor - to retirve after exiting scope
};

//Helper class - will pack value we want to print in special formatting. Ostream operator<< also needed.
template<typename T>
class scientific_type {
public:
    T value;
    explicit scientific_type(T val) : value(val) {}
};

// And here we will define special formatting
template<typename T>
ostream& operator<< (ostream& os, const scientific_type<T> &w)
{
    format_guard _;
    os << scientific << uppercase << showpos;
    return os << w.value;
}

void format_guard_example()
{
    cout << "Format guard example\n\n";
    {
        format_guard _;  //The guard destructor will retirve cout to format before special manner after exiting the scope.
        cout << hex << scientific << showbase << uppercase;
        cout << "Numbers formated explicitly in special manner: \n";
        cout << 0x123abc << endl;
        cout << 0.12345 << endl;
    }
    cout << "Numbers formated explicitly in normal manner: \n";
    cout << 0x123abc << endl;
    cout << 0.12345 << endl;    
    cout << "The formatting has been resetted by format guard. \n";

    cout << "Different formatting styles: \n" 
        << 123.0 << " " << scientific_type{123.0} << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 14: Exception handling example

/* In that recepie we will handle exceptions caused by stream class */

void exception_example()
{
    cout << "Exception example\n";

    ifstream f;
    f.exceptions(f.failbit | f.badbit); //Enable exceptions from data processing and file system errors
    try {
        f.open("plik.txt");
        int i;
        f >> i;
        cout << "Number: " << i << endl;
    } catch(ios_base::failure& e) {
        cout << "Exception catched: ";
        if (errno) {    //errno keeps system error code
            cout << strerror(errno) << endl;    //strerror converts system error code to string message
        }else{
            cout << e.what() << endl;
        }
    }
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

    map_serializer_example();

    ostream_example();

    redirect_buffer_example();

    own_string_example();

    regex_example();

    format_guard_example();

    exception_example();
}
