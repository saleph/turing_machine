#include "../include/MyExp.h"
#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( my_test )
{
    MyExp me;
    int val = me.myExpFunc(5.0);

    BOOST_CHECK_EQUAL(val, 24);
}
