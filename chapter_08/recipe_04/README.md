# Making a higher-order metafunction

Functions that accept other functions as an input parameter or functions that return other functions are called higher-order functions.

The main problem with writing the higher-order metafunctions is taking care of the placeholders. That's why we shall not call Func1<Param1>::type directly. Instead of that, we must use the boost::mpl::apply metafunction, which accepts one function and up to five parameters that shall be passed to this function.

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