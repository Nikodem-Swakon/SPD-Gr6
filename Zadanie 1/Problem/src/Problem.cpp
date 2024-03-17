#include <algorithm>
// #include <iostream>
// #include <vector>
#include "Problem.hpp"
#include "Heap.hpp"
#include <utility>

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

Solution Problem::AlgorithmSchrage() const
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
    Solution solution(criterion, sortedTasks);

    return solution;
}

// earlier attempt at solution
/* for(int i=0;i<RsortedTasks.size();i++){                    // For every task in vector do:
        while(RsortedTasks[i].GetRj()<=current_time){          // While release time of task is <= current time
            ReadyTasks.push_back(RsortedTasks[i]);             // Push task to Readytasks vector
            current_time+=RsortedTasks[i].GetPj();             // Advance current time by Process time of current task
        }

    }*/

Solution Problem::AlgorithmSchrage_sep() const
{
    std::vector<Task> sortedTasksByRj = m_tasks;
    std::sort(sortedTasksByRj.begin(), sortedTasksByRj.end(), [](const Task &a, const Task &b)
              { return a.GetRj() < b.GetRj(); });

    Structure::Heap<Task> heapTaskByRj;
    Structure::Heap<Task> ReadyTasks;
    std::vector<Task> temp;
    std::vector<std::pair<int,int>> answer;
    std::vector<std::pair<int,int>> interrupted;
    heapTaskByRj.BuildHeap(m_tasks);
    int current_time =0;

    while (!heapTaskByRj.Empty() || !temp.empty() ){
    while(!heapTaskByRj.Empty() && heapTaskByRj.GetMaximum().GetRj()<=current_time){
        temp.push_back(heapTaskByRj.GetMaximum());                                      // move tasks that can start now to temp
        heapTaskByRj.EraseMaximum();                                                    // and erase those tasks from heap
    }
                                                    



        int previous_qj=0;
        int previous_pj=0;
    for (int i=0;i<temp.size();i++){

        std::sort(temp.begin(),temp.end(), [](const Task &a, const Task &b)
        {return a.GetQj()> b.GetQj();});                                             // sort tasks in temp by qj

        if ( previous_pj + answer.back().second - current_time<=0){                 //If previous task is completed
            answer.push_back(std::make_pair(temp[i].GetTaskId(),current_time));         //make new pair
            previous_qj=temp[i].GetQj();                                                // set prev_qj to curr_qj
            previous_pj=temp[i].GetPj();                                                // set prev_pj to curr_pj
            temp.erase(temp.begin()+i);                                                 // erase current task from temp vector
        }else{                                                                      //If previous task is not completed
            if (previous_qj<temp[i].GetQj()){                                           // Check if previous task has lower cooldown than current task
            
            //interrupted.push_back(std::make_pair(answer.back().first, previous_pj + answer.back().second - current_time)); // (ID,time to work left)
           
            Task NewTask( previous_pj + answer.back().second - current_time, 0, previous_qj , answer.back().first ); // Create new task with id of previous pj set to remaining work time etc
            temp.push_back(NewTask);
            
            answer.push_back(std::make_pair(temp[i].GetTaskId(),current_time));         // make new pair
            previous_qj=temp[i].GetQj();                                                // set prev_qj to curr_qj
            previous_pj=temp[i].GetPj();                                                // set prev_pj to curr_pj
            temp.erase(temp.begin()+i);                                                 // erase current task from temp vector 
            }
        }
       
        
    }
   }
    for (const auto &pair : answer) {
            std::cout << "Task ID: " << pair.first << ", Start Time: " << pair.second << std::endl;
        }
    
    int criterion = CountCriterion(temp); // NOT READY
    Solution solution(criterion, temp);
    return solution; 
}
   // Previous attempt 
    /*std::vector<Task> sortedTasksByRj = m_tasks;
    std::sort(sortedTasksByRj.begin(), sortedTasksByRj.end(), [](const Task &a, const Task &b)
              { return a.GetRj() < b.GetRj(); });

    Structure::Heap<Task> heapTaskByQj;
    heapTaskByQj.BuildHeap(m_tasks);
    std::vector<Task> scheduledTasks;
    std::vector<bool> taskCompleted(m_tasks.size(), false); // Flag to mark tasks as completed
    int currentTime = 0;

    while (!heapTaskByQj.Empty() || !sortedTasksByRj.empty()) {
        if (!sortedTasksByRj.empty() && sortedTasksByRj.front().GetRj() <= currentTime && !taskCompleted[sortedTasksByRj.front().GetTaskId() - 1]) {
            Task nextTask = sortedTasksByRj.front();
            sortedTasksByRj.erase(sortedTasksByRj.begin());
            std::cout << "(" << nextTask.GetTaskId() << ", " << currentTime << ")" << std::endl;
            currentTime += nextTask.GetPj();
            taskCompleted[nextTask.GetTaskId() - 1] = true; // Mark the task as completed
        } else if (!heapTaskByQj.Empty()) {
            Task nextTask = heapTaskByQj.GetMaximum();
            heapTaskByQj.EraseMaximum();
            int taskStartTime = std::max(currentTime, nextTask.GetRj()); // Ensure start time respects task release time
            std::cout << "(" << nextTask.GetTaskId() << ", " << taskStartTime << ")" << std::endl;
            currentTime = taskStartTime + nextTask.GetPj();
        } else {
            // Update currentTime to the release time of the next task in the sorted list
            currentTime = sortedTasksByRj.front().GetRj();
        }

        // Update currentTime if there are completed tasks before the current time
        while (!sortedTasksByRj.empty() && sortedTasksByRj.front().GetRj() <= currentTime && taskCompleted[sortedTasksByRj.front().GetTaskId() - 1]) {
            sortedTasksByRj.erase(sortedTasksByRj.begin());
        }
    }

    // After scheduling all tasks, currentTime holds the finish time of the last task
    int criterion = CountCriterion(scheduledTasks);
    Solution solution(criterion, scheduledTasks);

    return solution;*/


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