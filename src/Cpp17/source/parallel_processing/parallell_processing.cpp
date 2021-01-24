/* This file contains all recepies regarding parallell processing */

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>
#include <execution>
#include <shared_mutex>
#include <mutex>
#include <sstream>
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
    cout << endl << endl;
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

    cout << "Wakeup! \n\n";
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

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 4: Mutex example

/* Mtex class is a mechanism for preventing 2 threads access the same object. In general, mute can have
locked and unlocked state. If mutex is locked, it means that protected resource is in use and cannot be used. 
Other thread has to wait for mutex to be unlocked, which means, that reaource is free again.
*/

// Define global shared mutex
shared_mutex m;

//Helper functions
static void print_exclusive()
{
    unique_lock<shared_mutex> lock {m, defer_lock};     //Defer lock - constructor will not lock mutex, just create lock
    if (lock.try_lock()) {  //Try to lock mutex here
        cout << "Unique lock granted! " << endl;
    }else{
        cout << "Unique lock not granted! " << endl;
    }
}   //Lock will be released

static void exclusive_throw()
{
    unique_lock<shared_mutex> lock {m}; //Try to lock mutex m immidietly
    throw 123;
}   //Lock will be released

void mutex_example()
{
    cout << "Mutex example\n\n";

    {
        shared_lock<shared_mutex> lck1(m); //Shared lock on mutex
        cout << "First shared lock granted! " << endl;
        {
            shared_lock<shared_mutex> lck2(m); //2nd shared lock on mutex
            cout << "Second shared lock granted! " << endl;
            print_exclusive();   //Try unique lock - will not lock!
        }   //2nd lock released
        cout << "Second shared lock released! " << endl;
        print_exclusive();  //Will not lock - 1st shared lock still active
    }
    cout << "First shared lock released! " << endl;
    try{
        exclusive_throw();
    }catch(int e)
    {
        cout << "Catched throw " << e << endl;
    }
    print_exclusive();  //Will lock
    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 5: Scoped lock example

/* Scoped lock is a special type of lock intriduced in Cpp17 for eliminating problem of deadlocks.
The scoped lck acts like a normal lock, but the scoped lock can accept many mutexes to lock on.
The mutexes will be locked as given in constructor, but the lock uses mechanism that prevents from deadlocks.

Deadlock - let assume we have thread 1 that locked mutex A and thtrad 2 that locked mutex B. If, after locking
mutex A by t1 we have context switching, t2 wil lock mutex B and try lock mutex A, which is already locked by t1. So
we have context switching again, and we go into t1 which tries to lock mutex B - locked by t2. And we have deadlock.

The deadlocks occurs when programmers locks many mutees in diffrent sequention in many threads. Scoped lock soves the problem.

*/

mutex m1;
mutex m2;

//Helper functions
void deadlock_f1()
{
    scoped_lock l {m1, m2};            //Scoped lock - prevents deadlock: m1 before m2
    cout << "Taking mutex m1 by func1 \n";
    cout << "Taking mutex m2 by func1 \n";
}

void deadlock_f2()
{
    scoped_lock l {m2, m1};            //Scoped lock - prevents deadlock: m2 before m1
    cout << "Taking mutex m2 by func2 \n";
    cout << "Taking mutex m1 by func2 \n";
}

void scoped_lock_example()
{
    cout << "Scoped lock example \n\n";

    thread t1 {deadlock_f1};
    thread t2 {deadlock_f2};

    t1.join();
    t2.join();
    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 6: Cout with locks

/* In the recepie we will write thread safe version of cout. We will pack sstream class by other class
acting like a lock using inheritance. The destructor of the pack class will cout all strema data at once, and
it will be safed by mutex, so we will have no problems with resource access.
*/

//Pack class
struct pcout : public stringstream {
    static inline mutex m;  //Cout protecting mutex
    ~pcout() {
        lock_guard<mutex> {m};
        cout << rdbuf();
        cout.flush();
    }
};

//Thread functions
static void print_cout(int x)
{
    cout << "Call normal cout from: " << x << "\n";
}

static void print_pcout(int x)
{
    pcout{} << "Call protected parallell cout from: " << x << "\n";
}

void cout_with_locks()
{
    cout << "Cout with locks eample \n\n";

    //Use standard cout
    vector<thread> t;
    for (size_t i {0}; i < 10; ++i)
    {
        t.emplace_back(print_cout, i);
    }
    for (auto &thr : t) {thr.join();}

    cout << "====================================\n";
    //Use parallell cout
    vector<thread> pt;
    for (size_t i {0}; i < 10; ++i)
    {
        pt.emplace_back(print_pcout, i);
    }
    for (auto &thr : pt) {thr.join();}
    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 7: Call once example

/* The call_once method is a mechanism that allows many threads shares same code, bot in situation, when 
some config function has to be executed before 1st thread uses the code. The call_once will take care about it automatically, 
so the user will not have to know which thread would be the first to execute the config function before.
*/

//Onceflag
once_flag callflag;

//Function to be called once before threads
void call_once_func()
{
    cout << "!";
}

//Thread using call_once fcn
void thr_foo(int x)
{
    call_once(callflag, call_once_func);
    cout << x;
}

void call_once_example()
{
    cout << "Call once example \n\n";

    vector<thread> t;
    for (size_t i {0}; i < 10; ++i)
    {
        t.emplace_back(thr_foo, i);
    }
    for (auto &thr : t) {thr.join();}
    cout << endl << endl;
}

void parallell_processing_example()
{
    using_policies();

    thread_sleep_example();

    using_threads_example();

    mutex_example();

    scoped_lock_example();

    cout_with_locks();

    call_once_example();
}