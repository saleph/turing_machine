#include "TMTape.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(tape_with_11_elements_wo_set_position);

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos ) {
    TMTape tape {11};
    BOOST_CHECK_EQUAL(tape.getPosition(), 11/2);
}

BOOST_AUTO_TEST_SUITE_END();

/*struct TMTapeTestFixtureShortTapeWOPosition
{
    TMTapeTestFixtureShortTapeWOPosition() : tape (TMTape {11}) {}
    ~TMTapeTestFixtureShortTapeWOPosition() = default;

    TMTape tape;
};*/
