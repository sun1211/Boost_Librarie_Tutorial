# Converting numbers to strings with Boost.LexicalCast

The boost::lexical_cast function may also accept numbers as input and convert them to a string type specified as the template parameter (in triangular brackets). This is pretty close to what we have done in the previous recipe.

A careful reader will notice that in case of lexical_cast, we have an additional call to string copy the constructor and that such a call degrades performance. It is true, but only for old or bad compilers. Modern compilers implement a *Named Return Value Optimization (NRVO)*, which eliminates the unnecessary calls to copy constructors and destructor. Even if the C++11-compatible compilers don't detect NRVO, they use a move constructor of *std::string*, which is fast and efficient. The Performance section of the *Boost.LexicalCast* documentation shows the conversion speed on different compilers for different types. In most cases, lexical_cast is faster than the *std::stringstream* and *printf* functions.

If *boost::array* or *std::array* is passed to *boost::lexical_cast* as the output parameter type, less dynamic memory allocations will occur (or there will be no memory allocations at all, it depends on the *std::locale* implementation).
C++11 has *std::to_string* and *std::to_wstring* functions that are declared in the <string> header. Those functions use locales and have behavior very close to *boost::lexical_cast<std::string>* and *boost::lexical_cast<std::wstring>*, respectively. C++17 has *std::to_chars* functions that convert numbers to char arrays amazingly fast.* std::to_chars* do not allocate memory, do not throw exception, and may report errors using error codes. If you need really fast conversion functions that do not use locales, then use *std::to_chars*.

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
