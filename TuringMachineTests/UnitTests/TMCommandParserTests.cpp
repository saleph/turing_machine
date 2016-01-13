#include "TMCommandParser.h"
#include "TMHeadMoveType.h"
#include "TMExceptions.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
using namespace std;

struct TMCommandParserTestFixture {
    TMCommandParser parser;
    pair<string, TMCommand> outputPair;
};
BOOST_FIXTURE_TEST_SUITE(command_parser, TMCommandParserTestFixture)

BOOST_AUTO_TEST_CASE( parsing_correct_line_move_right ) {
    const string line ("state_name #/#;R go_to_state");
    const TMCommand cmd ('#', '#', TMHeadMoveType::RIGHT, "go_to_state");
    outputPair = parser.parseToCommandWithItsName(line);
    BOOST_CHECK(cmd.isTheSameAs(outputPair.second));
}

BOOST_AUTO_TEST_CASE( parsing_correct_line_move_left ) {
    const string line ("state_name #/#;L go_to_state");
    const TMCommand cmd ('#', '#', TMHeadMoveType::LEFT, "go_to_state");
    outputPair = parser.parseToCommandWithItsName(line);
    BOOST_CHECK(cmd.isTheSameAs(outputPair.second));
}

BOOST_AUTO_TEST_CASE( parsing_correct_line_lowercase_move_type_move_right ) {
    const string line ("state_name #/#;r go_to_state");
    const TMCommand cmd ('#', '#', TMHeadMoveType::RIGHT, "go_to_state");
    outputPair = parser.parseToCommandWithItsName(line);
    BOOST_CHECK(cmd.isTheSameAs(outputPair.second));
}

BOOST_AUTO_TEST_CASE( parsing_correct_line_lowercase_move_type_move_left ) {
    const string line ("state_name #/#;l go_to_state");
    const TMCommand cmd ('#', '#', TMHeadMoveType::LEFT, "go_to_state");
    outputPair = parser.parseToCommandWithItsName(line);
    BOOST_CHECK(cmd.isTheSameAs(outputPair.second));
}

BOOST_AUTO_TEST_CASE( parsing_correct_line_with_additional_spaces ) {
    const string line ("     state_name   #/#;R    go_to_state ");
    const TMCommand cmd ('#', '#', TMHeadMoveType::RIGHT, "go_to_state");
    outputPair = parser.parseToCommandWithItsName(line);
    BOOST_CHECK(cmd.isTheSameAs(outputPair.second));
}

BOOST_AUTO_TEST_CASE( parsing_correct_line_with_special_chars_in_names ) {
    const string line ("!@#$%^&*()-=+|[]{}:?<>state_name #/#;R go_to_state!@#$%^&*()-=+|[]{}:?<>");
    const TMCommand cmd ('#', '#', TMHeadMoveType::RIGHT, "go_to_state!@#$%^&*()-=+|[]{}:?<>");
    outputPair = parser.parseToCommandWithItsName(line);
    BOOST_CHECK(cmd.isTheSameAs(outputPair.second));
}

BOOST_AUTO_TEST_CASE( parsing_incorrect_line_with_semicolon_in_goto_func ) {
    const string line ("state_name #/#;R go_to_stat;e");
    BOOST_CHECK_THROW(parser.parseToCommandWithItsName(line), InvalidCommandSyntax);
}

BOOST_AUTO_TEST_CASE( parsing_incorrect_line_with_semicolon_cmd_name_func ) {
    const string line ("state_n;ame #/#;R go_to_state");
    BOOST_CHECK_THROW(parser.parseToCommandWithItsName(line), InvalidCommandSyntax);
}

BOOST_AUTO_TEST_CASE( parsing_incorrect_line_with_slash_in_cmd_name ) {
    const string line ("state_n/ame; #/#;R go_to_state");
    BOOST_CHECK_THROW(parser.parseToCommandWithItsName(line), InvalidCommandSyntax);
}

BOOST_AUTO_TEST_CASE( parsing_incorrect_line_with_slash_in_goto_func_name ) {
    const string line ("state_name #/#;R go_to_st/ate");
    BOOST_CHECK_THROW(parser.parseToCommandWithItsName(line), InvalidCommandSyntax);
}

BOOST_AUTO_TEST_CASE( parsing_incorrect_line_with_J_as_move_type ) {
    const string line ("state_name #/#;J go_to_state");
    BOOST_CHECK_THROW(parser.parseToCommandWithItsName(line), InvalidCommandSyntax);
}

BOOST_AUTO_TEST_CASE( parsing_incorrect_line_with_p_as_move_type ) {
    const string line ("state_name #/#;p go_to_state");
    BOOST_CHECK_THROW(parser.parseToCommandWithItsName(line), InvalidCommandSyntax);
}

BOOST_AUTO_TEST_CASE( parsing_incorrect_line_with_double_slash ) {
    const string line ("state_name #//#;R go_to_state");
    BOOST_CHECK_THROW(parser.parseToCommandWithItsName(line), InvalidCommandSyntax);
}

BOOST_AUTO_TEST_CASE( parsing_incorrect_line_with_double_semicolon ) {
    const string line ("state_name #/#;;R go_to_state");
    BOOST_CHECK_THROW(parser.parseToCommandWithItsName(line), InvalidCommandSyntax);
}

BOOST_AUTO_TEST_CASE( parsing_incorrect_line_with_double_FROM_char ) {
    const string line ("state_name ##/#;R go_to_state");
    BOOST_CHECK_THROW(parser.parseToCommandWithItsName(line), InvalidCommandSyntax);
}

BOOST_AUTO_TEST_CASE( parsing_incorrect_line_with_double_TO_char ) {
    const string line ("state_name #/##;R go_to_state");
    BOOST_CHECK_THROW(parser.parseToCommandWithItsName(line), InvalidCommandSyntax);
}

BOOST_AUTO_TEST_CASE( parsing_incorrect_line_with_double_move_type_char ) {
    const string line ("state_name ##/#;Rr go_to_state");
    BOOST_CHECK_THROW(parser.parseToCommandWithItsName(line), InvalidCommandSyntax);
}

BOOST_AUTO_TEST_SUITE_END()
