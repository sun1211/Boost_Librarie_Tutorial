# Parsing complex input with Boost.Spirit

A very interesting variable here is *boost::spirit::qi::rule<const char*, void()>*. It erases the exact type of a resulting parser and allows you to write parsers for recursive grammars. It also allows you to write parsers in source files and export them to headers without significantly affecting compilation times of your project.

The Boost.Spirit library generates very fast parsers; there are some performance measures at the official site. Official documentation contains advanced recommendations for writing faster parsers.

The usage of *boost::phoenix::bind* is not mandatory, but without it the rule that parses specific zone offset in timezone_parser will be dealing with the

*boost::fusion::vector<char, unsigned short, unsigned short> *type. Using *bind(&set_zone_offset, ref(ret), _1, _2, _3)* seems to be a more reader-friendly solution.

Compiling the code that uses the *Boost.Spirit* (or *Boost.Fusion*) library may take a lot of time, because of the huge amount of template instantiations. When experimenting with the *Boost.Spirit* library use modern compilers, they provide better compilation times.


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
