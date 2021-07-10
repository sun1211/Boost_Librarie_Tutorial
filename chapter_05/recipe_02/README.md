# Syncing access to a common resource use boost::mutex

Now that we know how to start threads of execution, we want to have access to some common resources from different threads:
```
#include <cassert> 
#include <cstddef> 
#include <iostream>
 
// In previous recipe we included 
// <boost/thread.hpp>, which includes all 
// the classes of Boost.Thread.
// Following header includes only boost::thread. 
#include <boost/thread/thread.hpp> 
 
int shared_i = 0;

void do_inc() {
    for (std::size_t i = 0; i < 30000; ++i) {
        const int i_snapshot = ++shared_i;
        // Do some work with i_snapshot.
        // ...
    }
}

void do_dec() {
    for (std::size_t i = 0; i < 30000; ++i) {
        const int i_snapshot = --shared_i;
        // Do some work with i_snapshot.
        // ...
    }
}

void run() {
    boost::thread t1(&do_inc);
    boost::thread t2(&do_dec);

    t1.join();
    t2.join();

    assert(global_i == 0); // Oops!
    std::cout << "shared_i == " << shared_i;
}
```
For some people, it may be a surprise, but there is a big chance that shared_i won't be equal to 0:
```
    shared_i == 30000 //depend on runtime
```

Things get even worse in cases when a common resource is a non-trivial class; segmentation faults and memory leaks may (and will) occur.

We need to change the code so that only one thread modifies the shared_i variable at a single moment of time and so that all the processor and compiler optimizations that inflict multithreaded code are bypassed.

The boost::mutex class takes care of all the synchronization stuff. When a thread tries to lock it via the *boost::lock_guard<boost::mutex>* variable and there is no other thread holding a lock, it successfully acquires unique access to the section of code until the lock is unlocked or destroyed. If some other thread already holds a lock, the thread that tried to acquire the lock waits until another thread unlocks the lock. All the locking/unlocking operations imply specific instructions so that the changes made in a critical section are visible to all threads. Also, you no longer need to:

 - Make sure that modified values of resources are visible to all cores
 - Make sure that values are not just modified in the processor's register
 - Force the processor to not reorder the instructions
 - Force the compiler to not reorder the instructions
 - Force the compiler to not remove writes to storage that is not read
 - A bunch of other nasty compiler/architecture specific stuff

Locking a mutex is potentially a very slow operation, which may stop your code for a long time, until some other thread releases a lock. Try to make critical sections as small as possible; try to have less of them in your code.

Let's take a look at how some operating systems handle locking on a multicore CPU. When thread #1, running on CPU 1, tries to lock a mutex that is already locked by another thread, thread #1 is stopped by the OS till the lock is released. The stopped thread does not eat processor resources, so the OS executes other threads on CPU 1. Now, we have some threads running on CPU 1; some other thread releases the lock, and now the OS has to resume execution of a thread #1. So, it resumes its execution on a currently free CPU, for example, CPU2.

This results in CPU cache misses, so the code runs slightly slower after mutex is released. Usually, things are not so bad because a good OS tries hard to resume the thread on the same CPU that it was using before. Unfortunately, such OS-specific optimizations are not always possible. Reduce the count of critical sections and their sizes to reduce the chance of thread suspending and cache misses.

Do not attempt to lock a *boost::mutex* variable twice in the same thread; it will lead to a deadlock. If locking a mutex multiple times from a single thread is required, use *boost::recursive_mutex* instead from the <boost/thread/recursive_mutex.hpp> header. Locking it multiple times does not lead to a deadlock. The *boost::recursive_mutex* releases the lock only after unlock() is called once for each lock() call. Avoid using *boost::recursive_mutex *when it is not required, because it is slower than boost::mutex and usually indicates bad code flow design.

The *boost::mutex*, *boost::recursive_mutex*, and boost::lock_guard classes were accepted to the C++11 standard library, and you may find them in the <mutex> header in the std:: namespace. No big difference between Boost and standard library versions exists. The Boost version may have some extensions (which are marked in the official documentation as EXTENSION) and provide better portability because they can be used even on pre-C++11 compilers.

## How to build
```
mkdir build
cd build
cmake ..
cmake --build .
```

## How to run
```
./bin/main

shared_i == 30000
shared_i == 0

```
