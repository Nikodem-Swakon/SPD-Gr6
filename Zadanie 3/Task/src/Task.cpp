#include "Task.hpp"

Task::Task() //: m_values()
{
}

Task::Task(const std::vector<int>& values, int id) : m_values(values), m_id(id)
{
}

Task::Task(const Task &task) : m_values(task.m_values), m_id(task.m_id)
{
}

Task::~Task()
{
}

Task &Task::operator=(const Task &task) noexcept
{
    if (this != &task) {
        m_values = task.m_values;
        m_id = task.m_id;
    }
    return *this;
}
