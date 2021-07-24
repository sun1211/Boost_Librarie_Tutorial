# Writing metafunctions using simpler methods

The BOOST_NO_CXX11_CONSTEXPR macro is defined when C++11 constexpr is available.

The constexpr keyword tells the compiler that the function can be evaluated at compile time if all the inputs for that function are compile-time constants. C++11 imposes a lot of limitations on what a constexpr function can do. C++14 removed some of the limitations.

The BOOST_NO_CXX11_HDR_ARRAY macro is defined when the C++11 std::array class and the <array> header are available.

However, there are other usable and interesting macros for constexpr too, as follows:

 - The BOOST_CONSTEXPR macro expands to constexpr or does not expand
 - The BOOST_CONSTEXPR_OR_CONST macro expands to constexpr or const
 - The BOOST_STATIC_CONSTEXPR macro is the same as static BOOST_CONSTEXPR_OR_CONST
Using those macros, it is possible to write code that takes advantage of C++11 constant expression features if they are available:
```
template <class T, T Value> 
struct integral_constant { 
    BOOST_STATIC_CONSTEXPR T value = Value; 
    
    BOOST_CONSTEXPR operator T() const { 
        return this->value; 
    } 
}; 
```

Now, we can use integral_constant as shown in the following code:
```
char array[integral_constant<int, 10>()];
```

In the example, BOOST_CONSTEXPR operator T() is called to get the array size.

The C++11 constant expressions may improve compilation speed and diagnostic information in case of error. It's a good feature to use. If your function requires relaxed constexpr from C++14, then you may use BOOST_CXX14_CONSTEXPR macro. It expands to constexpr only if relaxed constexpr is available and expands to nothing otherwise.

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