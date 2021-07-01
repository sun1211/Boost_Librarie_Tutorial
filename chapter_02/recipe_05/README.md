# Storing any functional objects in a variable

The **Boost.Function** library has an insane amount of optimizations. It may store small functional objects without additional memory allocations and has optimized move assignment operators. It is accepted as a part of C++11 standard library and is defined in the *<functional>* header in the *std:: namespace.*

**boost::function** uses an **RTTI** for objects stored inside it. If you disable *RTTI*, the library will continue to work, but will dramatically increase the size of a compiled binary.

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
