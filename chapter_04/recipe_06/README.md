# Selecting an optimal operator for a template parameter with Boost.TypeTrait

All the magic is done via the *conditional<bool Condition, class T1, class T2>* metafunction. When *true* is passed into the metafunction as a first parameter, it returns *T1* via the *::type typedef*. When *false* is passed into the metafunction as a first parameter, it returns *T2* via the *::type typedef*. It acts like some kind of compile-time if statement.

So, *step0_t* holds a *detail::plus_functor* metafunction and *step1_t* holds *step0_t* or *detail::plus_assignable_functor*. The *step2_t* type holds *step1_t* or *detail::post_inc_functor*. The *step3_t* type holds *step2_t* or *detail::pre_inc_functor*. What each *step*_t* typedef holds is deduced using type trait.

C++17 has an if constexpr construction that makes the preceding example much simpler:
```
template <class T> 
void inc_cpp17(T& value) { 
    if constexpr (boost::has_pre_increment<T>()) {
        ++value;
    } else if constexpr (boost::has_post_increment<T>()) {
        value++;
    } else if constexpr(boost::has_plus_assign<T>()) {
        value += T(1);
    } else {
        value = value + T(1);
    }
}
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
