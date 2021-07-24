# Storing a few elements in a sequence container

The **boost::container::small_vector's** second template parameter is the elements count to preallocate on a stack. So if most of the time we have to store 8 or less elements in the vector, we just put 8 as a second template parameter.

If we have to store more than 8 elements in the container, then the *small_vector* behaves exactly as *std::vector* and dynamically allocates a chunk of memory to store more than 8 elements. Just like *std::vector*, the *small_vector* is a sequence container with random access iterators that stores the elements consistently.

To sum up, *boost::container::small_vector* is a container that behaves exactly as *std::vector*, but allows to avoid memory allocations for a compile time specified amount of elements.

A drawback of using small_vector is that our elements count assumption leaks into the function signature that accepts small_vector as a parameter. So if we have three functions specialized for 4, 8, and 16 elements, respectively, and all those functions process transactions using execute_operations from the preceding example, we'll end up with multiple instantiations of the execute_operations function:

```
void execute_operations(
    const boost::container::small_vector<operation, 4>&);

void execute_operations(
    const boost::container::small_vector<operation, 8>&);

void execute_operations(
    const boost::container::small_vector<operation, 16>&);
```

That's not good! Now, we have multiple functions in our executable that do exactly the same thing and consist of almost exactly the same machine codes. This leads to bigger binaries, longer startup times of the executable, longer compile, and link times. Some compilers may eliminate the redundancy but chances are low.

However, the solution is very simple. *boost::container::small_vector* is derived from the *boost::container::small_vector_base* type that is independent from preallocated elements count:

```
void execute_operations(
    const boost::container::small_vector_base<operation>& ops
);
```
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