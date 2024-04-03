#include <algorithm>
#include "Problem.hpp"
#include "Heap.hpp"
#include "Node.hpp"

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
        std::cout << "task: pj " << m_tasks[i].GetPj() << " rj " << m_tasks[i].GetRj() << " qj " << m_tasks[i].GetQj() << " taskId " << m_tasks[i].GetTaskId() << std::endl;
    }

    std::cout << "Number od tasks " << m_tasksNr << std::endl;
}

// it is example algorithm, just to test classes
Permutation Problem::ExampleAlgorith() const
{
    std::vector<Task> rankedTasks;

    for (int i = 0; i < m_tasksNr; i++)
    {
        rankedTasks.push_back(m_tasks[i]);
    }

    int criterion = CountCriterion(rankedTasks);

    Permutation solution(criterion, rankedTasks);

    return solution;
}

Permutation Problem::AlgorithmSortRj() const
{
    std::vector<Task> sortedTasks = m_tasks;

    auto start = std::chrono::high_resolution_clock::now();

    std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task &a, const Task &b)
              { return a.GetRj() < b.GetRj(); });

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed time: " << std::defaultfloat << duration.count() << " seconds" << std::endl;

    int criterion = CountCriterion(sortedTasks);

    Permutation solution(criterion, sortedTasks);

    return solution;
}

Permutation Problem::AlgorithmSortQj() const
{
    std::vector<Task> sortedTasks = m_tasks;

    auto start = std::chrono::high_resolution_clock::now();

    std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task &a, const Task &b)
              { return a.GetQj() > b.GetQj(); });

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed time: " << std::defaultfloat << duration.count() << " seconds" << std::endl;

    int criterion = CountCriterion(sortedTasks);

    Permutation solution(criterion, sortedTasks);

    return solution;
}

