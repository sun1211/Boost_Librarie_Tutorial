# The fastest way to read files

All popular operating systems have the ability to map a file to processes' address space. After such mapping is done, the process may work with those addresses just like with a usual memory. The operating system takes care of all the file operations, such as caching and read ahead.

Why is it faster than traditional read/writes? That's because in most cases read/write is implemented as memory mapping and copying data to a user-specified buffer. So, read usually does a little bit more than memory map.

Just like in the case of standard library's std::fstream, we must provide an open mode when opening a file. See step 2 where we provided the boost::interprocess::read_only mode.

See step 3 where we mapped a whole file at once. This operation is actually really fast, because OS does not read data from the disk, but waits for requests to a part of the mapped region. After a part of the mapped region was requested, the OS loads that part of the file from the disk into the memory. As we may see, memory mapping operations are lazy, and the size of the mapped region does not affect performance.

However, a 32-bit OS cannot memory-map big files, so you have to map them by pieces. POSIX (Linux) operating systems require the _FILE_OFFSET_BITS=64 macro to be defined for the whole project to work with big files on a 32-bit platform. Otherwise, the OS won't be able to map parts of the file that are beyond 4 GB.

Now, it's time to measure the performance:
```
$ TIME="%E" time ./reading_files m
    mapped_region: 0:00.08
    
    
    $ TIME="%E" time ./reading_files r
    ifstream: 0:00.09
    
    $ TIME="%E" time ./reading_files a
    C: 0:00.09
```

Just as it was expected, memory-mapped files are slightly faster than traditional reads. We may also see that pure C methods have the same performance as the C++ std::ifstream class, so do not use functions related to FILE* in C++. They are just for C, not for C++!

For optimal performance of std::ifstream, do not forget to open files in binary mode and read data by blocks:

```
std::ifstream f(filename, std::ifstream::binary); 
// ... 
char c[kilobyte]; 
f.read(c, kilobyte);
```

Writing to memory-mapped regions is also a very fast operation. The OS caches the writes and does not flush modifications to the disc immediately. There is a difference between OS and the std::ofstream data caching. In case the std::ofstream data is cached by an application and if it terminates, the cached data can be lost. When data is cached by the OS, termination of the application does not lead to data loss. Power failures and OS crashes lead to data loss in both cases.

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