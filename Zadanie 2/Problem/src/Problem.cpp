#include <algorithm>
#include "Problem.hpp"
#include <climits>
#include <iostream>
#include <chrono>
#include <tuple>
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

void Problem::LPT() const
{ // działa niepoprawnie
    std::vector<Task> rankedTasks = m_tasks;
    std::vector<Task> P1; // Machine 1
    std::vector<Task> P2; // Machine 2
    int P1_time = 0;      // Time of processing for machine 1
    int P2_time = 0;      // Time of processing for machine 2

    std::sort(rankedTasks.begin(), rankedTasks.end(), [](const Task &a, const Task &b)
              { return a.GetPj() > b.GetPj(); }); // ascending order

    for (int i = 0; i < rankedTasks.size(); i++)
    {
        if (P2_time >= P1_time)
        {
            P1.push_back(rankedTasks[i]);
            P1_time += rankedTasks[i].GetPj();
        }
        else
        {
            P2.push_back(rankedTasks[i]);
            P2_time += rankedTasks[i].GetPj();
        }
    }

    int criterion = std::max(P2_time, P1_time);
    std::cout << "Criterion: " << criterion << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Machine_nr_1: ";
    for (int x = 0; x < P1.size(); x++)
    {
        std::cout << P1[x].GetTaskId() << ", ";
    }
    std::cout << std::endl
              << "Machine_nr_2: ";
    for (int y = 0; y < P2.size(); y++)
    {
        std::cout << P2[y].GetTaskId() << ", ";
    }
    std::cout << std::endl;
    // Permutation solution(criterion, sortedTasks);
    // return solution;
}
void Problem::LSA() const
{ // Działa
    std::vector<Task> rankedTasks = m_tasks;
    std::vector<Task> P1; // Machine 1
    std::vector<Task> P2; // Machine 2
    int P1_time = 0;      // Time of processing for machine 1
    int P2_time = 0;      // Time of processing for machine 2

    for (int i = 0; i < rankedTasks.size(); i++)
    {
        if (P2_time < P1_time)
        {
            P2.push_back(rankedTasks[i]);
            P2_time += rankedTasks[i].GetPj();
        }
        else
        {
            P1.push_back(rankedTasks[i]);
            P1_time += rankedTasks[i].GetPj();
        }
    }
    int criterion = std::max(P2_time, P1_time);
    std::cout << std::endl
              << "Criterion: " << criterion << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Machine_nr_1: ";
    for (int x = 0; x < P1.size(); x++)
    {
        std::cout << P1[x].GetTaskId() << ", ";
    }
    std::cout << std::endl
              << "Machine_nr_2: ";
    for (int y = 0; y < P2.size(); y++)
    {
        std::cout << P2[y].GetTaskId() << ", ";
    }
    std::cout << std::endl;
}

void Problem::CompleteReview_2() const
{
    std::vector<Task> temp = m_tasks; // Assuming m_tasks is a member variable
    int num_tasks = temp.size();
    int minCmax = INT_MAX;
    std::vector<int> best_bitmask;

    // Generate all possible bitmasks
    for (int bitmask = 0; bitmask < (1 << num_tasks); ++bitmask)
    {
        int P1_time = 0;
        int P2_time = 0;

        for (int i = 0; i < num_tasks; ++i)
        {
            if (bitmask & (1 << i))
            { // Check if i-th bit is set
                P1_time += temp[i].GetPj();
            }
            else
            {
                P2_time += temp[i].GetPj();
            }
        }

        int Cmax = std::max(P1_time, P2_time);
        if (Cmax < minCmax)
        {
            minCmax = Cmax;
            best_bitmask = std::vector<int>(num_tasks, 0);
            for (int i = 0; i < num_tasks; ++i)
            {
                if (bitmask & (1 << i))
                {
                    best_bitmask[i] = 1;
                }
            }
        }
    }

    // Print the best schedule
    std::cout << "Best schedule to minimize Cmax:\n";
    for (int i = 0; i < num_tasks; ++i)
    {
        if (best_bitmask[i] == 1)
        {
            std::cout << "Task " << temp[i].GetTaskId() << " with processing time " << temp[i].GetPj() << " scheduled on machine 1\n";
        }
        else
        {
            std::cout << "Task " << temp[i].GetTaskId() << " with processing time " << temp[i].GetPj() << " scheduled on machine 2\n";
        }
    }
    std::cout << "Minimum Cmax: " << minCmax << std::endl;
}

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
int CountCriterionOnTheMachine(std::vector<Task> machine)
{
    int sum = 0;
    for (int i = 0; i < machine.size(); i++)
    {
        sum += machine[i].GetPj();
    }
    return sum;
}

