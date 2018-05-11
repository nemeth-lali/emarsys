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

tm DueDateCalculator::calculateDueDate(const tm& submitDate, const float turnAroundTime)
{
    static const time_t ONE_DAY = 24 * 60 * 60 ;
    if(submitDate.tm_wday >=6 || !(9 < submitDate.tm_hour && submitDate.tm_hour <17))
    {
        tm retVal;
        ::memset(&retVal,-1, sizeof(retVal)); // fastest way to set all members to -1
        return retVal;
    }

    tm retVal = submitDate;
    retVal.tm_hour += turnAroundTime;
    return retVal;

}

}
