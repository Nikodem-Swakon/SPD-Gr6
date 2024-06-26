#include <algorithm>
#include "Problem.hpp"
#include <climits>
#include <iostream>
#include <chrono>
#include <tuple>
#include <numeric>
#include <algorithm> // std::sort
#include <set>

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

// Na 3.0

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

void Problem::NEH() const
{
    std::vector<Task> rankedTasks = m_tasks;
    int N = m_tasks.size();
    if (N == 0)
        return;

    //   for (const auto &task : rankedTasks) {std::cout << task << std::endl;} // PRINTING ALL PJ VALUES FOR EACH TASK
    // std::cout<<N<<std::endl;  // PRINT AMOUNT OF TASKS

    // Step 1: Calculate total processing time for each task
    std::vector<std::pair<int, Task>> totalProcessingTimes;
    for (const auto &task : m_tasks)
    {
        int totalProcessingTime = std::accumulate(task.GetValues().begin(), task.GetValues().end(), 0);
        totalProcessingTimes.push_back({totalProcessingTime, task});
    }

    // Step 2: Sort tasks in non-increasing order of their total processing times
    std::sort(totalProcessingTimes.begin(), totalProcessingTimes.end(), [](const std::pair<int, Task> &a, const std::pair<int, Task> &b)
              { return a.first > b.first; });

    // Step 3: Build the sequence using the NEH heuristic
    std::vector<Task> sequence;
    for (const auto &[totalTime, task] : totalProcessingTimes)
    {
        std::vector<Task> bestSequence = sequence;
        int bestMakespan = std::numeric_limits<int>::max();

        // Try inserting the task at all positions in the current sequence
        for (size_t i = 0; i <= sequence.size(); ++i)
        {
            std::vector<Task> tempSequence = sequence;
            tempSequence.insert(tempSequence.begin() + i, task);
            int makespan = calculateMakespan(tempSequence);

            if (makespan < bestMakespan)
            {
                bestMakespan = makespan;
                bestSequence = tempSequence;
            }
        }

        sequence = bestSequence;
    }

    /* UJEDNOLICILAM WYSWIETLANIE, to jest stay kod
        // // Print the final sequence and makespan
        // std::cout << "Final task sequence:\n";
        // for (const auto &task : sequence)
        // {
        //     std::cout << task << std::endl;
        // }
        // std::cout << "Final makespan: " << calculateMakespan(sequence) << std::endl;
    */

    std::cout << "Solution" << std::endl;
    //DisplayTasks(sequence);
    std::cout << "\033[0;32m Cmax: \033[1;32m" << CalculateCMax(sequence) << "\033[0m" << std::endl;
}

void Problem::CompleteReview() const
{
    if (m_tasks.empty())
        return;

    std::vector<Task> bestSequence = m_tasks;
    int bestMakespan = std::numeric_limits<int>::max();

    std::vector<Task> currentSequence = m_tasks;
    // int x = 0;
    //  Generate all permutations of the task sequence
    do
    {

        int currentMakespan = calculateMakespan(currentSequence);

        if (currentMakespan < bestMakespan)
        {
            bestMakespan = currentMakespan;
            bestSequence = currentSequence;
            // std::cout << "curr_best_makespan: " << bestMakespan << std::endl;
            // std::cout << "Current perm num: " << x << std::endl;
            // x++;
        }
    } while (std::next_permutation(currentSequence.begin(), currentSequence.end(), [](const Task &a, const Task &b)
                                   {
                                       return a.GetValues() > b.GetValues(); // Comparison based on execution times
                                   }));

    /* UJEDNOLICILAM WYSWETLANIE, to jest stary kod

        // // Print the best sequence and its makespan
        // std::cout << "Best task sequence:\n";
        // for (const auto &task : bestSequence)
        // {
        //     std::cout << task << std::endl;
        // }
        // std::cout << "Best makespan: " << bestMakespan << std::endl;
    */

    std::cout << "Solution" << std::endl;
    DisplayTasks(bestSequence);
    std::cout << "\033[0;32m Cmax: \033[1;32m" << CalculateCMax(bestSequence) << "\033[0m" << std::endl;
}
// Na 3.0

// Na 3.5

bool CompareTasksTasksDec(const Task &a, const Task &b)
{
    return a.GetValueAt(0) < b.GetValueAt(0);
}

bool CompareTasksTasksAsc(const Task &a, const Task &b)
{
    return a.GetValueAt(0) > b.GetValueAt(0);
}

