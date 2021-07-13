# Registering a task for an arbitrary data type processing

The boost::asio::io_service variable can store and execute tasks posted to it. But we may not post a user's tasks to it directly, because they may receive an interruption addressed to other tasks or throw an exception. That is why we wrap a user's task in the detail::task_wrapped structure. It resets all the previous interruptions by calling:

```
try { 
    boost::this_thread::interruption_point(); 
} catch(const boost::thread_interrupted&){}
```

*detail::task_wrapped *executes the task in the *try{ } catch()* block making sure that no exception leaves the *operator()* bounds.

Take a look at the *start()* function. The *boost::asio::io_service::run()* starts processing tasks posted to the io_service variable. If *boost::asio::io_service::run()* is not called, then posted tasks are not executed (this can be seen in the *main()* function). Task processing may be stopped via a call to *boost::asio::io_service::stop()*.

The *boost::asio::io_service* class returns from the *run()* function if there are no more tasks left, so we force it to continue with the execution using an instance of *boost::asio::io_service::work*:

```
static boost::asio::io_service& get_ios() {
    static boost::asio::io_service ios;
    static boost::asio::io_service::work work(ios);

    return ios;
}
```






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

Exception: Just checking
Thread interrupted

```
