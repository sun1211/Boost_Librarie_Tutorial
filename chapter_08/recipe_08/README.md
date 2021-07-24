# Manipulating heterogeneous containers in C++14

The **Boost.Hana** puts the metaprogramming the other way around! In the previous recipes, we were working with types directly, but Boost.Hana makes a variable that holds a type and works with variable most of the time.

```
auto type = boost::hana::typeid_(v);
```

It actually returns a variable. Information about the type is now hidden inside the type variable and could be extracted by calling decltype(type)::type.

we store the generic lambda into the is_arithmetic_ variable. From this point, we can use that variable as a functional object. Inside the lambda, we create a type variable that now holds information about the type of the v. The next line is a special wrapper around std::is_arithmetic that extracts information about the v type from the type variable and passes it to the std::is_arithmetic trait. Result of that call is a Boolean integral constant.

And now, the magic part! Lambda stored inside the is_arithmetic_ variable is actually never called by boost::hana::remove_if and boost::hana::filter functions. All the Boost.Hana's functions that use it only need the result type of the lambda function, but not its body. We can safely change the definition and the whole example will continue to work well:
```
constexpr auto is_arithmetic_ = [] (const auto& v) {
    assert(false);
    auto type = boost::hana::typeid_(v);
    return boost::hana::traits::is_arithmetic(type);
};
```
we call boost::hana::remove_if and boost::hana::filter functions, respectively. We used is_arithmetic_ inside the lambda. In neext step, we used it directly. You can use any syntax you'd like, it's just a matter of habit.

Finally in main(), we check that everything works as expected and that the element in tuple by index 0 is equal to 8:
```
 using boost::hana::literals::operator ""_c;
    assert(res_a[0_c] == 8);
```

There's a small detail left undescribed. How does the tuple access by operator[] work? It is impossible to have a single function that returns different types!

This is very interesting if you meet this trick at first time. Boost.Hana's operator ""_c works with literals and constructs different types depending on the literal:

- If you write 0_c, then integral_constant<long long, 0> is returned
- If you write 1_c, then integral_constant<long long, 1> is returned
- If you write 2_c, then integral_constant<long long, 2> is returned

The boost::hana::tuple class actually has many operator[] overloads, accepting different types of integral_constant. Depending on the value of integral constant the correct tuple element is returned. For example, if you write some_tuple[1_c] then tuple::operator[](integral_constant<long long, 1>) is called the the element by index 1 is returned.

Boost.Hana is not a part of C++17. However, the author of the library participates in the C++ Standardization meetings and proposes different interesting things for inclusion into the C++ Standard.

If you are expecting order of magnitude better compile times from Boost.Hana than from Boost.MPL then don't. Currently compilers do not handle the Boost.Hana approach extremely well. This may change some day.


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