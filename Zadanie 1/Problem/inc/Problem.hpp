#pragma once
#include <iostream>
#include <vector>
#include <fstream>

#include "Task.hpp"
#include "Solution.hpp"
#include "Permutation.hpp"

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
    Permutation AlgorithmSortRj() const;
    Permutation AlgorithmSortQj() const;
    Permutation AlgorithmCompleteReview() const;
    Permutation ExampleAlgorith() const; // TO BE DELETED  it is just simle example of algotithm method structure
    Permutation AlgorithmSchrage() const;
    Permutation AlgorithmSchrageSep() const; // Schrage with seperations
    void DisplayTasks();
};
