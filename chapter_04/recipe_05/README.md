# Implementing a type trait with Boost.TypeTrait

Those readers who use the C++11 compatible compilers may use the true_type and false_type types declared in the *<type_traits>* header for creating their own type traits. Since C++17, the standard library has a *bool_constant<true_or_false>* type alias that you may use for convenience.
As usual, the Boost versions of the classes and functions are more portable because they can be used on pre-C++11 compilers.

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
