/* This file contains recepie 8 of file system */

#include <filesystem>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;
using namespace filesystem;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 8: File cleaner tool

/* In that recepie we will create simple program for cleaning space on the disk. The program will
look for files that has same content, and create symlinks in place of duplicates. */

//Helper function - calculates hash value from file in given path
static size_t hash_from_path (const path& p)
{
    ifstream is {p.c_str(), ios::in | ios::binary};

    if (!is) {throw errno;} //Throw error if no file found

    string s;

    is.seekg(0, ios::end);
    s.reserve(is.tellg());
    is.seekg(0, ios::beg);
    s.assign(istreambuf_iterator<char>{is}, {});
    return hash<string>{}(s);
}

//Helper function - will reduce duplicates
static size_t reduce_dupes(const path& dir)
{
    unordered_map<size_t, path> m;
    size_t count{0};    //Nr of duplicates
    for (const auto& entry : recursive_directory_iterator{dir})
    {
        const path p {entry.path()};
        if (is_directory(p)) {continue;}    //Skip dirs
        const auto &[it, success] = m.try_emplace(hash_from_path(p), p);    //If such key is already in map - (means we found duplicate) it will not be added
        if (!success) { //If not has been added -> duplicate
            cout << "Removed file: " << p.c_str() << "as a duplicate of " << it->second.c_str() << '\n';
            remove(p);
            create_symlink(absolute(p), p);
            ++count;
        }
    }
    return count;
}
int main(int argc, char* argv[])
{
    //Checnk if valid nr of args has been given
    if (argc != 2)      
    {
        cout << "Usage: " << argv[0] << " <path>\n";
        return 1;
    }

    //Check given path
    path dir {argv[1]};
    if (!exists(dir))
    {
        cout << "Input path does not exists! " << endl;
    }

    //Look for duplicates
    const size_t dups {reduce_dupes(dir)};
    cout << "Removed " << dups << " duplicates!\n\n";
}
