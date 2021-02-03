/* This file contains recepie 5 of file system */

#include <filesystem>
#include <vector>
#include <iostream>
#include <regex>

using namespace std;
using namespace filesystem;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 5: File name changer tool

/* In that recepie we will create simple program that will change given filename pattern to othr pattern
in current directory, recursively */

//Helper function - accepts filepath, matches it to all of given regex list and replaces the filename if matched
template<typename T>
static string replace(string s, const T& replacements)
{
    for (const auto& [pattern, rep] : replacements)
    {
        s = regex_replace(s, pattern, rep);
    }
    return s;
}

int main(int argc, char* argv[])
{
    //Checnk if valid nr of args has been given
    if (argc < 3 || argc % 2 != 1)      
    {
        cout << "Usage: " << argv[0] << " <pattern> <replacement>\n";
        return 1;
    }

    //Out pattern and replacements into vector
    vector<pair<regex, string>> patterns;
    for (int i = 1; i < argc; i += 2)
    {
        patterns.emplace_back(argv[i], argv[i + 1]);
    }

    for (const auto& entry : recursive_directory_iterator{current_path()})
    {
        path opath {entry.path()};      //Get currently iterated path
        string rname {replace(opath.filename().string(), patterns)};    //Make replacement
        path rpath {opath};
        rpath.replace_filename(rname);
        if (opath != rpath) //If name changed
        {
            cout << opath.c_str() << " --> "
            << rpath.filename().c_str() << endl;
            if (exists(rpath))
            {
                cout << "Error! Cannot change filename. File with new name already exists!\n";
            } else {
                rename(opath, rpath);   //Replace the names
            }
        }
    }
}
