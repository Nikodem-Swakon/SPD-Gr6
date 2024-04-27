#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>  //pair

#include "Task.hpp"
#include "Solution.hpp"
//#include "Permutation.hpp"
#include "Pair.hpp"

#define CRITICAL_NUMBER 12

class Node;
class Problem
{
private:
    /* private data */
    std::vector<Task> m_tasks;
    mutable std::vector<Task> m_machine1;   // tasks ranked on first machine
    mutable std::vector<Task> m_machine2;   // tasks ranked on second machine
    mutable std::vector<Task> m_machine3;   // tasks ranked on third machine
    int m_tasksNr;

    /* private methods */
    Node CreateNodeQj(int lowBarier, Node parent, int upBarier) const;
    Node CreateNodeRj(int lowBarier, Node parent, int upBarier) const;
    int CountCriterionOnTheMachine(std::vector<Task> machine) ;

    void CompleteReview_alg(std::vector<Task>& tasks, int start, std::vector<std::vector<Task>>& permutations);
    void DynamicProgramming2D(const std::vector<Task> &tasks) const;
    void DynamicProgramming3D(const std::vector<Task> &tasks) const;
public:
    /* public methods */
    Problem(std::vector<Task> tasks);
    ~Problem();

    void GenerateInstance();
    

    void LPT() const;
    void LSA() const;
    // Na 3.0
    void DynamicProgramming2D() const;
    // Na 3.5
    void CompleteReview_2() const;
    //Na 4.0
    void FPTAS(const int k) const;
    void PTAS_2(int k) const;
    //Na 4.5
    void CompleteReview_3() const;
    void PTAS_3(int k) const;
    void DynamicProgramming3D() const;
    // Na 5.0

    void DisplayTasks();
};
