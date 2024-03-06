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
    Task(double pj, double rj, double qj);
    ~Task();
};

Task::Task(double pj, double rj, double qj) : m_pj(pj), m_rj(rj), m_qj(qj)
{
}

Task::~Task()
{
}
