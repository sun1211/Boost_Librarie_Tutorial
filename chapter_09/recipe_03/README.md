# Comparing strings in an ultra-fast manner

The comparison of strings is slow because we are required to compare all the characters of the string one-by-one, if strings have equal length. Instead of doing that, we replace the comparison of strings with the comparison of integers. This is done via the hash function - the function that makes some short-fixed length representation of the string.

Let's talk about the hash values on apples. Imagine that you have two apples with labels, and you wish to check that the apples are of the same cultivar. The simplest way to compare those apples is by comparing them by labels. Otherwise, you'll lose a lot of time comparing the apples based on the color, size, form, and other parameters. Hash is something like a label that reflects the value of the object.

In step 1, we include the header file that contains definitions of the hash functions. In step 2, we declare our new string class that contains str_, which is the original value of string and comparison_, which is the computed hash value. Note the construction:

```
 boost::hash<std::string>()(s) 
```

Here, *boost::hash<std::string>* is a structure, a functional object just like std::negate<>. That is why we need the first parenthesis--we construct that functional object. The second parenthesis with s inside is a call to std::size_t operator()(const std::string& s), which computes the hash value.

Now, take a look at step 3, where we define operator==:

```
  return s1.comparison_ == s2.comparison_ && s1.str_ == s2.str_; 
```

Take additional care about the second part of the expression. Hashing operation loses information, which means that there is possibly more than one string that produces exactly the same hash value. It means that if hashes mismatch, there is a 100% guarantee that the strings does not match; otherwise, we are required to compare strings using the traditional methods.

Well, it's time to compare numbers. If we measure the execution time using the default comparison method, it'll give us 819 milliseconds; however, our hashing comparison works almost two times faster and finishes in 475 milliseconds.

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