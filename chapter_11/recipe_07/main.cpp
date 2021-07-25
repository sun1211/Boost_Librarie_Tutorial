#include <iostream>

//Pointers and references are everywhere in C++, and they do not work in shared memory
//if we have a structure like this in shared memory and
// assign the address of some integer variable in shared memory to pointer_, the pointer_ would be invalid in other process
struct with_pointer {
    int* pointer_;
    // ...
    int value_holder_;
};

//Fixing it is very simple; we need only to replace the pointer with offset_ptr<>
#include <boost/interprocess/offset_ptr.hpp>

struct correct_struct {
    boost::interprocess::offset_ptr<int> pointer_;
    // ...
    int value_holder_;
};


#include <boost/interprocess/managed_shared_memory.hpp>

template <class T>
void test() {
    typedef T correct_struct;
    static const int ethalon_value = 777;

    boost::interprocess::managed_shared_memory 
        segment(boost::interprocess::open_or_create, "segment", 4096);

    correct_struct* ptr =
        segment.find<correct_struct>("structure").first;

    if (ptr) {
        std::cout << "Structure found\n";
        assert(*ptr->pointer_ == ethalon_value);
        segment.destroy<correct_struct>("structure");
    } else {
        std::cout << "Creating structure\n";
        correct_struct& ref = *segment.construct<correct_struct>("structure")();
        ref.pointer_ = &ref.value_holder_;
        assert(ref.pointer_ == &ref.value_holder_);
        assert(*ref.pointer_ == ref.value_holder_);
        ref.value_holder_ = ethalon_value;
        assert(*ref.pointer_ == ethalon_value);
    }
}


#include <cassert>

int main() {
    test<correct_struct>(); // Shall be OK
    //test<with_pointer>(); // Shall fail
}
