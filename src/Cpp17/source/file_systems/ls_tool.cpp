/* This file contains recepie 6 of file system */

#include <filesystem>
#include <vector>
#include <iostream>
#include <regex>
#include <iomanip>
#include <numeric>

using namespace std;
using namespace filesystem;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 6: Direcotry sizer

/* In the recepie we eill create program that iterates threw whole directory and prints
    size of its files and subdirs */

//Helper function - calculates size of given directory entry
size_t sizer(const directory_entry& entry)
{
    if (!is_directory(entry))
    {
        return file_size(entry);    //Return file size if it is not directory
    } else {
        return accumulate(directory_iterator{entry}, {}, 0u, 
            [](size_t accum, const directory_entry& e)
            {
                return accum + sizer(e);    //Call recursively size calculate method
            });
    }
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

//That function will give information about single file - path, name, type, access rignts of the file
static tuple<filesystem::path, filesystem::file_status, size_t> file_info(const filesystem::directory_entry& entry)
{
    const auto fs (filesystem::status(entry));  //Get file info
    return {
        entry.path(),   //File path
        fs,             //File info
        sizer(entry)  //File size 
    };
}

int main(int argc, char* argv[])
{
    path dir {argc > 1 ? argv[1] : "."};    //Get dir from arg or use current dir

    //Check if dir exsits
    if (!exists(dir)) {
        cout << "Given directory " << dir << " does not exists! \n";
        return 1;
    }

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