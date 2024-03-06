#pragma once
#include <iostream>
#include <vector>
#include <fstream>

#include "Task.hpp"
#include "Solution.hpp"

class Problem
{
private:
    /* private data */
    std::vector<Task> m_tasks;
    int m_tasksNr;

    /* private methods */
    double CountCriterion(std::vector<Task> rankedTasks) const;

public:
    /* public methods */
    Problem(std::vector<Task> tasks);
    ~Problem();

    void GenerateInstance();
    void ReadFromFile(std::ifstream file);
    
    Solution AlgorithmSortRj() const;
    Solution AlgorithmSortQj() const;
    Solution AlgorithmCompleteReview() const;
    Solution ExampleAlgorith() const;     // TO BE DELETED  it is just simle example of algotithm method structure
    void DisplayTasks();
};
