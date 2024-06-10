#pragma once
#include <iostream>
#include <vector>
#include <fstream>

#include "Task.hpp"

#define CRITICAL_NUMBER 12

class bbNode;
class Problem
{
private:
    /* private data */
    std::vector<Task> m_tasks;
    int m_tasksNr;
    mutable int m_cMax;

    /* private methods */
    int calculateMakespan(const std::vector<Task> &sequence) const;
    void ShowNode(const bbNode &node) const;
    std::vector<std::vector<Task>> GetNeighborsAPEX(const std::vector<Task> vec); // APEX neighborhood

public:
    /* public methods */
    Problem(std::vector<Task> tasks);
    ~Problem();

    void GenerateInstance();
    void GetNextPerm(std::vector<Task> &vec) const;

    void DisplayTasks(const std::vector<Task> &vec);

    void TabuSearch(const std::vector<Task> &xInit, int maxIter, int tabuListSize);
};

int CalculateCMax(const std::vector<Task> &sequence);

