#define MY_LIBRARY_COMPILATION
#include "my_library.hpp"
#include <cassert>

int MY_LIBRARY_API foo() {
    // Implementation
    // ...
    return 0;
}

int bar::meow() const {
    throw bar_exception();
}

int main() {
    assert(foo() == 0);
    bar b;
    try {
        b.meow();
        assert(false);
    } catch (const bar_exception&) {}
}
