#include "TMStringCharPair.h"
#include <memory>

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
using namespace std;

struct TMStringCharPairTestFixture {
    void insertToPair(unique_ptr<TMStringCharPair>& strCharPair, string str, char c) {
        strCharPair = make_unique<TMStringCharPair>(str, c);
    }

    size_t getHashFrom(unique_ptr<TMStringCharPair>& strCharPair) {
        return hash<TMStringCharPair>{}(*strCharPair);
    }

    unique_ptr<TMStringCharPair> firstPair;
    unique_ptr<TMStringCharPair> secondPair;
};

BOOST_FIXTURE_TEST_SUITE(plain_TMStringCharPair_fixture, TMStringCharPairTestFixture)

BOOST_AUTO_TEST_CASE( hash_check_for_the_same_pairs ) {
    insertToPair(firstPair, "string", 'c');
    insertToPair(secondPair, "string", 'c');
    BOOST_CHECK_EQUAL(getHashFrom(firstPair), getHashFrom(secondPair));
}

BOOST_AUTO_TEST_CASE( hash_check_for_subtle_diffrent_pairs ) {
    insertToPair(firstPair, "string", 'c');
    insertToPair(secondPair, "strin", 'c');
    BOOST_CHECK_NE(getHashFrom(firstPair), getHashFrom(secondPair));
}

BOOST_AUTO_TEST_CASE( hash_check_for_the_same_strings_diffrent_chars ) {
    insertToPair(firstPair, "string", 'c');
    insertToPair(secondPair, "string", 'd');
    BOOST_CHECK_NE(getHashFrom(firstPair), getHashFrom(secondPair));
}

BOOST_AUTO_TEST_CASE( hash_check_for_entirely_diffrent_pairs  ) {
    insertToPair(firstPair, "string", 'c');
    insertToPair(secondPair, "someOther", '1');
    BOOST_CHECK_NE(getHashFrom(firstPair), getHashFrom(secondPair));
}

BOOST_AUTO_TEST_SUITE_END()
