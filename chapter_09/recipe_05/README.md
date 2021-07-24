# Making a map, where value is also a key

we define the bimap type:
```
typedef boost::bimap< 
        std::string, 
        boost::bimaps::multiset_of<std::size_t> 
    > name_id_type; 
```

The first template parameter tells that the first key must have type std::string, and should work as std::set. The second template parameter tells that the second key must have type std::size_t. Multiple first keys may have a single second key value, just like in std::multimap.

We may specify the underlying behavior of bimap using classes from the boost::bimaps:: namespace. We may use hash map as an underlying type for the first key:
```
#include <boost/bimap/unordered_set_of.hpp> 
#include <boost/bimap/unordered_multiset_of.hpp> 
 
typedef boost::bimap< 
    boost::bimaps::unordered_set_of<std::string>,  
    boost::bimaps::unordered_multiset_of<std::size_t>  
> hash_name_id_type; 
```

When we do not specify the behavior of the key and just specify its type, Boost.Bimap uses boost::bimaps::set_of as a default behavior. Just like in our example, we may try to express the following code using standard library:
```
#include <boost/bimap/set_of.hpp> 
 
typedef boost::bimap< 
    boost::bimaps::set_of<std::string>,  
    boost::bimaps::multiset_of<std::size_t>  
> name_id_type; 
```
Using standard library it would look like a combination of the following two variables:
```
std::map<std::string, std::size_t> key1;      // == name_id.left
std::multimap<std::size_t, std::string> key2; // == name_id.right
```

As we can see from the preceding comments, a call to name_id.left (in step 4) returns a reference to something with an interface close to std::map<std::string, std::size_t>. A call to name_id.right from step 5 returns something with an interface close to std::multimap<std::size_t, std::string>.

In step 6, we work with a whole bimap, searching for a pair of keys and making sure that they are in the container.

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