void Problem::DynamicProgramming2D() const
{
    DynamicProgramming2D(m_tasks);
    // display information
    std::cout << "Dynamic Programming 2D scheduling" << std::endl;
    int machine1 = 0;
    std::cout << "Machine 1:" << std::endl;
    for (int i = 0; i < m_machine1.size(); i++)
    {
        std::cout << m_machine1[i] << " ";
        machine1 += m_machine1[i].GetPj();
    }
    std::cout << std::endl;
    int machine2 = 0;
    std::cout << "Machine 2:" << std::endl;
    for (int i = 0; i < m_machine2.size(); i++)
    {
        std::cout << m_machine2[i] << " ";
        machine2 += m_machine2[i].GetPj();
    }
    std::cout << std::endl;
    std::cout << "Cmax: " << std::max(machine2, machine1) << std::endl;
    m_machine1.clear();
    m_machine2.clear();
}
void Problem::DynamicProgramming2D(const std::vector<Task> &tasks) const
{
    // prepare dimentions
    int pSum = 0;
    for (int i = 0; i < tasks.size(); i++)
        pSum += tasks[i].GetPj();
    int rows = tasks.size() + 1, cols = pSum / 2 + 1;

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

    // full fill the first column
    for (int r = 0; r < rows; r++)
        matrix[r][0] = 1;

    // full fill the matr
    for (int r = 1; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (matrix[r - 1][c] == 1)
                matrix[r][c] = 1;
            if (c >= tasks[r - 1].GetPj())
            {
                if (matrix[r - 1][c - tasks[r - 1].GetPj()] == 1)
                    matrix[r][c] = 1;
            }
        }
    }
    // find tasks which should be added to first machine
    std::vector<int> tasksIdFrorMachine1 = {};
    int r = rows - 1;
    int c = cols - 1;
    int taskId = -1;

    while (matrix[r][c] != 1)
        c--;

    while (c > 0)
    {
        // find the highest r
        while ((matrix[r][c] != 0))
        {
            r--;
            if (r < 0)
                break;
        }
        r++; // get back to last r which has 1
        tasksIdFrorMachine1.push_back(r - 1);

        // move to next colum directed by Pj
        c = c - tasks[r - 1].GetPj();
    }

    // remove duplicats
    sort(tasksIdFrorMachine1.begin(), tasksIdFrorMachine1.end());
    tasksIdFrorMachine1.erase(unique(tasksIdFrorMachine1.begin(), tasksIdFrorMachine1.end()), tasksIdFrorMachine1.end());

    // devide on machines
    for (int i = 0; i < tasks.size(); i++)
    {
        auto it = std::find(tasksIdFrorMachine1.begin(), tasksIdFrorMachine1.end(), (tasks[i].GetTaskId() - 1)); // there is numeration from 1
        if (it != tasksIdFrorMachine1.end())
        {
            if (tasks.size() != m_tasks.size())
                m_machine1.push_back(tasks[i]);
            else
                m_machine1.push_back(m_tasks[i]);
        }

        else
        {
            if (tasks.size() != m_tasks.size())
                m_machine2.push_back(tasks[i]);
            else
                m_machine2.push_back(m_tasks[i]);
        }
    }
}

