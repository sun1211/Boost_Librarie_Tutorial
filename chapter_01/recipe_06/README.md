# Using a safer way to work with a container that stores multiple chosen types with Boost.any

The Boost.Variant library implements a visitor programming pattern for accessing the stored data, which is much safer than getting values via boost::get<>. This pattern forces the programmer to take care of each type in variant, otherwise the code will fail to compile. You can use this pattern via the boost::apply_visitor function, which takes a visitor functional object as the first parameter and a variant as the second parameter. If you are using a pre C++14 compiler, then visitor functional objects must derive from the boost::static_visitor<T> class, where T is a type being returned by a visitor. A visitor object must have overloads of operator() for each type stored by a variant.

At compile time, the Boost.Variant library generates a big switch statement, each case of which calls a visitor for a single type from the variant's list of types. At runtime, the index of the stored type is retrieved using which() and jumps to a correct case in switch statement is made. Something like this will be generated for boost::variant<int, float, std::string>:

```
switch (which()) 
{ 
case 0 /*int*/: 
    return visitor(*reinterpret_cast<int*>(address())); 
case 1 /*float*/: 
    return visitor(*reinterpret_cast<float*>(address())); 
case 2 /*std::string*/: 
    return visitor(*reinterpret_cast<std::string*>(address())); 
default: assert(false); 
}
```

If we compare this example with the first example in this recipe, we'll see the following advantages of boost::variant:

- We know what types a variable can store
- If a library writer of the SQL interface adds or modifies a type held by a variant, we'll get a compile-time error instead of incorrect behavior

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

Wow! That is great!
```
