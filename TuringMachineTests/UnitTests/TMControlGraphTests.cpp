#include "TMControlGraph.h"
#include "TMExceptions.h"
#include "TMHeadMoveType.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
using namespace std;

struct TMControlGraphTestFixture {
    TMControlGraph graph;
};
