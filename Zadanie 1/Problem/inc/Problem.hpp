#pragma once
#include <iostream>
#include <vector>
#include <fstream>

#include "Task.hpp"
#include "Solution.hpp"

#define CRITICAL_NUMBER 12

class Problem
{
private:
    /* private data */
    std::vector<Task> m_tasks;
    int m_tasksNr;

    /* private methods */
    int CountCriterion(std::vector<Task> rankedTasks) const;
    std::vector<Task> CompleteReview(std::vector<Task> tasks, int untilTask, int criterion) const;

public:
    /* public methods */
    Problem(std::vector<Task> tasks);
    ~Problem();

    void GenerateInstance();
    Solution AlgorithmSortRj() const;
    Solution AlgorithmSortQj() const;
    Solution AlgorithmCompleteReview() const;
    Solution ExampleAlgorith() const; // TO BE DELETED  it is just simle example of algotithm method structure
    Solution AlgorithmSchrage() const;
    Solution AlgorithmSchrageSep() const; // Schrage with seperations
    void DisplayTasks();
};
