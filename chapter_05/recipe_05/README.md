# Multiple-readers-single-writer lock

We can allow getting the data from multiple threads simultaneously if those threads do not modify data. We need to uniquely own the mutex only if we are going to modify the data protected by it. In all other situations, simultaneous access to data is allowed. And that is what *boost::shared_mutex* was designed for. It allows shared locking (read locking), which allows multiple simultaneous access to resources.

When we do try to unique lock a resource that is shared locked, operations will be blocked till there are no read locks remaining, and only after that resource is unique locked, forcing new shared locks to wait until the unique lock is released.* boost::shared_lock* locking for reading and writing is much slower than the usual *boost::mutex locking*. Do not use boost::shared_lock unless you are sure that there's no good way to redesign your code and you are sure that boost::shared_lock will speed things up.

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
