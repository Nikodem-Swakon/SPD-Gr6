#pragma once
class Task
{
private:
    /* private data */
    double m_pj;
    double m_rj;
    double m_qj;

public:
    /* public methods */
    Task();
    Task(double pj, double rj, double qj);
    ~Task();
};

Task::Task() : m_pj(0), m_rj(0), m_qj(0)
{
}

Task::Task(double pj, double rj, double qj) : m_pj(pj), m_rj(rj), m_qj(qj)
{
}

Task::~Task()
{
}
