#include "Solution.hpp"

#include <algorithm>
#include <iostream>
#include <cstring>
#include <iomanip>

/* constructors and destructors */

Solution::Solution(double criterion, std::vector<Task> ranked) : m_criterion(criterion)
{
    for (int i = 0; i < ranked.size(); i++)
    {
        m_rankedTasks.push_back(ranked[i]);
        std::cout << ranked[i].GetTaskId();
    }
    std::cout << std::endl;
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
    
    m_rankedTasks.clear();
    for (int i = 0; i < solution.m_rankedTasks.size(); i++)
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

void Solution::DisplayGanttChart()
{
    int cMax = 0;
    std::cout << "------------------- Gantt chart  -------------------" << std::endl;
    for (const auto &task : m_rankedTasks)
    {
        std::cout << "Task nr " << task.GetTaskId() << "]" << std::setw(MAX_LENGTH);

        for (int x = 0; x < task.GetRj(); x++)
        {
            std::cout << " ";
        }

        for (int j = 0; j < cMax - task.GetRj(); j++)
        {
            std::cout << "_";
        }

        for (int j = 0; j < task.GetPj(); j++)
        {
            std::cout << "%";
        }

        for (int k = 0; k < task.GetQj(); k++)
        {
            std::cout << "-";
        }
        std::cout << std::endl;

        cMax = task.GetPj() + std::max(cMax, task.GetRj()); // it DOESN'T contain cooling time
    }
    // display criterion time
    std::cout << "criterion " << std::setw(MAX_LENGTH);
    for(int i = 0; i < m_criterion; i++)
        std::cout << "=";
    std::cout << std::endl;

    std::cout << "----------------------------------------------------" << std::endl;
}
