# Getting a human-readable type name

The **Boost.TypeIndex** library has a lot of workarounds for different compilers and knows the most efficient way to produce a human-readable name for the type. If you provide a type as a template parameter, the library guarantees that all the possible type related computations will be performed at compile time and code will work even if RTTI is disabled.

**cvr** in *boost::typeindex::type_id_with_cvr* stands for const, volatile, and reference. That makes sure that the type won't be decayed.

All the **boost::typeindex::type_id*** functions return instances of *boost::typeindex::type_index*. It is very close to *std::type_index*; however, it additionally, it has a *raw_name()* method for getting a raw type name, and *pretty_name()* for getting human-readable type name.

Unlike the *standard library's typeid()*, some classes from *Boost.TypeIndex* are usable with constexpr. It means that you can get a textual representation of your type at compile time if you use a specific *boost::typeindex::ctti_type_index class*.

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

T is d
x is i
T is double
x is int&&

```
