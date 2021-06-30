# Using the C++11 move emulation

The **Boost.Move** library is implemented in a very efficient way. When the C++11 compiler is used, all the macros for rvalues emulation are expanded to C++11-specific features otherwise (on C++03 compilers), rvalues are emulated.

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
