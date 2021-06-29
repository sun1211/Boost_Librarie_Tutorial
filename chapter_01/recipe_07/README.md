# Returning a value or flag where there is no value with Boost.Optional
Refer to: https://www.boost.org/doc/libs/1_76_0/libs/optional/doc/html/index.html

Imagine that we have a function that does not throw an exception and returns a value or indicates that an error has occurred. In Java or C# programming languages, such cases are handled by comparing a return value from a function value with a null pointer. If the function returned null, then an error has occurred. In C++, returning a pointer from a function confuses library users and usually requires slow dynamic memory allocation.

The Boost.Optional class does not use dynamic allocation and it does not require a default constructor for the underlying type. The current boost::optional implementation can work with C++11 rvalue references but is not usable with constexpr.


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

...trying again
...trying again
Device is locked
Success!
```
