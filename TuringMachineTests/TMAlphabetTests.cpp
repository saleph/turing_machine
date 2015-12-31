#include "TMAlphabet.h"
#include <string>
#include <algorithm>

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
using namespace std;

BOOST_AUTO_TEST_SUITE( TMAlphabet_has_func );

BOOST_AUTO_TEST_CASE( has_func_with_existing_elements_for_lowercase ) {
    TMAlphabet alphabet {"abcd"};
    string strAlphabet {"abcd"};
    for (const char& sign : strAlphabet)
        BOOST_CHECK(alphabet.has(sign));
}

BOOST_AUTO_TEST_CASE( has_func_with_existing_elements_for_uppercase ) {
    TMAlphabet alphabet {"ABCD"};
    string strAlphabet {"ABCD"};
    for (const char& sign : strAlphabet)
        BOOST_CHECK(alphabet.has(sign));
}

BOOST_AUTO_TEST_CASE( has_func_with_lowercase_alphabet_and_nonexisting_uppercase_elements ) {
    TMAlphabet alphabet {"abcd"};
    string strNonAlphabet {"UWXYZ"};
    for (const char& sign : strNonAlphabet)
        BOOST_CHECK(!alphabet.has(sign));
}

BOOST_AUTO_TEST_CASE( has_func_with_uppercase_alphabet_and_nonexisting_lowercase_elements ) {
    TMAlphabet alphabet {"ABCD"};
    string strNonAlphabet {"uwxyz"};
    for (const char& sign : strNonAlphabet)
        BOOST_CHECK(!alphabet.has(sign));
}

BOOST_AUTO_TEST_CASE( has_func_with_uppercase_alphabet_and_existing_signs_but_lowercase_elements ) {
    TMAlphabet alphabet {"ABCD"};
    string strNonAlphabet {"abcd"};
    for (const char& sign : strNonAlphabet)
        BOOST_CHECK(!alphabet.has(sign));
}

BOOST_AUTO_TEST_CASE( has_func_with_lowercase_alphabet_and_existing_signs_but_uppercase_elements ) {
    TMAlphabet alphabet {"abcd"};
    string strNonAlphabet {"ABCD"};
    for (const char& sign : strNonAlphabet)
        BOOST_CHECK(!alphabet.has(sign));
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE(TMAlphabet_getAlphabet_func)

BOOST_AUTO_TEST_CASE( getAlphabet_func_for_single_char ) {
    TMAlphabet alphabet {"a"};
    string strAlphabet {"a"};
    BOOST_CHECK(!strAlphabet.compare(alphabet.getAlphabet()));
}

BOOST_AUTO_TEST_CASE( getAlphabet_func_for_five_char ) {
    TMAlphabet alphabet {"acdef"};
    string strAlphabet {"acdef"};
    string strFromObject = alphabet.getAlphabet();
    // unordered_set doesn't keep order of element
    sort(strAlphabet.begin(), strAlphabet.end());
    sort(strFromObject.begin(), strFromObject.end());
    BOOST_CHECK(!strAlphabet.compare(strFromObject));
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE(TMAlphabet_getSortedAlphabet_func);

BOOST_AUTO_TEST_CASE( getSortedAlphabet_func ) {
    TMAlphabet alphabet {"abcd"};
    string strAlpha {"abcd"};
    string strAlphaFromObject {alphabet.getSortedAlphabet()};
    BOOST_CHECK(!strAlpha.compare(strAlphaFromObject));
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE(TMAlphabet_setAlphabet_func);

BOOST_AUTO_TEST_CASE( setAlphabet_func_for_new_alphabet ) {
    TMAlphabet alphabet {"abcd"};
    string newStrAlphabet {"qstw"};
    alphabet.setAlphabet(newStrAlphabet);
    string newAlphaFromObject {alphabet.getAlphabet()};
    sort(newStrAlphabet.begin(), newStrAlphabet.end());
    sort(newAlphaFromObject.begin(), newAlphaFromObject.end());
    BOOST_CHECK(!newStrAlphabet.compare(newAlphaFromObject));
}

BOOST_AUTO_TEST_CASE( setAlphabet_func_for_new_but_the_same_alphabet ) {
    TMAlphabet alphabet {"abcd"};
    string newStrAlphabet {"abcd"};
    alphabet.setAlphabet(newStrAlphabet);
    string newAlphaFromObject {alphabet.getAlphabet()};
    sort(newStrAlphabet.begin(), newStrAlphabet.end());
    sort(newAlphaFromObject.begin(), newAlphaFromObject.end());
    BOOST_CHECK(!newStrAlphabet.compare(newAlphaFromObject));
}

BOOST_AUTO_TEST_SUITE_END();
