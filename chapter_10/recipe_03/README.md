# Detecting and bypassing disabled RTTI

The macro BOOST_NO_RTTI is be defined if RTTI is disabled, and the macro BOOST_NO_CXX11_HDR_TYPEINDEX is be defined when the compiler has no <typeindex> header and no std::type_index class.

The handwritten type_index structure from step 3 of the previous section only holds the pointer to some string; nothing really interesting here.

Take a look at the BOOST_CURRENT_FUNCTION macro. It returns the full name of the current function, including template parameters, arguments, and the return type.
For example, type_id<double>() is represented as follows:
```
 type_index type_id() [with T = double]
```

So, for any other type, BOOST_CURRENT_FUNCTION returns a different string, and that's why the type_index variable from the example does not compare equal to it.

Congratulations! We've just reinvented most of the Boost.TypeIndex library functionality. Remove all the code from steps 1 to 4 and slightly change the code in step 5 to use the Boost.TypeIndex library:
```
#include <boost/type_index.hpp>

void test() {
    using boost::typeindex::type_id;

    assert(type_id<unsigned int>() == type_id<unsigned>());
    assert(type_id<double>() != type_id<long double>());
}
```

Of course Boost.TypeIndex is slightly more than that; it allows you to get human readable type name in a platform independent way, works around platform-related issues, allows to invent your own RTTI implementation, to have a constexpr RTTI, and other stuff.

Different compilers have different macros for getting a full function name. Using macros from Boost is the most portable solution. The BOOST_CURRENT_FUNCTION macro returns the name at compile time, so it implies minimal runtime penalty.

C++11 has a __func__ magic identifier that is evaluated to the name of the current function. However, result of __func__ is only the function name, while BOOST_CURRENT_FUNCTION tries hard to also show function parameters, including template ones.

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