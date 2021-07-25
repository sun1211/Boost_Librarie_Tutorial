# Combining multiple test cases in one test module

All the magic is done by the BOOST_TEST_MODULE macro. If it is defined before <boost/test/unit_test.hpp>, Boost.Test thinks that this source file is the main one and all the helper testing infrastructure must be placed in it. Otherwise, only the test macro is be included from <boost/test/unit_test.hpp>.

All the BOOST_AUTO_TEST_CASE tests will run if you link them with the source file that contains the BOOST_TEST_MODULE macro. When working on a big project, each developer may enable compilation and linking only of their own sources. That gives independence from other developers and increases the speed of development - no need to compile alien sources and run alien tests while debugging.


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