#pragma once
#include <iostream>
#include <vector>
#include <fstream>

#include "Task.hpp"
#include "Solution.hpp"

#define CRITICAL_NUMBER 12

typedef std::vector<std::vector<std::vector<std::vector<int>>>> cube; // is it needed?

class Node;
class Problem
{
private:
    /* private data */
    std::vector<Task> m_tasks;
    int m_tasksNr;
    mutable int m_cMax;

    /* private methods */
    int calculateMakespan(const std::vector<Task>& sequence) const;
    int CalculateCMax(const std::vector<Task>& sequence) const;
public:
    /* public methods */
    Problem(std::vector<Task> tasks);
    ~Problem();

    void GenerateInstance();
    void GetNextPerm(std::vector<Task>& vec) const;


    // Na 3.0
    void CompleteReview() const;
    void NEH() const;
    // Na 3.0
    
    // Na 3.5
    void Jhonson() const;
    // Na 3.5

    // Na 4.0
    void FNEH() const;
    // Na 4.0

    // Na 4.5
    void BasicBranchAndBound() const; //Podział i ograniczenia - a la'Carlier
    // Na 4.5

    // Na 5.0
    void BranchAndBound() const; // Wersja zaawansowana podziału i ograniczeń - już bardzo śmierdzi carlierem
    // Na 5.0


    void DisplayTasks();
};

struct bbNode{
	unsigned int	lev; // num of machine in the queue
	bool*			set;
	float			benef;
	float			cost; // time of executing tasks
	float			bound;
};
