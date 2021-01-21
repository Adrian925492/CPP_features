/* This file contains all recepies regarding parallell processing */

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>
#include <execution>
#include "parallell_processing.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 1: Policies example

/*
Execution poliy is a new feature added in C++17. It allows to set if algorithm provided by
STL would be run in sequential way (default), or parallel way. We can say it by adding 1st argumrnt
of execution policy type (optional)
*/

//Helper function
static bool odd(int n) {return n % 2;}

void using_policies()
{
    cout << "Processing policies usage example \n\n";

    vector<int> v(50000000);

    // Add function for random generating number
    mt19937 rd;
    uniform_int_distribution<int> dis(0, 100000);
    auto rand_num ([=] () mutable {return dis(rd);});

    cout << "Using generate sequentially! " << endl;
    const auto t11 = chrono::steady_clock::now();
    generate(v.begin(), v.end(), rand_num);
    const auto t12 = chrono::steady_clock::now();
    cout << "FINISH! in " << (t12 - t11).count() << " seconds" << endl;

    cout << "Using generate parallel!" << endl;
    const auto t21 = chrono::steady_clock::now();
    generate(execution::par, v.begin(), v.end(), rand_num);
    const auto t22 = chrono::steady_clock::now();
    cout << "FINISH! in " << (t22 - t21).count() << " seconds" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 2: Thread sleep example

/* From cpp11 standard new namespace was introduced - this_thread. That namsepace provides mechanisms
for acting with sleeping the thread. The sleep functions uses STL API, so are independent from used OS.
*/

void thread_sleep_example()
{
    cout << "Thread sleep example\n\n";
    cout << "Thread sleep for 5 s \n";

    this_thread::sleep_for(chrono::seconds(5));

    cout << "Wakeup! \n";
    cout << "Now sleep untill now() + 3s\n";

    this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(5));

    cout << "Wakeup! \n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 3: Starting and finishing threads

/* From C++11 we have ability to use additional thread class. The thread class provides STL abstraction
for manipulation threads. Thread class constructor accepts thread function, which can be lambda, functor
or function, and when created, starts execution.

Threads can be joined (by join()) or detached (by detach()). Join means, that parent thread will wait
for child thread execution. Detach means, we tell the thread we do not care about child thread. Exiting
main thread without join or detahc all its child threads will end program with error (call terminate signal)
*/

void thread_func(int id)
{
    cout << "Thread started: " << id << endl;
    this_thread::sleep_for(chrono::seconds(1) * id);
    cout << "Thread ends: " << id << endl;
}

void using_threads_example()
{
    cout << "Using threads example\n\n";

    // Examine number of physical cores of the hardware
    cout << "Number of physical cores: " << thread::hardware_concurrency() << endl;

    //Now thread example
    thread t1 (thread_func, 1);
    thread t2 (thread_func, 2);
    thread t3 (thread_func, 3);

    //Join just 2 threads, detach 3rd
    t1.join();
    t2.join();
    t3.detach();

    cout << "End of main thread! \n\n";
}

void parallell_processing_example()
{
    using_policies();

    thread_sleep_example();

    using_threads_example();
}