#pragma once
class Task
{
private:
    /* private data */
    double m_pj; // execution time
    double m_rj; // availability time
    double m_qj; // cooling time

public:
    /* public methods */
    Task();
    Task(double pj, double rj, double qj);
    Task(const Task& task);
    ~Task();
    Task &operator=(const Task &task) noexcept;

    double GetPj(){return m_pj;};
    double GetRj(){return m_rj;};
    double GetQj(){return m_qj;};
};
