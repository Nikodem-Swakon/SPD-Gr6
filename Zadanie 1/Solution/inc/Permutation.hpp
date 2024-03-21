#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "Task.hpp"
#include "Solution.hpp"

class Permutation :
    public Solution
{
private:
    /* private data */
    // int m_criterion;
    std::vector<Task> m_rankedTasks;

public:
    /* public methods */
    Permutation (); //default constructor
    Permutation(double criterion, std::vector<Task> ranked);
    Permutation(const Permutation &Permutation);
    Permutation &operator=(const Permutation &Permutation) noexcept;
    ~Permutation();

    void DisplaySolution();
    void DisplayGanttChart();
    std::vector<Task> GetRankedTasks() const {return m_rankedTasks;};
    int GetCriterion() const {return m_criterion;};

};