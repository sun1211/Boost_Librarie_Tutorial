# Interrupting a thread

**Boost.Thread** provides some predefined interruption points in which the thread is checked for being interrupted via the *interrupt()* call. If the thread is interrupted, the exception *boost::thread_interrupted* is thrown. While the exception is propagated through the *do_parse()* internals, it calls destructors for all the resources, just like a typical exception does. *boost::thread_interrupted* exceptions are treated specially by the *Boost.Thread* library, and for that exception, it is allowed to leave the thread function (*do_parse()* in our example). When the exception leaves the thread function, it is caught by the *boost::thread* internals and treated as a request to cancel the thread.

If interruptions are not required for a project, defining *BOOST_THREAD_DONT_PROVIDE_INTERRUPTIONS* gives a small performance boost and totally disables thread interruptions.

C++11 has no thread interruptions, but you can partially emulate them using atomic operations:

- Create an atomic bool variable
- Check the atomic variable in the thread and throw an exception if it has changed
Do not forget to catch that exception in the function passed to the thread (otherwise your application will terminate)

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
