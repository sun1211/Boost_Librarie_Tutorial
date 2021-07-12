# Initializing a shared variable safely

In short, **boost::call_once** and **boost::once_flag** make sure that the function passed as a second parameter is executed only once.

The *boost::call_once* function synchronizes calls to the function F passed as a second argument. *boost::call_once* and *boost::once_flag* make sure that only one call to the function F progresses if there are two or more concurrent calls on the same once_flag and make sure that only once successful call to F is performed.

If the call to function F has not thrown exceptions that left the body of F, then *boost::call_once* assumes that the call was successful and stores that information inside the boost::once_flag. Any subsequent calls to *boost::call_once* with the same *boost::once_flag* do nothing.

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

Print once 0

```
