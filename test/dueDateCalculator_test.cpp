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
    std::string input = "2018-05-11T09:15:00";
    std::tm t = {};
    std::istringstream ss(input);
    ss >> std::get_time(&t, "%Y-%m-%dT%H:%M%S");
    std::mktime(&t);
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL("Fri May 11 11:15:00 2018", std::asctime(&t));
}

BOOST_AUTO_TEST_CASE(MultipleDays)
{
    std::string input = "2018-05-10T09:15:00";//Thursday
    std::tm t = {};
    std::istringstream ss(input);
    ss >> std::get_time(&t, "%Y-%m-%dT%H:%M%S");
    std::mktime(&t);
    tm result = DueDateCalculator::calculateDueDate(t, 42);
    BOOST_CHECK_EQUAL("Fri May 16 11:15:00 2018", std::asctime(&t));
}

BOOST_AUTO_TEST_CASE(LastDayOfMonth)
{
    std::string input = "2018-05-31T16:15:00";//Thursday
    std::tm t = {};
    std::istringstream ss(input);
    ss >> std::get_time(&t, "%Y-%m-%dT%H:%M%S");
    std::mktime(&t);
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL("Fri Jun 01 10:15:00 2018", std::asctime(&t));
}

BOOST_AUTO_TEST_CASE(LastDayOfYear)
{
    std::string input = "2018-12-31T16:15:00";//Monday
    std::tm t = {};
    std::istringstream ss(input);
    ss >> std::get_time(&t, "%Y-%m-%dT%H:%M%S");
    std::mktime(&t);
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL("Tue Jan 01 10:15:00 2019", std::asctime(&t));
}

BOOST_AUTO_TEST_CASE(FridayCase)
{
    std::string input = "2018-05-11T16:15:00";//Friday
    std::tm t = {};
    std::istringstream ss(input);
    ss >> std::get_time(&t, "%Y-%m-%dT%H:%M%S");
    std::mktime(&t);
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL("Mon May 14 10:15:00 2018", std::asctime(&t));
}

BOOST_AUTO_TEST_CASE(HalfHourCase)
{
    std::string input = "2018-05-11T16:15:00";//Friday
    std::tm t = {};
    std::istringstream ss(input);
    ss >> std::get_time(&t, "%Y-%m-%dT%H:%M%S");
    std::mktime(&t);
    tm result = DueDateCalculator::calculateDueDate(t, 2.5);
    BOOST_CHECK_EQUAL("Mon May 14 10:45:00 2018", std::asctime(&t));
}

///Faulty cases
BOOST_AUTO_TEST_CASE(TimeOutOfWorkingHoursEarly)
{
    std::string input = "2018-05-10T08:15:00";
    std::tm t = {};
    std::istringstream ss(input);
    ss >> std::get_time(&t, "%Y-%m-%dT%H:%M%S");
    std::mktime(&t);
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL(-1, result.tm_hour);
}

BOOST_AUTO_TEST_CASE(TimeOutOfWorkingHoursLate)
{
    std::string input = "2018-05-10T18:15:00";
    std::tm t = {};
    std::istringstream ss(input);
    ss >> std::get_time(&t, "%Y-%m-%dT%H:%M%S");
    std::mktime(&t);
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL(-1, result.tm_hour);
}

BOOST_AUTO_TEST_CASE(Weekend)
{
    std::string input = "2018-05-12T09:15:00";
    std::tm t = {};
    std::istringstream ss(input);
    ss >> std::get_time(&t, "%Y-%m-%dT%H:%M%S");
    std::mktime(&t);
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL(-1, result.tm_hour);
}

BOOST_AUTO_TEST_SUITE_END( )

} /* namespace dueDateCalculator */
