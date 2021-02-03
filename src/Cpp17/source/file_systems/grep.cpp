/* This file contains recepie 4 of file system */

#include <filesystem>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;
using namespace filesystem;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 4: Grep tool

/* In that recepie we will create simple equivalent of grep tool. The tool will look for
file mathich the pattern recursively, in current directory */

//Helper function - accepts filepath, opens the file and looks for regex match in the file line by line
static vector<pair<size_t, string>> matches (const path& p, const regex& re)
{
    vector<pair<size_t, string>> d;
    ifstream is {p.c_str()};
    string s;
    for (size_t line = 1; getline(is, s); ++line)
    {
        if (regex_search(s.begin(), s.end(), re))
        {
            d.emplace_back(line, move(s));
        }
    }
    return d;
}

int main(int argc, char* argv[])
{
    //Checnk if valid nr of args has been given
    if (argc != 2)      
    {
        cout << "Usage: " << argv[0] << " <pattern>\n";
        return 1;
    }

    //Check pattern arg
    regex pattern;
    try {pattern = regex{argv[1]}; }
    catch (const regex_error &e)
    {
        cout << "Wrong pattern ! ";
        return 1;
    }

    //Look for matches
    for(const auto& entry : recursive_directory_iterator{current_path()})  //Look recursively in current path
    {
        auto ms (matches(entry.path(), pattern));
        for (const auto &[number, content] : ms)
        {
            cout << entry.path().c_str() << " : " << number << " - " << content << endl;
        }
    }
}
