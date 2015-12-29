#include "TMAlphabet.h"
#define BOOST_TEST_MODULE TMAlphabet
#include <boost/test/included/unit_test.hpp>
#include <string>

BOOST_AUTO_TEST_CASE( has_func_with_existing_elements ) {
    TMAlphabet alphabet {"abcd"};
    std::string strAlphabet {alphabet.getAlphabet()};
    for (const char& sign : strAlphabet) {
        BOOST_CHECK(alphabet.has(sign));
    }
}

//TODO: has_func_with_not_existing_elements
