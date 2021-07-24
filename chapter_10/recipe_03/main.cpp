//include the following header
#include <boost/config.hpp>

//Let's first look at the situation where RTTI is enabled and the C++11 std::type_index class is available
#if !defined(BOOST_NO_RTTI) \
    && !defined(BOOST_NO_CXX11_HDR_TYPEINDEX)

#include <typeindex>
using std::type_index;

template <class T>
type_index type_id() {
    return typeid(T);
}

#else

#include <cstring>
#include <iosfwd> // std::basic_ostream
// we need to construct our own type_index class
struct type_index {
    const char * name_;

    explicit type_index(const char* name)
        : name_(name)
    {}

    const char* name() const { return name_; }
};

inline bool operator == (const type_index& v1, const type_index& v2) {
    return !std::strcmp(v1.name_, v2.name_);
}

inline bool operator != (const type_index& v1, const type_index& v2) {
    // '!!' to supress warnings
    return !!std::strcmp(v1.name_, v2.name_);
}

template <class Char, class Trait>
inline std::basic_ostream<Char, Trait>& operator << (std::basic_ostream<Char, Trait>& os, const type_index& t) {
    return os << t.name_;
}

#include <boost/current_function.hpp>
template <class T>
inline type_index type_id() {
    return type_index(BOOST_CURRENT_FUNCTION);
}

#endif

#include <cassert>
#include <iostream>
int main() {
    assert(type_id<unsigned int>() == type_id<unsigned>());
    assert(type_id<double>() != type_id<long double>());

    std::cout << type_id<double>().name();
}

