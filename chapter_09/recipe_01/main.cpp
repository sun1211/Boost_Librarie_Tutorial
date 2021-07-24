#include <vector>
#define MAX_OPERATION   (8)

class operation;

template <class T>
void execute_operations(const T&);

bool has_operation();
operation get_operation();

void process_transaction_1() {
    std::vector<operation> ops;
    ops.reserve(MAX_OPERATION); // TODO: Memory allocation. Not good!

    while (has_operation()) {
        ops.push_back(get_operation());
    }

    execute_operations(ops);
    // ...
}

#include <boost/container/small_vector.hpp>
void process_transaction_2() {
    boost::container::small_vector<operation, MAX_OPERATION> ops;

    while (has_operation()) {
        ops.push_back(get_operation());
    }

    execute_operations(ops);
    // ...
}

int main(){
    return 0;
}