void Problem::DynamicProgramming3D() const
{
    std::cout << std::endl
              << "Dyamic programming for 3 machines" << std::endl;
    DynamicProgramming3D(m_tasks);
    // display information

    int machine1 = 0;
    std::cout << "Machine 1:" << std::endl;
    for (int i = 0; i < m_machine1.size(); i++)
    {
        std::cout << m_machine1[i] << " ";
        machine1 += m_machine1[i].GetPj();
    }
    std::cout << std::endl;

    int machine2 = 0;
    std::cout << "Machine 2:" << std::endl;
    for (int i = 0; i < m_machine2.size(); i++)
    {
        std::cout << m_machine2[i] << " ";
        machine2 += m_machine2[i].GetPj();
    }
    std::cout << std::endl;

    int machine3 = 0;
    std::cout << "Machine 3:" << std::endl;
    for (int i = 0; i < m_machine3.size(); i++)
    {
        std::cout << m_machine3[i] << " ";
        machine3 += m_machine3[i].GetPj();
    }
    std::cout << std::endl;
    int max = std::max(machine2, machine1);
    max = std::max(machine3, max);

<<<<<<< HEAD
    std::cout << "\033[1;31m Cmax: " << m_cMax << "\033[0m" << std::endl;
=======
    std::cout << "Cmax: " << m_cMax << std::endl;  // zmieniajac na max uzyskamy leszpe ale nadal złe wyniki
>>>>>>> 61400485f9a9ffe8008e8b85426cac1ade0f7b95
    m_machine1.clear();
    m_machine2.clear();
    m_machine3.clear();
}

/// @brief
/// @param tasks vector with taks scheduled on machine
void Problem::DynamicProgramming3DBase(const std::vector<Task> &tasks) const
{

    // find optimal scheduling
    std::vector<Task> tasksFrorMachine1 = {};
    std::vector<Task> tasksFrorMachine2 = {};
    std::vector<Task> tasksFrorMachine3 = {};

    std::vector<Task> theRest = {};

    DynamicProgramming2D(tasks);
    for (int i = 0; i < m_machine1.size(); i++)
    {
        tasksFrorMachine1.push_back(m_machine1[i]);
    }

    for (int i = 0; i < m_machine2.size(); i++)
    {
        theRest.push_back(m_machine2[i]);
    }

    m_machine1.clear();
    m_machine2.clear();
    DynamicProgramming2D(theRest);
    for (int i = 0; i < m_machine1.size(); i++)
    {
        tasksFrorMachine2.push_back(m_machine1[i]);
    }

    for (int i = 0; i < m_machine2.size(); i++)
    {
        tasksFrorMachine3.push_back(m_machine2[i]);
    }
}

