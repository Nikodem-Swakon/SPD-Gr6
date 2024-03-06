#include "Solution.hpp"

Solution::Solution(double criterion, std::vector<double> ranked) : m_criterion(criterion)
{
    for (int i = 0; i < ranked.size(); i++)
    {
        m_ranked.push_back(ranked[i]);
    }
}

Solution::Solution(Solution &solution) : m_criterion(solution.m_criterion)
{
    for (int i = 0; i < solution.m_ranked.size(); i++)
    {
        m_ranked.push_back(solution.m_ranked[i]);
    }
}

Solution::~Solution()
{
}
