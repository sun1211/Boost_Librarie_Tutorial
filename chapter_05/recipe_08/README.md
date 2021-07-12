# Manipulating a group of threads

The boost::thread_group variable just holds all the threads constructed or moved to it and may send some calls to all the threads.

C++11 has no thread_group class; it's Boost specific.

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
