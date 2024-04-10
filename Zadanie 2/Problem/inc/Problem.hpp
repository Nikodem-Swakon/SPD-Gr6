#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>  //pair

#include "Task.hpp"
#include "Solution.hpp"

#define CRITICAL_NUMBER 12

class Node;
class Problem
{
private:
    /* private data */
    std::vector<Task> m_tasks;
    std::vector<Task> m_machine1;   // tasks ranked on first machine
    std::vector<Task> m_machine2;   // tasks ranked on second machine
    int m_tasksNr;

    /* private methods */
    Node CreateNodeQj(int lowBarier, Node parent, int upBarier) const;
    Node CreateNodeRj(int lowBarier, Node parent, int upBarier) const;
    int CountCriterionOnTheMachine(std::vector<Task> machine) const;

public:
    /* public methods */
    Problem(std::vector<Task> tasks);
    ~Problem();

    void GenerateInstance();
    void DisplayTasks();
    Solution LsaAlgorithm();
};
