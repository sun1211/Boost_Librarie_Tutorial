# Detecting an OS and compiler

The header <boost/predef/compiler.h> knows all the possible compilers and has a macro for each of those. So if the current compiler is GCC, then macro BOOST_COMP_GNUC is defined to 1 and all the other macros for other compilers are defined to 0. If we are not on a GCC compiler, then the BOOST_COMP_GNUC macro is defined to 0.

The Boost.Predef library also has macros for detecting OS, architecture, standard library implementation, and some hardware abilities. Approach with macros that are always defined; this allows you to write complex expressions much shorter:

```
#include <boost/predef/os.h>
#include <boost/predef/compiler.h>

#if BOOST_COMP_GNUC && BOOST_OS_LINUX && !BOOST_OS_ANDROID

// Do something for non Android Linux.

#endif
```