#include <string>
std::string str1 = "Thanks for reading me!";
std::string str2 = "Thanks for reading ME!";

//The most simple one
#include <boost/algorithm/string/predicate.hpp>
void method1() { assert(
    boost::iequals(str1, str2)
);}

//Using the Boost predicate and standard library method
#include <boost/algorithm/string/compare.hpp>
#include <algorithm>
void method2() { assert(

str1.size() == str2.size() && std::equal(
    str1.begin(),
    str1.end(),
    str2.begin(),
    boost::is_iequal()
)

);}

//Making a lowercase copy of both the strings
#include <boost/algorithm/string/case_conv.hpp>
void method3() {

std::string str1_low = boost::to_lower_copy(str1);
std::string str2_low = boost::to_lower_copy(str2);
assert(str1_low == str2_low);

}

//Making an uppercase copy of the original strings
#include <boost/algorithm/string/case_conv.hpp>
void method4() {

std::string str1_up = boost::to_upper_copy(str1);
std::string str2_up = boost::to_upper_copy(str2);
assert(str1_up == str2_up);

}

//Converting the original strings to lowercase
#include <boost/algorithm/string/case_conv.hpp>
void method5() {

boost::to_lower(str1);
boost::to_lower(str2);
assert(str1 == str2);

}

int main() {
    method1();
    method2();
    method3();
    method4();
    method5();

    // On some platforms std::locale::classic() works
    // faster than std::locale()
    boost::iequals(str1, str2, std::locale::classic());
}
