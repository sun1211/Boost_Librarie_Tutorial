# Reference counting of pointers to classes used across functions

The **shared_ptr** class has an atomic reference counter inside. When you copy it, the reference counter is incremented, and when its destructor is called, the reference counter is decremented. When the count of references equals to zero, delete is called for the object pointed by shred_ptr.

Now, let's find out what's happening in the case of *boost::thread (boost::bind(&process_sp1, p))*. The function *process_sp1* takes a parameter as a reference, so why is it not deallocated when we do get out of the while loop? The answer is simple. The functional object returned by *bind()* contains a copy of the shared pointer, and that means the data pointed by *p* won't be deallocated until the functional object is destroyed. The functional object is copied into the thread and is kept alive until the threads executes.

Getting back to *boost::make_shared*, let's take a look at *shared_ptr<std::string> ps(new int(0))*. In this case, we have two calls to *new*:

 - While constructing a pointer to an integer via new int(0)
 - While constructing a shared_ptr class internal reference counter that is allocated on the heap
Use *make_shared<T>* to have only one call to new. A *make_shared<T>* allocates a single chunk of memory and constructs an atomic counter and the *T* object in that chunk.

The atomic reference counter guarantees correct behavior of shared_ptr across the threads, but you must remember that atomic operations are not as fast as non-atomic. *shared_ptr* touches the atomic variable on assignments, copy constructions, and on destruction of a non moved away *shared_ptr*. It means that on C++11 compatible compilers, you may reduce atomic operation's count using move constructions and move assignments where possible. Just use *shared_ptr<T> p1(std::move(p)*) if you are not going to use the *p* variable any more. If you are not going to modify the pointed value, it is recommended to make it *const*. Just add *const* to the template parameter of the smart pointer, and the compiler will make sure that you do not modify memory.

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
