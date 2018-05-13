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
static const int BEGINNING_OF_WORK = 9;
static const int END_OF_WORK_HOUR = 17;
static const int MINUTES_IN_HOUR = 60;
static const time_t ONE_DAY = 24 * 60 * 60;

tm DueDateCalculator::calculateDueDate(const tm& submitDate, const float turnAroundTime)
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
    retVal &= (BEGINNING_OF_WORK <= submitDate.tm_hour && submitDate.tm_hour < END_OF_WORK_HOUR);
    return retVal;
}

void DueDateCalculator::addDays(tm& submitDate, int days)
{
    time_t date_seconds = mktime( &submitDate ) + (days * ONE_DAY);
    submitDate = *localtime( &date_seconds );
}

void DueDateCalculator::calculateAndAddRequiredAmountOfWorkDays(tm& submitDate, float turnAroundTime)
{
   int requiredAmountOfWorkDays = static_cast<int>(turnAroundTime) / WORKING_HOURS;
   float requiredAmountOfTime = turnAroundTime - (requiredAmountOfWorkDays * WORKING_HOURS);

   int minutes= static_cast<int>(MINUTES_IN_HOUR * (requiredAmountOfTime - static_cast<int>(requiredAmountOfTime)));
   int remainingTimeInMinutes = static_cast<int>(requiredAmountOfTime * 60 + minutes);

   if(remainingTimeInMinutes + submitDate.tm_hour * MINUTES_IN_HOUR + submitDate.tm_min >= END_OF_WORK_HOUR * MINUTES_IN_HOUR)
   {
       remainingTimeInMinutes -= ((END_OF_WORK_HOUR * MINUTES_IN_HOUR) - (submitDate.tm_hour * MINUTES_IN_HOUR + submitDate.tm_min));
       submitDate.tm_hour = BEGINNING_OF_WORK;
       submitDate.tm_min = 0;
       ++requiredAmountOfWorkDays;
   }
   submitDate.tm_min += remainingTimeInMinutes % MINUTES_IN_HOUR;
   submitDate.tm_hour += remainingTimeInMinutes / MINUTES_IN_HOUR + (submitDate.tm_min / MINUTES_IN_HOUR);
   submitDate.tm_min %= MINUTES_IN_HOUR;

   if(requiredAmountOfWorkDays)
   {
       addDays(submitDate, requiredAmountOfWorkDays+addWeekendDays(submitDate, requiredAmountOfWorkDays));
   }
}

int DueDateCalculator::addWeekendDays(const tm&submitDate, int requiredWorkDays)
{
    int retVal = 0;
    return retVal;
}

}
