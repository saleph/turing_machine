#include "TMTape.h"
#include <memory>

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
using namespace std;

struct TMTapeTestFixtureFor1Arg {
    unique_ptr<TMTape> tape;
    void makeNewTapeWithLength(unsigned int len) {
        tape = unique_ptr<TMTape>(new TMTape(len));
    }
};

BOOST_FIXTURE_TEST_SUITE( tape_wo_setting_position, TMTapeTestFixtureFor1Arg );

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_0_long_tape ) {
    BOOST_CHECK_THROW(makeNewTapeWithLength(0), ZeroLongTape);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_1_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(1));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 1/2);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_11_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(11));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 11/2);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_111_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(111));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 111/2);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_1001_long_tape ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLength(1001));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 1001/2);
}

BOOST_AUTO_TEST_SUITE_END();

struct TMTapeTestFixtureFor2Args {
    unique_ptr<TMTape> tape;
    void makeNewTapeWithLengthAndHeadAt(unsigned int len, unsigned int pos) {
        tape = unique_ptr<TMTape>(new TMTape(len, pos));
    }
};
BOOST_FIXTURE_TEST_SUITE( tape_with_setting_position, TMTapeTestFixtureFor2Args );

BOOST_AUTO_TEST_CASE( construction_for_0_long_tape_with_head_at_0 ) {
    BOOST_CHECK_THROW(makeNewTapeWithLengthAndHeadAt(0, 0), ZeroLongTape);
}

BOOST_AUTO_TEST_CASE( construction_for_0_long_tape_with_head_at_1 ) {
    BOOST_CHECK_THROW(makeNewTapeWithLengthAndHeadAt(0, 1), ZeroLongTape);
}

BOOST_AUTO_TEST_CASE( construction_for_1_long_tape_with_head_at_1 ) {
    BOOST_CHECK_THROW(makeNewTapeWithLengthAndHeadAt(1, 1), HeadOutOfTape);
}

BOOST_AUTO_TEST_CASE( construction_for_1_long_tape_with_head_at_0 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1, 0));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 0);
}

BOOST_AUTO_TEST_CASE( construction_for_5_long_tape_with_head_at_0 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(5, 0));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 0);
}

BOOST_AUTO_TEST_CASE( construction_for_5_long_tape_with_head_at_3 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(5, 3));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 3);
}

BOOST_AUTO_TEST_CASE( construction_for_5_long_tape_with_head_at_4 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(5, 4));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 4);
}

BOOST_AUTO_TEST_CASE( construction_for_1001_long_tape_with_head_at_0 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 0));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 0);
}

BOOST_AUTO_TEST_CASE( construction_for_1001_long_tape_with_head_at_720 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 720));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 720);
}

BOOST_AUTO_TEST_CASE( construction_for_1001_long_tape_with_head_at_1000 ) {
    BOOST_REQUIRE_NO_THROW(makeNewTapeWithLengthAndHeadAt(1001, 1000));
    BOOST_CHECK_EQUAL(tape->getHeadPosition(), 1000);
}

BOOST_AUTO_TEST_SUITE_END();
