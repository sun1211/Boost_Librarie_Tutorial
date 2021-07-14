# Network communication as a task

The *Boost.Asio* library does not manage resources and buffers out of the box. So, if we want some simple interface for reading and writing data, the simplest solution would be to tie together the socket and buffer for sending/receiving data. That's what the connection_with_data class does. It holds a *boost::asio::ip::tcp::socket*, which is a *Boost.Asio* wrapper around native sockets and a *std::string* variable that we use as a buffer.

A constructor of the *boost::asio::ip::tcp::socket* class accepts *boost::asio::io_service* as almost all the classes in *Boost.Asio*. After we create a socket, it must be connected to some remote endpoint:
```
c->socket.connect(boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address_v4::from_string(addr),
            port_num
        ));
```
Take a look at the writing function. It accepts a unique pointer to the connection_with_data class and functor f:

```
#include <boost/asio/write.hpp>

template <class Functor>
void async_write_data(connection_ptr&& c, const Functor& f) {

```

In it, we get references to socket and buffer:

boost::asio::ip::tcp::socket& s = c->socket;
std::string& d = c->data;

Then, we ask for asynchronous write:

```
 boost::asio::async_write(
        s,
        boost::asio::buffer(d),
        task_wrapped_with_connection<Functor>(std::move(c), f)
    );
}
```

All the interesting things happen in the *boost::asio::async_write* function. Just as in the case of timers, asynchronous call returns immediately without executing a function. It only tells to post the callback task to the *boost::asio::io_service* after some operation finishes (in our case, it's writing data to the socket). *boost::asio::io_service* executes our function in one of the threads that called the *io_service::run()* method. The following diagram illustrates this.

take a look at *task_wrapped_with_connection::operator()*. It accepts const *boost::system::error_code&* error and *std::size_t* bytes_count, because both *boost::asio::async_write* and *boost::asio::async_read* functions pass those parameters on async operation completion. A call to *c_->data.resize(bytes_count)*; resizes the buffer to contain only the received/written data. Finally, we call the callback that was initially passed to an async function and stored as task_unwrapped_.

we have an async_write_data function that asynchronously writes data from the buffer to the socket and executes a callback on operation completion:
```
void on_send(connection_ptr&& soc, const boost::system::
error_code& err);

void connect_and_send() {
    connection_ptr s = tasks_processor::create_connection
    ("127.0.0.1", 80);

    s->data = "data_to_send";
    async_write_data(
        std::move(s),
        &on_send
    );
}
```

async_read_data is pretty close to async_write_data. It resizes the buffer, creates a task_wrapped_with_connection function, and pushes it into is_service on async operation completion.

Note the async_read_data_at_least function. In its body, there's a slightly different call to *boost::asio::async_read*:
```
boost::asio::async_read(
    s,
    boost::asio::buffer(p, at_most),
    boost::asio::transfer_at_least(at_least_bytes),
    task_wrapped_with_connection<Functor>(std::move(c), f)
);
```

It has a boost::asio::transfer_at_least(al_least_bytes) in it. Boost.Asio has a lot of functors for customizing reads and writes. This one functor says, transfer at least at_least_bytes bytes before calling the callback. More bytes are OK until they fit in buffer.

Finally, let's take a look at one of the callbacks:
```
void process_server_response(
        connection_ptr&& soc,
        const boost::system::error_code& err);

```
In this example, callbacks must accept connection_ptr and a *boost::system::error_code* variable. A *boost::system::error_code* variable holds information about errors. It has an explicit conversion to bool operator, so the simple way to check for errors is just to write *if (err) { ... }*. If the remote ends transmission and closes the socket, err may contain *boost::asio::error::eof* error code. This is not always bad. In our example, we treat it as a non error behavior:

```
if (err && err != boost::asio::error::eof) {
        std::cerr << "Client error on receive: " 
        << err.message() << '\n';
        assert(false);
    }
```
Because we have tied together the socket and the buffer, you can get the received data from *soc->data*:
```
if (soc->data.size() != 2) {
    std::cerr << "Wrong bytes count\n";
    assert(false);
}

if (soc->data != "OK") {
    std::cerr << "Wrong response: " << soc->data << '\n';
    assert(false);
}
```
The soc->shutdown() call is optional, because when soc goes out of scope, the destructor for it is called. Destructor of *unique_ptr<connection_with_data>* calls *~connection_with_data* that has a *shutdown()* in its body.

Our *task_wrapped_with_connection::operator()* is not good enough! User provided task_unwrapped_ callback my throw exceptions and may get interrupted by a Boost.Thread interruption that does not belong to that particular task. The fix would be to wrap the callback into the class from first recipe:
```
void operator()(
    const boost::system::error_code& error,
    std::size_t bytes_count)
{
    const auto lambda = [this, &error, bytes_count]() {
        this->c_->data.resize(bytes_count);
        this->task_unwrapped_(std::move(this->c_), error);
    };

    const auto task = detail::make_task_wrapped(lambda);
    task();
}
```
In *task_wrapped_with_connection::operator()*, we create a lambda function named lambda. On execution, lambda resizes the data inside the connection_with_data class to the bytes_count and calls an initially passed callback. Finally, we wrap the lambda into our safe for execution tasks from the first recipe and then execute it.

You may see a lot of *Boost.Asio* examples on the Internet. Many of those use *shared_ptr* instead of a *unique_ptr* for keeping the data around. Approach with *shared_ptr* is simpler to implement; however, it has two big drawbacks:

Efficiency: *shared_ptr* has an atomic counter inside, and modifying it from different threads may significantly degrade performance. In one of the next recipes, you will see how to process tasks in multiple threads, and that's the place where the differences may be noticeable in cases of high load.
Explicitness: With *unique_ptr*, you always see that the ownership of the connection was transferred to somewhere (you see std::move in code). With *shared_ptr*, you can not understand from the interface whether the function grabs the ownership or if it just uses a reference to an object.
However, you may be forced to use *shared_ptr*, if according to the application's logic, the ownership has to be shared across multiple tasks at the same time.

Boost.Asio is not a part of C++17, but it will be shipped as a Networking TS soon, and included into the one of the upcoming C++ standards.


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
