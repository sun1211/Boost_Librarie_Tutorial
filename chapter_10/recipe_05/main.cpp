#include <boost/config.hpp>

class move_nothrow {
    // Some class class members go here
    // ...
public:
    move_nothrow() BOOST_NOEXCEPT {}
    move_nothrow(move_nothrow&&) BOOST_NOEXCEPT
        // : members initialization
        // ...
    {}

    //If we remove BOOST_NOEXCEPT from the move constructor,
    // we'll get the following error because we provided no definition for the copy constructor
    move_nothrow& operator=(move_nothrow&&) BOOST_NOEXCEPT {
        // Implementation
        // ...
        return *this;
    }

    move_nothrow(const move_nothrow&);
    move_nothrow& operator=(const move_nothrow&);
};


#include <vector>
int main() {

    std::vector<move_nothrow> v(10);
    v.push_back(move_nothrow());

}

// In header file
int foo() BOOST_NOEXCEPT;


// In source file
int foo() BOOST_NOEXCEPT {
    return 0;
}
