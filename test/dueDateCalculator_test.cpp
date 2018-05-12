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
    //sec min hour day month year
    std::tm t = {0,15,9,11,4,118};//C++ standard says: 1900 + tm_year = current year
    std::mktime(&t);
    t.tm_hour = 9;//mktime uses local time and interprets date as UTC
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL("Fri May 11 11:15:00 2018\n", std::asctime(&result));
}

BOOST_AUTO_TEST_CASE(NextDay)
{
    //sec min hour day month year
    std::tm t = {0,15,14,10,4,118};//C++ standard says: 1900 + tm_year = current year
    std::mktime(&t);
    t.tm_hour = 14;//mktime uses local time and interprets date as UTC
    tm result = DueDateCalculator::calculateDueDate(t, 5);
    BOOST_CHECK_EQUAL("Fri May 11 11:15:00 2018\n", std::asctime(&result));
}

BOOST_AUTO_TEST_CASE(MultipleDays)
{
    //sec min hour day month year
    std::tm t = {0,15,9,11,4,118};//C++ standard says: 1900 + tm_year = current year
    std::mktime(&t);
    t.tm_hour = 9;//mktime uses local time and interprets date as UTC
    tm result = DueDateCalculator::calculateDueDate(t, 42);
    BOOST_CHECK_EQUAL("Fri May 16 11:15:00 2018", std::asctime(&result));
}

BOOST_AUTO_TEST_CASE(LastDayOfMonth)
{
    //sec min hour day month year
    std::tm t = {0,15,16,31,4,118};//C++ standard says: 1900 + tm_year = current year
    std::mktime(&t);
    t.tm_hour = 16;//mktime uses local time and interprets date as UTC
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL("Fri Jun 01 10:15:00 2018", std::asctime(&result));
}

BOOST_AUTO_TEST_CASE(LastDayOfYear)
{
    //sec min hour day month year
    std::tm t = {0,15,16,31,11,118};//C++ standard says: 1900 + tm_year = current year //Monday
    std::mktime(&t);
    t.tm_hour = 16;//mktime uses local time and interprets date as UTC
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL("Tue Jan 01 10:15:00 2019", std::asctime(&result));
}

BOOST_AUTO_TEST_CASE(FridayCase)
{
    //sec min hour day month year
    std::tm t = {0,15,16,11,4,118};//C++ standard says: 1900 + tm_year = current year //Friday
    std::mktime(&t);
    t.tm_hour = 16;//mktime uses local time and interprets date as UTC
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL("Mon May 14 10:15:00 2018", std::asctime(&result));
}

BOOST_AUTO_TEST_CASE(TimeOfWorkingHoursLast1Sec)
{
    //sec min hour day month year
    std::tm t = {59,59,14,10,4,118};//C++ standard says: 1900 + tm_year = current year //Thursday
    std::mktime(&t);
    t.tm_hour = 14;//mktime uses local time and interprets date as UTC
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK_EQUAL("Thu May 10 16:59:59 2018", std::asctime(&result));
}

static const tm invalidsubmitDate{-1,-1,-1,-1,-1,-1};

//no const comparison exists for tm type
static bool operator==(const tm& lhs, const tm& rhs)
{
    return lhs.tm_hour == rhs.tm_hour && lhs.tm_mday == rhs.tm_mday &&
            lhs.tm_min == rhs.tm_min && lhs.tm_mday == rhs.tm_mday &&
            lhs.tm_year == rhs.tm_year && lhs.tm_mon == rhs.tm_mon;
}
///Faulty cases
BOOST_AUTO_TEST_CASE(TimeOutOfWorkingHoursEarly)
{
    //sec min hour day month year
    std::tm t = {59,59,8,10,4,118};//C++ standard says: 1900 + tm_year = current year
    std::mktime(&t);
    t.tm_hour = 8;//mktime uses local time and interprets date as UTC
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK(invalidsubmitDate == result);
}

BOOST_AUTO_TEST_CASE(TimeOutOfWorkingHoursLate)
{
    //sec min hour day month year
    std::tm t = {59,59,18,10,4,118};//C++ standard says: 1900 + tm_year = current year //Thursday
    std::mktime(&t);
    t.tm_hour = 18;//mktime uses local time and interprets date as UTC
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK(invalidsubmitDate == result);
}

BOOST_AUTO_TEST_CASE(TimeOutOfWorkingHoursLate1Sec)
{
    std::string input = "2018-05-10T17:00:01";
    //sec min hour day month year
    std::tm t = {1,0,17,10,4,118};//C++ standard says: 1900 + tm_year = current year //Thursday
    std::mktime(&t);
    t.tm_hour = 17;//mktime uses local time and interprets date as UTC
    const tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK(invalidsubmitDate == result);
}

BOOST_AUTO_TEST_CASE(Weekend)
{
    //sec min hour day month year
    std::tm t = {59,59,14,12,4,118};//C++ standard says: 1900 + tm_year = current year //Thursday
    std::mktime(&t);
    t.tm_hour = 14;//mktime uses local time and interprets date as UTC
    tm result = DueDateCalculator::calculateDueDate(t, 2);
    BOOST_CHECK(invalidsubmitDate == result);
}

BOOST_AUTO_TEST_SUITE_END ()

} /* namespace dueDateCalculator */
