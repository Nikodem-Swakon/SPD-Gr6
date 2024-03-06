#include "Solution.hpp"

/* constructors and destructors */

Solution::Solution(double criterion, std::vector<Task> ranked) : m_criterion(criterion)
{
    for (int i = 0; i < ranked.size(); i++)
    {
        m_rankedTasks.push_back(ranked[i]);
    }
}

Solution::Solution(const Solution &solution) : m_criterion(solution.m_criterion)
{
    for (int i = 0; i < solution.m_rankedTasks.size(); i++)
    {
        m_rankedTasks.push_back(solution.m_rankedTasks[i]);
    }
}

Solution::~Solution()
{
}

Solution &Solution::operator=(const Solution &solution) noexcept
{
    m_criterion = solution.m_criterion;
    for (int i = 0; i > solution.m_rankedTasks.size(); i++)
    {
        m_rankedTasks.push_back(solution.m_rankedTasks[i]);
    }
    return *this;
}

/* methods */

void Solution::DisplaySolution()
{
    std::cout << "Tasks in the solution." << std::endl;
    for (int i = 0; i < m_rankedTasks.size(); i++)
    {
        std::cout << "task: pj " << m_rankedTasks[i].GetPj() << " rj " << m_rankedTasks[i].GetRj() << " qj " << m_rankedTasks[i].GetQj() << " taskId " << m_rankedTasks[i].GetTaskId() << std::endl;
    }

    std::cout << "Criterion  " << m_criterion << std::endl;
}
