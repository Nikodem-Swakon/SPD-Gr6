#include <algorithm>
//#include <iostream>
//#include <vector>
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
              { return a.GetQj() > b.GetQj(); });

    int criterion = CountCriterion(sortedTasks);

    Solution solution(criterion, sortedTasks);

    return solution;
}

// it looks for the most optimal solution using permutations
// CAUTION: it is sutable solution only if the m_tasks <= 12
Solution Problem::AlgorithmCompleteReview() const
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

    Solution solution(criterion, sortedTasks);
    return solution;
}

// it returns the most optimal task orter in subvector
std::vector<Task> Problem::CompleteReview(std::vector<Task> tasks, int fromTask, int criterion) const
{
    if(fromTask > tasks.size() - 2)
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

Solution Problem::AlgorithmSchrage () const
{
    // Sort by Rj but check for qj 
    int Task_end_time =0;
    int current_time=0;
    // Sort by RJ first
    //std::vector<Task> RsortedTasks = m_tasks;
    std::vector<Task> UnScheduledTasks = m_tasks;
    int Times = UnScheduledTasks.size();
    std::vector<Task> ReadyTasks;
    std::vector<Task> answer;
    std::sort(UnScheduledTasks.begin(), UnScheduledTasks.end(), [](const Task &a, const Task &b)                     //sort tasks by release time
              { return a.GetRj() < b.GetRj(); });
    
    while(answer.size()!=Times){ 
        std::cout<<"UNT:"<<UnScheduledTasks.size()<<::std::endl;                                                                               // while unscheduledtasks vector isn't empty
        auto it = remove_if(UnScheduledTasks.begin(),UnScheduledTasks.end(), [current_time](const Task& task){       // remove and hold a task from it
            return task.GetRj() <= current_time;                                                                     // if Release time of the task is equal/smaller than current time
        });
        for (auto task=it; task!=UnScheduledTasks.end(); task++){
            ReadyTasks.push_back(*task);                                                                             // Adding tasks to readytasks vector
        }
        UnScheduledTasks.erase(it, UnScheduledTasks.end()); 
        std::cout<<"UNT2:"<<UnScheduledTasks.size()<<::std::endl;                                                         // Erasing ready tasks from unscheduledtasks vector

        if (!ReadyTasks.empty()){                                                                                    // If readytasks vector is not empty
            int min_release_time = ReadyTasks.front().GetRj();                                                       // Get the smallest release time
            for (const auto& task : ReadyTasks){                                                                     
                min_release_time = std::min(min_release_time, task.GetRj());                                         // Determine min_release time
            }
            current_time = min_release_time;                                                                         // Update time
        }
        auto Qmax_Task = max_element(ReadyTasks.begin(), ReadyTasks.end(), [](const Task& T1, const Task& T2){
            return T1.GetQj() < T2.GetQj();                                                                          // Find task with maximum cooldown time
        });

        answer.push_back(*Qmax_Task);                                                                                // Save task with maximum cooldown time 
        //std::cout<<"task pushed"<<std::endl;
        current_time+=Qmax_Task->GetPj();                                                                            // Update time

        //ReadyTasks.erase(ReadyTasks.begin()+ std::distance(ReadyTasks.begin(),Qmax_Task));                                                                                 // Erase task from Readytasks vector
        ReadyTasks.erase(Qmax_Task);




    }
        int criterion = CountCriterion(answer);
        Solution solution(criterion, answer);
        return solution;
}

//earlier attempt at solution
/* for(int i=0;i<RsortedTasks.size();i++){                    // For every task in vector do:
        while(RsortedTasks[i].GetRj()<=current_time){          // While release time of task is <= current time 
            ReadyTasks.push_back(RsortedTasks[i]);             // Push task to Readytasks vector
            current_time+=RsortedTasks[i].GetPj();             // Advance current time by Process time of current task
        }
      
    }*/


//Solution Problem::AlgorithmSchrage_sep() const{}


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