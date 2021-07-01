void may_throw1(const char buffer);
void may_throw2(const char* buffer);

void foo() {
    // we can not allocate 10MB of memory on stack,
    // so we allocate it on heap
    char* buffer = new char[1024 * 1024 * 10];

    // Here comes some code, that may throw
    may_throw1(buffer[0]);
    may_throw2(buffer);

    delete[] buffer;
}

//The Boost.SmartPointer library has not only the scoped_ptr<> class, but also a scoped_array<> class
#include <boost/scoped_array.hpp>

void foo_fixed() {
    // so we allocate it on heap
    boost::scoped_array<char> buffer(new char[1024 * 1024 * 10]);

    // Here comes some code, that may throw,
    // but now exception won't couse a memory leak
    may_throw1(buffer[0]);
    may_throw2(buffer.get());

    // destructor of 'buffer' variable will call delete[]
}

//The Boost.Move library's boost::movelib::unique_ptr<> class can work with arrays too.
//You just need to indicate that it is storing an array by providing [] at the end of the template parameter
#include <boost/move/make_unique.hpp>
void foo_fixed2() {
    // We allocate array on heap
    const boost::movelib::unique_ptr<char[]> buffer
        = boost::movelib::make_unique<char[]>(1024 * 1024 * 10);

    // Here comes some code, that may throw,
    // but now exception won't cause a memory leak
    may_throw1(buffer[0]);
    may_throw2(buffer.get());

    // destructor of 'buffer' variable will call delete[]
}


#include <stdexcept>
#include <assert.h>

int main() {
    // foo(); // Leaks memory
    // terminate called after throwing an instance of 'std::exception'
    // what():  std::exception
    // Aborted (core dumped)
    try {
        foo_fixed();
        foo_fixed2();
    } catch (...){}

    return 0;
}

void may_throw1(const char /*buffer*/) {
    // Do nothing
}

void may_throw2(const char* /*buffer*/) {
    throw std::exception();
}