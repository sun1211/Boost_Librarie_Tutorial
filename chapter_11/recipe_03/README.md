# Writing and using plugins

There is a small trick in step 2. When you declare a function as extern "C", it means that the compiler must not mangle (change) the function name. In other words, in step 2 we just create a function that has a name greet and is exported with that exact name from the shared library.

In step 4, we create a boost::dll::shared_library variable with name plugin. The constructor of that variable loads the shared library by a specified path into the address space of the current executable. In step 5, we search for the function with name greet in the plugin. We also specify that the function has the signature std::string(const std::string&) and store a pointer to that function in the variable greet.

That's it! From now on, we can use the greet variable as a function, as long as the plugin variable and all its copies are not destroyed.

You can export multiple functions from shared library; you can even export variables.

Be careful! Always link C and C++ libraries dynamically to the plugin and your main executable, because otherwise your application will crash. Always use the same or ABI compatible versions of C and C++ libraries in your plugins and in your application. Otherwise your application will crash. Read the docs for typical missuses!
