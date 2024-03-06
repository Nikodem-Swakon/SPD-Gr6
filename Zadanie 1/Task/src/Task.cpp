#include "Task.hpp"

Task::Task() : m_pj(0), m_rj(0), m_qj(0)
{
}

Task::Task(double pj, double rj, double qj) : m_pj(pj), m_rj(rj), m_qj(qj)
{
}

Task::~Task()
{
}

Task &Task::operator=(const Task &task)
{
    m_pj = task.m_pj;
    m_rj = task.m_rj;
    m_qj = task.m_qj;

    return *this;
}
