#include "Solution.hpp"
Solution::Solution(std::vector<Task> machine1, std::vector<Task> machine2, int criterion) : m_criterion(criterion)
{
    for (int i = 0; i < machine1.size(); i++)
    {
        m_machine1[i] = machine1[i];
        std::cout << "m_machine1 " << m_machine1[i] << std::endl;
    }

    for (int i = 0; i < machine2.size(); i++)
    {
        m_machine2[i] = machine2[i];
        std::cout << "m_machine2 " << m_machine2[i] << std::endl;
    }
}

Solution &Solution::operator=(const Solution &solution) noexcept
{
    std::cout << "Solution" << std::endl;;
    m_criterion = solution.m_criterion;

    m_machine1.clear();
    for (int i = 0; i < solution.m_machine1.size(); i++)
    {
        m_machine1.push_back(solution.m_machine1[i]);
        std::cout << m_machine1[i] << std::endl;
    }

    m_machine2.clear();
    for (int i = 0; i < solution.m_machine2.size(); i++)
    {
        m_machine2.push_back(solution.m_machine2[i]);
        std::cout << m_machine2[i] << std::endl;
    }

    return *this;
}

Solution::~Solution()
{
    m_machine1.clear();
    m_machine2.clear();
}

void Solution::DisplaySolution()
{
    std::cout << "1. machine:" << std::endl;
    for (int i = 0; i < m_machine1.size(); i++)
    {
        std::cout << "taskId " << m_machine1[i].GetTaskId() << " task: pj " << m_machine1[i].GetPj() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "2. machine:" << std::endl;
    for (int i = 0; i < m_machine2.size(); i++)
    {
        std::cout << "taskId " << m_machine2[i].GetTaskId() << " task: pj " << m_machine2[i].GetPj() << std::endl;
    }
    std::cout << std::endl;
}
