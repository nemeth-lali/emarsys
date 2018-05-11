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
 * x=>
 * y=>z
 * z=>
 */
BOOST_AUTO_TEST_CASE(Simple2Endpoints1Path)
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
 * Testcase Example 3
 * u =>
 * v => w
 * w => z
 * x => u
 * y => v
 * z =>
 */
BOOST_AUTO_TEST_CASE(Example3)
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

/*
 * This can be solved with other graph implementation but for now I do my own implementation
 * Problem:
 * No endpoint for the route
 * x=>y
 * Decision:
 * The path ignored and dropped from output (all unterminated paths are dropped from the output x=>y rule ignored)
 */
BOOST_AUTO_TEST_CASE(NoEndPoint)
{
    std::stringstream ss;
    RoutePlanner sut;
    sut.addPoint("x", "y");
    sut.printPath(ss);
    sut.createSpanningTree();
    std::string result; // no initialization required
    ss >> result;
    BOOST_CHECK_EQUAL("", result);
}


 /*
 * Problem:
 * Path contains circle
 * x=>y
 * y=>x
 * Decision:
 * Spanning tree algorithm cuts off the circles
 */
BOOST_AUTO_TEST_CASE(Circle)
{
    std::stringstream ss;
    RoutePlanner sut;
    sut.addPoint("x", "y");
    sut.addPoint("y", "x");
    sut.printPath(ss);
    sut.createSpanningTree();
    std::string result; // no initialization required
    ss >> result;
    BOOST_CHECK_EQUAL("", result);
}

 /* Problem:
 * Point is endpoint but also source of route
 * x=>y
 * x=>
 * Decision: x used as endpoint x=>y rule ignored
 */
BOOST_AUTO_TEST_CASE(EndpointContinues)
{
    std::stringstream ss;
    RoutePlanner sut;
    sut.addPoint("x", "y");
    sut.addEndPoint("x");
    sut.printPath(ss);
    sut.createSpanningTree();
    std::string result; // no initialization required
    ss >> result;
    BOOST_CHECK_EQUAL("x", result);
}

/* Problem:
* Duplicate rule
* x=>y
* x=>y
* y=>
* Decision: x=>y rule ignored
*/
BOOST_AUTO_TEST_CASE(Duplicate)
{
   std::stringstream ss;
   RoutePlanner sut;
   sut.addPoint("x", "y");
   sut.addPoint("x", "y");
   sut.addEndPoint("y");
   sut.printPath(ss);
   sut.createSpanningTree();
   std::string result; // no initialization required
   ss >> result;
   BOOST_CHECK_EQUAL("xy", result);
}

/* Problem:
* Point is endpoint but also source of route which continues
* x=>y
* x=>
* y=>z
* z=>
* Decision: x used as endpoint x=>y rule ignored
*/
BOOST_AUTO_TEST_CASE(EndpointContinuesTerminatedPath)
{
   std::stringstream ss;
   RoutePlanner sut;
   sut.addPoint("x", "y");
   sut.addPoint("y", "z");
   sut.addEndPoint("x");
   sut.addEndPoint("z");
   sut.printPath(ss);
   sut.createSpanningTree();
   std::string result; // no initialization required
   ss >> result;
   BOOST_CHECK_EQUAL("xyz", result);
}

 /*
 * Problem:
 * Two paths leads to the same direction
 * x=>y
 * z=>y
 * z=>
 * Decision:both paths included in the result
 */
BOOST_AUTO_TEST_CASE(TwoPathsSameDirection)
{
    std::stringstream ss;
    RoutePlanner sut;
    sut.addPoint("x", "y");
    sut.addPoint("z", "y");
    sut.addEndPoint("y");
    sut.printPath(ss);
    sut.createSpanningTree();
    std::string result; // no initialization required
    ss >> result;
    BOOST_CHECK_EQUAL("xyzy", result);
}

 /* Problem:
 * Two paths overlaps each other
 * w=>x
 * x=>y
 * y=>z
 * u=>x
 * y=>s
 * s=>
 * z=>
 * Decision:
 * both paths are inluded in the result
 */
BOOST_AUTO_TEST_CASE(OverlappingPaths)
{
    std::stringstream ss;
    RoutePlanner sut;
    sut.addPoint("w", "x");
    sut.addPoint("x", "y");
    sut.addPoint("y", "z");
    sut.addPoint("u", "x");
    sut.addPoint("y", "s");
    sut.addEndPoint("s");
    sut.addEndPoint("z");
    sut.printPath(ss);
    sut.createSpanningTree();
    std::string result; // no initialization required
    ss >> result;
    BOOST_CHECK_EQUAL("wxyzuxys", result);
}



BOOST_AUTO_TEST_SUITE_END( )

} /* namespace routePlanner */
