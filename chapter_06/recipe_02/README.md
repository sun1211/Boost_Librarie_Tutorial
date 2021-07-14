# Making timers and processing timer events as tasks

In short, when a specified amount of time is passed, *boost::asio::deadline_timer* pushes the task to the instance of *boost::asio::io_service* class for execution.

```
    template <class Time, class Functor>
    static void run_delayed(Time duration_or_time, const Functor& f) {
        std::unique_ptr<boost::asio::deadline_timer> 
        timer( /* ... */ );

        boost::asio::deadline_timer& timer_ref = *timer;

        timer_ref.async_wait(
            detail::timer_task<Functor>(
                std::move(timer),
                f
            )
        );
    }
```

The *tasks_processor::run_delayed* function accepts a timeout and a functor to call after the timeout. In it, a unique pointer to *boost::asio::deadline_timer* is created. *boost::asio::deadline_timer* holds platform-specific stuff for asynchronous execution of a task.

*Boost.Asio* does not manage memory out of the box. The library user has to take care of managing resources usually by keeping them in the task. So if we need a timer and want some function to execute after the specified timeout, we have to move the timer's unique pointer into the task, get a reference to the timer, and pass a task to the timer.

We are getting a reference to the deadline_timer in this line:
```
boost::asio::deadline_timer& timer_ref = *timer;
```

we create a detail::timer_task object that stores a functor and gets the ownership of the unique_ptr<boost::asio::deadline_timer> :
```
  detail::timer_task<Functor>(
                std::move(timer),
                f
            )
```
boost::asio::deadline_timer must not be destroyed until it is triggered, and moving it into the timer_task functor guarantees that.

we instruct the boost::asio::deadline_timer to post the timer_task functor to the io_service when the requested amount of time elapses:

```
timer_ref.async_wait( /* timer_task */ )
```

boost::asio::deadline_timer::async_wait does not consume CPU resources or thread of execution while waiting for the timeout. You may simply push some further into the io_service and they will start executing while the timeout is being maintained by OS:



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
