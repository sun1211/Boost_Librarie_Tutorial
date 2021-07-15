# Storing an exception and making a task from it

The **Boost.Exception** library provides an ability to store and re-throw exceptions. The boost::current_exception() method must be called only from inside of the catch() block, and it returns an object of the type *boost::exception_ptr*.

In the preceding example in *func_test1()*, the *boost::bad_lexical_cast exception* is thrown. It is returned by *boost::current_exception();* a process_exception task is created from that exception.

The only way to restore the exception type from *boost::exception_ptr* is to re-throw it using *boost::rethrow_exception(exc)* function. That's what the process_exception function does.

*Throwing and catching exceptions is a heavy operation. Throwing may dynamically allocate memory, touch cold memory, lock mutex, compute a bunch of addresses, and do other stuff. Do not throw exception in performance critical paths without very good reasons to do so!*

In *func_test2*, we are throwing a *std::logic_error* exception using the *BOOST_THROW_EXCEPTION* macro. This macro does a lot of useful work; it checks that our exception is derived from *std::exception*, adds information to our exception about the source filename, function name, and the code line number from where the exception was thrown. When our *std::logic_error* exception is re-thrown inside the *process_exception::operator()* it is caught by catch(...). The *boost::current_exception_diagnostic_information()* outputs as much information about the thrown exception as possible.

The *boost::exception_ptr* class may allocate memory through heap multiple times, uses atomics, and implements some of the operations by re-throwing and catching exceptions. Try not to use it without an actual need.

C++11 has adopted *boost::current_exception*, *boost::rethrow_exception*, and *boost::exception_ptr*. You may find them in the <exception> in the *std:: namespace*. The *BOOST_THROW_EXCEPTION* and *boost::current_exception_diagnostic_information()* functions are not in C++17.

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

Lexical cast exception detected

Can not handle such exceptions:
~/boost_library_tutorial/chapter_06/recipe_06/main.cpp(48): Throw in function void func_test2()
Dynamic exception type: boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<std::logic_error> >
std::exception::what: Some fatal logic error

```
