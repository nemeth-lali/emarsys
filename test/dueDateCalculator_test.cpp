/*
 * dueDateCalculator_test.cpp
 *
 *  Created on: May 11, 2018
 *      Author: lali
 */

#include "../src/dueDateCalculator.hpp"

#include <boost/test/unit_test.hpp>

namespace dueDateCalculator {

BOOST_AUTO_TEST_SUITE (DueDateCalculatorTest)

BOOST_AUTO_TEST_CASE(SimpleInput)
{

}

BOOST_AUTO_TEST_CASE(MultipleDays)
{

}

///Faulty cases
BOOST_AUTO_TEST_CASE(EarlierThanNow)
{

}

BOOST_AUTO_TEST_CASE(TimeOutOfWorkingHoursEarly)
{

}

BOOST_AUTO_TEST_CASE(TimeOutOfWorkingHoursLate)
{

}

BOOST_AUTO_TEST_CASE(Weekend)
{

}

BOOST_AUTO_TEST_SUITE_END( )

} /* namespace dueDateCalculator */
