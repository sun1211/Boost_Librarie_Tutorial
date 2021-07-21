#include <boost/mpl/aux_/na.hpp>
template <
    class T0 = boost::mpl::na, // boost::mpl::na == n.a. == not available
    class T1 = boost::mpl::na,
    class T2 = boost::mpl::na,
    class T3 = boost::mpl::na,
    class T4 = boost::mpl::na,
    class T5 = boost::mpl::na,
    class T6 = boost::mpl::na,
    class T7 = boost::mpl::na,
    class T8 = boost::mpl::na,
    class T9 = boost::mpl::na
>
struct variant;


#include <boost/mpl/vector.hpp>
//let's pack all the types in one of the Boost.MPL type's container
template <
    class T0, class T1, class T2, class T3, class T4,
    class T5, class T6, class T7, class T8, class T9
>
struct variant {
    typedef boost::mpl::vector<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> types;
};

//Let's make our example less abstract and see how it works if we specify types
#include <string>
struct declared{ unsigned char data[4096]; };
struct non_declared;

typedef variant<
    volatile int, 
    const int, 
    const long, 
    declared, 
    non_declared, 
    std::string
>::types types;

//We may check everything at compile time. Let's assert that types is not empty
#include <boost/static_assert.hpp>
#include <boost/mpl/empty.hpp>
BOOST_STATIC_ASSERT((!boost::mpl::empty<types>::value));

// the non_declared types is still at index 4 position
#include <boost/mpl/at.hpp>
#include <boost/type_traits/is_same.hpp>
BOOST_STATIC_ASSERT((boost::is_same<
    non_declared, 
    boost::mpl::at_c<types, 4>::type
>::value));

//the last type is still std::string
#include <boost/mpl/back.hpp>
BOOST_STATIC_ASSERT((boost::is_same<
    boost::mpl::back<types>::type,
    std::string
>::value));

//We may carry out some transformations. Let's start with removing constant and volatile qualifiers
#include <boost/mpl/transform.hpp>
#include <boost/type_traits/remove_cv.hpp>
typedef boost::mpl::transform<
    types, 
    boost::remove_cv<boost::mpl::_1> 
>::type noncv_types;

//we can remove the duplicate types
#include <boost/mpl/unique.hpp>
typedef boost::mpl::unique<
    noncv_types, 
    boost::is_same<boost::mpl::_1, boost::mpl::_2>
>::type unique_types;

//check that the vector contains only 5 types
#include <boost/mpl/size.hpp>
BOOST_STATIC_ASSERT((boost::mpl::size<unique_types>::value == 5));

// Without this we'll get an error:
// use of undefined type 'non_declared'
struct non_declared{};

//compute sizes of each element
#include <boost/mpl/sizeof.hpp>
typedef boost::mpl::transform<
    unique_types, 
    boost::mpl::sizeof_<boost::mpl::_1>
>::type sizes_types;

//get the maximum size from the sizes_type type
#include <boost/mpl/max_element.hpp>
typedef boost::mpl::max_element<sizes_types>::type max_size_type;

BOOST_STATIC_ASSERT(max_size_type::type::value == sizeof(declared));


#include <algorithm>
#include <functional>
#include <vector>
#include <boost/bind.hpp>

void foo2() {
    typedef int type;
    std::vector<type> types;
    // ...
    std::unique(types.begin(), types.end(), boost::bind(std::equal_to<type>(), _1, _2));
}

#include <iostream>
#include <typeinfo>

#include <boost/mpl/size.hpp>
#include <cassert>

template <class Vector>
int foo_size() {
    return boost::mpl::size<Vector>::value;
}

int main() {
    typedef boost::mpl::vector<int,int,int> vector1_type;
    assert(foo_size<vector1_type>() == 3);
 
    foo2();
    std::cout << typeid(sizes_types).name();
    /*
        struct boost::mpl::vector<
            struct boost::mpl::size_t<4>,
            struct boost::mpl::size_t<4>,
            struct boost::mpl::size_t<4096>,
            struct boost::mpl::size_t<1>,
            struct boost::mpl::size_t<32> 
        >
    */
}

