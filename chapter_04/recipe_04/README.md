# Creating a type from a number

The most interesting part here is that **boost::mpl::int_<sizeof(T)>()**. *sizeof(T)* executes at compile time, so its output can be used as a template parameter. The class *boost::mpl::int_<>* is just an empty class that holds a compile-time value of integral type.

We need an instance of this class, which is why we have a round parentheses at the end of *boost::mpl::int_<sizeof(T)>()*.

let's take a closer look at how the compiler will decide which process_impl function to use. First of all, the compiler tries to match functions that have a non-template second parameter . If *sizeof(T)* is 4, the compiler tries to search the function with signatures like *process_impl(T, boost::mpl::int_<4>)* and finds our 4 bytes optimized version from the detail namespace. If *sizeof(T)* is 34, the compiler can not find the function with a signature like *process_impl(T, boost::mpl::int_<34>)*, and uses a template function *process_impl(const T& val, Tag /*ignore*/)*.

The **Boost.MPL** library has several data structures for metaprogramming. In this recipe, we only scratched the tip of the iceberg. You may find the following integral constant classes from MPL useful:
 - bool_
 - int_
 - long_
 - size_t
 - char_

 All the Boost.MPL functions (except the for_each runtime function) are executed at compile time and won't add runtime overhead.

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

 0 1 2 A 4 5

```
