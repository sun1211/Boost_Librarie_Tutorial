# Passing C++11 lambda functions in a variable

Performance of the lambda function storage in *Boost.Functional* is the same as in other cases. While a functional object produced by the lambda expression is small enough to fit in an instance of **boost::function**, no dynamic memory allocation is performed. Calling an object stored in **boost::function** is close to the speed of calling a function by a pointer. Copying **boost::function** allocates heap memory only if initial **boost::function** has a stored object that does not fit in it without allocation. Moving instances does not allocate and deallocate memory.


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
