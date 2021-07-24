#include <boost/filesystem/operations.hpp>
#include <cassert>
#include <fstream>
#include <iostream>

int main() {
    //we need a variable to store errors
    boost::system::error_code error;

    //We will also create directories, if required
    boost::filesystem::create_directories("dir/subdir", error);
    assert(!error);

    //we will write data to the file
    std::ofstream ofs("dir/subdir/file.txt");
    ofs << "Boost.Filesystem is fun!";
    assert(ofs);
    ofs.close();

    //We need to attempt to create symlink
    boost::filesystem::create_directory_symlink("dir/subdir", "symlink", error);

    // we need to check that the file is accessible through symlink
    if (!error) {
        std::cerr << "Symlink created\n";
        assert(boost::filesystem::exists("symlink/file.txt"));
    } else {
        //We'll remove the created file, if the symlink creation fails
        std::cerr << "Failed to create a symlink\n";
        boost::filesystem::remove("dir/subdir/file.txt", error);
        assert(!error);
    } /*if (!error)*/
} /*main*/
