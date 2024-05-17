#include "Permutation.hpp"

#include <algorithm>
#include <iostream>
#include <cstring>
#include <iomanip>

/* constructors and destructors */

Permutation::Permutation() {} // default constructor

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

/*void Permutation::DisplaySolution()
{
    std::cout << "Tasks in the permutation." << std::endl;
    std::cout << "ID||PJ" << std::endl;
    for (int i = 0; i < m_rankedTasks.size(); i++)
    {
        std::cout << " " << m_rankedTasks[i].GetTaskId() << "  " << m_rankedTasks[i].GetPj() << std::endl;
    }

    std::cout << "Criterion  " << m_criterion << std::endl;
}
*/
std::vector<Task> Permutation::GetRankedTasks() const
{
    return m_rankedTasks;
}

Task Permutation::GetElem(int id) const
{
    return m_rankedTasks[id];
}
