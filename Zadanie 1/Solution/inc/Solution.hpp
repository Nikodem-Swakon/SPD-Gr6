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
    // std::vector<Task> m_rankedTasks;

public:
    /* public methods */
    //Solution (); //default constructor
    // Solution(double criterion, std::vector<Task> ranked);
    // Solution(const Solution &solution);
    // Solution &operator=(const Solution &solution) noexcept;
    // ~Solution();

    virtual void DisplaySolution() = 0;
    virtual void DisplayGanttChart() = 0;
    // virtual std::vector<Task> GetRankedTasks() const = 0 {return m_rankedTasks;} ;
    virtual int GetCriterion() const  = 0; // {return m_criterion;};

};
