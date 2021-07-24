# Using an unordered set and map

Unordered containers store values and remember the hash of each value. Now if you wish to find a value in them, they will compute the hash of that value and search for that hash in the container. After hash is found, containers check for equality of the found value and the searched value. Then, the iterator to the value or to the end of container is returned.

Because the container may search for the constant width integral hash value, it may use some optimizations and algorithms suitable only for integers. Those algorithms guarantee constant search complexity O(1), when traditional std::set and std::map provide worse complexity O(log(N)), where N is the number of elements in the container. This leads us to a situation where the more the elements in traditional std::set or std::map, the slower it works. However, the performance of unordered containers does not depend on the element count.

Such good performance never comes free of cost. In unordered containers, values are unordered (you are not surprised, are you?). It means that we'll be elements of containers from begin() to end() will be the output, as follows:
```
template <class T>
void output_example() {
    T strings;
    
    strings.insert("CZ");
    strings.insert("CD");
    strings.insert("A");
    strings.insert("B");

    std::copy(
        strings.begin(),
        strings.end(),
        std::ostream_iterator<std::string>(std::cout, "  ")
    );
}
```
We'll get the following output for std::set and boost::unordered_set:
```
boost::unordered_set<std::string> : B A CD CZ
 std::set<std::string> : A B CD CZ
```
Multiversions of containers are also available, boost::unordered_multiset is defined in the <boost/unordered_set.hpp> header, and boost::unordered_multimap is defined in the <boost/unordered_map.hpp> header. Just like in the case of a standard library, multiversions of containers are capable of storing multiple equal key values.

All the unordered containers allow you to specify your own hashing functor, instead of the default boost::hash. They also allow you to specialize your own equal comparison functor, instead of the default std::equal_to.

C++11 has all the unordered containers of the Boost library. You may find them in the headers: <unordered_set> and <unordered_map>, in the std:: namespace, instead of boost::. The Boost and the standard library versions may differ in performance, but must work in the same way. However, Boost's unordered containers are available even on C++03/C++98 compilers and make use of the rvalue reference emulation of Boost.Move, so you may use those containers for the move-only classes even on pre-C++11 compilers.

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

boost::unordered_set<std::string> : B  A  CD  CZ  
std::set<std::string> : A  B  CD  CZ
```