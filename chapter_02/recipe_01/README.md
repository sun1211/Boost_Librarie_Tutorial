# Managing local pointers to classes that do not leave scope
**boost::scoped_ptr<T>** and **boost::movelib::unique_ptr** are typical **RAII** classes. When an exception is thrown or a variable goes out of scope, the stack is unwound and the destructor is called. In the destructor, **scoped_ptr<T>** and **unique_ptr<T>** call delete for a pointer that they store. Because both of these classes by default call delete, it is safe to hold a derived class by a pointer to the base class if destructor of the base class is virtual

```
#include <iostream>
#include <string>

struct base {
    virtual ~base(){}
};

class derived: public base {
    std::string str_;

public:
    explicit derived(const char* str)
        : str_(str)
    {}

    ~derived() /*override*/ {
        std::cout << "str == " << str_ << '\n';
    }
};

void base_and_derived() {
    const boost::movelib::unique_ptr<base> p1(
        boost::movelib::make_unique<derived>("unique_ptr")
    );

    const boost::scoped_ptr<base> p2(
        new derived("scoped_ptr")
    );
}

```
Running the base_and_derived() function will produce the following output:
```
str == scoped_ptr
str == unique_ptr
```

Those classes are extremely fast. Compiler optimizes the code that uses scoped_ptr and unique_ptr to the machine code, which involve no additional overhead compared to the handwritten manual memory management code.
C++11 has a *std::unique_ptr<T, D>* class that uniquely owns the resource and behaves exactly like *boost::movelib::unique_ptr<T, D>*.
The C++ standard library has no *boost::scoped_ptr<T>*, but you could use *const std::unique_ptr<T>* instead. The only difference is that *boost::scoped_ptr<T>* still can call *reset()* unlike const *std::unique_ptr<T>*.

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
