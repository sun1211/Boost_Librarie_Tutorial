# Creating work_queue class

In this example, we see a new *RAII* class *boost::unique_lock*. It is just a *boost::lock_guard* class with additional functionality for explicit unlocking and locking mutexes.

Back to our work_queue class. Let's start with the *pop_task()* function. In the beginning, we are acquiring a lock and checking for available tasks. If there is a task, we return it; otherwise, *cond_.wait(lock)* is called. This method atomically unlocks the lock and pauses the thread of execution till some other thread notifies the current thread.

Now, let's take a look at the push_task method. In it, we also acquire a lock, push a task in tasks_.queue, unlock the lock, and call *cond_.notify_one()*, which wakes up the thread (if any) waiting in *cond_.wait(lock)*. So, after that, if some thread is waiting on a conditional variable in a *pop_task()* method, the thread will continue its execution, call *lock.lock()* deep inside *cond_.wait(lock)*, and check *tasks_empty()* in while. Because we just added a task in tasks_, we'll get out from the while loop, unlock the <mutex> (the lock variable gets out of scope), and return a task.

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

shared_i == 0

```
