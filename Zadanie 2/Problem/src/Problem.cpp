#include <algorithm>
#include "Problem.hpp"

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
        std::cout << "taskId " << m_tasks[i].GetTaskId() << " task: pj " << m_tasks[i].GetPj() << std::endl;
    }

    std::cout << "Number od tasks " << m_tasksNr << std::endl;
}

// count sum of pj on the machine
int Problem::CountCriterionOnTheMachine(std::vector<Task> machine) const
{
    int sum = 0;
    for (int i = 0; i < machine.size(); i++)
    {
        sum += machine[i].GetPj();
    }
    std::cout << "policzne" << std::endl;
    return sum;
}

Solution Problem::LsaAlgorithm()
{
    std::cout << "LsaAlgorithm" << std::endl;
    for (int i = 0; i < m_tasks.size(); i++)
    {
        if (CountCriterionOnTheMachine(m_machine1) < CountCriterionOnTheMachine(m_machine2))
        {
            m_machine1.push_back(m_tasks[i]);
        }
        else
        {
            m_machine2.push_back(m_tasks[i]);
        }
    }

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

    Solution solution(m_machine1, m_machine2, std::max(CountCriterionOnTheMachine(m_machine1), CountCriterionOnTheMachine(m_machine2)));

    m_machine1.clear();
    m_machine2.clear();

    return solution;
}
