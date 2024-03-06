#include "Task.hpp"

Task::Task() : m_pj(0), m_rj(0), m_qj(0), m_taskId(0)
{
}

Task::Task(double pj, double rj, double qj, int id) : m_pj(pj), m_rj(rj), m_qj(qj), m_taskId(id)
{
}

Task::Task(const Task &task) : m_pj(task.m_pj), m_rj(task.m_rj), m_qj(task.m_qj), m_taskId(task.m_taskId)
{
}

Task::~Task()
{
}

Task &Task::operator=(const Task &task) noexcept
{
    m_pj = task.m_pj;
    m_rj = task.m_rj;
    m_qj = task.m_qj;
    m_taskId = task.m_taskId;

    return *this;
}
