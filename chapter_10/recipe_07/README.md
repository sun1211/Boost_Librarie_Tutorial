# Detecting the Boost version and getting latest features

The BOOST_VERSION macro contains the Boost version written in the following format: a single number for the major version, followed by three numbers for the minor version, and then two numbers for the patch level. For example, Boost 1.73.1 will contain the 107301 number in the BOOST_VERSION macro.

So, we check the Boost version in step 2 and choose the correct implementation of the to_int function according to the abilities of Boost.LexicalCast.

Having a version macro is a common practice for big libraries. Some of the Boost libraries allow you to specify the version of the library to use; see Boost.Thread and its BOOST_THREAD_VERSION macro for an example.

By the way, C++ has a version macro too. Value of the __cplusplus macro allows you to distinguish pre-C++11 from C++11, C++11 from C++14, or C++17. Currently it can be defined to one of the following values: 199711L, 201103L, 201402L, or 201703L. Macro value stands for year and month when the committee approved the standard.

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