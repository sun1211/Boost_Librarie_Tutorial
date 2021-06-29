# Using a safer way to work with a container that stores multiple chosen types with Boost.any

Imagine that you are creating a wrapper around some SQL database interface. You decided that boost::any will perfectly match the requirements for a single cell of the database table.

Some other programmer will use your classes, and his/her task would be to get a row from the database and count the sum of the arithmetic types in a row.

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

Sum of arithmetic types in database row is: 20.1
```
