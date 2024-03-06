#include "Problem.hpp"

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
        std::cout << "task2: pj " << m_tasks[i].GetPj() << " rj " << m_tasks[i].GetRj() << " qj " << m_tasks[i].GetQj() << std::endl;
    }

    std::cout << "Number od tasks " << m_tasksNr << std::endl;
}