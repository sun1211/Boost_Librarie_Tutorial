# Listing files in a directory

Functions and classes of Boost.Filesystem just wrap around system-specific functions to work with files.

Note the usage of / in step 2. POSIX systems use a slash to specify paths; Windows, by default, uses backslashes. However, Windows understands forward slashes too, so ./ will work on all the popular operating systems, and it means the current directory.

Take a look at step 3, where we are default constructing the boost::filesystem::directory_iterator class. It works just like a std::istream_iterator class, which acts as an end iterator when default constructed.

Step 4 is a tricky one, not because this function is hard to understand, but because lots of conversions are happening. Dereferencing the begin iterator returns boost::filesystem::directory_entry, which is implicitly converted to boost::filesystem::path, which is used as a parameter for the boost::filesystem::status function. Actually, we may do much better:

```
boost::filesystem::file_status fs = begin->status(); 
```

Step 5 is obvious, so we are moving to step 6 where implicit conversion to the path happens again. A better solution would be the following:
```
std::cout << begin->path() << '\n'; 
```

Here, begin->path() returns a const reference to the boost::filesystem::path variable that is contained inside boost::filesystem::directory_entry.

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