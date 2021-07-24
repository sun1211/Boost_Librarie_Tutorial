# Reducing code size and increasing performance of user-defined types (UDTs) in C++11

The BOOST_NOEXCEPT macro expands to noexcept on compilers that support it. The standard library containers use type traits to detect if the constructor throws an exception or not. Type traits make their decision mainly based on noexcept specifiers.

Why do we get an error without BOOST_NOEXCEPT? Compiler's type trait returns that move_nothrow throws, so std::vector tries to use the copy constructor of move_nothrow, which is not defined.

The BOOST_NOEXCEPT macro also reduces binary size irrespective of whether the definition of the noexcept function or method is in a separate source file or not.
```
// In header file.
int foo() BOOST_NOEXCEPT; 
 
// In source file.
int foo() BOOST_NOEXCEPT { 
    return 0; 
} 
```

That's because in the latter case, the compiler knows that the function does not throw exceptions and so there is no need to generate code that handles them.

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