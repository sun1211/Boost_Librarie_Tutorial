# Containers of pointers with Boost.PointerContainer

The examples are: storing polymorphic data in containers, forcing fast copy of data in containers, and strict exception requirements for operations with data in containers. In such cases, C++ programmer has the following choices.

The **Boost.PointerContainer** library has classes *ptr_array, ptr_vector, ptr_set, ptr_multimap*, and others. Those classes deallocate pointers as required and simplify access to data pointed by the pointer (no need for additional dereference in assert(*s.begin() == 0);).

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
