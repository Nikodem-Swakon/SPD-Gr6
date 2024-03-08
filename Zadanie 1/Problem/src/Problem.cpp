#include <algorithm>

#include "Problem.hpp"

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
Solution Problem::ExampleAlgorith() const
{
    std::vector<Task> rankedTasks;

    for (int i = 0; i < m_tasksNr; i++)
    {
        rankedTasks.push_back(m_tasks[i]);
    }

    int criterion = CountCriterion(rankedTasks);

    Solution solution(criterion, rankedTasks);

    return solution;
}

Solution Problem::AlgorithmSortRj() const
{
    std::vector<Task> sortedTasks = m_tasks;
    std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task &a, const Task &b)
              { return a.GetRj() < b.GetRj(); });

    int criterion = CountCriterion(sortedTasks);

    Solution solution(criterion, sortedTasks);

    return solution;
}

Solution Problem::AlgorithmSortQj() const
{
    std::vector<Task> sortedTasks = m_tasks;
    std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task &a, const Task &b)
              { return a.GetQj() < b.GetQj(); });

    int criterion = CountCriterion(sortedTasks);

    Solution solution(criterion, sortedTasks);

    return solution;
}

// it looks for the most optimal solution using permutations
// CAUTION: it is sutable solution only if the m_tasks <= 12
Solution Problem::AlgorithmCompleteReview() const
{
    if (m_tasks.size() > CRITICAL_NUMBER)
    {
        std::cout << "WARNING: It will take a long time." << std::endl;
    }

    std::vector<Task> sortedTasks = m_tasks;
    std::vector<Task> currentChacked = m_tasks;
    int criterion = CountCriterion(sortedTasks);
    int currentCriterion = criterion;

    for (int i = m_tasks.size() - 3; i > 0; i--)
    {
        currentChacked = CompleteReview(currentChacked, i, criterion);
        currentCriterion = CountCriterion(currentChacked);

        std::cout << "currentChecked in AlgorithmCompleteReview" << std::endl;
        for (int j = 0; j < currentChacked.size(); j++)
        {
            std::cout << currentChacked[j].GetTaskId() << " ";
        }
        std::cout << std::endl;
        std::cout << i << ". currentCriterion and criterion in AlgorithmCompleteReview " << currentCriterion << " " << criterion << std::endl;
        if (currentCriterion < criterion)
        {
            criterion = currentCriterion;
            sortedTasks = currentChacked;
            std::cout << "changed" << std::endl;
        }

        std::cout << "sortedTasks in AlgorithmCompleteReview" << std::endl;
        for (int j = 0; j < sortedTasks.size(); j++)
        {
            std::cout << sortedTasks[j].GetTaskId() << " ";
        }
        std::cout << std::endl;
    }

    Solution solution(criterion, sortedTasks);
    return solution;
}

// it returns the most optimal task orter in subvector
std::vector<Task> Problem::CompleteReview(std::vector<Task> tasks, int fromTask, int criterion) const
{
    std::vector<Task> sortedTasks = tasks;
    std::vector<Task> currentChacked = tasks;
    int currentCriterion = criterion;

    for (int i = fromTask; i < tasks.size() - 2; i++)
    {
        std::swap(currentChacked[i + 1], currentChacked[i + 2]);
        std::cout << "  currentChecked in CompleteReview" << std::endl;
        std::cout << "  ";
        for (int j = 0; j < currentChacked.size(); j++)
        {
            std::cout << currentChacked[j].GetTaskId() << " ";
        }
        std::cout << std::endl;

        currentCriterion = CountCriterion(currentChacked);
        std::cout << "  " << i << ". currentCriterion and criterion in CompleteReview " << currentCriterion << " " << criterion << std::endl;
        if (currentCriterion < criterion)
        {
            criterion = currentCriterion;
            sortedTasks = currentChacked;
            std::cout << "  changed" << std::endl;
        }
    }
    std::cout << "  sortedTasks in CompleteReview" << std::endl;
    std::cout << "  ";
    for (int j = 0; j < sortedTasks.size(); j++)
    {
        std::cout << sortedTasks[j].GetTaskId() << " ";
    }
    std::cout << std::endl;
    return sortedTasks;
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