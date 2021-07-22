# Manipulating a vector of types
we assert that sizes are equal, but we do it in an unusual way. The *boost::mpl::size<Types>::type* metafunction actually returns an integral constant struct *boost::mpl::long_<4>*, so in a static assertion, we actually compare two types, not two numbers. This can be rewritten in a more familiar way:
```
 BOOST_STATIC_ASSERT((
        boost::mpl::size<Types>::type::value
        ==
        boost::mpl::size<Modifiers>::type::value
    ));
```
Notice the typename keyword we use. Without it, the compiler won't be able to decide if ::type is actually a type or some variable. Previous recipes did not require it, because parameters for the metafunction were fully known at the point where we were using them. But in this recipe, parameter for the metafunction is a template.




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

N4mpl_5long_ILl4EEE

```