void Problem::Jhonson() const
{
    if (m_tasks[0].GetValuesSize() > 2)
    {
        std::cout << "It is Jhonson algorithm ONLY FOR 2 machines. " << std::endl;
        std::cout << "This test instane is unstuitable, plese use another one. " << std::endl;
    }
    else
    {
        int Cmax = INT_MAX;
        std::vector<Task> tasksL = {};
        std::vector<Task> tasksR = {};
        std::vector<Task> result = {};

        // Setp 1. Devide tasks on Jl and Jr (TasksL and TasksR)
        for (int i = 0; i < m_tasks.size(); i++)
        {
            m_tasks[i].GetValueAt(0) < m_tasks[i].GetValueAt(1) ? tasksL.push_back(m_tasks[i]) : tasksR.push_back(m_tasks[i]);
        }

        // Step 2. Sort Jl and Jr
        std::sort(tasksL.begin(), tasksL.end(), CompareTasksTasksDec);

        std::sort(tasksR.begin(), tasksR.end(), CompareTasksTasksAsc);

        // Step 3. Concatenate Jl with Jr
        result = tasksL;
        result.insert(result.end(), tasksR.begin(), tasksR.end());

        std::cout << "Solution" << std::endl;
        DisplayTasks(result);
        std::cout << "\033[0;32m Cmax: \033[1;32m" << CalculateCMax(result) << "\033[0m" << std::endl;
    }
}

// Na 3.5

// Na 4.0
int Problem::calculatePartialMakespan(const std::vector<Task> &sequence, const Task &newTask, size_t position, std::vector<std::vector<int>> &partialCompletionTimes) const
{
    int numMachines = newTask.GetValues().size();
    int numJobs = sequence.size() + 1;

    // Create a new completion times matrix with an additional row for the new task
    std::vector<std::vector<int>> completionTimes(numJobs, std::vector<int>(numMachines, 0));

    // Copy the existing partial completion times up to the insertion point
    for (size_t i = 0; i < position; ++i)
    {
        completionTimes[i] = partialCompletionTimes[i];
    }

    // Insert the new task and update the completion times
    for (int j = 0; j < numMachines; ++j)
    {
        if (position == 0 && j == 0)
        {
            completionTimes[position][j] = newTask.GetValues()[j];
        }
        else if (position == 0)
        {
            completionTimes[position][j] = completionTimes[position][j - 1] + newTask.GetValues()[j];
        }
        else if (j == 0)
        {
            completionTimes[position][j] = completionTimes[position - 1][j] + newTask.GetValues()[j];
        }
        else
        {
            completionTimes[position][j] = std::max(completionTimes[position - 1][j], completionTimes[position][j - 1]) + newTask.GetValues()[j];
        }
    }

    // Update the completion times for the tasks after the inserted task
    for (size_t i = position + 1; i < numJobs; ++i)
    {
        for (int j = 0; j < numMachines; ++j)
        {
            if (j == 0)
            {
                completionTimes[i][j] = completionTimes[i - 1][j] + sequence[i - 1].GetValues()[j];
            }
            else
            {
                completionTimes[i][j] = std::max(completionTimes[i - 1][j], completionTimes[i][j - 1]) + sequence[i - 1].GetValues()[j];
            }
        }
    }

    return completionTimes[numJobs - 1][numMachines - 1];
}

void Problem::FNEH() const
{
std::vector<Task> rankedTasks = m_tasks;
    int N = m_tasks.size(); // number of tasks
    int M = m_tasks[0].GetValues().size(); //number of machines
    //std::cout<<"M: "<<M<<std::endl;
    if (N == 0) return;

    // Step 1: Calculate total processing time for each task
    std::vector<std::pair<int, Task>> totalProcessingTimes;
    for (const auto& task : m_tasks) {
        int totalProcessingTime = std::accumulate(task.GetValues().begin(), task.GetValues().end(), 0);
        totalProcessingTimes.push_back({totalProcessingTime, task});
    }

    // Step 2: Sort tasks in non-increasing order of their total processing times
    std::sort(totalProcessingTimes.begin(), totalProcessingTimes.end(), [](const std::pair<int, Task>& a, const std::pair<int, Task>& b) {
        return a.first > b.first;
    });

    // Initialize sequence with the first task from m_tasks
    std::vector<Task> sequence = { m_tasks[0] };
    totalProcessingTimes.erase(std::remove_if(totalProcessingTimes.begin(), totalProcessingTimes.end(),
                                              [&](const std::pair<int, Task>& p) { return p.second.GetValues() == m_tasks[0].GetValues(); }),
                               totalProcessingTimes.end());

    // Step 3: Build the sequence using the QNEH heuristic
    for (size_t index = 0; index < totalProcessingTimes.size(); ++index) { //for each task
        const Task& task = totalProcessingTimes[index].second;
        std::vector<Task> bestSequence = sequence;
        int bestCMax = std::numeric_limits<int>::max();

        // Try inserting the task at all positions in the current sequence
        for (size_t i = 0; i <= sequence.size(); ++i) { //for each machine
            std::vector<Task> tempSequence = sequence;
            tempSequence.insert(tempSequence.begin() + i, task);

            int CMax = CalculateCMaxX(tempSequence);

            if (CMax < bestCMax) {
                bestCMax = CMax;
                bestSequence = tempSequence;
            }
        }

        sequence = bestSequence;
    }

    std::cout << "Solution" << std::endl;
    //DisplayTasks(sequence);
    std::cout << "\033[0;32m Cmax: \033[1;32m" << CalculateCMaxX(sequence) << "\033[0m" << std::endl;
}

