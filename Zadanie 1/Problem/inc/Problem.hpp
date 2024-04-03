#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>  //pair

#include "Task.hpp"
#include "Solution.hpp"
#include "Permutation.hpp"
#include "Pair.hpp"

#define CRITICAL_NUMBER 12

class Node;
class Problem
{
private:
    /* private data */
    std::vector<Task> m_tasks;
    int m_tasksNr;

    /* private methods */
    int CountCriterion(std::vector<Task> rankedTasks) const;
    int CountCriterion(std::vector<std::pair<Task,int>>  rankedTasks) const;
    std::vector<Task> CompleteReview(std::vector<Task> tasks, int untilTask, int criterion) const;
    Node CreateNodeQj(int lowBarier, Node parent, int upBarier) const;
    Node CreateNodeRj(int lowBarier, Node parent, int upBarier) const;

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
    Permutation AlgorithmCarlier() const;
    Pair AlgorithmSchrageSep() const; // Schrage with seperations
    Permutation OurAlgorithm () const;
    Permutation Carlier(Node node, int lowBarier, int upBarrier) const;

    void DisplayTasks();
};
