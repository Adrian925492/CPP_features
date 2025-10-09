/* This file contains all recepies regarding multimaps */

#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <set>
#include <iterator>
#include <vector>
#include "multimap.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: Using multimap for implementing tool for searching long sentences in text

/* That recepie uses multimap features, that it keeps sorted elements, but can have same key many times.

Input data is string with some sentences. The goal is to sort the sentences according to its lenght. The
sentences will be written into multimap, where value is sentence, and key is lenght of the sentence.

Example:

*/

static string filter_ws(const string& input)
{
    const char *ws {" \r\n\t"};
    const auto a (input.find_first_not_of(ws));
    const auto b (input.find_last_not_of(ws));  //Find iterators of first and last element not of ws

    if (a == string::npos)
    {
        return {};  //If a is none - we passed only whitespaces - return empty string
    }
    return input.substr(a, b);  //Return substring wo ws
}

multimap<int, string> sentence_calculator(string input)
{
    multimap<int, string> sorted {};

    const auto it_end = input.end();
    auto it1 = input.begin();
    auto it2 = find(it1, it_end, '.');  //it 1 and 2 - between 1st sentence

    while(it1 != it_end && distance(it1, it2) > 0)
    {
        string s {filter_ws({it1, it2})};

        if (s.length() > 0)
        {
            const auto words (s.length());
            sorted.emplace(make_pair(words, move(s)));
        }

        it1 = next(it2, 1);
        it2 = find(it1, it_end, '.');
    }

    return sorted;
}

void sentence_lenght_example()
{
    cout << "Sentence lenght calculating tool example \n\n";
    string input_data = "Hellow world. I am albe to write for You. My name is sentence reader. Good job.";

    cout << "The goal is to process sentence: " << input_data << "\n\n" << "results:\n";

    multimap<int, string> sorted = sentence_calculator(input_data);

    for(const auto & [counter, sentence] : sorted)
    {
        cout << counter << " : " << sentence << "\n";
    }
}



void multimap_example()
{
    cout << "Multimap recepies examples!  \n\n";

    sentence_lenght_example();

}