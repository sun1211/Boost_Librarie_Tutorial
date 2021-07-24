//include only a single header file
#include <boost/container/flat_set.hpp>
//for assert function
#include <cassert>

void test_flat() {
    //we are free to construct the flat container and experiment with it
    boost::container::flat_set<int> set;
    //Reserving space for elements
    //Without reserving memory, insertion of elements may become at times slower and less memory efficient
    set.reserve(4096);

    //Filling the container
    for (int i = 0; i < 4000; ++i) {
        set.insert(i);
    }

    // 5.1
    //getting the distance between two iterators returned by calls to the lower_bound member functions
    //etting distance with flat set takes constant time O(1), while the same operation on iterators of std::set takes linear time O(N).
    // In case of 5.1, getting the distance using std::set would be 400 times slower than getting the distance for flat set containers.
    assert(set.lower_bound(500) - set.lower_bound(100) == 400);

    //5.2 and 5.3 do not differ much, except in their execution speed. Rules for erasing elements are pretty much the same as for inserting them.
    //See the preceding paragraph for explanations.
    // 5.2
    set.erase(0);

    // 5.3
    set.erase(5000);

    // 5.4
    //5.4 shows you that the std::lower_bound function works faster with boost::container::flat_set than with std::set, because of random access iterators.
    assert(std::lower_bound(set.cbegin(), set.cend(), 900000) == set.cend());

    // 5.5
    //5.5 also shows you the benefit of random access iterators
    assert(
        set.lower_bound(100) + 400 
        == 
        set.find(500)
    );
}

int main() {
    test_flat();
}

