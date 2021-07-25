# Syncing interprocess communications

In this recipe, we are doing almost exactly the same things as in the Making a work_queue class recipe in Chapter 5, Multithreading, but we allocate the data in shared memory.

Take additional care when storing the shared memory objects that have pointers or references as member fields. We'll see how to cope with pointers in the next recipe.
Take a look at step 2. We did not use boost::function as a task type because it has pointers in it, so it does not work in shared memory.

Step 3 is interesting because of allocator_t. If memory is not allocated from the shared memory segment, it is available to other processes; that's why a specific allocator for containers is required. An allocator_t is a stateful allocator, which means that it is copied along with the container. Also, it cannot be default constructed.

Step 4 is pretty simple, except that we have only references to tasks_, mutex_, and cond_. This is done because objects themselves are constructed in the shared memory. So, work_queue may only store references in them.

In step 5, we are initializing members. This code must be familiar to you. We were doing exactly the same things in the previous recipe.

We are providing an instance of the allocator to tasks_ while constructing it. That's because allocator_t cannot be constructed by the container itself. Shared memory is not destructed at the exit event of a process, so we may run the program once, post the tasks to a work queue, stop the program, start some other program, and get tasks stored by the first instance of the program. Shared memory is destroyed only at restart, or if you explicitly call segment.deallocate("work-queue");

As was already mentioned in the previous recipe, C++17 has no classes from Boost.Interprocess. Moreover, you must not use C++17 or C++03 containers in shared memory segments. Some of those containers may work, but that behavior is not portable.

If you look inside some of the <boost/interprocess/containers/*.hpp> headers, you'll find that they just use containers from the Boost.Containers library:
```
namespace boost { namespace interprocess { 
    using boost::container::vector; 
}}
```

Containers of Boost.Interprocess have all the benefits of the Boost.Containers library, including rvalue references and their emulation on older compilers.

A Boost.Interprocess is the fastest solution for communication of processes that are running on the same machine.

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

```