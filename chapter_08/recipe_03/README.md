# Getting a function's result type at compile time

The main idea of this recipe is that we may make a special metafunction that deduces the resulting type. Such a technique can be seen all around the Boost libraries, for example, in the Boost.Variant's implementation of *boost::get<>* or in almost any function from Boost.Fusion.

Now, let's move step-by-step. The result_of namespace is just some kind of a tradition, but you may use your own and it does not matter. The *boost::common_type<>* metafunction deduces a type common of several types, so we use it for a general case. We also added two template specializations of the *result_of::my_function_cpp03* structures for the s1 and s2 types.

The disadvantage of writing metafunctions in C++03 is that sometimes we are required to write a lot. Compare the amount of code for my_function_cpp11 and my_function_cpp03 including the result_of namespace to feel the difference.

This technique does not add runtime overhead but it may slow down compilation a little bit. You may use it on modern C++ compilers as well.


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