#include "Problem.hpp"

Problem::Problem(std::vector<Task> tasks, int tasksNr) : m_tasks(tasks)
{
    for (int i = 0; i < tasksNr; i++)
    {
        Task *newTask = new (Task);
        m_tasks.push_back(*newTask);
    }
}

Problem::~Problem()
{
    m_tasks.clear();
}
