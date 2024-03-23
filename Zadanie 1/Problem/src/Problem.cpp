#include <algorithm>
#include "Problem.hpp"
#include "Heap.hpp"

#include <iostream>

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
    std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task &a, const Task &b)
              { return a.GetRj() < b.GetRj(); });

    int criterion = CountCriterion(sortedTasks);

    Permutation solution(criterion, sortedTasks);

    return solution;
}

Permutation Problem::AlgorithmSortQj() const
{
    std::vector<Task> sortedTasks = m_tasks;
    std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task &a, const Task &b)
              { return a.GetQj() > b.GetQj(); });

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
    int criterion = CountCriterion(sortedTasks);
    Permutation solution(criterion, sortedTasks);

    return solution;
}

// earlier attempt at solution

Pair Problem::AlgorithmSchrageSep() const
{
    std::vector<Task> sortedTasksByRj = m_tasks;
    std::sort(sortedTasksByRj.begin(), sortedTasksByRj.end(), [](const Task &a, const Task &b)
              { return a.GetRj() < b.GetRj(); });

    Structure::Heap<Task> heapTaskByQj;
    heapTaskByQj.BuildHeap(m_tasks);
    std::vector<std::pair<Task, int>> answer;
    Task currentTask;

    int currentTime = 0;
    int workingTime = 0;
    int sorTaByRj = 0;
    int finishedTasksNr = 0;
    while (!heapTaskByQj.Empty() || (finishedTasksNr < m_tasks.size()))
    {
        if (!heapTaskByQj.Empty() && (heapTaskByQj.GetMaximum().GetRj() <= currentTime) && (workingTime == 0))
        {
            currentTask = heapTaskByQj.GetMaximum(); // move tasks that can start now to temp
            heapTaskByQj.EraseMaximum();             // and erase those tasks from heap
            auto toRemove = std::find(sortedTasksByRj.begin(), sortedTasksByRj.end(), currentTask);
            sortedTasksByRj.erase(toRemove, sortedTasksByRj.end());
        }
        else if ((sorTaByRj < sortedTasksByRj.size()) && (workingTime == 0))
        {
            currentTask = sortedTasksByRj[sorTaByRj];
            heapTaskByQj.Erase(sortedTasksByRj[sorTaByRj]);
            sorTaByRj++;
        }

        workingTime++;
        currentTime++;

        if (workingTime >= currentTask.GetPj())
        {
            answer.push_back(std::make_pair(currentTask, currentTime - currentTask.GetPj()));
            workingTime = 0;
            finishedTasksNr++;
        }
        else if (!sortedTasksByRj.empty())
        {
            if ((currentTime >= sortedTasksByRj.front().GetRj()) && (currentTask.GetQj() < heapTaskByQj.GetMaximum().GetQj()))
            {
                Task *newTask = new Task(currentTask.GetPj() - workingTime, currentTask.GetRj(), currentTask.GetQj(), currentTask.GetTaskId());
                answer.push_back(std::make_pair(currentTask, currentTime - 1));
                workingTime = 0;
                heapTaskByQj.Insert(*newTask);
            }
        }
    }


    std::cout << "( Task_ID , Start time ):" << std::endl;
    for (const auto& pair : answer) {
    std::cout << "("<<pair.first << ", " << pair.second<<")" << std::endl;
    }

    std::cout << std::endl;


    // End of Gantts chart
    int criterion = CountCriterion(answer);
    Pair solution(criterion, answer);
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