/// @brief
/// @param tasks vector with taks scheduled on machine
void Problem::DynamicProgramming3D(const std::vector<Task> &tasks) const
{
    // prepare dimentions
    Task maxPjTask = tasks[0];
    auto maxPjTaskIterator = std::max_element(tasks.begin(), tasks.end(), [](const Task &a, const Task &b)
                                              { return a.GetPj() < b.GetPj(); });
    if (maxPjTaskIterator != tasks.end())
        maxPjTask = *maxPjTaskIterator;

    int pSum = 0;
    for (int i = 0; i < tasks.size(); i++)
        pSum += tasks[i].GetPj();

    int nSize = tasks.size() + 1;
    int xyzSize = std::max(maxPjTask.GetPj(), pSum) + 1;
    int xSize = xyzSize, ySize = xyzSize, zSize = xyzSize;

    // create matrix and full fill of zeros
    cube matrix(
        nSize, std::vector<std::vector<std::vector<int>>>(
                   xSize, std::vector<std::vector<int>>(
                              ySize, std::vector<int>(
                                         zSize, 0))));

    matrix[0][0][0][0] = 1;

    // full fill the matrix
    for (int n = 1; n < nSize; n++)
    {
        for (int x = 0; x < xSize; x++)
        {
            for (int y = 0; y < ySize; y++)
            {
                for (int z = 0; z < ySize; z++)
                {
                    int pj = tasks[n - 1].GetPj();
                    if (x - pj >= 0)
                    {
                        if (matrix[n - 1][x - pj][y][z])
                            matrix[n][x][y][z] = 1;
                    }
                    if (y - pj >= 0)
                    {
                        if (matrix[n - 1][x][y - pj][z])
                            matrix[n][x][y][z] = 1;
                    }
                    if (z - pj >= 0)
                    {
                        if (matrix[n - 1][x][y][z - pj])
                            matrix[n][x][y][z] = 1;
                    }
                }
            }
        }
    }

    // find optimal scheduling
    std::vector<int> tasksIdFrorMachine3 = {};
    int x = xyzSize - 1, y = xyzSize - 1, z = xyzSize - 1, cMax = xyzSize - 1;
    int xn = nSize - 1;
    char maxAxis = 'n';

    // find max axis and tv max for the axis
    cMax = FindTv(matrix, xn, maxAxis, xyzSize);

    // find tasks for machine 3
    for (int n = 1; n < xn; n++)
    {
        int tvMax = FindTv(matrix, n, maxAxis, xyzSize);
        bool exist = false;
        // find 1 if exist
        if (maxAxis == 'x')
        {
            for (int x = 0; x <= tvMax; x++)
            {
                exist = false;
                for (int y = 0; y < ySize; y++)
                {
                    for (int z = 0; z < zSize; z++)
                    {
                        if (matrix[n][x][y][z] == 1)
                        {
                            exist = true;
                            break;
                        }
                    }
                    if (exist)
                        break;
                }
                if (!exist)
                    break;
            }
        }
        else if (maxAxis == 'x')
        {
            for (int y = 0; y <= tvMax; y++)
            {
                exist = false;
                for (int x = 0; x < ySize; x++)
                {
                    for (int z = 0; z < zSize; z++)
                    {
                        if (matrix[n][x][y][z] == 1)
                        {
                            exist = true;
                            break;
                        }
                    }
                    if (exist)
                        break;
                }
                if (!exist)
                    break;
            }
        }
        else if (maxAxis == 'x')
        {
            for (int z = 0; z <= tvMax; z++)
            {
                exist = false;
                for (int y = 0; y < ySize; y++)
                {
                    for (int x = 0; x < xSize; x++)
                    {
                        if (matrix[n][x][y][z] == 1)
                        {
                            exist = true;
                            break;
                        }
                    }
                    if (exist)
                        break;
                }
                if (!exist)
                    break;
            }
        }

        if (exist)
            tasksIdFrorMachine3.push_back(n - 1);
    }

    // find the rest of tasks
    std::vector<Task> tasksForMachine1and2 = {};
    for (int i = 0; i < tasks.size(); i++)
    {
        auto it = std::find(tasksIdFrorMachine3.begin(), tasksIdFrorMachine3.end(), (tasks[i].GetTaskId() - 1)); // there is numeration from 1
        if (it != tasksIdFrorMachine3.end())
        {
            m_machine3.push_back(tasks[i]);
        }
        else
        {
            tasksForMachine1and2.push_back(tasks[i]);
        }
    }

    // find optimal solution for 2 machines
    DynamicProgramming2D(tasksForMachine1and2);

    // find max
    do
    {

        if (maxAxis == 'x')
        {
            x--;

            for (y = x; y > 0; y--)
            {
                for (z = x; z > 0; z--)
                {
                    if (matrix[xn][x][y][z] == 1)
                        cMax = x;
                }
            }
        }
        else if (maxAxis == 'y')
        {
            y--;

            for (x = y; x > 0; x--)
            {
                for (z = y; z > 0; z--)
                {
                    if (matrix[xn][x][y][z] == 1)
                        cMax = y;
                }
            }
        }
        else if (maxAxis == 'z')
        {
            z--;
            for (x = z; x > 0; x--)
            {
                for (y = z; y > 0; y--)
                {
                    if (matrix[xn][x][y][z] == 1)
                        cMax = z;
                }
            }
        }

    } while (x >= 0 && y >= 0 && z >= 0);

    // find task for first machine
    m_cMax = cMax;
}

