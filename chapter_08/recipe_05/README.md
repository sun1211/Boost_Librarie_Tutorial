# Evaluating metafunctions lazily

Lazy evaluation means that the function is not called until we really need its result.

Imagine that we are writing some metafunction that accepts a function Func, a parameter Param, and a condition Cond. The resulting type of that function must be a fallback type if applying the Cond to Param returns false, otherwise the result must be a Func applied to Param:
```
struct fallback;

template <
        class Func,
        class Param,
        class Cond,
        class Fallback = fallback>
struct apply_if; 
```

The main idea of this recipe is that we must not execute the metafunction if the condition is false, because when the condition is false, there is a chance that the metafunction for that type can't be applied:
```
// Will fail with static assertion somewhere deeply in the implementation
// of boost::make_unsigned<_1> if we do not evaluate the function lazily.
typedef apply_if<
    boost::make_unsigned<_1>,
    float,
    boost::is_integral<_1>
>::type res2_t;

BOOST_STATIC_ASSERT((
    boost::is_same<res2_t, fallback>::value
));
```
The compiler does look inside the metafunction if there is no access to the metafunction's internal types or values. In other words, the compiler tries to compile the metafunction when we try to get one of its members via *::*. This can be a call to *::type* or *::value*. That is how an incorrect version of apply_if looks like:
```
template <class Func, class Param, class Cond, class Fallback>
struct apply_if {
    typedef typename boost::mpl::apply<
        Cond, Param
    >::type condition_t;

    // Incorrect: metafunction is evaluated when `::type` called.
    typedef typename boost::mpl::apply<Func, Param>::type applied_type;

    typedef typename boost::mpl::if_c<
        condition_t::value,
        applied_type,
        boost::mpl::identity<Fallback>
    >::type type;
};
```

This differs from our example, where we did not call *::type* and implemented using *eval_if_c*, which calls *::type* only for one of its parameters. The *boost::mpl::eval_if_c* metafunction is implemented like this:
```
template<bool C, typename F1, typename F2>
struct eval_if_c {
    typedef typename if_c<C,F1,F2>::type f_;
    typedef typename f_::type type; // call `::type` only for one parameter
};
```

Because *boost::mpl::eval_if_c* calls *::type* for a succeeded condition and fallback has no *::type*, we were required to wrap fallback into the boost::mpl::identity class. This class is very simple, but useful structure that returns its template parameter via a *::type* call and does nothing more:
```
template <class T> 
struct identity { 
    typedef T type; 
};
```

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