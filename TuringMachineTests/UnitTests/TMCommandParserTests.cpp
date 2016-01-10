#include "TMCommandParser.h"
#include "TMHeadMoveType.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
using namespace std;

struct TMCommandParserTestFixture {
    TMCommandParser parser;
    pair<string, TMCommand> outputPair;
};
BOOST_FIXTURE_TEST_SUITE(command_parser, TMCommandParserTestFixture);

BOOST_AUTO_TEST_CASE( parse_correct_line ) {
    const string line ("state_name #/#;R go_to_state");
    const TMCommand cmd ('#', '#', TMHeadMoveType::RIGHT, "go_to_state");
    outputPair = parser.parseToCommandWithItsName(line);
    BOOST_CHECK(cmd.isTheSameAs(outputPair.second));
}

BOOST_AUTO_TEST_SUITE_END();
