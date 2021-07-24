# Erasing and creating files and directories

We saw boost::system::error_code in action in almost all the recipes in Chapter 6, Manipulating Tasks. It can store information about errors and is widely used all around Boost libraries.

If you do not provide an instance of boost::system::error_code to the Boost.Filesystem functions, the code will compile well. In that case, when an error occurs, a boost::filesystem::filesystem_error exception is thrown.
Take a careful look at step 3. We used the boost::filesystem::create_directories function, not boost::filesystem::create_directory, because the latter one cannot create sub-directories. It is the same story with boost::filesystem::remove_all and boost::filesystem::remove. The first can remove non empty directories, that contain files and sub-directories. The second one removes a single file.

The remaining steps are simple to understand and should not cause any trouble.


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

Symlink created

```