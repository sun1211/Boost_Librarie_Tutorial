//Include a heade
#include <boost/config.hpp>

namespace project {

//detect int128 support
#ifdef BOOST_HAS_INT128
//some typedefs and implement the method as follows
typedef boost::int128_type int_t;
typedef boost::uint128_type uint_t;

inline int_t mul(int_t v1, int_t v2, int_t v3) {
    return v1 * v2 * v3;
}

#else // BOOST_NO_LONG_LONG

//For compilers that do not support the int128 type and have no long long, we may produce compile time error
#ifdef BOOST_NO_LONG_LONG
#error "This code requires at least int64_t support"
#endif

//we need to provide some implementation for compilers without int128 support using int64
struct int_t { boost::long_long_type hi, lo; };
struct uint_t { boost::ulong_long_type hi, lo; };

inline int_t mul(int_t v1, int_t v2, int_t v3) {
    // Some hand written math
    // ...
    return int_t();
}

#endif // BOOST_NO_LONG_LONG

} // namespace project

int main() {
    using namespace project;

    mul(int_t(), int_t(), int_t());
    return 0;
}

