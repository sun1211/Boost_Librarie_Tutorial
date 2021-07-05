# Casting polymorphic objects with boost::polymorphic_cast

The **boost::polymorphic_cast** function just wraps around code from the first example, and checks input for null and then tries to do a dynamic cast. Any error during those operations will throw a *std::bad_cast exception.*

The *Boost.Conversion* library also has a polymorphic_downcast function, which should be used only for downcasts that certainly shall succeed. In debug mode (when NDEBUG is not defined), it will check for the correct downcast using dynamic_cast. When NDEBUG is defined, the polymorphic_downcast function will just do a static_cast operation. It is a good function to use in performance-critical sections, still leaving the ability to detect errors in debug compilations.

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
