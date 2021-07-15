# CChanging cases and case-insensitive comparison

The second method is not an obvious one. In the second method, we compare the length of strings. If they have the same length, we compare the strings character by character using an instance of the *boost::is_iequal* predicate. The *boost::is_iequal* predicate compares two characters in a case insensitive way.

Unfortunately, C++17 has no string functions from Boost.StringAlgorithm. All the algorithms are fast and reliable, so do not be afraid to use them in your code.


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
