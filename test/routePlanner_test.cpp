/*
 * routePlanner_test.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: lali
 */

#include "../src/routePlanner.hpp"

#include <sstream>
#include <boost/test/unit_test.hpp>

namespace routePlanner {

BOOST_AUTO_TEST_SUITE (routePlannerTest)

/**
 * Simplest example
 * =>x
 */
BOOST_AUTO_TEST_CASE(Simple1Endpoint)
{
    std::stringstream ss;
    RoutePlanner sut;
    sut.addEndPoint("x");
    sut.printPath(ss);
    sut.createSpanningTree();
    std::string result; // no initialization required
    ss >> result;
    BOOST_CHECK_EQUAL("x", result);
}

/**
 * Testcase
 * =>x
 * =>z
 */
BOOST_AUTO_TEST_CASE(Simple1Endpoint)
{
    std::stringstream ss;
    RoutePlanner sut;
    sut.addEndPoint("x");
    sut.addEndPoint("z");
    sut.printPath(ss);
    sut.createSpanningTree();
    std::string result; // no initialization required
    ss >> result;
    BOOST_CHECK_EQUAL("x", result);
    ss >> result;
    BOOST_CHECK_EQUAL("y", result);
}

BOOST_AUTO_TEST_SUITE_END( )

} /* namespace routePlanner */
