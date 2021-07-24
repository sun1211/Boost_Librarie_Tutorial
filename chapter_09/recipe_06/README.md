# Using multi-index containers
The hardest part here is a construction of multi-index type using boost::multi_index::multi_index_container. The first template parameter is a class that we are going to index. In our case, it is person. The second parameter is a type boost::multi_index::indexed_by, all the indexes must be described as a template parameter of that class.

Now, let's take a look at the first index description:
```
boost::multi_index::ordered_unique< 
                boost::multi_index::identity<person> 
            > 
```
The usage of the boost::multi_index::ordered_unique class means that the index must work like std::set and have all of its members. The boost::multi_index::identity<person> class means that the index must use the operator < of a person class for orderings.

Take a look at the second index:
```
boost::multi_index::hashed_non_unique< 
                boost::multi_index::member< 
                    person, std::size_t, &person::id_ 
                > 
            >
```
The boost::multi_index::hashed_non_unique type means that the index works like std::set, and boost::multi_index::member<person, std::size_t, &person::id_> means that the index must apply the hash function only to a single member field of the person structure to person::id_.

The remaining indexes won't be a trouble now; so let's take a look at the usage of indexes in the print function instead. Getting the type of iterator for a specific index is done using the following code:

```
typedef typename Indexes::template nth_index< 
            IndexNo 
    >::type::const_iterator const_iterator_t; 
```
This looks slightly overcomplicated because Indexes is a template parameter. The example would be simpler, if we could write this code in the scope of indexes_t:
```
typedef indexes_t::nth_index<0>::type::const_iterator const_iterator_t;
```

The nth_index member metafunction takes a zero-based number of index to use. In our example, index 1 is index of IDs, index 2 is index of heights, and so on.

Now, let's take a look at how to use const_iterator_t:
```
for (const_iterator_t it = persons.template get<IndexNo>().begin(), 
         iend = persons.template get<IndexNo>().end(); 
         it != iend; 
         ++it) 
    { 
        const person& v = *it; 
        // ... 
```
This can also be simplified for indexes_t being in scope:
```
 for (const_iterator_t it = persons.get<0>().begin(), 
         iend = persons.get<0>().end(); 
         it != iend; 
         ++it) 
    { 
        const person& v = *it; 
        // ... 
```
The function get<indexNo>() returns index. We may use that index almost like an STL container.

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

0:
Anton Polukhin, 3, 182, 70
Antony Polukhin, 3, 183, 70
John Snow, 1, 185, 80
Vasya Pupkin, 2, 165, 60

1:
John Snow, 1, 185, 80
Vasya Pupkin, 2, 165, 60
Anton Polukhin, 3, 182, 70
Antony Polukhin, 3, 183, 70

2:
Vasya Pupkin, 2, 165, 60
Anton Polukhin, 3, 182, 70
Antony Polukhin, 3, 183, 70
John Snow, 1, 185, 80

3:
Vasya Pupkin, 2, 165, 60
Antony Polukhin, 3, 183, 70
Anton Polukhin, 3, 182, 70
John Snow, 1, 185, 80
```