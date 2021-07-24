# Splitting tuples

The idea behind Boost.Fusion is that the compiler knows the structure layout at compile time and whatever the compiler knows at compile time, we may change at the same time. The Boost.Fusion allows us to modify different sequences, adding and removing fields, and changing field types. we removed the non-required fields from the tuple.

Now, let's take a very close look at get_nonarithmetics. First of all, its result type is deduced using the following construction:

```
typename boost::fusion::result_of::remove_if<
    const Sequence, 
    boost::is_arithmetic<boost::mpl::_1> 
>::type
```

This must be familiar to us. We saw something like this in the Getting function result type at compile-time recipe in this chapter. The Boost.MPL's placeholder *boost::mpl::_1* works well with the *boost::fusion::result_of::remove_if* metafunction that returns a new sequence type.

Now, let's move inside the function and we watch the following code:
```
return boost::fusion::remove_if< 
        boost::is_arithmetic<boost::mpl::_1> 
    >(seq);
```
Remember that the compiler knows all the types of seq at compile time. This means that Boost.Fusion may apply metafunctions for different elements of seq and get the metafunction results for them. This also means that Boost.Fusion knows how to copy required fields from the old structure to the new one.

However, Boost.Fusion tries not to copy fields as long as possible.

Our functions can be used with any type supported by Boost.Fusion and not just with *boost::fusion::vector*.

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