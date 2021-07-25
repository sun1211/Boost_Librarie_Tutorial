# Using pointers in a shared memory

We cannot use pointers in shared memory because, when a piece of shared memory is mapped into the address space of a process, its address is valid only for that process. When we are getting the address of a variable, it is just a local address for that process. Other processes will map shared memory to a different base address, and as a result, the variable address differs.

As the pointer and structure are in the same shared memory segment, the distance between them does not change. The idea behind boost::interprocess::offset_ptr is to remember that distance between offset_ptr and the pointed value. On deference, offset_ptr adds the distance value to the process-dependent address of the offset_ptr variable.

The offset pointer imitates the behavior of pointers, so it is a drop-in replacement that can be applied quickly.

*Do not place the classes that may have pointers or references into shared memory!*

An offset pointer works slightly slower than the usual pointer because, on each dereference, it is required to compute the address. But, this difference is not usually what should bother you.

C++17 has no offset pointers.

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

Creating structure
Structure found

```