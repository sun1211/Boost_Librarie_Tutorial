# Formatting strings using safe printf-like functions

The **boost::format**class accepts the string that specifies the resulting string format. Arguments are passed to *boost::format* using operator%. Values %1%, %2%, %3%, %4%, and so on, in the format specifying string are replaced by arguments passed to *boost::format*.

We also disable the exceptions for cases when a format string contains fewer arguments than passed to *boost::format*:
```
  boost::format f(format_specifier);
    unsigned char flags = boost::io::all_error_bits;
    flags ^= boost::io::too_many_args_bit;
```
This is done to allow some formats like this:

```
// Outputs 'Reader'
    std::cout << class_instance.to_string("%2%\n\n");
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

Hello, dear Reader! Did you read the book for 100 % !
100 == 100 && 100% != 100

Reader

boost::too_few_args: format-string referred to more arguments than were passed

```