int Problem::FindTv(cube &matrix, int xn, char &maxAxis, int xyzSize) const
{

    int x = xyzSize - 1, y = xyzSize - 1, z = xyzSize - 1, cMax = xyzSize - 1;

    // find max x
    while (x >= 0 && y >= 0 && z >= 0)
    {
        for (y = xyzSize - 1; y > 0; y--)
        {
            for (z = xyzSize - 1; z > 0; z--)
            {
                if (matrix[xn][x][y][z] == 1)
                    break;
            }
            if (matrix[xn][x][y][z] == 1)
                break;
        }
        if (matrix[xn][x][y][z] == 1)
            break;

        x--;
    }
    const int maxTvx = x;

    x = xyzSize - 1;
    y = xyzSize - 1;
    z = xyzSize - 1;
    // find max y
    while (x >= 0 && y >= 0 && z >= 0)
    {
        for (x = xyzSize - 1; x > 0; x--)
        {
            for (z = xyzSize - 1; z > 0; z--)
            {
                if (matrix[xn][x][y][z] == 1)
                    break;
            }
            if (matrix[xn][x][y][z] == 1)
                break;
        }
        if (matrix[xn][x][y][z] == 1)
            break;

        y--;
    }
    const int maxTvy = y;

    x = xyzSize - 1;
    y = xyzSize - 1;
    z = xyzSize - 1;
    // find max z
    while (x >= 0 && y >= 0 && z >= 0)
    {
        for (x = xyzSize - 1; x > 0; x--)
        {
            for (y = xyzSize - 1; y > 0; y--)
            {
                if (matrix[xn][x][y][z] == 1)
                    break;
            }
            if (matrix[xn][x][y][z] == 1)
                break;
        }
        if (matrix[xn][x][y][z] == 1)
            break;

        z--;
    }
    const int maxTvz = z;

    if (maxAxis == 'x')
    {
        return maxTvx;
    }
    else if (maxAxis == 'y')
    {
        return maxTvy;
    }
    else if (maxAxis == 'z')
    {
        return maxTvz;
    }

    if (cMax == maxTvx)
        maxAxis = 'x';
    else if (cMax == maxTvy)
        maxAxis = 'y';
    else if (cMax == maxTvz)
        maxAxis = 'z';
    return cMax = std::max(std::max(maxTvx, maxTvy), maxTvz);
}

/// @brief
/// @param k numebr of devide time in tasks
void Problem::FPTAS(const int k) const
{
    std::vector<Task> tasks = {};
    for (int i = 0; i < m_tasks.size(); i++)
    {
        tasks.push_back(Task(m_tasks[i].GetPj() / k + 1, m_tasks[i].GetTaskId()));
    }

    DynamicProgramming2D(tasks);
    // display information
    int machine1 = 0;
    std::cout << "FPTAS scheduling" << std::endl;
    std::cout << "Machine 1:" << std::endl;
    for (int i = 0; i < m_machine1.size(); i++)
    {

        std::cout << m_tasks[m_machine1[i].GetTaskId() - 1] << " ";
        machine1 += m_tasks[m_machine1[i].GetTaskId() - 1].GetPj();
    }
    std::cout << std::endl;
    int machine2 = 0;
    std::cout << "Machine 2:" << std::endl;
    for (int i = 0; i < m_machine2.size(); i++)
    {
        std::cout << m_tasks[m_machine2[i].GetTaskId() - 1] << " ";
        machine2 += m_tasks[m_machine2[i].GetTaskId() - 1].GetPj();
    }
    std::cout << std::endl;
    std::cout << "Cmax: " << std::max(machine2, machine1) << std::endl;
    m_machine1.clear();
    m_machine2.clear();
}

std::pair<std::vector<Task>, std::vector<Task>> PTAS_CR_2(const std::vector<Task> &tasks)
{
    int num_tasks = tasks.size();
    int minCmax = INT_MAX;
    std::vector<int> best_bitmask;

    // Generate all possible bitmasks
    for (int bitmask = 0; bitmask < (1 << num_tasks); ++bitmask)
    {
        int P1_time = 0;
        int P2_time = 0;

        for (int i = 0; i < num_tasks; ++i)
        {
            if (bitmask & (1 << i))
            { // Check if i-th bit is set
                P1_time += tasks[i].GetPj();
            }
            else
            {
                P2_time += tasks[i].GetPj();
            }
        }

        int Cmax = std::max(P1_time, P2_time);
        if (Cmax < minCmax)
        {
            minCmax = Cmax;
            best_bitmask = std::vector<int>(num_tasks, 0);
            for (int i = 0; i < num_tasks; ++i)
            {
                if (bitmask & (1 << i))
                {
                    best_bitmask[i] = 1;
                }
            }
        }
    }
    // Print the best schedule
    std::vector<Task> temp_machine1;
    std::vector<Task> temp_machine2;
    for (int i = 0; i < num_tasks; ++i)
    {
        if (best_bitmask[i] == 1)
        {
            temp_machine1.push_back(tasks[i]);
        }
        else
        {
            temp_machine2.push_back(tasks[i]);
        }
    }
    return std::make_pair(temp_machine1, temp_machine2);
}

