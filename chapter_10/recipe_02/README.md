# Detecting int128 support

The header <boost/config.hpp> contains a lot of macros to describe compiler and platform features. In this example, we used BOOST_HAS_INT128 to detect support of 128-bit integers and BOOST_NO_LONG_LONG to detect support of 64-bit integers.

As we may see from the example, Boost has typedefs for 64-bit signed and unsigned integers:

```
boost::long_long_type  
boost::ulong_long_type 
```

It also has typedefs for 128-bit signed and unsigned integers:
```
boost::int128_type 
boost::uint128_type
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