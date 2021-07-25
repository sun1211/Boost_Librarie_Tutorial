# TCoroutines - saving the state and postponing the execution

At step 2, we are describing the input parameter of our subprogram using the std::size_t as a template parameter.

Step 3 is pretty simple, except for the corout_t::pull_type& yield parameters. We'll see it in action in a few seconds.

When we call coroutine(10) in step 5, we are making a coroutine program to execute. Execution jumps to coroutine_task::operator(), where a call to yield.get() returns the input parameter 10. The execution continues and the coroutine_task::tick function measures elapsed ticks.

Here comes the most interesting part!

In step 7, if in function coroutine_task::tick the ticks_to_work variable becomes equal to 0, the execution of the coroutine suspends at yield() and main() continues execution. On the next call to coroutine(some_value), the execution of the coroutine continues from the middle of the tick function, right at the line next to yield(). In that line, ticks_to_work = yield.get(); is executed and the ticks_to_work variable starts to hold a new input value some_value.

It means that we can suspend/continue the coroutine in multiple places of the function. All the function state and variables are restored

Let me describe the main difference between coroutines and threads. When a coroutine is executed, the main task does nothing. When the main task is executed, the coroutine task does nothing. You have no such guarantee with threads. With coroutines, you explicitly specify when to start a subtask and when to suspend it. In a single core environment, threads may switch at any moment; you cannot control that behavior.

While switching threads, the OS does a lot of work, so it is not a very fast operation. However, with coroutines, you have full control over switching tasks; moreover, you do not need to do some OS-specific internal kernel work. Switching coroutines is much faster than switching threads, although, not as fast as calling boost::function.

The Boost.Coroutine2 library takes care about calling a destructor for variables in a coroutine task, so there's no need to worry about leaks.

Coroutines use the boost::coroutines2::detail::forced_unwind exception to free resources that are not derived from std::exception. You must take care to not catch that exception in coroutine tasks.
You cannot copy Boost.Coroutine2 coroutines, but you can std::move them.

There is a Boost.Coroutine library (without 2 at the end!), that does not require a C++11 compatible compiler. But that library is deprecated and has some differences (for example it does not propagate exceptions from coroutines). Beware of the differences! Boost.Coroutine also changed its interface significantly in Boost 1.56.

C++17 has no coroutines. But Coroutines TS is almost ready, so the chances are high that next C++ standard will have them out of the box.

Coroutines TS differs from Boost.Coroutine2! Boost provides stackful coroutines, which means that you do not need to specially decorate your code with macro/keywords to use them. But it also means that Boost coroutines are harder to optimize by the compiler and that they may allocate more memory. Coroutines TS provides stackless coroutines, which means that compiler could precisely compute the required memory for a coroutine and even optimize out the whole coroutine. However, this approach requires code changes and may be slightly harder to adopt.

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