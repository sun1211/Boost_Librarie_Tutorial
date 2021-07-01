# Managing pointers to arrays that do not leave scope

In all examples, smart pointer classes count references and call *delete[]* for a pointer when the count of references becomes equal to zero. The first and second examples are simple. In the third example, we provide a custom deleter object for a *shared pointer*. The deleter object of a smart pointer is called when the smart pointer decides to free resources. When smart pointer is constructed without explicit deleter, the default deleter is constructed that calls *delete* or *delete[]* depending on the template type of the smart pointer.

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
