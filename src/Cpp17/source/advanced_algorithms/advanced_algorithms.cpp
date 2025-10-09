#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <complex>
#include <valarray>
#include <numeric>
#include <vector>
#include <cmath>
#include <list>
#include <optional>
#include <functional>
#include "advanced_algorithms.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: Trei tree example

/* Trie tree is a specialdata structure that reduces size of elements. Of we put 2 ranges to trie structure, 
and that 2 ranges would have the same beggining, the beggining will be common for each record.


Example: we have ranges 1,2,3 and 1,2,5. The trie will look like;

1 - 2 - 3
     \- 5

Using STL algorithms we can simply apply trie structure tree.

*/

template<typename T>
class Trie
{
    map<T, Trie> tries; //Each trie node is a map, that maps element and assigne it to next node.

public:
    template<typename It>
    void insert(It it, It end_it)
    {
        if (it == end_it) {return;}
        tries[*it].insert(next(it), end_it);   //Go threw nodes in recursive manner. The [] operator will look for a key or insert a new node, if key is not present.
    }

    template<typename C>
    void insert(const C &container)
    {
        insert(container.begin(), container.end());
    }

    void insert(const initializer_list<T> &il)
    {
        insert(begin(il), end(il));
    }

    void print(vector<T> &v) const
    {
        if(tries.empty())
        {
            copy(v.begin(), v.end(), ostream_iterator<T>{cout, ", "});
            cout << endl;
        }
        for(const auto &node : tries)
        {
            v.push_back(node.first);
            node.second.print(v);
            v.pop_back();                   //Use vector to recusive print - v is a list of elements to print. 
        }
    }

    void print() const{
        vector<T> v;
        print(v);
    }

    template<typename It>
    optional<reference_wrapper<const Trie>>
    subtrie(It it, It end_it) const
    {   
        if (it == end_it) {return ref(*this); } // if range is 0 - return this
        auto found (tries.find(*it));           // Find element inn tree
        if (found == end(tries)) {return {};}    // Return null obj if not found (end it returned)
        return found->second.subtrie(next(it), end_it);  //Look for next element of looked chain in tree
    }
};

void trie_tree_example()
{
    cout << "Trie tree example\n\n";

    Trie<string> t;
    t.insert({"Ala", "ma", "kota"});
    t.insert({"Ala", "poszla", "spac"});
    t.insert({"Ala", "ma", "psa"});

    cout << "Registered sentences: \n";
    t.print();

}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 2: Suggestion generator basing on trie tree

