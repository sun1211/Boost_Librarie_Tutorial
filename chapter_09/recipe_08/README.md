# Using flat associative containers

The boost::container::flat_set class stores its values ordered in vector, which means that any insertion or deletion of elements not on the end on the container takes liner time O(N), just like in case of std::vector. This is a necessary evil. But for that, we gain almost three times less memory usage per element, more processor cache friendly storage, and random access iterators.

Without reserving memory, insertion of elements may become at times slower and less memory efficient. The std::vector class allocates the required chunk of memory and then in-place construct elements on that chunk. When we insert some element without reserving the memory, there is a chance that there is no free space remaining on the preallocated chunk of memory, so std::vector allocates a bigger chunk of memory . After that, std::vector copies or moves elements from the first chunk to the second, deletes elements of the first chunk, and deallocates the first chunk. Only after that, insertion occurs. Such copying and deallocation may occur multiple times during insertions, dramatically reducing the speed.

we are inserting elements here. Note that we are inserting ordered elements. This is not required, but recommended to speed up insertion. Inserting elements at the end of std::vector is much more cheaper than in the middle or at the beginning.

When should we use flat containers, and when should we use usual ones? Well, it's up to you, but here is a list of differences from the official documentation of Boost.Container that will help you to decide:

 - A faster lookup than standard associative containers
 - Much faster iteration than standard associative containers
 - Less memory consumption for small objects (and for big objects if shrink_to_fit is used)
 - Improved cache performance (data is stored in contiguous memory)
 - Nonstable iterators (iterators are invalidated when inserting and erasing elements)
 - Non-copyable and non-movable value types can't be stored
 - Weaker exception safety than standard associative containers (copy/move constructors can throw an exception when shifting values in erasures and insertions)
 - Slower insertion and erasure than standard associative containers (specially for non-movable types)
C++17 unfortunately has no flat containers. Flat containers from Boost are fast, have a lot of optimizations, and do not use virtual functions. Classes from Boost.Containers have support of rvalue reference emulation via Boost.Move, so you are free to use them even on C++03 compilers.

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