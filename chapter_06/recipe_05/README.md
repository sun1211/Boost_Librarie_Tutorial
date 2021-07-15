# Pipeline tasks processing

The trick is to split the processing of a single data packet into some equally small subtasks and process them one by one in different work_queues. In this example, we can split the data process into data decoding, data compressing, and data sending.

However, our world is not ideal, so some tasks may finish faster than others. For example, receiving may work faster than decoding and, in that case, the decoding queue will be holding a set of tasks to be done. To avoid queue overflows, try hard to make each subsequent task slightly faster than the previous one.

We did not use *boost::asio::io_service* in our example, because it does not guarantee that posted tasks are executed in order of their postage.

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
