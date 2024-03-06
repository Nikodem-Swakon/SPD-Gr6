#pragma once
#include <iostream>
#include <vector>
class Solution
{
private:
    /* private data */
    double m_criterion;
    std::vector<double> m_ranked;

public:
    /* public methods */
    Solution(double m_criterion, std::vector<double> ranked);
    Solution(Solution &solution);
    ~Solution();
};
