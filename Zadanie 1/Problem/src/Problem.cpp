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

    double criterion = CountCriterion(rankedTasks);

    Solution solution(criterion, rankedTasks);

    return solution;
}

Solution Problem::AlgorithmSortRj() const {
    std::vector<Task> sortedTasks;
    std::sort(sortedTasks.begin(), sortedTasks.end(),[](const Task& a, const Task& b) {
        return a.GetRj() < b.GetRj();
    });

    double criterion = CountCriterion(sortedTasks);

    Solution solution(criterion, sortedTasks);

    return solution;
}

Solution Problem::AlgorithmSortQj() const { 
    std::vector<Task> sortedTasks;
    std::sort(sortedTasks.begin(), sortedTasks.end(),[](const Task& a, const Task& b) {
        return a.GetQj() < b.GetQj();
    });


    double criterion = CountCriterion(sortedTasks);

    Solution solution(criterion, sortedTasks);

    return solution;
}
// it measures the criterion Cmax
double Problem::CountCriterion(std::vector<Task> rankedTasks) const
{
    return 0;
}