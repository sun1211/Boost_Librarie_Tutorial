#include <assert.h>
#include <boost/noncopyable.hpp>
//we want to send the results of an executed task using some connection
// We have the following solutions:

// - Open a new connection when we need to send the data (which is very slow)
// - Have a single connection for all the threads and wrap them in mutex (which is also slow)
// - Have a pool of connections, get a connection from it in a thread-safe manner,
// and use it (a lot of coding is required, but this solution is fast)
// - Have a single connection per thread (fast and simple to implement)
class connection: boost::noncopyable {
public:
    // Opening a connection is a slow operation
    void open();

    void send_result(int result);

    // Other methods
    // ...
    int open_count_;
    connection(): open_count_(0) {}
};

// In header file
#include <boost/thread/tss.hpp>
//make a thread local variable. Declare a function in a header file after the connection class definition
connection& get_connection();

// In source file
//The boost::thread_specific_ptr variable holds a separate pointer for each thread
//Initially, this pointer is equal to nullptr
boost::thread_specific_ptr<connection> connection_ptr;

connection& get_connection() {
    //when we enter get_connection() from the thread 
    //that already initiated the pointer,
    //!p return the value false and we return the already opened connection
    connection* p = connection_ptr.get();
    //we check for !p and open a connection if it is nullptr
    if (!p) {
        connection_ptr.reset(new connection);
        p = connection_ptr.get();
        p->open();
    }
    //delete for the pointer stored inside the connection_ptr variable is called when the thread is exiting,
    //so we do not need to worry about memory leaks.
    return *p;
}


void task() {
    int result = 2;
    // Some computations go there
    // ...

    // Sending result
    get_connection().send_result(result);
}

void connection::open() {
    assert(!open_count_);
    open_count_ = 1;
}
#include <iostream>
void connection::send_result(int result) {
    std::cout << result << ".";
}

void run_tasks() {
    for (std::size_t i = 0; i < 10000000; ++i) {
        task();
    }
}

#include <boost/thread/thread.hpp>

int main() {
    boost::thread t1(&run_tasks);
    boost::thread t2(&run_tasks);
    boost::thread t3(&run_tasks);
    boost::thread t4(&run_tasks);

    // Waiting for all the tasks to pop
    t1.join();
    t2.join();
    t3.join();
    t4.join();

}
