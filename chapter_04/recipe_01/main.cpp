#include <cstring> 
#include <boost/array.hpp> 

// C++17 has std::byte out of the box!
// Unfortunately this is as C++03 example. 
typedef unsigned char byte_t;
 
template <class T, std::size_t BufSizeV> 
void serialize_bad(const T& value, boost::array<byte_t, BufSizeV>& buffer) {  
    // TODO: think of something better.
    assert(BufSizeV >= sizeof(value));
    std::memcpy(&buffer[0], &value, sizeof(value)); 
}

#include <boost/static_assert.hpp> 
#include <boost/type_traits/has_trivial_copy.hpp> 
 
template <class T, std::size_t BufSizeV> 
void serialize(const T& value, boost::array<byte_t, BufSizeV>& buffer) { 
    BOOST_STATIC_ASSERT(BufSizeV >= sizeof(value)); 
    BOOST_STATIC_ASSERT(boost::has_trivial_copy<T>::value); 

    std::memcpy(&buffer[0], &value, sizeof(value)); 
}

int main(){
    // BOOST_STATIC_ASSERT(3 < 1);

    // ~boost_library_tutorial/chapter_04/recipe_01/main.cpp:27:5: error: static assertion failed: 3 < 1
    //  BOOST_STATIC_ASSERT(3 < 1);
    return 0;
}


