# Getting a human-readable type name

The **Boost.TypeIndex** library has a lot of workarounds for different compilers and knows the most efficient way to produce a human-readable name for the type. If you provide a type as a template parameter, the library guarantees that all the possible type related computations will be performed at compile time and code will work even if RTTI is disabled.

**cvr** in *boost::typeindex::type_id_with_cvr* stands for const, volatile, and reference. That makes sure that the type won't be decayed.

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

T is d
x is i
T is double
x is int&&

```
