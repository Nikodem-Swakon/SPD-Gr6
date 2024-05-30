#include "Task.hpp"

Task::Task() //: m_values()
{
}

Task::Task(const std::vector<int>& values) : m_values(values)
{
}

Task::Task(const Task &task) : m_values(task.m_values)
{
}

Task::~Task()
{
}

Task &Task::operator=(const Task &task) noexcept
{
    if (this != &task) {
        m_values = task.m_values;
    }
    return *this;
}
