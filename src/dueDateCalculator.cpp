/*
 * dueDateCalculator.cpp
 *
 *  Created on: May 11, 2018
 *      Author: lali
 */

#include "dueDateCalculator.hpp"
#include <cstring>

namespace dueDateCalculator {

static const int WORKING_HOURS=8;
static const int MONDAY=1;
static const int FRIDAY=5;
static const int BEGINNING_OF_WORKDAY=9;
static const int END_OF_WORKDAY=17;
static const time_t ONE_DAY = 24 * 60 * 60 ;


tm DueDateCalculator::calculateDueDate(const tm& submitDate, const float turnAroundTime)
{
    if(!isWorkingTime(submitDate))
    {
        tm retVal;
        ::memset(&retVal,-1, sizeof(retVal)); // fastest way to set all members to -1
        return retVal;
    }

    //int extradays = turnAroundTime % WORKING_HOURS;
    //float remainingHours = turnAroundTime / WORKING_HOURS;
    //addDays(submitDate, extradays);
    tm retVal = submitDate;
    retVal.tm_hour += turnAroundTime;
    return retVal;
}

bool DueDateCalculator::isWorkingTime(const tm& submitDate)
{
    return (MONDAY <= submitDate.tm_wday && submitDate.tm_wday <=FRIDAY)  &&
           (BEGINNING_OF_WORKDAY <= submitDate.tm_hour && submitDate.tm_hour <= END_OF_WORKDAY);
}

}
