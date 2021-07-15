# Executing different tasks in parallel

The **boost::asio::io_service::run** method is thread safe. All we need to do is just run the *boost::asio::io_service::run* method from different threads.

If you are executing tasks that modify a common resource, you need to add mutexes around that resources, or organize your application in a way, that the common resource is not used simultaneously by different tasks. It is safe to use resource from different tasks without concurrent access to the resource because *boost::asio::io_service* takes care of additional synchronization between tasks and forces the modification results of one task to be seen by another task.

See the call to *boost::thread::hardware_concurrency()*. It returns the count of threads that can be run concurrently on current hardware. But, it is just a hint, and sometimes it may return a 0 value, which is why we are calling the *std::max* function for it. *std::max* ensures that threads_count stores at least the value 1.

We wrapped *std::max* in parentheses because some popular compilers define the *min()* and *max()* macros, so we need additional tricks to work around this.

The *boost::thread::hardware_concurrency()* function is a part of C++11; you may find it in the <thread> header of the *std:: namespace*.

All the *boost::asio* classes are not part of C++17, but they will be available soon as a Networking TS.

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
