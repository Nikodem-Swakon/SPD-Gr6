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
    Problem(std::vector<Task> tasks);
    ~Problem();

    void GenerateInstance();
    void ReadFromFile(std::ifstream file);
    void AlgorithmSortRj();
    void AlgorithmSortQj();
    void AlgorithmCompleteReview();
    void DisplayTasks();
};
