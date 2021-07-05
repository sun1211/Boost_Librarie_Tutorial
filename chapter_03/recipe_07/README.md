# Parsing simple input with Boost.Spirit

**Boost.Spirit** library allows writing parsers (as well as lexers and generators) directly in C++ code, which are immediately executable (do not require additional tools for C++ code generation). Grammar of Boost.Spirit is very close to Extended Backus-Naur Form (EBNF), which is used for expressing grammar by many standards and understood by other popular parsers. Grammar at the beginning of this chapter is in EBNF

This is a very simple implementation; it does not check the count of digits for numbers. Parsing occurs in the *boost::spirit::qi::parse* function. Let's simplify it a little bit, removing the actions on successful parsing:
```
const bool success = boost::spirit::qi::parse(first, end, 
     ushort_ >> char_('-') >> ushort_ >> char_('-') >> ushort_ 
);
```
The *first* argument points to the beginning of data to parse. It must be a nonconstant variable because the parse function will modify it to point to the end of the parsed sequence.

The *end* argument points to the position that goes after the last element to parse. first and end shall be iterators or pointers.

The third argument to the function is a parsing rule. It looks exactly like the EBNF rule:
```
date-fullyear "-" date-month "-" date-md
```

We just replaced white spaces with the >> operator.

The parse function returns true on success. If we want to make sure that the whole string was successfully parsed, we need to check for the parser's return value and equality of the end and modified first iterators.

Now, we need to deal with actions on successful parse and this recipe will be over. Semantic actions in Boost.Spirit are written inside [] and they can be written using function pointers, function objects, boost::bind, std::bind (or the other bind() implementations), or C++11 lambda functions.

So, you could also write a rule for YYYY using C++11 lambda:

```
const auto y = [&res](unsigned short s) { res.year = s; };
// ...
    
ushort_[y] >> char_('-') >> // ...
```

```
date parse_date_time2_cxx(const std::string& s) {
    using boost::spirit::qi::uint_parser; 
    using boost::spirit::qi::char_; 

    date res; 
    
    uint_parser<unsigned short, 10, 2, 2> u2_; 
    uint_parser<unsigned short, 10, 4, 4> u4_; 

    const auto y = [&res](unsigned short s) { res.year = s; };
    const auto m = [&res](unsigned short s) { res.month = s; };
    const auto d = [&res](unsigned short s) { res.day = s; };
    
    const char* first = s.data(); 
    const char* const end = first + s.size();
    const bool success = boost::spirit::qi::parse(first, end, 
        u4_[y] >> char_('-') >> u2_[m] >> char_('-') >> u2_[d] 
    );
    
    if (!success || first != end) { 
        throw std::logic_error("Parsing failed"); 
    } 
```

*You cannot put the lambda definition directly inside the [] because the C++ compiler will think that it's an attribute. As a workaround, you can make an auto variable with the lambda function in it and use that variable in parser rule description (just like it was done in the preceding code snippet).*

Now, let's take a look at the month's semantic action closer:

```
ushort_[ ref(res.month) = _1 ] 
```

ref(res.month) means pass res.month as a modifiable reference and _1 means the first input parameter, which would be a number (result of ushort_ parsing).

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
