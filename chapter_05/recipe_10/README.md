# Locking multiple mutexes

The core idea is to order mutexes somehow and lock them always following that particular order. In that case, there's no ABBA problem possible, as all the threads would always lock mutex A before B. Usually, other deadlock avoidance algorithms are used but for the simplicity of the example here, we assume that the ordering of mutexes is used.

In the first example, we used boost::make_unique_locks that always locks threads in some particular order and returns a tuple that holds the locks.

In the second example, we created the locks manually but have not locked them thanks to a passed boost::defer_lock parameter. The actual locking happened in the *boost::lock(l0, l1)* call, which locked the mutexes in some predefined order.

Now, if user1 and user2 call *exchange_loot* for each other concurrently, then both *user1.exchange_loot(user2)* and u*ser2.exchange_loot(user1)* calls will try to lock *user1.loot_mutex_* first or both will try to lock *user2.loot_mutex_* first. That depends on a runtime.

*boost::make_unique_locks* and *boost::lock* functions may accept more than 2 locks or mutexes, so you could use them in more advanced cases, where more than two mutexes must be locked simultaneously.

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

Print once 0

```
