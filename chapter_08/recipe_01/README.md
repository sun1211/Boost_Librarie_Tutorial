# Using type vector of types

The *boost::mpl::vector* class is a compile-time container that holds types. To be more precise, it is a type that holds types. We do not make instances of it; instead, we are just using it in typedefs.

Unlike the standard library containers, the Boost.MPL containers have no member methods. Instead, methods are declared in a separate header. So to use some methods, we need to:

Include the correct header.
Call that method, usually by specifying the container as a first parameter.

Placeholders are widely used by the Boost.MPL library for combining the metafunctions:
```
typedef boost::mpl::transform<
    types,
    boost::remove_cv<boost::mpl::_1>
>::type noncv_types;
```

Here, *boost::mpl::_1* is a placeholder and the whole expression means, for each type in types, do *boost::remove_cv<>::type* and push back that type to the resulting vector. Return the resulting vector via *::type*.

Here, we specify a comparison metafunction for *boost::mpl::unique* using the *boost::is_same<boost::mpl::_1, boost::mpl::_2>* template parameter, where *boost::mpl::_1* and *boost::mpl::_2* are placeholders. You may find it similar to *boost::bind(std::equal_to(), _1, _2)*

```
std::vector<type> t; // 't' stands for 'types'. 
std::unique(t.begin(), t.end(), boost::bind(std::equal_to<type>(), _1, _2)); 
```

In the preceding code, sizes_types is not a vector of values, but rather a vector of integral constants-types representing numbers. The sizes_types typedef is actually a following type:

```
struct boost::mpl::vector<
    struct boost::mpl::size_t<4>,
    struct boost::mpl::size_t<4>,
    struct boost::mpl::size_t<4096>,
    struct boost::mpl::size_t<1>,
    struct boost::mpl::size_t<32> 
>
```

The Boost.MPL library usage results in longer compilation times, but gives you the ability to do everything you want with types. It does not add runtime overhead and won't even add a single instruction to the resulting binary. C++17 has no Boost.MPL classes, and Boost.MPL does not use features of modern C++, such as the variadic templates. This makes the Boost.MPL compilation times not as short as possible on C++11 compilers, but makes the library usable on C++03 compilers.

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

N5boost3mpl6v_itemIN4mpl_6size_tILm32EEENS1_INS3_ILm1EEENS1_INS3_ILm4096EEENS1_INS3_ILm8EEENS1_INS3_ILm4EEENS0_7vector0INS2_2naEEELi0EEELi0EEELi0EEELi0EEELi0EEE

```