/* This file contains recepie 7 of file system */

#include <filesystem>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <string>

using namespace std;
using namespace filesystem;

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 7: File size stats

/* In the recepie we will recursively iterate threw catalogue, and calculate sum of sizes
of files of each type (extension). Then, we return average files sizes.
*/

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

//Helper function - return extensions and sizes of files in dir
static map<string, pair<size_t, size_t>> ext_stats(const path& dir)
{
    map<string, pair<size_t, size_t>> m;
    for (const auto &entry : recursive_directory_iterator{dir})
    {
        const path p = entry.path();

        const file_status fs = status(p);
        if (is_directory(fs)) {continue;}   //Skip dirs

        const string ext = p.extension().string();
        if (ext.length() == 0) {continue;}  //Skip files w-o extensions

        const size_t size = file_size(p);
        auto &[size_accum, count] = m[ext];
        size_accum += size;
        count += 1;
    }
    return m;
}

int main(int argc, char* argv[])
{
    path dir {argc > 1 ? argv[1] : "."}; //If given, use given path, else use current path

    if (!exists(dir))
    {
        cout << "Path " << dir << " does not exists!\n";
        return 1;
    }

    for (const auto &[ext, status] : ext_stats(dir)) 
    {
        const auto &[accum_size, count] = status;    //Unpack pair
        cout << setw(15) << left << ext << ": "
        << setw(4) << right << count
        << " elements of average size: " << setw(4)
        << size_strings(accum_size/count) << endl;
    }

}