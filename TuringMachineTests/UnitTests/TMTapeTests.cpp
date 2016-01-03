#include "TMTape.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( tape_wo_setting_position );

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_0_long_tape ) {
    BOOST_CHECK_THROW(TMTape {0}, ZeroLongTape);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_1_long_tape ) {
    TMTape tape {1};
    BOOST_CHECK_EQUAL(tape.getHeadPosition(), 1/2);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_11_long_tape ) {
    TMTape tape {11};
    BOOST_CHECK_EQUAL(tape.getHeadPosition(), 11/2);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_111_long_tape ) {
    TMTape tape {111};
    BOOST_CHECK_EQUAL(tape.getHeadPosition(), 111/2);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_1001_long_tape ) {
    TMTape tape {1001};
    BOOST_CHECK_EQUAL(tape.getHeadPosition(), 1001/2);
}

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos_for_10001_long_tape ) {
    TMTape tape {10001};
    BOOST_CHECK_EQUAL(tape.getHeadPosition(), 10001/2);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE( tape_with_setting_position );

BOOST_AUTO_TEST_CASE( construction_with_head_at_0_for_0_long_tape ) {
    BOOST_CHECK_THROW(TMTape (0, 0), ZeroLongTape);
}

BOOST_AUTO_TEST_CASE( construction_with_head_at_1_for_0_long_tape ) {
    BOOST_CHECK_THROW(TMTape (0, 1), ZeroLongTape);
}

BOOST_AUTO_TEST_CASE( construction_with_head_at_2_for_1_long_tape ) {
    BOOST_CHECK_THROW(TMTape (1, 1), HeadOutOfTape);
}

BOOST_AUTO_TEST_SUITE_END();
