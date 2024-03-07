#pragma once
#include <iostream>
#include <vector>

#include "Task.hpp"

class Solution
{
private:
    /* private data */
    int m_criterion;
    std::vector<Task> m_rankedTasks;

public:
    /* public methods */
    Solution(double criterion, std::vector<Task> ranked);
    Solution(const Solution &solution);
    Solution &operator=(const Solution &solution) noexcept;
    ~Solution();

    void DisplaySolution();
    void DisplayGanttChart();
};
