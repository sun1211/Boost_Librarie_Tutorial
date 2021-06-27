# Storing multiple chosen types in a container/variable
Refer to : https://www.boost.org/doc/libs/1_37_0/doc/html/any.html

C++03 unions can only hold extremely simple types called **Plain Old Data (POD)**. For example in C++03, you cannot store **std::string** or **std::vector** in a union.

The Boost.Variant library can store any of the types specified at compile time. It also manages in-place construction/destruction and even does not even require the C++11 standard

Boost.Variant has no empty state, but has an empty() function which is useless and always returns false. If you need to represent an empty state, just add some simple type at the first position of the types supported by the Boost.Variant library. When Boost.Variant contains that type, interpret it as an empty state. Here is an example in which we will use a boost::blank type to represent an empty state

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

Wow! That is great!
```
