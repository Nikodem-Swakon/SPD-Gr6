#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <utility> //pair

#include "Task.hpp"
#include "Solution.hpp"
// #include "Permutation.hpp"
#include "Pair.hpp"

#define CRITICAL_NUMBER 12

typedef std::vector<std::vector<std::vector<std::vector<int>>>> cube;

class Node;
class Problem
{
private:
    /* private data */
    std::vector<Task> m_tasks;
    mutable std::vector<Task> m_machine1; // tasks ranked on first machine
    mutable std::vector<Task> m_machine2; // tasks ranked on second machine
    mutable std::vector<Task> m_machine3; // tasks ranked on third machine
    int m_tasksNr;
    mutable int m_cMax;

    /* private methods */
    Node CreateNodeQj(int lowBarier, Node parent, int upBarier) const;
    Node CreateNodeRj(int lowBarier, Node parent, int upBarier) const;
    int CountCriterionOnTheMachine(std::vector<Task> machine);

    void CompleteReview_alg(std::vector<Task> &tasks, int start, std::vector<std::vector<Task>> &permutations);
    void DynamicProgramming2D(const std::vector<Task> &tasks) const;
    void DynamicProgramming3D(const std::vector<Task> &tasks) const;
    void DynamicProgramming3DBase(const std::vector<Task> &tasks) const;
    int FindTv(cube &matrix, int xn, char &maxAxis, int xyzSize) const;
    
    int calculateMakespan(const std::vector<Task>& sequence) const;

public:
    //Problem(const std::vector<Task>& tasks) : m_tasks(tasks) {}

    /* public methods */
    Problem(std::vector<Task> tasks);
    ~Problem();

    void GenerateInstance();


    // Na 3.0
    void Complete_Review() const;
    void NEH() const;
    // Na 3.0
    
    // Na 3.5
    void Jhonson() const;
    // Na 3.5

    // Na 4.0
    void FNEH() const;
    // Na 4.0

    // Na 4.5
    void PiO() const; //Podział i ograniczenia - a la'Carlier
    // Na 4.5

    // Na 5.0
    void pro_PiO() const; // Wersja zaawansowana podziału i ograniczeń - już bardzo śmierdzi carlierem
    // Na 5.0


    void DisplayTasks();
};
