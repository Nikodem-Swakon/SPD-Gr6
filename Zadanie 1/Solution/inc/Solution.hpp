#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "Task.hpp"

class Solution
{
private:
    /* private data */
    int m_criterion;
    std::vector<Task> m_rankedTasks;

public:
    /* public methods */
    //Solution (); //default constructor
    Solution(double criterion, std::vector<Task> ranked);
    Solution(const Solution &solution);
    Solution &operator=(const Solution &solution) noexcept;
    ~Solution();

    void DisplaySolution();
    void DisplayGanttChart();
};
