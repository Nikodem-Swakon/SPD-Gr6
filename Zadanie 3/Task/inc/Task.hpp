#pragma once
#include <vector>
#include <iostream>
class Task
{
private:
    /* private data */
     // execution time
    std::vector<int> m_values;

public:
    /* public methods */
    Task();
    Task(const std::vector<int>& values);
    Task(const Task &task);
    ~Task();

    // Assignment operator
    Task &operator=(const Task &task) noexcept;

    // Getters and Setters
    const std::vector<int> &GetValues() const { return m_values; }
    int GetValuesSize() const {return m_values.size();}
    void SetValues(const std::vector<int> &values) { m_values = values; }

    // Access element
    int GetValueAt(size_t index) const { return m_values.at(index); }
    void SetValueAt(size_t index, int value) { m_values.at(index) = value; }

    // Operator overloads
    friend std::ostream &operator<<(std::ostream &out, const Task &task);
    friend bool operator==(const Task &task1, const Task &task2);
};

inline std::ostream &operator<<(std::ostream &out, const Task &task) {
    for (const auto &val : task.GetValues()) {
        out << val << " ";
    }
    return out;
}

inline bool operator==(const Task &task1, const Task &task2) {
    return task1.GetValues() == task2.GetValues();
}