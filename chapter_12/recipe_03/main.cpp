//include the following headers
#include <boost/config.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <iostream>

int main() {
//Advanced random bits providers have different names under different platforms
    static const std::string provider =
#ifdef BOOST_WINDOWS
        "Microsoft Strong Cryptographic Provider"
#else
        "/dev/urandom"
#endif
    ;

    //include the following headers
    boost::random_device device(provider);
    //Let's get a uniform distribution that returns a value between 1000 and 65535:
    boost::random::uniform_int_distribution<unsigned short> random(100000);

    for (unsigned int i = 0; i < 1000000; ++i) {
        //get true random numbers using the random(device) call
        std::cerr << random(device) << '\t';
    }
}
