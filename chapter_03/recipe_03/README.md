# Converting numbers to numbers with Boost.LexicalCast

**boost::numeric_cast **checks if the value of the input parameter fits into the new type without losing data and throws an exception if something is lost during conversion.

The *Boost.NumericConversion* library has a very fast implementation. It can do a lot of work at compile time, for example, when converting to types of a wider range, the source will be converted to target type by just via static_cast.

The **boost::numeric_cast** function is implemented via *boost::numeric::converter*, which can be tuned to use different overflow, range checking, and rounding policies. But usually, numeric_cast is just what you need.

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

#47 bad numeric conversion: negative overflow
#58 bad numeric conversion: positive overflow



NEG OVERFLOW in #47 bad numeric conversion: negative overflow
POS OVERFLOW in #59 bad numeric conversion: positive overflow



It works! val = 0 Error msg: Not in range!

```
