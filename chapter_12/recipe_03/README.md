# Using a true random number generator

Why does the rand() function not suit banking? Because it generates pseudo-random numbers, which means that the hacker may predict the next generated number. This is an issue with all pseudo-random number algorithms. Some algorithms are easier to predict and some harder, but it's still possible.

That's why, we are using boost::random_device in this example (see step 3). That device gathers entropy--information about random events from all around the operating system to produce unpredictable uniform random bits. The examples of such events are delays between pressed keys, delays between some of the hardware interruptions, and the internal CPU's random bits generators.

Operating systems may have more than one such type of random bit generator. In our example for POSIX systems, we used /dev/urandom instead of the more secure /dev/random because the latter remains in a blocked state until enough random events have been captured by the OS. Waiting for entropy may take seconds, which is usually unsuitable for applications. Use /dev/random for the long-lifetime GPG/SSL/SSH keys.

Now that we are done with generators, it's time to move to step 4 and talk about distribution classes. If the generator just generates uniform distributed bits, the distribution class makes a random number from those bits. In step 4, we made a uniform distribution that returns a random number of unsigned short type. The parameter 1000 means that distribution must return numbers greater or equal to 1000. We can also provide the maximum number as a second parameter, which is by default equal to the maximum value storable in the return type.

The Boost.Random has a huge number of true/pseudo random bit generators and distributions for different needs. Avoid copying distributions and generators. This may turn out to be an expensive operation.

C++11 has support for different distribution classes and generators. You may find all the classes from this example in the <random> header in the std:: namespace. The Boost.Random libraries do not use C++11 features, and they are not really required for that library either. Should you use Boost implementation or standard library? Boost provides better portability across systems. However, some standard libraries may have assembly-optimized implementations and may provide some useful extensions.

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