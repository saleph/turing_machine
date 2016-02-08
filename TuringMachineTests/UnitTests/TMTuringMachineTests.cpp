#include "TMTuringMachine.h"
#include "TMExceptions.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
using namespace std;

struct TMTuringMachineTestFixture {
    const size_t tapeLength = 11;
    const size_t middlePos = 5;
    TMTuringMachineTestFixture() : turingMachine(tapeLength) {
        turingMachine.alphabet->setAlphabet("#01$");
    };
    TMTuringMachine turingMachine;
};

BOOST_FIXTURE_TEST_SUITE(TMTuringMachine_integration, TMTuringMachineTestFixture)

BOOST_AUTO_TEST_CASE( execution_1_command_on_plain_tape ) {
    turingMachine.addToGraph("Start #/1;L next_cmd");
    turingMachine.doStep();
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos], '1');
}

BOOST_AUTO_TEST_CASE( execution_2_commands_on_plain_tape ) {
    turingMachine.addToGraph("Start #/1;L next_cmd");
    turingMachine.addToGraph("next_cmd #/1;L next_next_cmd");
    for (int i=0;i<2;i++) turingMachine.doStep();
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos], '1');
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos-1], '1');
}

BOOST_AUTO_TEST_CASE( execution_chain_of_commands_on_plain_tape_with_some_overwrites_previous_changes ) {
    turingMachine.addToGraph("Start #/1;L cmd1");
    turingMachine.addToGraph("cmd1 #/1;L cmd2");
    turingMachine.addToGraph("cmd2 #/$;r cmd3");
    turingMachine.addToGraph("cmd3 1/0;r cmd4");
    turingMachine.addToGraph("cmd4 1/$;R cmd5");
    turingMachine.addToGraph("cmd5 #/0;r cmd6");
    for (int i=0;i<6;i++) turingMachine.doStep();
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos-2], '$');
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos-1], '0');
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos], '$');
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos+1], '0');
}

BOOST_AUTO_TEST_CASE( reaching_end_of_the_control_graph ) {
    turingMachine.addToGraph("Start #/1;L next_cmd");
    turingMachine.addToGraph("next_cmd #/1;L Stop");
    turingMachine.doStep();
    BOOST_REQUIRE_THROW(turingMachine.doStep(), EndOfTheControlGraph);
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos], '1');
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos-1], '1');
    BOOST_CHECK_EQUAL(turingMachine.tape->getHeadPosition(), middlePos-2);
}

BOOST_AUTO_TEST_CASE( execution_1_command_with_different_fromState_and_char_on_tape ) {
    turingMachine.addToGraph("Start 1/1;L next_cmd"); // under head is now '#'
    BOOST_REQUIRE_THROW(turingMachine.doStep(), CommandNotExist);
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos], '#');
}

BOOST_AUTO_TEST_CASE( execution_1_command_with_no_Start_name ) {
    turingMachine.addToGraph("no-Start #/1;L next_cmd"); // under head is now '#'
    BOOST_REQUIRE_THROW(turingMachine.doStep(), CommandNotExist);
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos], '#');
}

BOOST_AUTO_TEST_CASE( execution_1_command_with_no_Start_name_and_mismatch_fromState_and_char_on_tape ) {
    turingMachine.addToGraph("no-Start 1/1;L next_cmd"); // under head is now '#'
    BOOST_REQUIRE_THROW(turingMachine.doStep(), CommandNotExist);
    BOOST_CHECK_EQUAL((*turingMachine.tape)[middlePos], '#');
}

BOOST_AUTO_TEST_CASE( backTheGraphToTheBeginning_test ) {
    turingMachine.addToGraph("Start #/1;L next_cmd");
    turingMachine.addToGraph("next_cmd $/1;L next_next_cmd");
    turingMachine.doStep(); // now tape looks: ##1##, so next_cmd has different fromStatus
    // head                                     ^
    BOOST_REQUIRE_THROW(turingMachine.doStep(), CommandNotExist);
    turingMachine.backTheGraphToTheBeginning();
    turingMachine.doStep(); // now should execute 1. cmd with Start name
}

BOOST_AUTO_TEST_CASE( notExist_next_cmd ) {
    turingMachine.addToGraph("Start #/1;L next_cmd");
    turingMachine.addToGraph("nextCmdDoesn'tExist $/1;L next_next_cmd");
    turingMachine.doStep(); // now tape looks: ##1##
    // head                                     ^
    BOOST_REQUIRE_THROW(turingMachine.doStep(), CommandNotExist); // because in the graph isn't any next_cmd
}

BOOST_AUTO_TEST_SUITE_END()
