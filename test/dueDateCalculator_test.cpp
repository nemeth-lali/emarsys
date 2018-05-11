/*
 * dueDateCalculator_test.cpp
 *
 *  Created on: May 11, 2018
 *      Author: lali
 */

#include "../src/dueDateCalculator.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <locale>
#include <ctime>
#include <iomanip>
#include <boost/test/unit_test.hpp>

namespace dueDateCalculator {

BOOST_AUTO_TEST_SUITE (DueDateCalculatorTest)

BOOST_AUTO_TEST_CASE(SimpleInput)
{
    std::string input = "2018-05-11T21:15:00";
    std::tm t = {};
    std::istringstream ss(input);
    ss >> std::get_time(&t, "%Y-%m-%dT%H:%M%S");
    std::mktime(&t);
    std::cout << std::asctime(&t);
}

BOOST_AUTO_TEST_CASE(MultipleDays)
{

}

BOOST_AUTO_TEST_CASE(LastDayOfMonth)
{
    tm submitDate;
    submitDate.tm_year = 2018;
    submitDate.tm_mon = 1;
    submitDate.tm_mday = 2018;
    submitDate.tm_year = 2018;
    submitDate.tm_year = 2018;
    submitDate.tm_year = 2018;
}

BOOST_AUTO_TEST_CASE(LastDayOfYear)
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