std::tuple<std::pair<std::vector<Task>, std::vector<Task>>, std::pair<int, int>> PTAS_LSA(const std::vector<Task> &tasks, int P1_time, int P2_time)
{
    std::vector<Task> rankedTasks = tasks;
    std::vector<Task> P1; // Machine 1
    std::vector<Task> P2; // Machine 2

    for (int i = 0; i < rankedTasks.size(); i++)
    {
        if (P2_time < P1_time)
        {
            P2.push_back(rankedTasks[i]);
            P2_time += rankedTasks[i].GetPj();
        }
        else
        {
            P1.push_back(rankedTasks[i]);
            P1_time += rankedTasks[i].GetPj();
        }
    }
    return std::make_tuple(std::make_pair(P1, P2), std::make_pair(P1_time, P2_time));
}

void Problem::PTAS_2(const int k) const
{
    std::vector<Task> tasks = m_tasks;
    // Step 1: Sort tasks by their processing time in descending order
    std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b)
              { return a.GetPj() > b.GetPj(); });

    // Step 2: Take first 'k' amount of tasks and sort them using CompleteReview_2()
    std::vector<Task> firstKTasks(tasks.begin(), tasks.begin() + k);
    std::pair<std::vector<Task>, std::vector<Task>> schedule = PTAS_CR_2(firstKTasks);
    std::vector<Task> machine1_tasks = schedule.first;
    std::vector<Task> machine2_tasks = schedule.second;

    int machine1_time = 0;
    int machine2_time = 0;
    for (int i = 0; i < machine1_tasks.size(); i++)
    {
        machine1_time += machine1_tasks[i].GetPj();
    }
    for (int i = 0; i < machine2_tasks.size(); i++)
    {
        machine2_time += machine2_tasks[i].GetPj();
    }

    // Step 3: Take the rest of the tasks and sort them using LSA()
    std::vector<Task> restTasks(tasks.begin() + k, tasks.end());
    // std::pair<std::vector<Task>, std::vector<Task>> schedule2 = PTAS_LSA(restTasks, machine1_time, machine2_time);
    auto result = PTAS_LSA(restTasks, machine1_time, machine2_time);
    std::pair<std::vector<Task>, std::vector<Task>> task_pair = std::get<0>(result);
    std::pair<int, int> time_pair = std::get<1>(result);
    std::vector<Task> temp1 = task_pair.first;
    std::vector<Task> temp2 = task_pair.second;

    machine1_time = time_pair.first;
    machine2_time = time_pair.second;

    machine1_tasks.insert(machine1_tasks.end(), temp1.begin(), temp1.end());
    machine2_tasks.insert(machine2_tasks.end(), temp2.begin(), temp2.end());

    std::cout << "Machine 1 tasks: ";
    for (int i = 0; i < machine1_tasks.size(); i++)
    {
        // machine1_time+=machine1_tasks[i].GetPj();
        std::cout << machine1_tasks[i].GetTaskId() << ", ";
    }
    std::cout << std::endl
              << "Machine 2 tasks: ";
    for (int i = 0; i < machine2_tasks.size(); i++)
    {
        // machine2_time+=machine2_tasks[i].GetPj();
        std::cout << machine2_tasks[i].GetTaskId() << ", ";
    }
    int CMAX = std::max(machine1_time, machine2_time);
    std::cout << std::endl
              << "CMAX: " << CMAX << std::endl;
}

