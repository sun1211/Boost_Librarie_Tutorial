# Representing a string with two iterators
The main idea of this recipe is that we do not need to construct std::string from substrings. We even do not need to tokenize the whole string at once. All we need to do is find the first substring and return it as a pair of iterators to the beginning and to the end of the substring. If we need more substrings, find the next substring and return a pair of iterators for that substring.

Now, let's take a closer look at *boost::split_iterator*. We constructed one using the *boost::make_split_iterator* function that takes range as the first argument and a binary finder predicate (or binary predicate) as the second. When split_iterator is dereferenced, it returns the first substring as *boost::iterator_range<const char*>*, which just holds a pair of pointers and has a few methods to work with them. When we increment split_iterator, it tries to find the next substring, and if there is no substring found, split_iterator::eof() returns true.

Default constructed split iterator represents an eof(). So we could rewrite the loop condition from !sentences.eof() to sentences != split_iter_t(). You could also use the split iterators with algorithms, for example: std::for_each(sentences, split_iter_t(), [](auto range){ /**/ });.

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

Sentence #1 :   This is a long long character array
Sentence has 35 characters.
Sentence has 6 whitespaces.

Sentence #2 :   Please split this character array to sentences
Sentence has 46 characters.
Sentence has 6 whitespaces.

Sentence #3 :   Do you know, that sentences are separated using period, exclamation mark and question mark
Sentence has 90 characters.
Sentence has 13 whitespaces.

Sentence #4 :    :-)
Sentence has 4 characters.
Sentence has 1 whitespaces.
```
