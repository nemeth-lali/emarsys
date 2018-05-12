/*
 * dueDateCalculator.cpp
 *
 *  Created on: May 11, 2018
 *      Author: lali
 */

#include "dueDateCalculator.hpp"
#include <cstring>

namespace dueDateCalculator {

static const int WORKING_HOURS = 8;
static const int MONDAY = 1;
static const int FRIDAY = 5;
static const int BEGINNING_OF_WORKDAY = 9;
static const int END_OF_WORKDAY = 17;
static const time_t ONE_DAY = 24 * 60 * 60;

tm DueDateCalculator::calculateDueDate(const tm& submitDate, const int turnAroundTime)
{
    if (!isWorkingTime(submitDate)) {
        return invalidsubmitDate;
    }

    tm retVal = submitDate;
    calculateAndAddRequiredAmountOfWorkDays(retVal, turnAroundTime);
    return retVal;
}

bool DueDateCalculator::isWorkingTime(const tm& submitDate)
 {
    bool retVal = (MONDAY <= submitDate.tm_wday && submitDate.tm_wday <= FRIDAY);
    retVal &= (BEGINNING_OF_WORKDAY <= submitDate.tm_hour && submitDate.tm_hour < END_OF_WORKDAY);
    return retVal;
}

void DueDateCalculator::addDays(tm& submitDate, int days)
{
    time_t date_seconds = mktime( &submitDate ) + (days * ONE_DAY);
    submitDate = *localtime( &date_seconds );
}

void DueDateCalculator::calculateAndAddRequiredAmountOfWorkDays(tm& submitDate, int turnAroundTime)
{
    int requiredAmountOfWorkDays = turnAroundTime / WORKING_HOURS;
    int requiredHours = turnAroundTime % WORKING_HOURS;
    int overFlowTime = submitDate.tm_hour + requiredHours - END_OF_WORKDAY;
    if(overFlowTime > 0)
    {
        ++requiredAmountOfWorkDays;
        submitDate.tm_hour = BEGINNING_OF_WORKDAY + overFlowTime;
    }
    else
    {
        submitDate.tm_hour += turnAroundTime;
    }
    addDays(submitDate, requiredAmountOfWorkDays);
}

int DueDateCalculator::addWeekendDays(const tm&submitDate, int requiredWorkDays)
{
    int retVal = 0;
    return retVal;
}

}
