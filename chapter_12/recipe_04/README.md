# Using portable math functions

Real types have specific values that cannot be checked using equality operators. For example, if the variable v contains NaN, assert(v != v) may or may not pass depending on the compiler.

For such cases, Boost.Math provides functions that may reliably check for infinity and NaN values.

Step 3 contains the boost::math::signbit function, which requires clarification. This function returns a signed bit, which is 1 when the number is negative and 0 when the number is positive. In other words, it returns true if the value is negative.

Looking at step 3, some readers may ask, why can't we just multiply by -1 instead of calling boost::math::changesign? We can. But, multiplication may work slower than boost::math::changesign and is not guaranteed at work for special values. For example, if your code can work with nan, the code in step 3 is able to change the sign of -nan and write nan to the variable.

The Boost.Math library maintainers recommend wrapping math functions from this example in round parentheses to avoid collisions with C macro. It is better to write (boost::math::isinf)(value) instead of boost::math::isinf(value).

C99 contains all the functions described in this recipe. Why do we need them in Boost? Well, some compiler vendors think that programmers do not need the full support of C99, so you won't find those functions in at least one very popular compiler. Another reason is that the Boost.Math functions may be used for classes that behave like numbers.

Boost.Math is a very fast, portable, and reliable library. Mathematical special functions are part of the Boost.Math library and some mathematical special functions were accepted into C++17. A Boost.Math, however, provides more of them and has highly usable recurrent versions that have better complexities and better suit some of the tasks (like numerical integrations).

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