int Problem::CalculateCMaxY(const std::vector<Task>& sequence) const {
    if (sequence.empty()) return 0;

    int numTasks = sequence.size();
    int numMachines = sequence[0].GetValues().size();
    std::vector<std::vector<int>> completionTimes(numTasks, std::vector<int>(numMachines, 0));

    // Initialize the completion times for the first task
    completionTimes[0][0] = sequence[0].GetValues()[0];
    for (int m = 1; m < numMachines; ++m) {
        completionTimes[0][m] = completionTimes[0][m - 1] + sequence[0].GetValues()[m];
    }

    // Calculate the completion times for the rest of the tasks
    for (int t = 1; t < numTasks; ++t) {
        completionTimes[t][0] = completionTimes[t - 1][0] + sequence[t].GetValues()[0];
        for (int m = 1; m < numMachines; ++m) {
            completionTimes[t][m] = std::max(completionTimes[t - 1][m], completionTimes[t][m - 1]) + sequence[t].GetValues()[m];
        }
    }

    return completionTimes[numTasks - 1][numMachines - 1];
}

std::pair<std::vector<int>, std::vector<int>> Problem::CalculateTables(const std::vector<Task>& schedule, const Task& task) const {
    int numTasks = schedule.size();
    int numMachines = task.GetValues().size();
    std::vector<int> incomingTable(numMachines, 0);
    std::vector<int> outgoingTable(numMachines, 0);

    // Calculate incoming table
    for (int m = 0; m < numMachines; ++m) {
        if (m == 0) {
            incomingTable[m] = (numTasks > 0 ? schedule[numTasks - 1].GetValues()[m] : 0) + task.GetValues()[m];
        } else {
            int prevTaskTime = numTasks > 0 ? incomingTable[m - 1] : 0;
            int prevMachineTime = numTasks > 0 ? schedule[numTasks - 1].GetValues()[m] : 0;
            incomingTable[m] = std::max(prevTaskTime, prevMachineTime) + task.GetValues()[m];
        }
    }

    // Calculate outgoing table
    for (int m = numMachines - 1; m >= 0; --m) {
        if (m == numMachines - 1) {
            outgoingTable[m] = task.GetValues()[m];
        } else {
            int nextTaskTime = outgoingTable[m + 1];
            int nextMachineTime = numTasks > 0 ? schedule[numTasks - 1].GetValues()[m] : 0;
            outgoingTable[m] = std::max(nextTaskTime, nextMachineTime) + task.GetValues()[m];
        }
    }

    return {incomingTable, outgoingTable};
}

int Problem::CalculateCMaxX(const std::vector<Task>& sequence) const {
    if (sequence.empty()) return 0;

    int numMachines = sequence[0].GetValues().size();
    std::vector<int> endTimes(numMachines, 0);

    for (const auto& task : sequence) {
        for (int m = 0; m < numMachines; ++m) {
            if (m == 0) {
                endTimes[m] += task.GetValues()[m];
            } else {
                endTimes[m] = std::max(endTimes[m], endTimes[m - 1]) + task.GetValues()[m];
            }
        }
    }

    return endTimes[numMachines - 1];
}

int Problem::CalculateCMaxQuick(int position, const std::vector<int>& incomingTable, const std::vector<int>& outgoingTable, const Task& task, const std::vector<Task>& sequence) const {
    int numMachines = incomingTable.size();
    std::vector<int> endTimes(numMachines, 0);

    // Calculate end times for the existing sequence
    for (const auto& seqTask : sequence) {
        for (int m = 0; m < numMachines; ++m) {
            if (m == 0) {
                endTimes[m] += seqTask.GetValues()[m];
            } else {
                endTimes[m] = std::max(endTimes[m], endTimes[m - 1]) + seqTask.GetValues()[m];
            }
        }
    }

    // Calculate Cmax by inserting the task
    int CMax = 0;
    for (int m = 0; m < numMachines; ++m) {
        if (m == 0) {
            CMax = std::max(CMax, endTimes[m] + task.GetValues()[m]);
        } else {
            CMax = std::max(CMax, std::max(endTimes[m], endTimes[m - 1]) + task.GetValues()[m]);
        }
    }

    return CMax;
}

