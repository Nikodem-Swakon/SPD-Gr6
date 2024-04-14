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
    std::vector<Task> m_criticPath; // critic pathfrom A to B
    int  m_cId; // interference task C id
    Task m_interferenceTask;
    Task m_criticalTask;
    std::vector<Task> m_criticSet; // critical set from C+1 to B
    

    void DesignateCriticalPath(std::vector<Task> &path);
    void DesignateCriticalSet(std::vector<Task> &path);
    int DesignateInterferenceTaskId();
    void NodeInit();
    void UpdateUpBarier();
    void UpdateLowBarier();

public:
    Node(std::vector<Task> tasks, int lb);
    Node(std::vector<Task> tasks, int lb, int ub);
    ~Node();
    bool IsOptimal() const;
    Task GetInterferenceTask() const;
    Permutation GetPermutation() const;
    std::vector<Task> GetCriticalPath() const;
    int GetCmax() const {return m_cMax;};
    int GetUpBarier() const;
    int GetLowBarier() const;

};
