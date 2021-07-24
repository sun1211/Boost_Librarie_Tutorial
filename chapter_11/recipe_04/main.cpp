#include <iostream>
#include <boost/stacktrace.hpp>

void report_bankruptcy() {
    std::cout << "Sorry, you're bankrupt!\n";
    std::cout << "Here's how it happened:\n" 
        << boost::stacktrace::stacktrace();

    std::exit(0);
}

int main() {
    report_bankruptcy();
    return 0;
}