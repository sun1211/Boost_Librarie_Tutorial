# Converting all the tuple elements to strings

The main problem of the stringize function is that neither *boost::tuple* nor *std::pair* have *begin()* or *end()* methods, so we cannot call *std::for_each*. This is where the *Boost.Fusion* steps in.

The *Boost.Fusion* library contains lots of terrific algorithms that may manipulate structures at compile time.

The *boost::fusion::for_each* function iterates through elements of sequence and applies a functor for each of the elements.

Note that we have included:

```
#include <boost/fusion/adapted/boost_tuple.hpp> 
#include <boost/fusion/adapted/std_pair.hpp> 
#include <boost/fusion/adapted/boost_array.hpp> 
```
This is required because by default Boost.Fusion works only with its own classes. Boost.Fusion has its own tuple class, *boost::fusion::vector*, which is quite close to boost::tuple:
```
#include <string>
#include <cassert>

#include <boost/tuple/tuple.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>

void tuple_example() {
    boost::tuple<int, int, std::string> tup(1, 2, "Meow");
    assert(boost::get<0>(tup) == 1);
    assert(boost::get<2>(tup) == "Meow");
}

void fusion_tuple_example() {
    boost::fusion::vector<int, int, std::string> tup(1, 2, "Meow");
    assert(boost::fusion::at_c<0>(tup) == 1);
    assert(boost::fusion::at_c<2>(tup) == "Meow");
}
```
But *boost::fusion::vector* is not as simple as boost::tuple. We'll see the difference in the Splitting tuples recipe.

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

Meow! 0_0
 Meow! 0_0
 Meow! Meow! 
 Meow! Meow! Meow! Meow! Meow! Meow! Meow! Meow! Meow! Meow!

```