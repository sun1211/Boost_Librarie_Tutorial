# Fast access to common resource using atomics

Processors provide specific atomic operations that cannot be interfered with by other processors or processor cores. These operations appear to occur instantaneously for a system. Boost.Atomic provides classes that wrap around system-specific atomic operations, cooperate with the compiler to disable optimizations that may break multithreaded work with a variable, and provide a unified portable interface to work with atomic operations. If two atomic operations on the same memory location start simultaneously from different threads, one of the operations waits till the other one finishes and then reuses the result of the previous operation.

In other words, it is safe to use the boost::atomic<> variables from different threads simultaneously. Each operation on the atomic variable is seen by the system as a single transaction. Series of operations on the atomic variables are treated by the system as a series of independent transactions

The Boost.Atomic library can work only with POD types; otherwise, behavior is undefined. Some platforms/processors do not provide atomic operations for some types, so Boost.Atomic emulates atomic behavior using boost::mutex. The atomic type does not use boost::mutex if the type specific macro is set to 2:

```
#include <boost/static_assert.hpp> 
BOOST_STATIC_ASSERT(BOOST_ATOMIC_INT_LOCK_FREE == 2); 
```

The *boost::atomic<T>::is_lock_free* member function depends on runtime, so it is not good for compile-time checks but may provide a more readable syntax when the runtime check is enough:

```
assert(shared_i.is_lock_free()); 
```

Atomics work much faster than mutexes but are still much slower than non-atomic operations. If we compare the execution time of a recipe that uses mutexes (0:00.08 seconds) and the execution time of the preceding example in this recipe (0:00.02 seconds), we'll see the difference (tested on 30,0000 iterations).


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

shared_i == 0

```
