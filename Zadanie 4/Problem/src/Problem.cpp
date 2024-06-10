#include <algorithm>
#include "Problem.hpp"
#include <climits>
#include <iostream>
#include <chrono>
#include <tuple>
#include <numeric>
#include <algorithm> // std::sort

/* additional functions */
void printMatrix(const std::vector<std::vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

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
int CalculateCMax(const std::vector<Task> &sequence)
{

    int machineNum = sequence[0].GetValuesSize();
    std::vector<std::vector<int>> CzPi(machineNum + 1, std::vector<int>(sequence.size() + 1, 0));

    for (int i = 0; i < sequence.size() + 1; i++)
        CzPi[0][i] = 0;

    for (int z = 0; z < machineNum + 1; z++)
        CzPi[z][0] = 0;

    for (int z = 1; z < machineNum + 1; z++) // process iteration
    {
        for (int i = 1; i < sequence.size() + 1; i++) // task iteration
        {
            CzPi[z][i] = std::max(CzPi[z - 1][i], CzPi[z][i - 1]) + sequence[i - 1].GetValueAt(z - 1);
        }
    }

    return CzPi[machineNum][sequence.size()];
}

int Problem::calculateMakespan(const std::vector<Task> &sequence) const
{
    if (sequence.empty())
        return 0;

    int numJobs = sequence.size();
    int numMachines = sequence[0].GetValues().size();

    std::vector<std::vector<int>> completionTimes(numJobs, std::vector<int>(numMachines, 0));

    // Initialize the first job's completion times
    completionTimes[0][0] = sequence[0].GetValueAt(0);
    for (int j = 1; j < numMachines; ++j)
    {
        completionTimes[0][j] = completionTimes[0][j - 1] + sequence[0].GetValueAt(j);
    }

    // Calculate completion times for the rest of the jobs
    for (int i = 1; i < numJobs; ++i)
    {
        completionTimes[i][0] = completionTimes[i - 1][0] + sequence[i].GetValueAt(0);
        for (int j = 1; j < numMachines; ++j)
        {
            completionTimes[i][j] = std::max(completionTimes[i - 1][j], completionTimes[i][j - 1]) + sequence[i].GetValueAt(j);
        }
    }

    return completionTimes[numJobs - 1][numMachines - 1];
}

bool CompareTasksTasksDec(const Task &a, const Task &b)
{
    return a.GetValueAt(0) < b.GetValueAt(0);
}

bool CompareTasksTasksAsc(const Task &a, const Task &b)
{
    return a.GetValueAt(0) > b.GetValueAt(0);
}

void Problem::GetNextPerm(std::vector<Task> &vec) const
{
    std::next_permutation(vec.begin(), vec.end());
}

// Na 5.0
