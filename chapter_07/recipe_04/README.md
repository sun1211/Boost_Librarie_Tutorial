# Replacing and erasing strings

All the examples are self-documenting. The only one that is not obvious is the replace_head_copy function. It accepts count of bytes to replace as a second parameter and a replace string as the third parameter. So, in the preceding example, Hello gets replaced with Whaaaaaaa!.


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

 erase_all_copy   :Hello hello dear Reader.
 erase_first_copy :Hello hello, dear Reader.
 erase_last_copy  :Hello, hello dear Reader.
 ierase_all_copy  :, , dear Reader.
 ierase_nth_copy  :Hello, hello dear Reader.
 replace_all_copy  :Hello! hello! dear Reader.
 replace_first_copy  :Hello! hello, dear Reader.
 replace_head_copy  :Whaaaaaaa! hello, dear Reader.

```
