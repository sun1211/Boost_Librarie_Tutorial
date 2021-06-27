# Storing multiple chosen types in a container/variable
Refer to : https://www.boost.org/doc/libs/1_76_0/doc/html/variant.html

C++03 unions can only hold extremely simple types called **Plain Old Data (POD)**. For example in C++03, you cannot store **std::string** or **std::vector** in a union.

The Boost.Variant library can store any of the types specified at compile time. It also manages in-place construction/destruction and even does not even require the C++11 standard

Boost.Variant has no empty state, but has an empty() function which is useless and always returns false. If you need to represent an empty state, just add some simple type at the first position of the types supported by the Boost.Variant library. When Boost.Variant contains that type, interpret it as an empty state. Here is an example in which we will use a boost::blank type to represent an empty state.

The boost::variant class holds an array of bytes and stores values in that array. The size of the array is determined at compile time by applying sizeof() and functions to get alignment to each of the template types. On assignment, or construction of boost::variant, the previous values are in-place destructed and new values are constructed on top of the byte array, using the placement new.

The Boost.Variant variables usually do not dynamically allocate memory, and they do not require RTTI to be enabled. Boost.Variant is extremely fast and used widely by other Boost libraries. To achieve maximum performance, make sure that there is a simple type in the list of supported types at the first position. boost::variant takes advantage of C++11 rvalue references if they are available on your compiler.

Boost.Variant is part of the C++17 standard. std::variant differs slightly from theboost::variant:

 - std::variant is declared in the <variant> header file rather than in <boost.variant.hpp>
 - std::variant never ever allocates memory
 - std::variant is usable with constexpr
 - Instead of writing boost::get<int>(&variable), you have to write std::get_if<int>(&variable) for std::variant
 - std::variant can not recursively hold itself and misses some other advanced techniques
 - std::variant can in-place construct objects
 - std::variant has index() instead of which()

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
