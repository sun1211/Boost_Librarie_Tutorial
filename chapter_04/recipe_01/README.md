# Checking sizes at compile time with Boost.StaticAssert and Boost.TypeTraits

Let's imagine that we are writing some serialization function that stores values in a buffer of a specified size:

```
#include <cstring> 
#include <boost/array.hpp> 

// C++17 has std::byte out of the box!
// Unfortunately this is as C++03 example. 
typedef unsigned char byte_t;
 
template <class T, std::size_t BufSizeV> 
void serialize_bad(const T& value, boost::array<byte_t, BufSizeV>& buffer) { 
    // TODO: check buffer size.
    std::memcpy(&buffer[0], &value, sizeof(value)); 
}
```

This code has the following problems:
 - The size of the buffer is not checked, so it may overflow
 - This function can be used with non-trivially copyable types, which would lead to incorrect behavior

We may partially fix it by adding some asserts, for example:
```
template <class T, std::size_t BufSizeV> 
void serialize_bad(const T& value, boost::array<byte_t, BufSizeV>& buffer) {  
    // TODO: think of something better.
    assert(BufSizeV >= sizeof(value));
    std::memcpy(&buffer[0], &value, sizeof(value)); 
}
```

But, this is a bad solution. Runtime checks do not trigger the assert during testing in the debug mode if the function was not called. Runtime checks may even be optimized out in the release mode, so very bad things may happen.
*BufSizeV* and *sizeof(value)* values are known at compile time. It means that, instead of having a runtime assert, we can force this code to fail compilation if the buffer is too small.

The **BOOST_STATIC_ASSERT** macro can be used only if an assert expression can be evaluated at compile time and is implicitly convertible to bool. It means that you may only use *sizeof()*, static constants, constexpr variables, constexpr functions with parameters known at compile time, and other constant expressions in *BOOST_STATIC_ASSERT*. If assert expression evaluates to false, *BOOST_STATIC_ASSERT* will stop compilation. In the case of a serialize function, if the first static assertion fails, it means that the user misused the serialize function and provided a very small buffer.

For example:
```
BOOST_STATIC_ASSERT(3 >= 1); 
 
struct some_struct { enum enum_t { value = 1}; }; 
BOOST_STATIC_ASSERT(some_struct::value); 
 
template <class T1, class T2> 
struct some_templated_struct 
{ 
    enum enum_t { value = (sizeof(T1) == sizeof(T2))}; 
}; 
BOOST_STATIC_ASSERT((some_templated_struct<int, unsigned int>::value));

template <class T1, class T2>
struct some_template { 
    BOOST_STATIC_ASSERT(sizeof(T1) == sizeof(T2));
};
```

The **BOOST_STATIC_ASSSERT** macro has a more verbose variant called *BOOST_STATIC_ASSSERT_MSG* that tries hard to output an error message in the compiler log (or in the IDE window) if assertion fails. Take a look at the following code:
```
template <class T, std::size_t BufSizeV> 
void serialize2(const T& value, boost::array<byte_t, BufSizeV>& buf) { 
    BOOST_STATIC_ASSERT_MSG(boost::has_trivial_copy<T>::value, 
        "This serialize2 function may be used only " 
        "with trivially copyable types." 
    ); 
 
    BOOST_STATIC_ASSERT_MSG(BufSizeV >= sizeof(value), 
        "Can not fit value to buffer. " 
        "Make the buffer bigger." 
    ); 
 
    std::memcpy(&buf[0], &value, sizeof(value)); 
} 

int main() { 
    // Somewhere in code: 
    boost::array<unsigned char, 1> buf; 
    serialize2(std::string("Hello word"), buf);
}
```

The preceding code will give the following result during compilation on the g++ compiler in the C++11 mode:

```
boost/static_assert.hpp:31:45: error: static assertion failed: This serialize2 function may be used only with trivially copyable types.
 #     define BOOST_STATIC_ASSERT_MSG( ... ) static_assert(__VA_ARGS__)
                                             ^
Chapter04/01_static_assert/main.cpp:76:5: note: in expansion of macro ‘BOOST_STATIC_ASSERT_MSG;
     BOOST_STATIC_ASSERT_MSG(boost::has_trivial_copy<T>::value,
     ^~~~~~~~~~~~~~~~~~~~~~~


boost/static_assert.hpp:31:45: error: static assertion failed: Can not fit value to buffer. Make the buffer bigger.
 #     define BOOST_STATIC_ASSERT_MSG( ... ) static_assert(__VA_ARGS__)
                                             ^
Chapter04/01_static_assert/main.cpp:81:5: note: in expansion of macro ‘BOOST_STATIC_ASSERT_MSG;
     BOOST_STATIC_ASSERT_MSG(BufSizeV >= sizeof(value),
     ^~~~~~~~~~~~~~~~~~~~~~
```

The C++11 standard has *static_assert(condition, "message")* that is equivalent to Boost's *BOOST_STATIC_ASSSERT_MSG*. The *BOOST_STATIC_ASSERT* functionality of asserting at compile time without a user provided message is available in C++17 as static_assert(condition). You do not have to include header files to be able to use your compiler built in static_assert.

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
