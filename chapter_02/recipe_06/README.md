# Passing function pointer in a variable

The **Boost.Function** library provides a good performance for pointers to functions, and it will not allocate memory on heap. Standard library **std::function** is also effective in storing function pointers. Since *Boost 1.58*, the *Boost.Function* library can store functions and functional objects that have call signature with rvalue references

```
boost::function<int(std::string&&)> f = &something;
f(std::string("Hello")); // Works
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

10

```
