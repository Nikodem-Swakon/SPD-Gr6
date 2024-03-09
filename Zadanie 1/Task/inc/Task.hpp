#pragma once
class Task
{
private:
    /* private data */
    int m_pj; // execution time
    int m_rj; // availability time
    int m_qj; // cooling time
    int m_taskId;

public:
    /* public methods */
    Task();
    Task(int pj, int rj, int qj, int id);
    Task(const Task& task);
    ~Task();
    Task &operator=(const Task &task) noexcept;

    int GetPj() const {return m_pj;};
    int GetRj() const {return m_rj;};
    int GetQj() const {return m_qj;};
    int GetTaskId() const {return m_taskId;};

    void SetPj(int pj){ m_pj = pj;};
    void SetRj(int rj){ m_rj = rj;};
    void SetQj(int qj){ m_qj = qj;};
    void SetTaskId(int id){ m_taskId = id;};
};
