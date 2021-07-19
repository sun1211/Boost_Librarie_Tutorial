# Boost C++ Application Libraries Tutorial
Boost is a collection of C++ libraries. Each library has been reviewed by many professional programmers before being accepted by Boost. Libraries are tested on multiple platforms using many compilers and many C++ standard library implementations. While using Boost, you can be sure that you are using one of the most portable, fast, and reliable solutions that is distributed under a license suitable for commercial and open source projects.

## Setup environment
**1. Install CMake**
```
cd ~
wget https://github.com/Kitware/CMake/releases/download/v3.14.5/cmake-3.14.5.tar.gz
tar xf cmake-3.14.5.tar.gz
cd cmake-3.14.5
./bootstrap --parallel=10
make -j4
sudo make -j4 install
```
**2. Install Boost**
```
cd ~
wget https://boostorg.jfrog.io/artifactory/main/release/1.69.0/source/boost_1_69_0.tar.gz
tar xf boost_1_69_0.tar.gz
cd boost_1_69_0
./bootstrap.sh
./b2 ... cxxflags="-std=c++0x -stdlib=libc++" linkflags="-stdlib=libc++" ...
sudo ./b2 toolset=gcc -j4 install
```
## Table of contents

### [Chapter 1: Starting to Write Your Application](chapter_01/README.md)

- [1. Program with option base with Boost.program_options](chapter_01/recipe_01/README.md)
- [2. Program with option short with Boost.program_options](chapter_01/recipe_02/README.md)
- [3. Storing any value in a container/variable with Boost.any](chapter_01/recipe_03/README.md)
- [4. Storing multiple chosen types in a container/variable with Boost.variant](chapter_01/recipe_04/README.md)
- [5. Using a safer way to work with a container that stores multiple chosen types with Boost.any](chapter_01/recipe_05/README.md)
- [6. Using a safer way to work with a container that stores multiple chosen types with Boost.Variant](chapter_01/recipe_06/README.md)
- [7. Returning a value or flag where there is no value with Boost.Optional](chapter_01/recipe_07/README.md)
- [8. Returning an array from a function with Boost.array](chapter_01/recipe_08/README.md)
- [9. Combining multiple values into one with Boost.Tuple](chapter_01/recipe_09/README.md)
- [10. Binding and reordering function parameters with Boost.bind](chapter_01/recipe_10/README.md)
- [11. Getting a human-readable type name with Boost.type_index](chapter_01/recipe_11/README.md)
- [12. Using the C++11 move emulation with Boost.swap](chapter_01/recipe_12/README.md)
- [13. Making a noncopyable class with Boost.noncopyable](chapter_01/recipe_13/README.md)
- [14. Making a noncopyable but movable class](chapter_01/recipe_14/README.md)
- [15. Using C++14 and C++11 algorithms with Boost.algorithm](chapter_01/recipe_15/README.md)

### [Chapter 2: Managing Resources](chapter_02/README.md)

- [1. Managing local pointers to classes that do not leave scope](chapter_02/recipe_01/README.md)
- [2. Reference counting of pointers to classes used across functions](chapter_02/recipe_02/README.md)
- [3. Managing pointers to arrays that do not leave scope](chapter_02/recipe_03/README.md)
- [4. Reference counting of pointers to arrays used across functions](chapter_02/recipe_04/README.md)
- [5. Storing any functional objects in a variable](chapter_02/recipe_05/README.md)
- [6. Passing function pointer in a variable](chapter_02/recipe_06/README.md)
- [7. Passing C++11 lambda functions in a variable](chapter_02/recipe_07/README.md)
- [8. Containers of pointers with Boost.PointerContainer](chapter_02/recipe_08/README.md)
- [9. Do it at scope exit with Boost.scope_exit](chapter_02/recipe_09/README.md)
- [10. Initializing the base class by the member of the derived class with Boost.Utility](chapter_02/recipe_10/README.md)

### [Chapter 3: Converting and Casting](chapter_03/README.md)

- [1. Converting strings to numbers with Boost.LexicalCast](chapter_03/recipe_01/README.md)
- [2. Converting numbers to strings with Boost.LexicalCast](chapter_03/recipe_02/README.md)
- [3. Converting numbers to numbers with Boost.LexicalCast](chapter_03/recipe_03/README.md)
- [4. Converting user-defined types to/from strings](chapter_03/recipe_04/README.md)
- [5. Converting smart pointers](chapter_03/recipe_05/README.md)
- [6. Casting polymorphic objects with Boost::polymorphic_cast](chapter_03/recipe_06/README.md)
- [7. Parsing simple input with Boost.Spirit](chapter_03/recipe_07/README.md)
- [8. Parsing complex input with Boost.Spirit](chapter_03/recipe_08/README.md)

### [Chapter 4: Compile-Time Tricks](chapter_04/README.md)

- [1. Checking sizes at compile time with Boost.StaticAssert and Boost.TypeTraits](chapter_04/recipe_01/README.md)
- [2. Enabling function template usage for integral types with Boost.Core and Boost.TypeTraits](chapter_04/recipe_02/README.md)
- [3. Disabling function template usage for real types with Boost.Core and Boost.TypeTraits](chapter_04/recipe_03/README.md)
- [4. Creating a type from a number](chapter_04/recipe_04/README.md)
- [5. Implementing a type trait with Boost.TypeTrait](chapter_04/recipe_05/README.md)
- [6. Selecting an optimal operator for a template parameter with Boost.TypeTrait](chapter_04/recipe_06/README.md)
- [7. Getting a type of expression in C++03 with Boost.Typeof](chapter_04/recipe_07/README.md)

### [Chapter 5: Multithreading](chapter_05/README.md)

- [1. Creating a thread of execution](chapter_05/recipe_01/README.md)
- [2. Syncing access to a common resource use boost::mutex](chapter_05/recipe_02/README.md)
- [3. Fast access to common resource using atomics](chapter_05/recipe_03/README.md)
- [4. Creating work_queue class](chapter_05/recipe_04/README.md)
- [5. Multiple-readers-single-writer lock](chapter_05/recipe_05/README.md)
- [6. Creating variables that are unique per thread](chapter_05/recipe_06/README.md)
- [7. Interrupting a thread](chapter_05/recipe_07/README.md)
- [8. Manipulating a group of threads](chapter_05/recipe_08/README.md)
- [9. Initializing a shared variable safely](chapter_05/recipe_09/README.md)
- [10. Locking multiple mutexes](chapter_05/recipe_10/README.md)

### [Chapter 6: Manipulating Tasks](chapter_06/README.md)

- [1. Registering a task for an arbitrary data type processing](chapter_06/recipe_01/README.md)
- [2. Making timers and processing timer events as tasks](chapter_06/recipe_02/README.md)
- [3. Network communication as a task and Accepting incoming connections](chapter_06/recipe_03/README.md)
- [4. Executing different tasks in parallel](chapter_06/recipe_04/README.md)
- [5. Pipeline tasks processing](chapter_06/recipe_05/README.md)
- [6. Making a nonblocking barrier](chapter_06/recipe_06/README.md)
- [7. Storing an exception and making a task from it](chapter_06/recipe_07/README.md)
- [8. Getting and processing system signals as tasks](chapter_06/recipe_08/README.md)

### [Chapter 7: Manipulating Strings](chapter_07/README.md)

- [1. Changing cases and case-insensitive comparison](chapter_07/recipe_01/README.md)
- [2. Matching strings using regular expressions](chapter_07/recipe_02/README.md)
- [3. Formatting strings using safe printf-like functions](chapter_07/recipe_03/README.md)


