# Getting backtrace – current call sequence

All the magic is within the boost::stacktrace::stacktrace class. On construction, it quickly stores the current call stack in itself. boost::stacktrace::stacktrace is copyable and movable, so a stored a call sequence can be passed to other functions, copied into the exception classes, and even stored in some file. Do whatever you like with it!

Instances of boost::stacktrace::stacktrace on the output, decode the stored call sequence and attempt to get human readable function names. That's what you've seen in the example from earlier: call sequence that leads to the report_bankruptcy() function call.

The boost::stacktrace::stacktrace you to iterate over stored addresses, decode individual addresses into human readable names. If you do not like the default output format of the trace, you can write your own function that does the output in a way you prefer.

A Boost.Stacktrace library has a very neat feature for big projects. You can disable all the tracing while linking your program. It means that you do not need to rebuild all your source files. Just define BOOST_STACKTRACE_LINK macro for a whole project. Now, if you link with the boost_stacktrace_noop library, empty traces will be collected. Link with boost_stacktrace_windbg/boost_stacktrace_windbg_cached/boost_stacktrace_backtrace/ ... libraries to get traces of different readability.

Boost.Stacktrace is a new library; it appeared in Boost in 1.65.

boost::stacktrace::stacktrace collects current call sequences pretty fast; it just dynamically allocates a chunk of memory and copies a bunch of addresses into it. Decoding addresses is much slower; it uses multiple platform-specific calls, may fork processes, and may initialize and use COM.

C++17 does not have Boost.Stacktrace functionality. Work is going on to add it to one of the next C++ standards.


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