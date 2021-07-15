# Making a nonblocking barrier

In multithreaded programming, there is an abstraction called barrier. It stops threads of execution that reach it until the requested number of threads are not blocked on it. After that, all the threads are released and they continue with their execution. Consider the following example of where it can be used.

We want to process different parts of data in different threads and then send the data:
```
#include <boost/array.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/thread/thread.hpp>

typedef boost::array<std::size_t, 10000> vector_type;
typedef boost::array<vector_type, 4> data_t;

void fill_data(vector_type& data);
void compute_send_data(data_t& data);

void runner(std::size_t thread_index, boost::barrier& barrier, data_t& data) {
    for (std::size_t i = 0; i < 1000; ++ i) {
        fill_data(data.at(thread_index));
        barrier.wait();

        if (!thread_index) {
            compute_send_data(data);
        }
        barrier.wait();
    }
}

int main() {
    // Initing barrier.
    boost::barrier barrier(data_t::static_size);

    // Initing data.
    data_t data;

    // Run on 4 threads.
    boost::thread_group tg;
    for (std::size_t i = 0; i < data_t::static_size; ++i) {
        tg.create_thread([i, &barrier, &data] () {
            runner(i, barrier, data);
        });
    }

    tg.join_all();
}
```

The *data_barrier.wait()* method blocks until all the threads fill the data. After that, all the threads are released. The thread with the index 0 computes data to be sent using compute_send_data(data), while other threads are again waiting at the barrier

Solution:
We do not block at all. Instead of blocking, we count the tasks that finished filling the data. This is done by the counter atomic variable. The last remaining task will have a counter variable equal to *data_t::static_size*. Only that task must compute and send the data.

After that, we check for the exit condition (1000 iterations are done) and post the new data by pushing tasks to the queue.


## How to build
```
mkdir build
cd build
cmake ..
cmake --build .
```

## How to run
```
./bin/main

```
