#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>  //pair

#include "Task.hpp"
#include "Solution.hpp"

class Pair :
    public Solution
{
private:
    /* private data */
    std::vector<std::pair<Task,int>> m_rankedTasks;

    /* private methods */
    std::vector<std::pair<Task,int>> GetRankedTasks() const {return m_rankedTasks;};

public:
    /* public methods */
    Pair (); //default constructor
    Pair(double criterion, std::vector<std::pair<Task,int>> ranked);
    Pair(const Pair &pair);
    Pair &operator=(const Pair &pair) noexcept;
    ~Pair();

    void DisplaySolution();
    void DisplayGanttChart();

    int GetCriterion() const {return m_criterion;};
    

};