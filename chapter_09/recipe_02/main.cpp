#include <boost/container/static_vector.hpp>
#include <cassert>
#include <iostream>

struct event{};


boost::container::static_vector<event, 5> get_events(){};

int main () {
    boost::container::static_vector<event, 5> ev = get_events();
    assert(ev.size() == 5);

    boost::container::static_vector<int, 2> ints;
    ints.push_back(1);
    ints.push_back(2);
    try {
        // The following line always throws:
        ints.push_back(3);
    } catch (const std::bad_alloc&) {
        // ...
    }
}