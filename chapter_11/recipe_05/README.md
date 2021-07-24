# Passing data quickly from one process to another

The main idea of this recipe is to get a segment of memory that is visible to all processes and place some data in it. Let's take a look at step 3, where we retrieve such a segment of memory. Here, shm1- cache is the name of the segment (different segments differ in names). You may give any names to the segments. The first parameter is boost::interprocess::open_or_create, which tells that boost::interprocess::managed_shared_memory must open an existing segment with the name shm1- cache or construct it. The last parameter is the size of the segment.

The size of the segment must be big enough to fit the Boost.Interprocess library-specific data in it. That's why we used 1024 and not sizeof(atomic_t). But actually, the operating system rounds this value to the nearest bigger supported value, which is usually equal to or bigger than 4 kilobytes.

Step 4 is a tricky one, as we are performing multiple tasks at the same time here. In part 2 of this step, we find or construct a variable with the name shm1-counter in the segment. In part 3 of step 4, we provide a parameter, which is used for the initialization of a variable, if it has not been found in step 2. This parameter is used only if the variable is not found and must be constructed, otherwise it is ignored. Take a closer look at the second line (part 1). See the call to the dereference operator *. We are doing it because segment.find_or_construct<atomic_t> returns a pointer to atomic_t, and working with bare pointers in C++ is a bad style.

We are using atomic variables in shared memory! This is required, because two or more processes may simultaneously work with the same shm1-counter atomic variable.
You must be very careful when working with objects in shared memory; do not forget to destroy them! In step 6, we are destroying the object and segment using their names.

Take a closer look at step 2, where we are checking for BOOST_ATOMIC_INT_LOCK_FREE != 2. We are checking that atomic_t does not use mutexes. This is very important, because the usual mutexes do not work in shared memory. So if BOOST_ATOMIC_INT_LOCK_FREE is not equal to 2, we get an undefined behavior.

Unfortunately, C++11 has no interprocess classes, and, as far as I know, Boost.Interprocess is not proposed for inclusion in C++20.

Once a managed segment is created, it cannot increase in size automatically! Make sure that you are creating segments big enough for your needs, or take a look at the See also section for information about increasing managed segments.
Shared memory is the fastest way for processes to communicate, but works for processes that may share memory. That usually means that processes must run on the same host or on a symmetric multiprocessing (SMP) cluster.

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

I have index 1
Press any key...

```