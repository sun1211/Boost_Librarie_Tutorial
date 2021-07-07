# Enabling function template usage for integral types with Boost.Core and Boost.TypeTraits

The **boost::enable_if_c** template is a tricky one. It makes use of the Substitution Failure Is Not An Error (**SFINAE**) principle, which is used during template instantiation. This is how the principle works; if an invalid argument or return type is formed during the instantiation of a function or class template, the instantiation is removed from the overload resolution set and does not cause a compilation error. Now the tricky part, *boost::enable_if_c<true>* has a member type accessible *via ::type*, but *boost::enable_if_c<false>* has no *::type*. Let's get back to our solution and see how the **SFINAE** works with different types passed to the data_processor class as the T parameter.

If we pass an int as the T type, first the compiler will try to instantiate template partial specializations from step 3, before using our nonspecialized generic version. When it tries to instantiate a float version, the *boost::is_float<T>::value* metafunction returns false. The *boost::enable_if_c<false>::type* metafunction cannot be correctly instantiated because *boost::enable_if_c<false>* has no *::type*, and that is the place where SFINAE acts. Because the class template cannot be instantiated, this must be interpreted as not an error, compiler skips this template specialization. The next partial specialization is the one that is optimized for integral types. The *boost::is_integral<T>::value* metafunction returns true, and *boost::enable_if_c<true>::type* can be instantiated, which makes it possible to instantiate the whole data_processor specialization. The compiler found a matching partial specialization, so it does not need to try to instantiate the nonspecialized method.

Now, let's try to pass some nonarithmetic type (for example, *const char **), and let's see what the compiler will do. First, the compiler tries to instantiate template partial specializations. The specializations with *is_float<T>::value* and *is_integral<T>::value* fail to instantiate, so the compiler tries to instantiate our generic version and succeeds.

Without *boost::enable_if_c<>*, all the partially specialized versions may be instantiated at the same time for any type, which leads to ambiguity and failed compilation.


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
