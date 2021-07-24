# Getting benefits of a single linked list and memory pool

When we are using std::list, we may notice a slowdown because each node of the list needs separate allocation. It means that usually when we insert 10 elements into std::list, the container calls new 10 times. Also, the allocated nodes usually are located randomly in memory, which is not CPU cache friendly.

That is why we used Boost ::fast_pool_allocator<int> from Boost.Pool. This allocator tries to allocate bigger blocks of memory, so that at a later stage, multiple nodes could be constructed without multiple calls to new.

The Boost.Pool library has a drawback--it uses memory for internal needs. Usually, additional sizeof(void*) is used per element. To workaround that issue, we are using a single linked list from Boost.Containers.

The boost::container::slist class is more compact, but its iterators can iterate only forward. Step 3 is simple for those readers who are aware of standard library containers, so we move to step 4 to see some boost::container::slist specific features. Since a single linked list iterator could iterate only forward, traditional algorithms of insertion and deletion take linear time O(N). That's because when we are erasing or inserting, the previous element of the list must be modified. To workaround that issue, the single linked list has methods erase_after and insert_after that work for a constant time O(1). These methods insert or erase elements right after the current position of the iterator.

Take a careful look at the following code:
``` 
boost::singleton_pool<
        boost::fast_pool_allocator_tag,
        sizeof(slist_t::stored_allocator_type::value_type)
    >::release_memory();

```
It is required because boost::fast_pool_allocator does not free memory, so we must do it by hand
Let's take a look at the execution times to feel the difference:
```
$ TIME="Runtime=%E RAM=%MKB" time ./bin/main l
std::list: Runtime=0:00.17 RAM=34692KB

$ TIME="Runtime=%E RAM=%MKB" time ./07_slist_and_pool s
slist_t:   Runtime=0:00.8 RAM=19804KB
```

As we may see, slist_t uses half the memory, and is twice as fast compared to the std::list class.


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