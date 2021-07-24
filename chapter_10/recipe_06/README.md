# The portable way to export and import functions and classes

There, we are defining the macro MY_LIBRARY_API, which we apply to classes and methods that we wish to export from our library.

we check for MY_LIBRARY_LINK_DYNAMIC. If it is not defined, we are building a static library and there is no need to define MY_LIBRARY_API.

The developer must take care of MY_LIBRARY_LINK_DYNAMIC! It will not define itself. If we are making a dynamic library, we need to make our build system to define it, 

If MY_LIBRARY_LINK_DYNAMIC is defined, we are building a runtime library, and that's where the workarounds start. You, as the developer, must tell the compiler that we are now exporting function to the user. The user must tell the compiler that he/she is importing methods from the library. To have a single header file for both the import and export library, we use the following code:

```
#if defined(MY_LIBRARY_COMPILATION) 
#    define MY_LIBRARY_API BOOST_SYMBOL_EXPORT 
#else 
#    define MY_LIBRARY_API BOOST_SYMBOL_IMPORT 
#endif 
```
When exporting the library (or, in other words, compiling it), we must define MY_LIBRARY_COMPILATION. This leads to MY_LIBRARY_API being defined to BOOST_SYMBOL_EXPORT. For example, see step 5, where we defined MY_LIBRARY_COMPILATION before including my_library.hpp. If MY_LIBRARY_COMPILATION is not defined, the header is included by the user, who doesn't know anything about that macro. And, if the header is included by the user, the symbols must be imported from the library.

The BOOST_SYMBOL_VISIBLE macro must be used only for those classes that are not exported but are used by RTTI. Examples of such classes are exceptions and classes being cast using dynamic_cast.

Some compilers export all the symbols by default but provide flags to disable such behavior. For example, GCC and Clang on Linux provide -fvisibility=hidden. It is highly recommended to use those flags because it leads to smaller binary size, faster loading of dynamic libraries, and better logical structuring of binary. Some inter-procedural optimizations can perform better when fewer symbols are exported. C++17 has no standard way for describing visibilities. Hopefully someday, a portable way to work with visibility will appear in C++, but until then, we have to use macros from Boost.

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