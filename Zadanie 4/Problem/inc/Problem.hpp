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

public:
    /* public methods */
    Problem(std::vector<Task> tasks);
    ~Problem();

    void GenerateInstance();
    void GetNextPerm(std::vector<Task> &vec) const;

    void DisplayTasks();
};

int CalculateCMax(const std::vector<Task> &sequence);

struct bbNode
{
    unsigned int lev; // num of machine in the queue
    std::vector<Task> permutation;
    int cost; // time of executing tasks

    bbNode(const std::vector<Task> &perm, unsigned int level)
        : lev(level), permutation(perm)
    {
        if (level != 0)
        {
            std::vector<Task> subvector(permutation.begin(), permutation.begin() + level);
            cost = CalculateCMax(subvector);
        }
        else
        {
            cost = 0;
        }
    }
};