void Problem::CompleteReview_3() const
{
    std::vector<Task> temp = m_tasks; // Assuming m_tasks is a member variable
    int num_tasks = temp.size();
    int minCmax = INT_MAX;
    std::vector<int> best_bitmask;

    // Generate all possible bitmasks
    for (int bitmask = 0; bitmask < (1 << (2 * num_tasks)); ++bitmask)
    {
        int P1_time = 0;
        int P2_time = 0;
        int P3_time = 0;

        for (int i = 0; i < num_tasks; ++i)
        {
            int machine = (bitmask >> (2 * i)) & 3;
            if (machine == 0)
            {
                P1_time += temp[i].GetPj();
            }
            else if (machine == 1)
            {
                P2_time += temp[i].GetPj();
            }
            else
            {
                P3_time += temp[i].GetPj();
            }
        }

        int Cmax = std::max({P1_time, P2_time, P3_time});
        if (Cmax < minCmax)
        {
            minCmax = Cmax;
            best_bitmask = std::vector<int>(2 * num_tasks, 0);
            for (int i = 0; i < num_tasks; ++i)
            {
                best_bitmask[2 * i] = (bitmask >> (2 * i)) & 1;
                best_bitmask[2 * i + 1] = (bitmask >> (2 * i + 1)) & 1;
            }
        }
    }

    // Print the best schedule
    std::cout << "Best schedule to minimize Cmax:\n";
    for (int i = 0; i < num_tasks; ++i)
    {
        int machine = best_bitmask[2 * i] + 2 * best_bitmask[2 * i + 1];
        if (machine == 0)
        {
            std::cout << "Task " << temp[i].GetTaskId() << " with processing time " << temp[i].GetPj() << " scheduled on machine 1\n";
        }
        else if (machine == 1)
        {
            std::cout << "Task " << temp[i].GetTaskId() << " with processing time " << temp[i].GetPj() << " scheduled on machine 2\n";
        }
        else
        {
            std::cout << "Task " << temp[i].GetTaskId() << " with processing time " << temp[i].GetPj() << " scheduled on machine 3\n";
        }
    }
    std::cout << "Minimum Cmax: " << minCmax << std::endl;
}

std::tuple<std::vector<Task>, std::vector<Task>, std::vector<Task>> PTAS_CR_3(const std::vector<Task> &tasks)
{
    int num_tasks = tasks.size();
    int minCmax = INT_MAX;
    std::vector<int> best_bitmask;

    // Generate all possible bitmasks
    for (int bitmask = 0; bitmask < (1 << (2 * num_tasks)); ++bitmask)
    {
        int P1_time = 0;
        int P2_time = 0;
        int P3_time = 0;

        for (int i = 0; i < num_tasks; ++i)
        {
            int machine = (bitmask >> (2 * i)) & 3;
            if (machine == 0)
            {
                P1_time += tasks[i].GetPj();
            }
            else if (machine == 1)
            {
                P2_time += tasks[i].GetPj();
            }
            else
            {
                P3_time += tasks[i].GetPj();
            }
        }

        int Cmax = std::max({P1_time, P2_time, P3_time});
        if (Cmax < minCmax)
        {
            minCmax = Cmax;
            best_bitmask = std::vector<int>(2 * num_tasks, 0);
            for (int i = 0; i < num_tasks; ++i)
            {
                best_bitmask[2 * i] = (bitmask >> (2 * i)) & 1;
                best_bitmask[2 * i + 1] = (bitmask >> (2 * i + 1)) & 1;
            }
        }
    }

    // Print the best schedule
    std::vector<Task> temp_machine1;
    std::vector<Task> temp_machine2;
    std::vector<Task> temp_machine3;
    for (int i = 0; i < num_tasks; ++i)
    {
        int machine = best_bitmask[2 * i] + 2 * best_bitmask[2 * i + 1];
        if (machine == 0)
        {
            temp_machine1.push_back(tasks[i]);
        }
        else if (machine == 1)
        {
            temp_machine2.push_back(tasks[i]);
        }
        else
        {
            temp_machine3.push_back(tasks[i]);
        }
    }
    return std::make_tuple(temp_machine1, temp_machine2, temp_machine3);
}

