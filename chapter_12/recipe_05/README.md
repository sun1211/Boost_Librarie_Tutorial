# Writing test cases

Writing unit tests is easy. You know how the function works and what result it will produce in specific situations. Therefore, you just check if the expected result is the same as the function's actual output. That's what we did in step 3. We know that f1.is_not_null() returns true and we checked it. At step 4, we do know that f1 is not equal to f2, so we checked it too. The call to f1.throws() produces the std::logic_error exception and we check that an exception of the expected type is thrown.

At step 2, we are making a test case--a set of checks to validate correct behavior of the foo structure. We may have multiple test cases in a single source file. For example, if we add the following code:
```
BOOST_AUTO_TEST_CASE(test_no_2) { 
    foo f1 = {1}, f2 = {2}; 
    BOOST_REQUIRE_NE(f1, f2); 
    // ... 
} // BOOST_AUTO_TEST_CASE(test_no_2) 
```

This code will run along with the test_no_1 test case.

The parameter passed to the BOOST_AUTO_TEST_CASE macro is just a unique name of the test case that is shown in case of error.
```
Running 2 test cases... 
main.cpp(15): error in "test_no_1": check f1.is_not_null() failed 
main.cpp(17): error in "test_no_1": check f1 != f2 failed [0 == 0] 
main.cpp(19): error in "test_no_1": exception std::logic_error is expected 
main.cpp(24): fatal error in "test_no_2": critical check f1 != f2 failed [0 == 0] 
 
*** 4 failures detected in test suite "test_module_name" 
```

There is a small difference between the BOOST_REQUIRE_* and BOOST_CHECK_* macros. If the BOOST_REQUIRE_* macro check fails, the execution of the current test case stops and Boost.Test runs the next test case. However, failing BOOST_CHECK_* does not stop the execution of the current test case.

Step 1 requires additional care. Note the BOOST_TEST_MODULE macro definition. This macro must be defined before including the Boost.Test headers; otherwise, linking the program will fail. More information can be found in the See also section of this recipe.

Some readers may wonder, why did we write BOOST_CHECK_NE(f1, f2) in step 4 instead of BOOST_CHECK(f1 != f2)? The answer is simple: the macro at step 4 provides a more readable and verbose output on older versions of Boost.Test library.

C++17 lacks support for unit testing. However, the Boost.Test library can be used to test C++17 and pre-C++11 code.

Remember that the more tests you have, the more reliable code you get!

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