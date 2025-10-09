/* This file contains all recepies regarding file system processing */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <filesystem>

#include "file_systems.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: Convert relative path to absolute

/* In the recepie we will use canninical() function from filesystem namespace introduced on C++17
to get absolute path from its relative form.
*/

void cannonical_path_example()
{
    cout << "Cannonical path example \n\n";

    string input_path = ".";
    string cannonical_path;

    if (!filesystem::exists(input_path))
    {
        cout << "Input path does not exists! \n";
    }
    else
    {
        cannonical_path = filesystem::canonical(input_path);
    }

    cout << "Indirect path: " << input_path << endl;
    cout << "Cannonical path: " << cannonical_path << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 2: Cannonical vs relative paths - more features

/* In the recepie we will present more features of filesystem namespace. */

void filesystem_path_features()
{
    cout << "Filesystem path features \n\n";

    //Example 1: Path operations
    cout << "Current path: " << filesystem::current_path() << endl;
    cout << "Absolute path of . :" << filesystem::absolute(".") << endl;
    cout << "Canonical path of . :" << filesystem::canonical(".") << endl;
    //Might be out of current compiler supported version of standard!
    //cout << "System complete path of . :" << filesystem::system_complete(".") << endl;

    //Example 2: concat paths
    cout << "Concated path of . and foo.txt: " << filesystem::current_path() / "foo.txt" << endl;

    //Example 3: compare paths
    cout << "Equivalence: " << filesystem::equivalent(".", "/repo/build") << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 3: Tool for listing direcotry content

/* In the recepie we will implement silmple tool for listing direcotry content, like ls tool. */

//Helper functions:
//That function will give information about single file - path, name, type, access rignts of the file
static tuple<filesystem::path, filesystem::file_status, size_t> file_info(const filesystem::directory_entry& entry)
{
    const auto fs (filesystem::status(entry));  //Get file info
    return {
        entry.path(),   //File path
        fs,             //File info
        filesystem::is_regular_file(fs) ? filesystem::file_size(entry.path()) : 0u  //File size or 0 if not a file 
    };
}

//That function will return appropriate char according to dir element type (file, symlink, dir etc...)
static char type_char(filesystem::file_status fs)
{
         if (filesystem::is_directory(fs))      {return 'd';}
    else if (filesystem::is_symlink(fs))        {return 'l';}
    else if (filesystem::is_character_file(fs)) {return 'c';}
    else if (filesystem::is_block_file(fs))     {return 'b';}
    else if (filesystem::is_fifo(fs))           {return 'p';}
    else if (filesystem::is_socket(fs))         {return 's';}
    else if (filesystem::is_other(fs))          {return 'o';}
    else if (filesystem::is_regular_file(fs))   {return 'f';}
    return '?';
}

//That function will accept perms type (permissions) and return permissions in rwx type
static string rwx(filesystem::perms p)
{
    auto check ([p](filesystem::perms bit, char c){
        return (p & bit) == filesystem::perms::none ? '-' : c;
    });

    return {
        check(filesystem::perms::owner_read,  'r'),
        check(filesystem::perms::owner_write, 'w'),
        check(filesystem::perms::owner_exec,  'x'),
        check(filesystem::perms::group_read,  'r'),
        check(filesystem::perms::group_write, 'w'),
        check(filesystem::perms::group_exec,  'x'),
        check(filesystem::perms::others_read,  'r'),
        check(filesystem::perms::others_write, 'w'),
        check(filesystem::perms::others_exec,  'x'),
    };
}

//That function will convert file size to more readable format
static string size_strings(size_t size)
{
    stringstream ss;
    if (size >= 1000000000) {
        ss << (size/1000000000) << 'G';
    }
    else if (size >= 1000000) {
        ss << (size/1000000) << 'M';
    }
    else if (size >= 1000) {
        ss << (size/1000) << 'k';
    }
    else
    {
        ss << size << 'B';
    }
    return ss.str();
}

void ls_tool_example()
{
    cout << "Listing direcotry content tool example \n";
    string dir = ".";
    cout << "Listing urrent dir: " << dir << endl;

    if (!filesystem::exists(dir))
    {
        cout << "Direcotry " << dir << " does not exists! \n\n";
    }
    else
    {
        vector<tuple<filesystem::path, filesystem::file_status, size_t>> items;
        transform(filesystem::directory_iterator{dir}, {}, back_inserter(items), file_info);

        for (const auto& [path, status, size] : items)
        {
            cout << type_char(status) 
            << rwx(status.permissions()) << " "
            << setw(4) << right << size_strings(size)
            << " " << path.filename().c_str() << endl;
        }
        cout << endl << endl;
    }

}

void file_systems_example()
{
    cout << "File system example\n\n!";

    cannonical_path_example();

    filesystem_path_features();

    ls_tool_example();
}