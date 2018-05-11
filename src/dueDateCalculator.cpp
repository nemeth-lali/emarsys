/*
 * dueDateCalculator.cpp
 *
 *  Created on: May 11, 2018
 *      Author: lali
 */

#include "dueDateCalculator.hpp"
#include <cstring>

namespace dueDateCalculator {

tm DueDateCalculator::calculateDueDate(const tm& submitDate, const float turnAroundTime)
{
    tm retVal = submitDate;
    if(submitDate.tm_wday >=6 || !(9 < submitDate.tm_hour && submitDate.tm_hour <17))
    {
        ::memset(&retVal,-1, sizeof(retVal)); // fastest way to set all members to -1
    }
    return retVal;

}

}
