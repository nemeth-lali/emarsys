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
BOOST_AUTO_TEST_CASE(Simple2Endpoints)
{
    std::stringstream ss;
    RoutePlanner sut;
    sut.addEndPoint("x");
    sut.addEndPoint("z");
    sut.printPath(ss);
    sut.createSpanningTree();
    std::string result; // no initialization required
    ss >> result;
    BOOST_CHECK_EQUAL("xz", result);
}


/**
 * Testcase
 * x =>
 * y => z
 * z =>
 */
BOOST_AUTO_TEST_CASE(Simple2Endpoints)
{
    std::stringstream ss;
    RoutePlanner sut;
    sut.addEndPoint("x");
    sut.addPoint("y", "z");
    sut.addEndPoint("z");
    sut.printPath(ss);
    sut.createSpanningTree();
    std::string result; // no initialization required
    ss >> result;
    BOOST_CHECK_EQUAL("xzy", result);
}

/**
 * Testcase
 * u =>
 * v => w
 * w => z
 * x => u
 * y => v
 * z =>
 */
BOOST_AUTO_TEST_CASE(Simple2Endpoints)
{
    std::stringstream ss;
    RoutePlanner sut;
    sut.addEndPoint("u");
    sut.addPoint("v", "w");
    sut.addPoint("w", "z");
    sut.addPoint("x", "u");
    sut.addPoint("y", "v");
    sut.addEndPoint("z");
    sut.printPath(ss);
    sut.createSpanningTree();
    std::string result; // no initialization required
    ss >> result;
    BOOST_CHECK_EQUAL("xuyvwz", result);
}


BOOST_AUTO_TEST_SUITE_END( )

} /* namespace routePlanner */
