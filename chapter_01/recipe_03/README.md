# Storing any value in a container/variable with any
Refer to : https://www.boost.org/doc/libs/1_37_0/doc/html/any.html

The boost::any class just stores any value in it. To achieve this, it uses the **type erasure** technique (close to what Java or C# does with all types). To use this library you do not really need to know its internal implementation in detail, but here's a quick glance at the type erasure technique for the curious.

On the assignment of some variable of type T, Boost.Any instantiates a holder<T> type that may store a value of the specified type T and is derived from some base-type placeholder:

```
template<typename ValueType>
struct holder : public placeholder {
    virtual const std::type_info& type() const {
         return typeid(ValueType);
    }
     ValueType held;
};
```
A placeholder type has virtual functions for getting std::type_info of a stored type T and for cloning a stored type:

```
struct placeholder {
    virtual ~placeholder() {}
    virtual const std::type_info& type() const = 0;
};
```
boost::any stores ptr-- a pointer to placeholder. When any_cast<T>() is used, boost::any checks that calling ptr->type() gives std::type_info equal to typeid(T) and returns static_cast<holder<T>*>(ptr)->held.

Such flexibility never comes without any cost. Copy constructing, value constructing, copy assigning, and assigning values to instances of boost::any do dynamic memory allocation; all the type casts do RunTime Type Information (RTTI) checks; boost::any uses virtual functions a lot. If you are keen on performance, the next recipe will give you an idea of how to achieve almost the same results without dynamic allocations and RTTI usage.

boost::any makes use of rvalue references but can not be used in constexpr.

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

Wow! That is great!
```