/*
With trie tree we can build suggestion generator. It is easy, just print out
subtree after pointing word being node of trie tree.

In the recepie we will use trie tree form previous example.

*/
void trie_suggestion_gen()
{
    cout <<  "Trie suggestion generator example\n\n";

    Trie<string> t;
    t.insert({"Ala", "ma", "kota"});
    t.insert({"Ala", "poszla", "spac"});
    t.insert({"Ala", "ma", "psa"});

    cout << "Please type next data: ";
    string line; 
    getline(cin, line);
    istringstream iss {line};
    if(auto st (t.subtrie(istream_iterator<string>{iss}, {})); st)
    {
        cout << "Suggestions: \n";
        st->get().print();
    } else {
        cout << "no sugestions\n";
    }

    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 3: Fourier using STL

/* The recepie presents example of making fourier transform using STL algorithms.

*/

using cmplx = complex<double>;  //Define od single fft result
using csignal = vector<cmplx>;  //Define of set of fft results

class num_iterator {            // Number iterator example (for counting sequence)
    size_t i;
public:
    explicit num_iterator(size_t position) : i{position} {}
    size_t operator*() const {return i;}
    num_iterator& operator++()
    {
        ++i;
        return *this;
    }
    bool operator!= (const num_iterator& other) const
    {
        return i != other.i;
    }
};

csignal fourier_transform(const csignal &input, bool back = false)
{
    csignal result (input.size());   //Allocate space for output data
    
    const double pol {2.0 * M_PI * (back ? -1.0 : 1.0)};    //Polarisation - 2*pi constant
    const double div {back ? 1.0 : double(input.size())};       //Divider - in signal to fouritr it will be 1.0

    auto sum_up ([=, &input](size_t j){     //Furier for single signal sub probe - count signle formula
        return [=, &input](cmplx c, size_t k) {
            return c + input[k] * polar(1.0, pol * k * j / double(input.size()));
        };
    });

    auto to_ft ([=, &input](size_t j){      //Will return sum of fourier formula from 1 to input vector size -return fourier for single singal probe
        return accumulate(num_iterator{0}, num_iterator{input.size()}, cmplx{}, sum_up(j)) / div;
    });

    transform (num_iterator{0}, num_iterator{input.size()}, begin(result), to_ft);   //That will calculate the formula
    return result;
}

static auto gen_cosine(size_t period_len) {
    return [period_len, n{0}] () mutable {
        return cos(double(n++)) * 2.0 * M_PI / period_len;  //Size wave generator with period period_len
    };
}

static auto gen_square(size_t period_len)
{
    return [period_len, n{0}] () mutable {      //n{0} - initial phase = 0 !
        return ((n++ * 2 / period_len) % 2) * 2 - 1.0;
    };
}

static void print_signal(const csignal& s)
{
    auto real_val ([](cmplx x){return x.real();});
    transform(s.begin(), s.end(), ostream_iterator<double>{cout, " ,"}, real_val);
    cout << endl;
}

void fourier_example()
{
    cout << "Fourier exaple\n\n";

    //Generate input signals:
    const size_t signal_len {100};
    csignal cosine (signal_len);
    csignal square (signal_len);
    generate(cosine.begin(), cosine.end(), gen_cosine(signal_len/2));
    generate(square.begin(), square.end(), gen_square(signal_len/2));
    cout << "Input signal cosine: \n";
    print_signal(cosine);

    cout << "Fourier cosine:\n";
    print_signal(fourier_transform(cosine));

    cout << "Input signal square: \n";
    print_signal(square);

    cout << "Fourier square:\n";
    print_signal(fourier_transform(square));
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 4: Vector error example

/* In the recepie we will use STL to calculate error between 2 vectors.

The error will be calculated as sum od square differences of each vector element.
*/

void vector_error_example()
{
    cout << "Vector error example\n\n";

    const size_t sig_len {20};
    vector<double> origin_sig (sig_len);
    vector<int>    disrupted_sig (sig_len);     //We will calculate error between disrupted and origin signal. The disruptation is of mapping doubles to ints.

    auto sin_gen ([n{0}] () mutable {   //Sine signal generation
        return 5.0 * sin(n++ * 2.0 * M_PI / sig_len);
    });

    generate(origin_sig.begin(), origin_sig.end(), sin_gen);

    transform (origin_sig.begin(), origin_sig.end(), disrupted_sig.begin(), [](double x){return static_cast<int>(x);});

    cout << "Origin signal: ";
    copy(origin_sig.begin(), origin_sig.end(), ostream_iterator<double>{cout, ", "});

    cout << endl << "Disarupted signal: ";
    copy(disrupted_sig.begin(), disrupted_sig.end(), ostream_iterator<int>{cout, ", "});

    cout << endl << "Error: " << inner_product(origin_sig.begin(), origin_sig.end(), disrupted_sig.begin(), 
        0.0, std::plus<double>{}, [](double a, double b) {
            return pow(a-b, 2);
        }
    ) << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 5: Mandlebort example

using cplx = complex<double>;

// Scaller - will convert coordinates of complex types to mandelbort coordinates
static auto scaler(int min_from, int max_from, double min_to, double max_to)
{
    const int w_from {max_from - min_from};
    const double w_to {max_to - min_to};
    const int mid_from {(max_from - min_from) / 2 + min_from};
    const double mid_to {(max_to - min_to) / 2.0 + min_to};
    return [=](int from) {
        return double(from - mid_from) / w_from * w_to + mid_to;
    };
}

template<typename A, typename B>
static auto scaled_cmplx(A scaler_x, B scaler_y)
{
    return [=](int x, int y) {
        return cmplx{scaler_x(x), scaler_y(y)};
    };
}

static auto mandelbort_iterations(cplx c)
{
    cplx z {};
    size_t iterations = 0;
    const size_t max_iterations = 1000;
    while(abs(z) < 2 && iterations < max_iterations) {
        ++iterations;
        z = pow(z, 2) + c;
    }
    return iterations;
}

void mandelbort_example()
{
    cout << "Manderbolt example\n\n";

    //Scalling section - we will keep results in linear vector, so we need to scale manderbold
    // space to the vector space
    const size_t w = 100;
    const size_t h = 40;
    auto scale (scaled_cmplx(
        scaler(0, w, -2.0, 1.0),
        scaler(0, h, -1.0, 1.0)
    ));

    auto i_to_xy ([=](int i){return scale(i%w, i/w);});

    auto to_iteration_count ([=](int i) {
        return mandelbort_iterations(i_to_xy(i));
    });

    // Here the manderbolt result will be stored in v.
    vector<int> v (w * h);
    iota(begin(v), end(v), 0);
    transform (begin(v), end(v), begin(v), to_iteration_count);

    // Printing section
    auto binfunc ([w, n{0}] (auto output_it, int x) mutable {
        *++output_it = (x > 50 ? '*' : ' ');
        if (++n % w == 0) {++output_it = '\n';}
        return output_it;
    });

    accumulate(v.begin(), v.end(), ostream_iterator<char>{cout}, binfunc);

}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 6: Splitting algorithm

/* In the recepie we will create complex algorithm using basic algorithm. The algorithm
will split input data by given element to output container */

template<typename InIt, typename OutIt, typename T, typename F>
InIt split(InIt it_begin, InIt it_end, OutIt it_dest, T splitval, F binfunc)
{
    while(it_begin != it_end)
    {
        auto range_it_end = find(it_begin, it_end, splitval);
        *it_dest++ = binfunc(it_begin, range_it_end);
        if (range_it_end == it_end) {return it_end;}
        it_begin = next(range_it_end);
    }
    return it_begin;
}

void split_example()
{
    cout << "Split example\n\n";

    string s{"a-b-c-d-e-f-g-h"};
    cout << "String will by splitted by - sign. String to split: " << s << endl;

    list<string> l;
    auto binfunc = [](auto it1, auto it2){return string(it1, it2);};
    split(s.begin(), s.end(), back_inserter(l), '-', binfunc);

    cout << "Splitted: \n";
    copy(l.begin(), l.end(), ostream_iterator<string>{cout, ", "});
    cout << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 7: Geather function example

/* Geather is a function that reorders range to have all pointed elements
close to pointed position in the range. Example:
*/

template <typename It, typename F>
pair<It, It> geather(It first, It last, It geather_pos, F predictate)
{
    return {
        stable_partition(first, geather_pos, not_fn(predictate)),
        stable_partition(geather_pos, last, predictate)
    };
}

template<typename It>
void geather_sort(It first, It last, It geather_pos)
{
    using T = typename std::iterator_traits<It>::value_type;
    stable_sort(first, geather_pos, greater<T>{});
    stable_sort(geather_pos, last, less<T>{});
}

void geather_example()
{
    cout << "Geather example \n\n";
    string s {"a-a-a-a-a-a-a"};
    cout << "Input string: " << s << endl;
    auto middle = (s.begin() + s.size() / 2);
    auto is_a = [](char c){return c == 'a';};
    geather(s.begin(), s.end(), middle, is_a);
    cout << "Geathered string: " << s << endl;

    string s2 {"b-b-b-b-b-b-b"};
    cout << "Input string: " << s2 << endl;
    auto middle2 = (s2.begin() + s2.size() / 2);
    geather_sort(s2.begin(), s2.end(), middle2);
    cout << "Geathered sort (element is - ) string: " << s2 << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 8: White sign remove example:

/*
In the recepie we will use unique algorithm with predictate for removing not needed white spaces from text.
*/

template <typename It>
It remove_white_spaces(It begin, It end)
{
    return unique(begin, end, [](const auto &a, const auto &b){
        return isspace(a) && isspace(b);
    });
}

void white_sign_remove_example()
{
    cout << "White signs remove example\n\n";
    string s{"Ala   ma        kota"};
    cout << "Input string: " << s << endl;
    auto it = remove_white_spaces(s.begin(), s.end());
    s.erase(it, s.end());
    cout << "String with removed not needed whitespaces: " << s << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 9: Compress and decompress 

/*
In the recepie we will implement algorithm for compressing strings like in example:

aaabbc -> 3a2b1c
*/

//The method will return counting of occurences of sign given by it
template<typename It>
tuple<It, char, size_t> occurences(It it, It end_it)
{
    if (it == end_it) { return {it, '?', 0};}
    const char c {*it};
    const auto diff (find_if(it, end_it, [c](char x) {return c != x;}));
    return {diff, c, distance(it, diff)};
}

//Compress function
string compress(const string &s)
{
    const auto end_it (s.end());
    stringstream r;

    for (auto it (s.begin()); it != end_it;)
    {
        const auto [next_diff, c, n] (occurences(it, end_it));  //Count the occurances of ranges
        r << c << n;    //Put char and its counter to string
        it = next_diff; //Move iterator
    }
    return r.str();
}

//Decompress function
string decompress(const string &s)
{
    stringstream ss{s};
    stringstream r;
    char c;
    size_t n;
    while (ss >> c >> n) {r << string(n, c); }  //For each element in ss make string on n elements of char c and put to stream
    return r.str(); //String the stream
}

void compress_example()
{
    cout << "Compress example \n\n";
    string s {"aaaaaaaaaaaaaaaaabbbbbbbbbbbbbb"};
    cout << "Input string to compress: " << s << endl;

    cout << "Compressed string: " << compress(s) << endl;
    cout << "Decompressed string: " << decompress(compress(s)) << endl;
}

void advanced_algorithms_example()
{
    cout << "Advanced algorithms\n\n";

    trie_tree_example();

    trie_suggestion_gen();

    fourier_example();

    vector_error_example();

    mandelbort_example();

    split_example();

    geather_example();

    white_sign_remove_example();

    compress_example();
}