# Matching strings using regular expressions

All the matching is done by the boost::regex class. It constructs an object that is capable of regex parsing and compilation. Additional configuration options are passed to the class using a flag input variable.

If the regular expression is incorrect, boost::regex throws an exception. If the boost::regex::no_except flag was passed, it reports an error returning a non-zero in the status() call (just like in our example):

```
if (e.status()) {
            std::cout << "Incorrect regex pattern!\n";
            continue;
        }
```
This will result in:
```
Input regex: (incorrect regex(
Incorrect regex pattern!
```
Regular expressions matching is done by a call to the *boost::regex_match* function. It returns true in case of a successful match. Additional flags may be passed to regex_match, but we avoided their usage for brevity of the example.

C++11 contains almost all the Boost.Regex classes and flags. They can be found in the <regex> header of the std:: namespace (instead of boost::). Official documentation provides information about differences of C++11 and Boost.Regex. It also contains some performance measures that tell that Boost.Regex is fast. Some standard libraries have performance issues, so choose wisely between Boost and Standard library versions.



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

Available regex syntaxes:
 [0] Perl
 [1] Perl case insensitive
 [2] POSIX extended
 [3] POSIX extended case insensitive
 [4] POSIX basic
 [5] POSIX basic case insensitive

```
