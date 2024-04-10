#pragma once

#include <iostream>
class Task
{
private:
    /* private data */
    int m_pj; // execution time
    int m_taskId;

public:
    /* public methods */
    Task();
    Task(int pj,int id);
    Task(const Task &task);
    ~Task();
    Task &operator=(const Task &task) noexcept;

    int GetPj() const { return m_pj; };
    int GetTaskId() const { return m_taskId; };

    void SetPj(int pj) { m_pj = pj; };
    void SetTaskId(int id) { m_taskId = id; };
};

inline std::ostream &operator<<(std::ostream &out, const Task &task)
{
    out << task.GetTaskId();
    return out;
};
inline bool operator==(const Task &task1, const Task &task2) {return    ( task1.GetPj() == task2.GetPj()) &&
                                                                        ( task1.GetTaskId() == task2.GetTaskId()); }
