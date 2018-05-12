/*
 * dueDateCalculator.hpp
 *
 *  Created on: May 11, 2018
 *      Author: lali
 */

#pragma once
#include <ctime> // In c++20 there are better date and time handling functions

namespace dueDateCalculator {

/*
 *  Assumption: Submit date is submit date and time
 *  Decision: Sunday is the first day of the week (Use the UK style not Hungarian)
 *  Your task is to implement the CalculateDueDate method, which takes the submit date and
 *  turnaround time as an input and returns the date and time when the issue is to be resolved.
 */
class DueDateCalculator {
public:

    /**
     * @brief Adds the given turnAroundTime as hours to the submit date
     * @param submitDate Issue submit date and time
     * @param turnAroundTime Turn around time of the issue
     * @return The expected delivery time of the issue -1 in tm_hour if the time is out of working hours or day
     */
    static tm calculateDueDate(const tm& submitDate, const float turnAroundTime);
private:
    static bool isWorkingTime(const tm& submitDate);
};

} /* namespace dueDateCalculator */
