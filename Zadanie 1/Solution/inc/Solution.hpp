#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "Task.hpp"

#define MAX_LENGTH 10

class Solution
{
protected:
    /* protected data */
    int m_criterion;

public:
    /* public methods */

    virtual void DisplaySolution() = 0;
    virtual void DisplayGanttChart() = 0;
    virtual int GetCriterion() const  = 0; 
    

};
