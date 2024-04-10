#include "Task.hpp"

Task::Task() : m_pj(0), m_taskId(0)
{
}

Task::Task(int pj,int id) : m_pj(pj), m_taskId(id)
{
}

Task::Task(const Task &task) : m_pj(task.m_pj), m_taskId(task.m_taskId)
{
}

Task::~Task()
{
}

Task &Task::operator=(const Task &task) noexcept
{
    m_pj = task.m_pj;
    m_taskId = task.m_taskId;

    return *this;
}
