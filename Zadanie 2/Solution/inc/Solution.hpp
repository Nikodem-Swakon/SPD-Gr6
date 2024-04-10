#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "Task.hpp"

#define MAX_LENGTH 10

class Solution
{
private:
    /* protected data */
    std::vector<Task> m_machine1;
    std::vector<Task> m_machine2;
    int m_criterion;

public:
    /* public methods */

    // void DisplaySolution();
    Solution(std::vector<Task> machine1, std::vector<Task> machine2, int criterion);
    ~Solution();
    Solution &operator=(const Solution &Solution) noexcept;

    int GetCriterion() const {return m_criterion;}
    void DisplaySolution();
    
    
    
};
