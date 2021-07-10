# Creating a thread of execution

The **boost::thread** variable accepts a functional object that can be called without parameters (we provided one using *boost::bind*) and creates a separate thread of execution. That functional object is copied into a constructed thread of execution and run there. The return value of the functional object is ignored.

After that, we call the *detach()* function, which does the following:

- The thread of execution is detached from the *boost::thread* variable but continues its execution
- The *boost::thread* variable starts to hold a Not-A-Thread state



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
