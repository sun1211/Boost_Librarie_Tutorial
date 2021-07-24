//C Style
#include <something_that_defines_macros>
#if !defined(__clang__) \
    && !defined(__ICC) \
    && !defined(__INTEL_COMPILER) \
    && (defined(__GNUC__) || defined(__GNUG__))

// GCC specific

#endif

#include <boost/predef/compiler.h>

#if BOOST_COMP_GNUC
//#if defined(BOOST_COMP_GNUC) // Wrong!

// GCC specific

#endif