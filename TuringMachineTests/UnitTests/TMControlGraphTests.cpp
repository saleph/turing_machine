#include <memory>
#include "TMControlGraph.h"
#include "TMExceptions.h"
#include "TMStringCharPair.h"
#include "TMHeadMoveType.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
using namespace std;

struct TMControlGraphTestFixture {
    using PairStrCmd = std::pair<std::string, TMCommand>;
    TMControlGraphTestFixture() {
        cmdName = make_unique<string>("name");
        cmdBody = make_unique<TMCommand>('#', '#', TMHeadMoveType::RIGHT, "goto");
        cmd = make_unique<PairStrCmd>(make_pair(*cmdName, *cmdBody));
        char fromState = cmdBody->getFromState();
        nameAndToStatePair = make_unique<TMStringCharPair>(*cmdName, fromState);
        graph = make_unique<TMControlGraph>();
    }
    unique_ptr<TMControlGraph> graph;
    unique_ptr<PairStrCmd> cmd;
    unique_ptr<string> cmdName;
    unique_ptr<TMCommand> cmdBody;
    unique_ptr<TMStringCharPair> nameAndToStatePair; // it uniquely defines command by its name and 'fromState'
};

BOOST_FIXTURE_TEST_SUITE(plain_TMControlGraph_instance, TMControlGraphTestFixture)

BOOST_AUTO_TEST_CASE( addition_1_command_to_plain_graph ) {
    *graph += *cmd;
    BOOST_CHECK(cmdBody->isTheSameAs((*graph)[*nameAndToStatePair]));
}

BOOST_AUTO_TEST_CASE( addition_existing_cmd_to_graph ) {
    *graph += *cmd;
    BOOST_CHECK_THROW(*graph += *cmd, CommandAlreadyExist);
}

BOOST_AUTO_TEST_SUITE_END()