// Na 4.0

// Na 4.5
// Na 4.5

// Na 5.0

int Problem::CalculateLowerBound(int level, std::vector<Task> scheduled) const
{
    if (level != 0)
    {
        std::vector<Task> subvector(scheduled.begin(), scheduled.begin() + level);
        // std::cout << "Subvector dla poziomu " << level << "." << std::endl;
        // DisplayTasks(subvector);
        int costScheduled = CalculateCMax(subvector);

        int est = 0;
        for (Task task : m_tasks)
        {
            est += task.GetValueAt(task.GetValuesSize() - 1);
        }

        for (int j = 0; j < level; j++)
        {
            est -= scheduled[j].GetValueAt(scheduled[j].GetValuesSize() - 1);
        }

        return costScheduled + est;
    }
    else
    {
        return CalculateCMax(scheduled);
    }
}

int Problem::CalculateUpperBound(int level, std::vector<Task> scheduled) const
{
    return CalculateCMax(scheduled);
}

void Problem::DisplayTasks(std::vector<Task> &tasks) const
{
    for (Task task : tasks)
    {
        std::cout << task << std::endl;
    }
}

void Problem::BranchAndBound() const
{
    std::vector<Task> vec = m_tasks;
    std::vector<Task> result = {};
    std::vector<bbNode> nodesQueue;
    std::set<std::vector<Task>> visitedPermutations;

    int globalUpperBound = INT_MAX;
    bbNode root(vec, 0);
    root.lowerBound = CalculateLowerBound(root.lev, root.permutation);
    root.upperBound = CalculateUpperBound(root.lev, root.permutation);
    nodesQueue.push_back(root); // it is root
    // std::cout << "Low barrier: " << root.lowerBound << std::endl;
    // std::cout << "Upper barrier: " << root.upperBound << std::endl;

    while (!nodesQueue.empty())
    {
        // std::cout << "Analiza nastepego noda" << std::endl;
        bbNode node = nodesQueue.front();
        nodesQueue.erase(nodesQueue.begin());

        // Poka nody
        // ShowNode(node);

        if (node.upperBound < globalUpperBound)
        {
            // std::cout << "Przypisz nowe rozwiazanie " << std::endl;
            globalUpperBound = node.upperBound;
            result = node.permutation;
        }

        // std::cout << "Tworzenie galezi" << std::endl;
        // Podziel na dzieci tego węzła
        for (size_t i = node.lev; i < vec.size(); ++i)
        {
            std::vector<Task> newPermutation = node.permutation;
            std::swap(newPermutation[node.lev], newPermutation[i]);
            if (visitedPermutations.find(newPermutation) == visitedPermutations.end())
            {
                visitedPermutations.insert(newPermutation);

                // std::cout << "Zaakceptowany node: " << std::endl;
                bbNode newNode(newPermutation, node.lev + 1);

                // Oblicz dolne ograniczenie tego noda
                newNode.lowerBound = CalculateLowerBound(newNode.lev, newNode.permutation);
                newNode.upperBound = CalculateUpperBound(newNode.lev, newNode.permutation);

                // std::cout << "LB: " << newNode.lowerBound << " i UB: " << newNode.upperBound << std::endl;

                if (newNode.lowerBound < globalUpperBound)
                {
                    // std::cout << "Dodano noda do kolejki" << std::endl;
                    nodesQueue.push_back(newNode);
                }
            }
        }
    }

    std::cout << "Solution" << std::endl;
    DisplayTasks(result);
    std::cout << "\033[0;32m Cmax: \033[1;32m" << CalculateCMax(result) << "\033[0m" << std::endl;
}

void Problem::ShowNode(const bbNode &node) const
{
    std::cout << "Level: " << node.lev << ", LB: " << node.lowerBound << ", UB: " << node.upperBound << std::endl;
    for (const Task &task : node.permutation)
    {
        std::cout << "Task ID: " << task.GetId() << std::endl;
    }
    std::cout << "------" << std::endl;
}

void Problem::GetNextPerm(std::vector<Task> &vec) const
{
    std::next_permutation(vec.begin(), vec.end());
}

// Na 5.0
