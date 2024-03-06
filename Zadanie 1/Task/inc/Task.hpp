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
    Task & operator = (const Task * task);
};