// it looks for the most optimal solution using permutations
// CAUTION: it is sutable solution only if the m_tasks <= 12
Permutation Problem::AlgorithmCompleteReview() const
{
    if (m_tasks.size() >= CRITICAL_NUMBER)
    {
        std::cout << "WARNING: It will take a long time." << std::endl;
    }

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Task> sortedTasks = m_tasks;
    std::vector<Task> currentChacked = m_tasks;
    int criterion = CountCriterion(sortedTasks);
    int currentCriterion = criterion;

    for (int i = 0; i < m_tasks.size() - 1; i++)
    {
        currentChacked = CompleteReview(sortedTasks, i, criterion);
        currentCriterion = CountCriterion(currentChacked);

        // if criterion is better, save this solution
        if (currentCriterion < criterion)
        {
            criterion = currentCriterion;
            sortedTasks = currentChacked;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed time: " << std::defaultfloat << duration.count() << " seconds" << std::endl;

    Permutation solution(criterion, sortedTasks);
    return solution;
}

// it returns the most optimal task orter in subvector
std::vector<Task> Problem::CompleteReview(std::vector<Task> tasks, int fromTask, int criterion) const
{
    if (fromTask > tasks.size() - 2)
    {
        return tasks;
    }
    std::vector<Task> sortedTasks = tasks;
    std::vector<Task> currentChacked = tasks;
    int currentCriterion = criterion;

    for (int i = fromTask; i < tasks.size(); i++)
    {

        std::swap(currentChacked[fromTask], currentChacked[i]);

        currentChacked = CompleteReview(currentChacked, fromTask + 1, criterion);
        currentCriterion = CountCriterion(currentChacked);

        // if criterion is better save this solution
        if (currentCriterion < criterion)
        {
            criterion = currentCriterion;
            sortedTasks = currentChacked;
        }
    }

    return sortedTasks;
}

Permutation Problem::AlgorithmSchrage() const
{
    // Sort by Rj
    std::vector<Task> sortedTasksByRj = m_tasks;

    // auto start = std::chrono::high_resolution_clock::now();

    std::sort(sortedTasksByRj.begin(), sortedTasksByRj.end(), [](const Task &a, const Task &b)
              { return a.GetRj() < b.GetRj(); });

    // Prepare heap with ordered by Qj decreasing
    Structure::Heap<Task> heapTaskByQj;
    heapTaskByQj.BuildHeap(m_tasks);

    std::vector<Task> sortedTasks = m_tasks;
    int currentTime = 0;
    int sorTaByRj = 0; // sortedTasksByRj's iterator
    for (int j = 0; j < sortedTasks.size(); j++)
    {
        if (!heapTaskByQj.Empty() && heapTaskByQj.GetMaximum().GetRj() <= currentTime) // is there are any tasks in queue
        {
            sortedTasks[j] = heapTaskByQj.EraseMaximum(); // choose the task with maximum qj
            auto toRemove = std::find(sortedTasksByRj.begin(), sortedTasksByRj.end(), sortedTasks[j]);
            sortedTasksByRj.erase(toRemove, sortedTasksByRj.end());
        }
        else if (!sortedTasksByRj.empty()) // if there is no waiting task choose task with min rj
        {
            sortedTasks[j] = sortedTasksByRj[sorTaByRj];
            heapTaskByQj.Erase(sortedTasksByRj[sorTaByRj]);
            sorTaByRj++;
        }

        currentTime = sortedTasks[j].GetPj() + std::max(currentTime, sortedTasks[j].GetRj()); // count current time
    }

    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duration = end - start;
    // std::cout << "Elapsed time: " << std::defaultfloat << duration.count() << " seconds" << std::endl;

    int criterion = CountCriterion(sortedTasks);
    Permutation solution(criterion, sortedTasks);

    return solution;
}

// earlier attempt at solution
Pair Problem::AlgorithmSchrageSep() const
{
    std::vector<Task> sortedTasksByRj = m_tasks;

    auto start = std::chrono::high_resolution_clock::now();

    std::sort(sortedTasksByRj.begin(), sortedTasksByRj.end(), [](const Task &a, const Task &b)
              { return a.GetRj() < b.GetRj(); });

    Structure::Heap<Task> heapTaskByQj;
    std::vector<std::pair<Task, int>> answer;
    Task currentTask;

    int currentTime = 0;
    int workingTime = 0;
    int sorTaByRj = 0;
    int finishedTasksNr = 0;
    int elemInHeap = 0;

    // add first task
    currentTime = sortedTasksByRj[sorTaByRj].GetRj();
    heapTaskByQj.Insert(sortedTasksByRj[sorTaByRj]);
    sorTaByRj++;

    while (sorTaByRj < sortedTasksByRj.size())
    {
        if (!heapTaskByQj.Empty())
        {
            currentTask = heapTaskByQj.GetMaximum();
            heapTaskByQj.EraseMaximum();
            workingTime = std::min(sortedTasksByRj[sorTaByRj].GetRj() - currentTime, currentTask.GetPj());
            if (workingTime == currentTask.GetPj())
            {
                answer.push_back(std::make_pair(currentTask, currentTime));
                currentTime = currentTime + workingTime;
                workingTime = 0;
            }
            else
            {
                // add the rest of the task to heap
                Task *newTask = new Task(currentTask.GetPj() - workingTime, currentTask.GetRj(), currentTask.GetQj(), currentTask.GetTaskId());
                answer.push_back(std::make_pair(currentTask, currentTime));
                workingTime = 0;
                heapTaskByQj.Insert(*newTask);

                currentTime = sortedTasksByRj[sorTaByRj].GetRj();
            }
        }
        else
        {
            std::cout << "heap is empty:(" << std::endl;
        }
        // add new ready task
        if (heapTaskByQj.Empty())
            currentTime = sortedTasksByRj[sorTaByRj].GetRj();
        while (sortedTasksByRj[sorTaByRj].GetRj() == currentTime)
        {
            heapTaskByQj.Insert(sortedTasksByRj[sorTaByRj]);
            sorTaByRj++;
        }
    }

    while (!heapTaskByQj.Empty())
    {
        currentTask = heapTaskByQj.GetMaximum();
        heapTaskByQj.EraseMaximum();
        answer.push_back(std::make_pair(currentTask, currentTime));
        currentTime = currentTime + currentTask.GetPj();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed time: " << std::defaultfloat << duration.count() << " seconds" << std::endl;

    std::cout << std::endl;

    int criterion = CountCriterion(answer);
    Pair solution(criterion, answer);
    return solution;
}

Permutation Problem::OurAlgorithm() const
{
    std::vector<Task> sortQJ = m_tasks;
    std::vector<Task> sortRJ = m_tasks;
    std::vector<Task> sortedtasks;

    auto start = std::chrono::high_resolution_clock::now();

    size_t size = sortQJ.size();

    std::sort(sortRJ.begin(), sortRJ.end(), [](const Task &a, const Task &b)
              { return a.GetRj() < b.GetRj(); });

    sortedtasks.insert(sortedtasks.end(), sortRJ.begin(), sortRJ.begin() + size / 2);

    std::sort(sortQJ.begin(), sortQJ.end(), [](const Task &a, const Task &b)
              { return a.GetQj() < b.GetQj(); });

    size_t j = size / 2;
    for (size_t i = size / 2; i < size; i++)
    { // Skip tasks that are present in the first half of sortRJ
        while (j < sortQJ.size() && std::find(sortedtasks.begin(), sortedtasks.end(), sortQJ[j]) != sortedtasks.end())
        {
            j++;
        }
        if (j < sortQJ.size())
        {
            sortedtasks.push_back(sortQJ[j]);
            j++;
        }
    }

    for (; j < sortQJ.size(); j++)
    { // Add remaining tasks from sortQJ if not present in sortedTasks
        sortedtasks.push_back(sortQJ[j]);
    }

    for (const Task &task : sortRJ)
    { // Add remaining tasks from sortRJ if not already present in sortedTasks
        if (std::find(sortedtasks.begin(), sortedtasks.end(), task) == sortedtasks.end())
        {
            sortedtasks.push_back(task);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed time: " << std::defaultfloat << duration.count() << " seconds" << std::endl;

    int criterion = CountCriterion(sortedtasks);

    Permutation solution(criterion, sortedtasks);

    return solution;
}

// it measures the criterion Cmax
int Problem::CountCriterion(std::vector<Task> rankedTasks) const
{
    int cMax = 0;
    int cooling = 0;
    for (int j = 0; j < rankedTasks.size(); j++)
    {
        int last = cMax;
        // criterium taking into account avaliability and execution time
        cMax = rankedTasks[j].GetPj() + std::max(cMax, rankedTasks[j].GetRj());

        cooling = cooling - (cMax - last);

        // take into counting cooling time
        if (cooling <= rankedTasks[j].GetQj())
            cooling = rankedTasks[j].GetQj();

        // if last task add colling time
        if (j == rankedTasks.size() - 1)
            cMax = cMax + cooling;
    }
    return cMax;
}

// it measures the criterion Cmax for solution as pair
int Problem::CountCriterion(std::vector<std::pair<Task, int>> rankedTasks) const
{

    int cMax = 0;
    int cooling = 0;
    int last = 0;

    for (int j = 0; j < rankedTasks.size(); j++)
    {

        if (j < rankedTasks.size() - 1)
        {
            cMax = rankedTasks[j + 1].second;
            last = rankedTasks[j].second;

            if (rankedTasks[j].first.GetPj() - (cMax - last) == 0)
            {
                cooling = cooling - (cMax - last);

                // take into counting cooling time
                if (cooling <= rankedTasks[j].first.GetQj())
                    cooling = rankedTasks[j].first.GetQj();
            }
        }
        else
        {
            cMax += rankedTasks[j].first.GetPj();
            cooling = cooling - rankedTasks[j].first.GetPj();

            // take into counting cooling time
            if (cooling <= rankedTasks[j].first.GetQj())
                cooling = rankedTasks[j].first.GetQj();

            if (j == rankedTasks.size() - 1)
                cMax = cMax + cooling;
        }
    }
    return cMax;
}

Permutation Problem::AlgorithmCarlier() const
{
    // create node
    Pair schrageSepSolution = AlgorithmSchrageSep();
    int lowBarier = schrageSepSolution.GetCriterion();
    Permutation solution = AlgorithmSchrage();
    Node node(m_tasks, lowBarier);
    Permutation currentCheck;

    std::cout << " loweBar " << lowBarier << "  upBarier" << node.GetUpBarier() << std::endl;
    if (node.IsOptimal())
    {
        std::cout << "Optimal" << std::endl;
        if (node.GetPermutation().GetCriterion() < solution.GetCriterion())
        {
            solution = node.GetPermutation();
        }
    }
    else if (lowBarier < node.GetUpBarier())
    {

        currentCheck = Carlier(node, node.GetLowBarier(), node.GetUpBarier());
        if (currentCheck.GetCriterion() < solution.GetCriterion())
        {
            solution = currentCheck;
        }
    }

    // check if node own optimal soltion
    // if not - create two new nodes

    return solution;
}

Node Problem::CreateNodeQj(int lowBarier, Node parent, int upBarier) const
{
    std::cout << "create node " << std::endl; 
    Task interferenceTask = parent.GetInterferenceTask();
    std::cout << "interference task taken" << std::endl; 
    std::vector<Task> tasks = parent.GetPermutation().GetRankedTasks();
    std::cout << "tasks initialized" << std::endl; 
    auto toChange = std::find(tasks.begin(), tasks.end(), interferenceTask);
    std::cout << "to change " << std::endl; 
    int cId = toChange - tasks.begin(); // a moze wystarczy tutaj zwracac inta?
    int bId;
    // create new task;
    std::vector<Task> temTasks(tasks.begin(), tasks.begin() + cId);
    std::cout << "temTasks " << std::endl; 
    int pk = parent.GetCmax() - CountCriterion(temTasks);
    int qc = std::max(tasks[cId].GetQj(), pk + tasks[bId].GetQj());
    Task *newTask = new Task(tasks[cId].GetPj(), tasks[cId].GetRj(), qc, tasks[cId].GetTaskId());
    std::cout << "new Task " << std::endl;
    // add new task
    // tasks.erase(toChange);
    tasks[cId] = *newTask;
    std::cout << "erase " << std::endl;
    Node *pNode = new Node(m_tasks, lowBarier, upBarier);
    std::cout << "temTasks " << std::endl;
    delete newTask;
    std::cout << "po delate " << std::endl;
    return *pNode;
}

Node Problem::CreateNodeRj(int lowBarier, Node parent, int upBarier) const
{
    Task interferenceTask = parent.GetInterferenceTask();
    std::vector<Task> tasks = parent.GetPermutation().GetRankedTasks();
    auto toChange = std::find(tasks.begin(), tasks.end(), interferenceTask);
    int cId = toChange - tasks.begin(); // a moze wystarczy tutaj zwracac inta?
    int bId;
    // create new task;
    std::vector<Task> temTasks(tasks.begin(), tasks.begin() + cId);
    int pk = parent.GetCmax() - CountCriterion(temTasks);
    int rk = tasks[cId].GetRj();
    std::vector<Task> tasksCritic = parent.GetCriticalPath();
    for (int i = 0; i < tasksCritic.size(); i++)
    {
        if (tasksCritic[i].GetRj() < rk)
            rk = tasksCritic[i].GetRj();
    }
    int rc = std::max(tasks[cId].GetQj(), pk + rk);
    Task *newTask = new Task(tasks[cId].GetPj(), rc, tasks[cId].GetQj(), tasks[cId].GetTaskId());
    // add new task
    tasks.erase(toChange);
    Node *pNode = new Node(m_tasks, lowBarier, upBarier);
    delete newTask;
    return *pNode;
}

Permutation Problem::Carlier(Node node, int lowBarier, int upBarrier) const
{
    std::cout << "Carlier" << std::endl;
    Permutation solution = node.GetPermutation();
    std::cout << "solution zainicjalizowane" << std::endl;
    Permutation currentCheck;
    std::cout << "node.GetUpBarier() " << node.GetUpBarier() << "node.GetLowBarier()  " << node.GetLowBarier() << std::endl;
    if (node.GetUpBarier() > node.GetLowBarier())
    {
        Node nodeQj = CreateNodeQj(lowBarier, node, upBarrier);
        std::cout << "node created " << std::endl;
        // the optimal solution in this path is found
        if (nodeQj.IsOptimal())
        {
            std::cout << "Optimal Qj" << std::endl;
            if (nodeQj.GetPermutation().GetCriterion() < solution.GetCriterion())
            {
                solution = nodeQj.GetPermutation();
            }
        }
        else if (nodeQj.GetLowBarier() < nodeQj.GetUpBarier())
        {
            
            currentCheck = Carlier(nodeQj, nodeQj.GetLowBarier(), nodeQj.GetUpBarier());
            if (currentCheck.GetCriterion() < solution.GetCriterion())
            {
                solution = currentCheck;
            }
        }

        Node nodeRj = CreateNodeRj(lowBarier, node, upBarrier);

        // the optimal solution in this path is found
        if (nodeRj.IsOptimal())
        {
            std::cout << "Optimal Rj" << std::endl;
            if (nodeRj.GetPermutation().GetCriterion() < solution.GetCriterion())
            {
                solution = nodeRj.GetPermutation();
            }
        }
        else if (nodeRj.GetLowBarier() < nodeRj.GetUpBarier())
        {
            currentCheck = Carlier(nodeRj, nodeRj.GetLowBarier(), nodeRj.GetUpBarier());
            if (currentCheck.GetCriterion() < solution.GetCriterion())
            {
                solution = currentCheck;
            }
        }
    }

    return solution;
}
