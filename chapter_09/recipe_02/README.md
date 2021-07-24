# Storing at most N elements in the sequence container

The **boost::container::static_vector<T, N>** is a container that does not allocate memory and can hold no more than a compile-time-specified amount of elements. Think of it as of *boost::container::small_vector<T, N>* that just cannot dynamically allocate memory and any attempt to store more than N elements results in a std::bad_alloc exception:

Just like all the containers of the Boost.Container library, static_vector supports move semantics and emulates rvalue references using Boost.Move library if your compiler does not support rvalues.

The std::vector allocates bigger chunks of memory if a user inserts an element and it is impossible to fit the new value into the already allocated memory. In that case, std::vector moves elements from the old location to the new one if the elements are nothrow move constructible. Otherwise, std::vector copies elements to a new location and after that calls destructor for each element in the old location.

Because of that, behavior std::vector has amortized constant complexity for many member functions. The static_vector never allocates memory so that it does not have to move or copy elements from an old location to a new one. Because of that, operations that have amortized O(1) complexity for std::vector have true O(1) complexity for boost::container::static_vector. This may be handy for some real-time applications; though, beware of exceptions!

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