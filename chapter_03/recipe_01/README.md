# Converting strings to numbers with Boost.LexicalCast

consists of a *boost::bad_lexical_cast* exception class and a few *boost::lexical_cast* and *boost::conversion::try_lexical_convert* functions

The **boost::lexical_cast** function accepts string as input and converts it to the type specified in triangular brackets. The *boost::lexical_cast* function will even check bounds for you.

The C++ standard library has no lexical_cast, but since C++17 has std::from_chars functions that could be used to create amazingly fast generic converters. Note that those converters do not use locales at all, so they have slightly different functionality because of that. std::from_chars functions were designed to not allocate memory, do not throw exceptions, and have no atomic or some other heavy operations.

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
