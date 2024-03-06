#pragma once
class Task
{
private:
    /* private data */
    double m_pj; // execution time
    double m_rj; // availability time
    double m_qj; // cooling time
    int m_taskId;

public:
    /* public methods */
    Task();
    Task(double pj, double rj, double qj, int id);
    Task(const Task& task);
    ~Task();
    Task &operator=(const Task &task) noexcept;

    double GetPj(){return m_pj;};
    double GetRj(){return m_rj;};
    double GetQj(){return m_qj;};
    int GetTaskId(){return m_taskId;};

    void SetPj(double pj){ m_pj = pj;};
    void SetRj(double rj){ m_rj = rj;};
    void SetQj(double qj){ m_qj = qj;};
    void SetTaskId(double id){ m_taskId = id;};
};
