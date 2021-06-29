# Returning a value or flag where there is no value with Boost.Optional
Refer to: https://www.boost.org/doc/libs/1_76_0/doc/html/array.html

boost::array is a fixed-size array. The first template parameter of boost::array is the element type and the second one is the size of an array. If you need to change the array size at runtime, use std::vector , boost::container::small_vector, boost::container::stack_vector, or boost::container::vector instead.

The boost::array<> class has no handwritten constructors and all its members are public, so the compiler will treat it as a POD type.
(POD stands for Plain Old Data - that is, a class (whether defined with the keyword struct or the keyword class) without constructors, destructors and virtual members functions.)

One of the biggest advantages of boost::array is that it does not allocated dynamic memory and provides exactly the same performance as a usual C array.


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
