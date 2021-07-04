#include <boost/function.hpp>
#include <iostream>
typedef boost::function<void(int)> fobject_t;

// Now this function may accept functional objects
void process_integers(const fobject_t& f);


void my_ints_function(int i);

int main() {
   process_integers(&my_ints_function);
}

void my_ints_function(int i) {
    std::cout << i << "\n";
}
void process_integers(const fobject_t& f) { f(10); }
