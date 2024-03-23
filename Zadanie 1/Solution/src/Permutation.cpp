#include "Permutation.hpp"

#include <algorithm>
#include <iostream>
#include <cstring>
#include <iomanip>

/* constructors and destructors */

//permutation::permutation(){} //default constructor

Permutation::Permutation(double criterion, std::vector<Task> ranked)
{
    m_criterion = criterion;
    for (int i = 0; i < ranked.size(); i++)
        m_rankedTasks.push_back(ranked[i]);
}

Permutation::Permutation(const Permutation &permutation) 
{
    m_criterion = permutation.m_criterion;
    m_rankedTasks.clear();
    for (int i = 0; i < permutation.m_rankedTasks.size(); i++)
    {
        m_rankedTasks.push_back(permutation.m_rankedTasks[i]);
    }
}

Permutation::~Permutation()
{
}

Permutation &Permutation::operator=(const Permutation &permutation) noexcept
{
    m_criterion = permutation.m_criterion;
    
    m_rankedTasks.clear();
    for (int i = 0; i < permutation.m_rankedTasks.size(); i++)
    {
        m_rankedTasks.push_back(permutation.m_rankedTasks[i]);
            }
        return *this;
}

/* methods */

void Permutation::DisplaySolution()
{
    std::cout << "Tasks in the permutation." << std::endl;
    std::cout<<"ID||RJ||PJ||QJ"<<std::endl;
    for (int i = 0; i < m_rankedTasks.size(); i++)
    {
        std::cout <<" "<<  m_rankedTasks[i].GetTaskId() <<"  "<<m_rankedTasks[i].GetRj() <<"  "<<m_rankedTasks[i].GetPj() <<"  "<<  m_rankedTasks[i].GetQj()<< std::endl;
    }

    std::cout << "Criterion  " << m_criterion << std::endl;
}

void Permutation::DisplayGanttChart()
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
