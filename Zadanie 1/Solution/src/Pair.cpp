#include "Pair.hpp"
#include <iomanip> // setw

Pair::Pair(double criterion, std::vector<std::pair<Task, int>> ranked)
{
    m_criterion = criterion;
    m_rankedTasks = ranked;
}

Pair::Pair(const Pair &pair)
{
    m_criterion = pair.GetCriterion();
    m_rankedTasks = pair.GetRankedTasks();
}

Pair &Pair::operator=(const Pair &pair) noexcept
{
    m_criterion = pair.GetCriterion();
    m_rankedTasks = pair.GetRankedTasks();

    return *this;
}

void Pair::DisplaySolution()
{
    std::cout << "( Task_ID , Start time ):" << std::endl;
    for (const auto &pair : m_rankedTasks)
    {
        std::cout << "(" << pair.first.GetTaskId() << ", " << pair.second << ")" << std::endl;
    }

    std::cout << "Criterion: " << m_criterion << std::endl;
}

void Pair::DisplayGanttChart()
{
    // Gantts chart

    std::cout << "------------------- Gantt chart  -------------------" << std::endl;
    for (int i = 0; i < m_rankedTasks.size(); i++)
    {
        std::cout << std::endl
                  << "Task nr " << m_rankedTasks[i].first << "]" << std::setw(MAX_LENGTH);
        // int Cmax=0;
        for (int j = 0; j < m_rankedTasks[i].second; j++)
        {
            std::cout << " ";
        }

        if (i < m_rankedTasks.size() - 1)
        {
            for (int x = 0; x < m_rankedTasks[i + 1].second - m_rankedTasks[i].second; x++)
            {
                std::cout << "%";
            }
        }
        else
        {
            for (int x = 0; x < m_rankedTasks[i].second; x++)
            {
                std::cout << "%";
            }
        }
    }

    std::cout << std::endl;
}

Pair::~Pair()
{
}