std::tuple<std::tuple<std::vector<Task>, std::vector<Task>, std::vector<Task>>, std::tuple<int, int, int>> PTAS_LSA_3(const std::vector<Task> &tasks, int P1_time, int P2_time, int P3_time)
{
    std::vector<Task> rankedTasks = tasks;
    std::vector<Task> P1; // Machine 1
    std::vector<Task> P2; // Machine 2
    std::vector<Task> P3; // Machine 3

    for (int i = 0; i < rankedTasks.size(); i++)
    {
        if (P1_time <= P2_time && P1_time <= P3_time)
        {
            P1.push_back(rankedTasks[i]);
            P1_time += rankedTasks[i].GetPj();
        }
        else if (P2_time <= P1_time && P2_time <= P3_time)
        {
            P2.push_back(rankedTasks[i]);
            P2_time += rankedTasks[i].GetPj();
        }
        else
        {
            P3.push_back(rankedTasks[i]);
            P3_time += rankedTasks[i].GetPj();
        }
    }
    return std::make_tuple(std::make_tuple(P1, P2, P3), std::make_tuple(P1_time, P2_time, P3_time));
}

void Problem::PTAS_3(int k) const
{
    std::vector<Task> tasks = m_tasks;
    // Step 1: Sort tasks by their processing time in descending order
    std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b)
              { return a.GetPj() > b.GetPj(); });

    // Step 2: Take first 'k' amount of tasks and sort them using CompleteReview_2()
    std::vector<Task> firstKTasks(tasks.begin(), tasks.begin() + k);
    std::tuple<std::vector<Task>, std::vector<Task>, std::vector<Task>> schedule = PTAS_CR_3(firstKTasks);
    std::vector<Task> machine_1 = std::get<0>(schedule);
    std::vector<Task> machine_2 = std::get<1>(schedule);
    std::vector<Task> machine_3 = std::get<2>(schedule);

    int machine1_time = 0;
    int machine2_time = 0;
    int machine3_time = 0;
    for (int i = 0; i < machine_1.size(); i++)
    {
        machine1_time += machine_1[i].GetPj();
    }
    for (int i = 0; i < machine_2.size(); i++)
    {
        machine2_time += machine_2[i].GetPj();
    }
    for (int i = 0; i < machine_3.size(); i++)
    {
        machine2_time += machine_3[i].GetPj();
    }

    // Step 3: Take the rest of the tasks and sort them using LSA()
    std::vector<Task> restTasks(tasks.begin() + k, tasks.end());
    // std::pair<std::vector<Task>, std::vector<Task>> schedule2 = PTAS_LSA(restTasks, machine1_time, machine2_time);
    // std::tuple<std::tuple<std::vector<Task>,std::vector<Task>,std::vector<Task>>,std::tuple<int,int,int>>
    auto [task, times] = PTAS_LSA_3(restTasks, machine1_time, machine2_time, machine3_time);
    auto [temp1, temp2, temp3] = task;
    // std::vector<Task> temp1 = std::get<1>(tasks);
    auto [t1, t2, t3] = times;

    machine1_time = t1;
    machine2_time = t2;
    machine3_time = t3;

    machine_1.insert(machine_1.end(), temp1.begin(), temp1.end());
    machine_2.insert(machine_2.end(), temp2.begin(), temp2.end());
    machine_3.insert(machine_3.end(), temp3.begin(), temp3.end());

    std::cout << "Machine 1 tasks: ";
    for (int i = 0; i < machine_1.size(); i++)
    {
        // machine1_time+=machine1_tasks[i].GetPj();
        std::cout << machine_1[i].GetTaskId() << ", ";
    }
    std::cout << std::endl
              << "Machine 2 tasks: ";
    for (int i = 0; i < machine_2.size(); i++)
    {
        // machine2_time+=machine2_tasks[i].GetPj();
        std::cout << machine_2[i].GetTaskId() << ", ";
    }
    std::cout << std::endl
              << "Machine 3 tasks: ";
    for (int i = 0; i < machine_3.size(); i++)
    {
        // machine2_time+=machine2_tasks[i].GetPj();
        std::cout << machine_3[i].GetTaskId() << ", ";
    }
    int CMAX = std::max(machine1_time, std::max(machine2_time, machine3_time));
    std::cout << std::endl
              << "CMAX: " << CMAX << std::endl;
}