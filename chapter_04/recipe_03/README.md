# Enabling function template usage for integral types with Boost.Core and Boost.TypeTraits

The **boost::disable_if_c<bool_value>::type** metafunction disables the method, if bool_value equals true. It works just like *boost::enable_if_c<!bool_value>::type*.

A class passed as the second parameter for *boost::enable_if_c* or *boost::disable_if_c* is returned via *::type* in the case of successful substitution. In other words, *boost::enable_if_c<true, T>::type* is the same as T.

Let's go through the *process_data(i, i, i)* case, step by step. We pass an int as T type and the compiler searches for *function process_data(int, int, int)*. Because there is no such function, the next step is to instantiate a template version of process_data. However, there are two template process_data functions. For example, the compiler starts instantiating the templates from our second (optimized) version; in that case, it successfully evaluates the typename *boost::enable_if_c<boost::has_plus_assign<T>::value, T>::type* expression, and gets the T return type. But, the compiler does not stop; it continues instantiation attempts and tries to instantiate our first version of the function. During substitution of typename *boost::disable_if_c<boost::has_plus_assign<T>::value* a failure happens, which is not treated as an error due to the SFINAE rule. There are no more template process_data functions, so the compiler stops instantiating. As you can see, without *enable_if_c* and *disable_if_c*, the compiler would be able to instantiate both templates and there will be an ambiguity.


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
