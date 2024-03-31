#pragma once

#include <iostream>
#include <limits>

#include "Problem.hpp"
#include "Permutation.hpp"
#include "Task.hpp"


class Problem;

class Node
{
private:
    int m_lb; // lower barier
    int m_ub; // upper barier
    int m_cMax; // criterion
    bool m_isOptimal; // true if it is optimal
    Problem m_problem;
    Permutation m_permutation; 
    Permutation m_criticPath; // critic pathfrom A to B
    int  m_cId; // interference task C id
    Permutation m_criticSet; // critical set from C+1 to B

    Permutation DesignateCriticalPath();
    Permutation DesignateCriticalSet();
    int DesignateInterferenceTaskId();
    void NodeInit();

public:
    Node(std::vector<Task> tasks, int lb);
    Node(std::vector<Task> tasks, int lb, int ub);
    ~Node();
    bool IsOptimal();
};
