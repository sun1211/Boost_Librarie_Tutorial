# Initializing the base class by the member of the derived class

Direct base classes are initialized before non-static data members and in declaration order as they appear in the base-specifier list. If we need to initialize base class B with something, we need to make that something a part of a base class A that is declared before B. In other words, boost::base_from_member is just a simple class that holds its template parameter as a non-static data member

```
template < typename MemberType, int UniqueID = 0 >
class base_from_member {
protected:
    MemberType  member;
    //      Constructors go there...
};
```

The *boost::base_from_member*class neither applies additional dynamic memory allocations nor has virtual functions. The current implementation does support perfect forwarding and variadic templates if your compiler supports them.
C++ standard library has no *base_from_member*.


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
