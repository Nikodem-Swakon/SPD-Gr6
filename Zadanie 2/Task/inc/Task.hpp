#pragma once

#include <iostream>
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
    Task(const Task &task);
    ~Task();
    Task &operator=(const Task &task) noexcept;

    int GetPj() const { return m_pj; };
    int GetRj() const { return m_rj; };
    int GetQj() const { return m_qj; };
    int GetTaskId() const { return m_taskId; };

    void SetPj(int pj) { m_pj = pj; };
    void SetRj(int rj) { m_rj = rj; };
    void SetQj(int qj) { m_qj = qj; };
    void SetTaskId(int id) { m_taskId = id; };
};

inline std::ostream &operator<<(std::ostream &out, const Task &task)
{
    out << task.GetTaskId() << ":" << task.GetQj();
    return out;
};
inline bool operator<(const Task &task1, const Task &task2) { return task1.GetQj() < task2.GetQj(); }
inline bool operator>(const Task &task1, const Task &task2) { return task1.GetQj() > task2.GetQj(); }
inline bool operator==(const Task &task1, const Task &task2) {return    ( task1.GetPj() == task2.GetPj()) &&
                                                                        ( task1.GetRj() == task2.GetRj()) && 
                                                                        ( task1.GetQj() == task2.GetQj()) &&
                                                                        ( task1.GetTaskId() == task2.GetTaskId()); }
