/* This file contains all recepies regarding parallell processing */

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <chrono>
#include <thread>
#include <execution>
#include <shared_mutex>
#include <mutex>
#include <sstream>
#include <future>
#include <queue>
#include <condition_variable>
#include <complex>
#include <iomanip>
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

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 8: Async eample

/* std::async in a new function introduced in C++11. It allows for asynchronus call of a function
(in othre thread or in that thread, but lated - that is defined by policy). It allows
to return value (standar thread usage does not allows it!). The returned value is packed by future object.
*/

//Define helper functions - will be called by asybc later
string sort_string(string input)
{
    sort(input.begin(), input.end());
    return input;
}

string convert_to_upper(string input)
{
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    return input;
}

string convert_to_lower(string input)
{
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

void async_example()
{
    cout << "Async example \n\n";

    string input = "Ala Ma Kota, a kot ma Ale!";

    //Call functions asynchronically
    auto o1 = async(launch::async, sort_string, input);
    auto o2 = async(launch::async, convert_to_upper, input);
    auto o3 = async(launch::async, convert_to_lower, input);

    cout << "Input string: " << input << endl;
    cout << "Sorted by async: " << o1.get() << endl;        //As o1, o2, o3 are promise type, we will need .get() to get a result !
    cout << "Toupper by async: " << o2.get() << endl;
    cout << "Tolower by async: " << o3.get() << endl;

    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 9: Producer - consumer example

/* Producer - consuler is an parallell processing design pattern. We have 2 threads - producer, 
which produces data to process, and consumer which process the data. Both are connected each other by
queue, which as shared resource, is protected by mutex. If no data are in queue, the consumer
thread sleeps. If no data is to process, the producer thread sleeps.

In the situation we need some sync mechanism between threads. After putting new data into the queue, the
produces shall wake up sleeping consumer thread. That is done by introduced in C++11 condition_variable
class.

*/

mutex queue_mutex;
queue<size_t> q;
condition_variable cv;
bool finished = false;

//Producer and consumer threads
static void producer_thr(size_t items)
{
    for (size_t i = 0; i < items; ++i)
    {
        lock_guard<mutex> lk {queue_mutex};
        cout << "Producer putted data: " << i << endl;
        q.push(i);
        cv.notify_all();    //Wake up all threads waiting for cv
    }
    {
        lock_guard<mutex> lk {queue_mutex};
        finished = true;        //Modify finished variable - has to be also quarded by mutex
    }
    cv.notify_all();    //And wake up waiting threads
}

static void consumer_thr()
{
    while(!finished) {
        unique_lock<mutex> l {queue_mutex};
        cv.wait(l, [](){return !q.empty() || finished;});   //Wait for cv. If waken up, check predictate - finished variable and if queue is not empty.
        
        while(! q.empty())
        {
            cout << "Get data from queue: " << q.front() << endl;
            q.pop();
        }
    }
}

void condition_variable_example()
{
    cout << "Condition variable example \n\n";

    thread t1 {producer_thr, 10};
    thread t2 {consumer_thr};

    t1.join();
    t2.join();

    cout << "Finished" << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 10: Extended producer - consumer example

/* In that recepie we eill extend producer-consume example by writing code for more than one
producers and consumers working together, on the same queue. We will add also mechanism for
protection write ti queue if its size is too high. We will use some code from previour recepies.
*/

condition_variable go_produce;
condition_variable go_consume;
bool production_stopped {false};

// Producer and consumer functions
static void ext_producer_thr(size_t id, size_t items, size_t stock)
{
    for (size_t i = 0; i < items; ++i)
    {
        unique_lock<mutex> lock {queue_mutex};
        go_produce.wait(lock, [&](){return q.size() < stock;}); //CV for waiting for space in queue. Stock defines max queue size.
        q.push(id * 100 + i);
        pcout {} << "Producer id: " << id << " putted data: " << i << endl;
        go_consume.notify_all();    //Notigy consumers
        this_thread::sleep_for(chrono::milliseconds(90));    //SImulate time for producing data
    }
    pcout{} << "End of production by: " << id << endl;
}

static void ext_consumer_thr(size_t id)
{
    while(!production_stopped || !q.empty())
    {
        unique_lock<mutex> lock(queue_mutex);
        if (go_consume.wait_for(lock, chrono::seconds(1), [](){return !q.empty();}))
        {
            pcout{} << "Consumer id: " << id << " get data from queue: " << q.front() << endl;
            q.pop();
            go_produce.notify_all();    //Notify producers - some data from queue has been processed and we have space
            this_thread::sleep_for(chrono::milliseconds(120));
        }
    }
    pcout{} << "End of consuming by: " << id << endl;
}

void extended_producer_consumer_example()
{
    cout << "Extended condition variable example \n\n";

    vector<thread> workers;
    vector<thread> consumers;

    for (size_t x = 0; x < 3; ++x)
    {
        workers.emplace_back(ext_producer_thr, x, 15, 5);   //Create 3 producers
    }

    for (size_t x = 0; x < 2; ++x)
    {
        consumers.emplace_back(ext_consumer_thr, x);   //Create 2 consumers
    }

    for(auto &t : workers)
    {
        t.join();
    }
    production_stopped = true;
    for(auto &t : consumers)
    {
        t.join();
    }

    cout << "Finish " << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 11: Mandlebort parallell example

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
        return cplx{scaler_x(x), scaler_y(y)};
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

void parallell_mandelbort_example()
{
    cout << "Parallell manderbolt example\n\n";

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
        return async(launch::async, mandelbort_iterations, i_to_xy(i));
    });

    // Here the manderbolt result will be stored in v.
    vector<int> v (w * h);
    vector<future<size_t>> r (w * h);
    iota(begin(v), end(v), 0);
    transform (begin(v), end(v), begin(r), to_iteration_count);

    // Printing section
    auto binfunc ([w, n{0}] (auto output_it, future<size_t>& x) mutable {
        *++output_it = (x.get() > 50 ? '*' : ' ');
        if (++n % w == 0) {++output_it = '\n';}
        return output_it;
    });

    accumulate(r.begin(), r.end(), ostream_iterator<char>{cout}, binfunc);

    cout << endl << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RECEPIE 12: Parallell programming with future example

/* In the recepie we will create parallell version of some job 8

We will also use pcout{} from one of the previous recepies.

*/

//Job functions. Additional delays will simulate complexity of functions.

//1st function - create string
static string create(const char *s)
{
    pcout{} << "3s CREATE " << quoted(s) << '\n';
    this_thread::sleep_for(chrono::milliseconds(3000));
    return {s};
}

//2nd function - concat 2 strings
static string concat(const string &a, const string &b)
{
    pcout{} << "5s CONCAT STRINGS: " << a << " and " << b << '\n';
    this_thread::sleep_for(chrono::milliseconds(5000));
    return a + b;
}

//3rd function - double given string
static string twice(const string &s)
{
    pcout{} << "2s DOUBLE STRING: " << s << '\n';
    this_thread::sleep_for(chrono::milliseconds(2000));
    return s + s;
}

//This functions will pack series functions into parallell versions

//1st of them is asynchronize, which will create callable object of async version of some worker function (the one that needs non future type args)
//That tyoe of sunctions can be used at the end of call chain only.
template <typename F>
static auto asynchronize(F f)
{
    return [f](auto ...xs){     //The asynchronize function will return callable objects, which takes any list of args
        return [=] () {         //Which will return callable object, non - args
            return async(launch::async, f, xs...);  //Which will call function f with args asynchonically and return retval of f
        };
    };
}

//That 2 functions will allow us to pack functions that takes future objects and returns future objects.
template<typename F>
static auto fut_unwrap(F f)
{
    return [f](auto ...xs) {    //The fut_unwrap will return callable object, which takes any long list of args of future type
        return f(xs.get()...);      //Which called will call f function with args stored in future objects
    };
}

template<typename F>
static auto async_adapter(F f)
{
    return [f](auto ...xs) {    //The async_adapter function will return callable object, which accepts any number of future type args
        return [=](){           //Which will return non-argument callable object, which will call given operation asynchronically/
            return async(launch::async, fut_unwrap(f), xs()...);    //The fun_unwrap used here will pack given standard type args of f function to callable object taking s args of future types (we have .get())
        };
    };
}

void parallel_usage_example()
{
    cout << "Parallell usage example \n\n";

    //Create parallell versions of standard functions
    auto pcreate (asynchronize(create));
    auto pconcat (async_adapter(concat));
    auto ptwice  (async_adapter(twice));

    auto result (
        pconcat(
            ptwice (
                pconcat(
                    pcreate("foo "),
                    pcreate("bar ")
                )
            ),
            pconcat(
                pcreate("this "),
                pcreate("that ")
            )
        )
    );

    cout << "Results: " << result().get() << endl << endl;

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

    async_example();

    condition_variable_example();

    extended_producer_consumer_example();

    parallell_mandelbort_example();

    parallel_usage_example();
}