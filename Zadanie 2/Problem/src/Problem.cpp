#include <algorithm>
#include "Problem.hpp"

#include <iostream>
#include <chrono>

/* constructors and destructors */
Problem::Problem(std::vector<Task> tasks) : m_tasksNr(tasks.size())
{
    for (int i = 0; i < tasks.size(); i++)
    {
        Task *newTask = new (Task);
        *newTask = tasks[i];
        m_tasks.push_back(*newTask);
    }
}

Problem::~Problem()
{
    m_tasks.clear();
}

/* methods */

void Problem::DisplayTasks()
{
    std::cout << "Tasks in the problem." << std::endl;
    for (int i = 0; i < m_tasksNr; i++)
    {
        std::cout << "taskId " << m_tasks[i].GetTaskId() << " task: pj " << m_tasks[i].GetPj() << std::endl;
    }

    std::cout << "Number od tasks " << m_tasksNr << std::endl;
}

// count sum of pj on the machine
int Problem::CountCriterionOnTheMachine(std::vector<Task> machine) const
{
    int sum = 0;
    for (int i = 0; i < machine.size(); i++)
    {
        sum += machine[i].GetPj();
    }
    return sum;
}

void Combination(std::vector<int> a, int reqLen, int start, int currLen, std::vector<bool> check, int len, int **&matrix)
{
    // Return if the currLen is more than the required length.
    if (currLen > reqLen)
        return;
    // If currLen is equal to required length then print the sequence.
    else if (currLen == reqLen)
    {
        std::cout << "\t";
        int sum = 0;
        for (int i = 0; i < len; i++)
        {
            if (check[i] == true)
            {
                std::cout << a[i] << " ";
                sum += a[i];
            }
        }
        std::cout << "suma " << sum << std::endl;
        std::cout << "\n";
        return;
    }
    // If start equals to len then return since no further element left.
    if (start == len)
    {

        return;
    }
    // For every index we have two options.
    // First is, we select it, means put true in check[] and increment currLen and start.
    check[start] = true;
    Combination(a, reqLen, start + 1, currLen + 1, check, len,matrix);
    // Second is, we don't select it, means put false in check[] and only start incremented.
    check[start] = false;
    Combination(a, reqLen, start + 1, currLen, check, len,matrix);
}

void Problem::DynamicProgramming2D()
{
    // prepare dimentions
    int pSum = 0;
    for (int i = 0; i < m_tasks.size(); i++)
        pSum += m_tasks[i].GetPj();
    int rows = m_tasks.size(), cols = pSum / 2;

    // create matrix
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; ++i)
        matrix[i] = new int[cols];
    // full fill the matr
    std::vector<bool> check = {};
    std::vector<int> arr = {};

    for (int r = 0; r < rows; r++)
    {
        check.push_back(false);
        arr.push_back(m_tasks[r].GetPj());

        // for each length of sub-array, call the Combination().
        for (int i = 0 ; i < r; i++)
        {
            std::cout << "r: " << r << std::endl;
            // find all combinations os pj sum and fill the matrix
            Combination(arr, i+1, 0, 0, check, r, matrix);
        }
        
    }
}

