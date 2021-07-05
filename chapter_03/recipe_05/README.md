# Converting smart pointers

The Boost library has a lot of functions for smart pointer conversions. All of them accept a smart pointer and a template parameter T, where T is the desired template type of the smart pointer. Those conversion operator mimic the behavior of built-in casts while correctly managing the reference counting and other smart pointer internals:

 - boost::static_pointer_cast<T>(p) - does static_cast<T*>(p.get())
 - boost::dynamic_pointer_cast<T>(p) - does dynamic_cast<T*>(p.get())
 - boost::const_pointer_cast<T>(p) - does const_cast<T*>(p.get())
 - boost::reinterpret_pointer_cast<T>(p) - does reinterpret_cast<T*>(p.get())

All the **boost::*_pointer_cast** functions can work with smart pointers from the standard library and C pointers if you include <boost/pointer_cast.hpp>.

In C++11, the standard library has *std::static_pointer_cast*, *std::dynamic_pointer_cast*, and *std::const_pointer_cast* defined in the <memory> header, however, it is only for *std::shared_ptr*. The C++17 standard library has *std::reinterpret_pointer_cast*, but it is only for *std::shared_ptr*.

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
