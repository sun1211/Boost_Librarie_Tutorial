# Getting and processing system signals as tasks

Nothing is difficult here (compared to some previous recipes from this chapter). The *register_signals_handler* function adds the signal numbers that will be processed. It is done via a call to the *boost::asio::signal_set::add function* for each element of the *signals_to_wait*.

Next, the sigs.async_wait starts the async waiting for a signal and calls the *tasks_processor::handle_signals* function on the signal capture. The *tasks_processor::handle_signals* function immediately starts async wait for the next signal, checks for errors and, if there are none, it calls a callback providing a signal number.

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

^CCaptured 1 SIGINT
^CCaptured 2 SIGINT
^CCaptured 3 SIGINT

```
