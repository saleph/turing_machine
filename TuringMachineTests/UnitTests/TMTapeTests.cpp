#include "TMTape.h"
#include <string>

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
using namespace std;

struct TMTapeTestFixtureShortTapeWOPosition
{
    TMTapeTestFixtureShortTapeWOPosition() : tape (TMTape {11}) {}
    ~TMTapeTestFixtureShortTapeWOPosition() = default;

    TMTape tape;
};

BOOST_FIXTURE_TEST_SUITE(tape_with_11_elements_wo_set_position, TMTapeTestFixtureShortTapeWOPosition);

BOOST_AUTO_TEST_CASE( head_position_after_construction_wo_specified_pos ) {
    // checks if a head is at the middle of the tape if pos not specified
    BOOST_CHECK_EQUAL(tape.getPosition(), 11/2);
}

BOOST_AUTO_TEST_SUITE_END();
