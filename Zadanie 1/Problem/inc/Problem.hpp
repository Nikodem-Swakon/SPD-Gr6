#pragma once
#include <iostream>
#include <vector>
#include <fstream>

#include "Task.hpp"

class Problem
{
private:
    /* private data */
    std::vector<Task> m_tasks;
    int m_tasksNr;
public:
    /* public methods */
    Problem(std::vector<Task> tasks, int tasksNr);
    ~Problem();

    void GenerateInstance();
    void ReadFromFile(std::ifstream file);
    void AlgorithmSortRj();
    void AlgorithmSortQj();
    void AlgorithmCompleteReview();

};

Problem::Problem(std::vector<Task> tasks, int tasksNr) : m_tasks(tasks)
{
    for(int i = 0; i < tasksNr; i++)
    {
        Task *newTask = new(Task);
        m_tasks.push_back(*newTask);
    }
}

Problem::~Problem()
{
    m_tasks.clear();
}
