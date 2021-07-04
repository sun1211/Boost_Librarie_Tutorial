# Do it at scope exit

If you were dealing with languages, such as Java, C#, or Delphi, you obviously were using the *try {} finally{}* construction. Let me briefly describe to you what do these language constructions do.

When a program leaves the current scope via return or exception, code in the finally block is executed. This mechanism is used as a replacement for the RAII pattern

```
// Some pseudo code (suspiciously similar to Java code) 
try { 
    FileWriter f = new FileWriter("example_file.txt"); 
    // Some code that may throw or return 
    // ... 
} finally { 
    // Whatever happened in scope, this code will be executed 
    // and file will be correctly closed 
    if (f != null) { 
        f.close() 
    } 
}
```

C++ uses the RAII pattern instead of try {} finally{} construction. The Boost.ScopeExit library was designed to allow user definition of RAII wrappers right in the function body.

The **Boost.ScopeExit** library allocates no additional memory on heap and does not use virtual functions. Use the default syntax and do not define *BOOST_SCOPE_EXIT_CONFIG_USE_LAMBDAS* because otherwise scope exit will be implemented using *boost::function*, which may allocate additional memory and imply an optimization barrier. You may achieve close to the *BOOST_SCOPE_EXIT* results using *boost::movelib::unique_ptr* or *std::unique_ptr* by specifying a custom deleter

```
#include <boost/move/unique_ptr.hpp>
#include <cstdio>

void unique_ptr_example() {
    boost::movelib::unique_ptr<std::FILE, int(*)(std::FILE*)> f(
        std::fopen("example_file.txt", "w"), // open file
        &std::fclose  // specific deleter
    );
    // ...
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
