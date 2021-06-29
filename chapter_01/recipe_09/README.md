# Combining multiple values into one with Boost.Tuple

here is a very nice present for those who like std::pair. Boost has a library called Boost.Tuple. It is just like std::pair, but it can also work with triples, quads, and even bigger collections of types.

A tuple works as fast as std::pair (it does not allocate memory on a heap and has no virtual functions). The C++ committee found this class to be very useful and it was included in the standard library. 

The current Boost implementation of a tuple does not use variadic templates, does not support rvalue references, does not support C++17 structured bindings, and is not usable with constexpr.

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
