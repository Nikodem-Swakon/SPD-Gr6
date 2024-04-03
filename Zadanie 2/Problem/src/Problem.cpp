#include <algorithm>
#include "Problem.hpp"
#include "Heap.hpp"
#include "Node.hpp"

#include <iostream>
#include <chrono>

/* constructors and destructors */
Problem::Problem(std::vector<Task> tasks) : m_tasksNr(tasks.size())
{
    for (int i = 0; i < tasks.size(); i++)
    {
        Task *newTask = new (Task);
        *newTask = tasks[i];
        m_tasks.push_back(*newTask);
    }
}

Problem::~Problem()
{
    m_tasks.clear();
}

/* methods */

void Problem::DisplayTasks()
{
    std::cout << "Tasks in the problem." << std::endl;
    for (int i = 0; i < m_tasksNr; i++)
    {
        std::cout << "task: pj " << m_tasks[i].GetPj() << " rj " << m_tasks[i].GetRj() << " qj " << m_tasks[i].GetQj() << " taskId " << m_tasks[i].GetTaskId() << std::endl;
    }

    std::cout << "Number od tasks " << m_tasksNr << std::endl;
}

// it is example algorithm, just to test classes
Permutation Problem::ExampleAlgorith() const
{
    std::vector<Task> rankedTasks;

    for (int i = 0; i < m_tasksNr; i++)
    {
        rankedTasks.push_back(m_tasks[i]);
    }

    int criterion = CountCriterion(rankedTasks);

    Permutation solution(criterion, rankedTasks);

    return solution;
}


// it measures the criterion Cmax
int Problem::CountCriterion(std::vector<Task> rankedTasks) const
{
    int cMax = 0;
    int cooling = 0;
    for (int j = 0; j < rankedTasks.size(); j++)
    {
        int last = cMax;
        // criterium taking into account avaliability and execution time
        cMax = rankedTasks[j].GetPj() + std::max(cMax, rankedTasks[j].GetRj());

        cooling = cooling - (cMax - last);

        // take into counting cooling time
        if (cooling <= rankedTasks[j].GetQj())
            cooling = rankedTasks[j].GetQj();

        // if last task add colling time
        if (j == rankedTasks.size() - 1)
            cMax = cMax + cooling;
    }
    return cMax;
}

// it measures the criterion Cmax for solution as pair
int Problem::CountCriterion(std::vector<std::pair<Task, int>> rankedTasks) const
{

    int cMax = 0;
    int cooling = 0;
    int last = 0;

    for (int j = 0; j < rankedTasks.size(); j++)
    {

        if (j < rankedTasks.size() - 1)
        {
            cMax = rankedTasks[j + 1].second;
            last = rankedTasks[j].second;

            if (rankedTasks[j].first.GetPj() - (cMax - last) == 0)
            {
                cooling = cooling - (cMax - last);

                // take into counting cooling time
                if (cooling <= rankedTasks[j].first.GetQj())
                    cooling = rankedTasks[j].first.GetQj();
            }
        }
        else
        {
            cMax += rankedTasks[j].first.GetPj();
            cooling = cooling - rankedTasks[j].first.GetPj();

            // take into counting cooling time
            if (cooling <= rankedTasks[j].first.GetQj())
                cooling = rankedTasks[j].first.GetQj();

            if (j == rankedTasks.size() - 1)
                cMax = cMax + cooling;
        }
    }
    return cMax;
}
