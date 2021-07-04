#include <set>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <cassert>

//storing polymorphic data in containers,
//forcing fast copy of data in containers,
//and strict exception requirements for operations with data in containers
template <class T>
struct ptr_cmp: public std::binary_function<T, T, bool> {
    template <class T1>
    bool operator()(const T1& v1, const T1& v2) const {
        return operator ()(*v1, *v2);
    }

    bool operator()(const T& v1, const T& v2) const {
        return std::less<T>()(v1, v2);
    }
};

template <class T>
struct ptr_deleter: public std::unary_function<T, void> {
    void operator()(T* ptr) {
        delete ptr;
    }
};

void example1() {

    std::set<int*, ptr_cmp<int> > s;
    s.insert(new int(1));
    s.insert(new int(0));

    // ...
    assert(**s.begin() == 0);

    // ...
    // Deallocating resources
    // Any exception in this code will lead to
    // memory leak
    std::for_each(s.begin(), s.end(), ptr_deleter<int>());
}

//void example2_a() {
//    typedef std::auto_ptr<int> int_aptr_t;
//    std::set<int_aptr_t, ptr_cmp<int> > s;
//    s.insert(int_aptr_t(new int(1)));
//    s.insert(int_aptr_t(new int(0)));
//    // ...
//    assert(**s.begin() == 0);
//    // ...
//    // resources will be deallocated by auto_ptr<>
//}

//This solution is a good one, but it cannot be used in C++03, and you still need to write a comparator functional object.
void example2_b() {
    typedef std::unique_ptr<int> int_uptr_t;
    std::set<int_uptr_t, ptr_cmp<int> > s;
    s.insert(int_uptr_t(new int(1)));
    s.insert(int_uptr_t(new int(0)));
    // ...
    assert(**s.begin() == 0);
    // ...
    // resources will be deallocated by unique_ptr<>
}

//This solution is portable, but it adds performance penalties
//(atomic counter requires additional memory,
//and its increments/decrements are not as fast as non-atomic operations) and you still need to write comparators.
#include <boost/shared_ptr.hpp>
void example3() {
    typedef boost::shared_ptr<int> int_sptr_t;
    std::set<int_sptr_t, ptr_cmp<int> > s;
    s.insert(int_sptr_t(new int(1)));
    s.insert(int_sptr_t(new int(0)));
    // ...
    assert(**s.begin() == 0);
    // ...
    // resources will be deallocated by shared_ptr<>
}

#include <boost/ptr_container/ptr_set.hpp>
void correct_impl() {
    boost::ptr_set<int> s;
    s.insert(new int(1));
    s.insert(new int(0));
    // ...
    assert(*s.begin() == 0);
    // ...
    // resources will be deallocated by container itself
}

//When we want to clone some data,
//we need to define a freestanding function T*new_clone(const T& r) in the namespace of the object to be cloned.
//Moreover, you may use the default T* new_clone(const T& r) implementation 
//if you include the header file <boost/ptr_container/clone_allocator.hpp>, as shown in the following code
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
void theres_more_example() {
    // Creating vector of 10 elements with values 100
    boost::ptr_vector<int> v;
    int value = 100;
    v.resize(10, &value); // Beware! No ownership of pointer!
    assert(v.size() == 10);
    assert(v.back() == 100);
}

//C++ standard library has no pointer containers,
//but you can achieve the same functionality using a container of* std::unique_ptr*.
//By the way, since Boost 1.58, there is a *boost::movelib::unique_ptr *class
//that is usable in C++03.
//You can mix it with containers from the Boost.Container library to have C++11 functionality for storing pointers
#include <boost/container/set.hpp>
#include <boost/move/make_unique.hpp>
#include <cassert>

void example2_cpp03() { 
    typedef boost::movelib::unique_ptr<int> int_uptr_t; 
    boost::container::set<int_uptr_t, ptr_cmp<int> > s; 
    s.insert(boost::movelib::make_unique<int>(1)); 
    s.insert(boost::movelib::make_unique<int>(0)); 
    // ... 
    assert(**s.begin() == 0); 
}

int main() {
    example1();
//    example2_a();
    example2_b();
    example3();
    correct_impl();
    theres_more_example();
    example2_cpp03();
}
