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

void Combination(std::vector<int> a, int reqLen, int start, int currLen, std::vector<bool> check, int len, int **&matrix, int rows)
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
        for (int i = len - 1; i < rows; i++)
        {
            matrix[i][sum] = 1;
        }
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
    Combination(a, reqLen, start + 1, currLen + 1, check, len, matrix, rows);
    // Second is, we don't select it, means put false in check[] and only start incremented.
    check[start] = false;
    Combination(a, reqLen, start + 1, currLen, check, len, matrix, rows);
}

void Problem::DynamicProgramming2D()
{
    // prepare dimentions
    int pSum = 0;
    for (int i = 0; i < m_tasks.size(); i++)
        pSum += m_tasks[i].GetPj();
    int rows = m_tasks.size(), cols = pSum;

    // create matrix
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; ++i)
        matrix[i] = new int[cols];

    // full fill teh matrix of zeros
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            matrix[r][c] = 0;
        }
    }
    // full fill the matr
    std::vector<bool> check = {};
    std::vector<int> arr = {};

    for (int r = 0; r < rows; r++)
    {
        check.push_back(false);
        arr.push_back(m_tasks[r].GetPj());

        // for each length of sub-array, call the Combination().
        for (int i = 0; i < r; i++)
        {
            std::cout << "r: " << r << std::endl;
            // find all combinations os pj sum and fill the matrix
            Combination(arr, i + 1, 0, 0, check, r, matrix, rows);
        }
    }

    std::cout << "matrix" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // find tasks which should be added to first machine

    std::vector<int> tasksIdFrorMachine1 = {};
    int r = rows - 1;
    int c = cols / 2;
    int taskId = -1;
    while (c > 0)
    {
        std::cout << "c " << c << std::endl;
        while ((matrix[r][c] != 1) && (r > 0) && (c > 0))
        {
            std::cout << "col"
                      << " ";
            std::cout << r << " " << c << " " << matrix[r][c] << std::endl;
            c--;
            if (c < 0)
                break;
        }

        while ((matrix[r][c] != 0))
        {
            std::cout << "row"
                      << " ";
            std::cout << r << " " << c << " " << matrix[r][c] << std::endl;
            r--;
            if (r < 0)
                break;
        }
        r++; // get back to last r which has 1
        std::cout << "zapisz" << r << std::endl;
        tasksIdFrorMachine1.push_back(r);
        c--;
    }

    for (int i = 0; i < tasksIdFrorMachine1.size(); i++)
    {
        std::cout << tasksIdFrorMachine1[i] << " ";
    }
    // remove duplicats
    sort(tasksIdFrorMachine1.begin(), tasksIdFrorMachine1.end());
    tasksIdFrorMachine1.erase(unique(tasksIdFrorMachine1.begin(), tasksIdFrorMachine1.end()), tasksIdFrorMachine1.end());
    std::cout << "after removing duplicats" << std::endl;
    for (int i = 0; i < tasksIdFrorMachine1.size(); i++)
    {
        std::cout << tasksIdFrorMachine1[i] << " ";
    }

    for (int i = 0; i < m_tasks.size(); i++)
    {
        auto it = std::find(tasksIdFrorMachine1.begin(), tasksIdFrorMachine1.end(), (m_tasks[i].GetTaskId() - 1)); // there is numeration from 1
        if (it != tasksIdFrorMachine1.end())
            m_machine1.push_back(m_tasks[i]);
        else
            m_machine2.push_back(m_tasks[i]);
    }

    int machine1 = 0;
    std::cout << "macine 1" << std::endl;
    for (int i = 0; i < m_machine1.size(); i++)
    {
        std::cout << m_machine1[i] << " ";
        machine1+=m_machine1[i].GetPj();
    }
    std::cout << std::endl;
    int machine2 = 0;
    std::cout << "macine 2" << std::endl;
    for (int i = 0; i < m_machine2.size(); i++)
    {
        std::cout << m_machine2[i] << " ";
        machine2+=m_machine2[i].GetPj();
    }
    std::cout << std::endl;
    std::cout << "criterion " << std::max(machine2, machine1) << std::endl;

}