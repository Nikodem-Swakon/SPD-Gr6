#include <algorithm>
#include "Problem.hpp"
#include <climits>
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

void Problem::LPT() const { // działa niepoprawnie
    std::vector<Task> rankedTasks = m_tasks;
    std::vector<Task> P1; // Machine 1
    std::vector<Task> P2; // Machine 2
    int P1_time = 0;     // Time of processing for machine 1
    int P2_time = 0;     // Time of processing for machine 2

    std::sort(rankedTasks.begin(), rankedTasks.end(), [](const Task &a, const Task &b)
              { return a.GetPj() > b.GetPj(); });  //ascending order 

    for (int i=0;i<rankedTasks.size();i++){
        if (P2_time>=P1_time){
            P1.push_back(rankedTasks[i]);
            P1_time+=rankedTasks[i].GetPj();
        }else{
            P2.push_back(rankedTasks[i]);
            P2_time+=rankedTasks[i].GetPj();
        }
    }
    
    int criterion = std::max (P2_time,P1_time);
    std::cout<<"Criterion: "<<criterion<<std::endl;
    std::cout<<"=================================="<<std::endl;
    std::cout<<"Machine_nr_1: ";
    for (int x=0;x<P1.size();x++){ std::cout<< P1[x].GetTaskId()<<", ";}
    std::cout<<std::endl<<"Machine_nr_2: ";
    for (int y=0;y<P2.size();y++){ std::cout<< P2[y].GetTaskId()<<", ";}
    std::cout<<std::endl;
    //Permutation solution(criterion, sortedTasks);
    //return solution;

}
    void Problem::LSA() const { // Działa 
    std::vector<Task> rankedTasks= m_tasks;
    std::vector<Task> P1; // Machine 1
    std::vector<Task> P2; // Machine 2
    int P1_time = 0;     // Time of processing for machine 1
    int P2_time = 0;     // Time of processing for machine 2

       for (int i=0;i<rankedTasks.size();i++){
        if (P2_time<P1_time){
            P2.push_back(rankedTasks[i]);
            P2_time+=rankedTasks[i].GetPj();
        }else{
            P1.push_back(rankedTasks[i]);
            P1_time+=rankedTasks[i].GetPj();
        }
    } 
    int criterion = std::max (P2_time,P1_time);
    std::cout<<std::endl<<"Criterion: "<<criterion<<std::endl;
    std::cout<<"=================================="<<std::endl;
    std::cout<<"Machine_nr_1: ";
    for (int x=0;x<P1.size();x++){ std::cout<< P1[x].GetTaskId()<<", ";}
    std::cout<<std::endl<<"Machine_nr_2: ";
    for (int y=0;y<P2.size();y++){ std::cout<< P2[y].GetTaskId()<<", ";}
    std::cout<<std::endl;
}
//Permutation Problem::Dynamic_2() const {}

void Problem::CompleteReview_2() const {
    std::vector<Task> temp = m_tasks;  // Assuming m_tasks is a member variable
    int num_tasks = temp.size();
    int minCmax = INT_MAX;
    std::vector<int> best_bitmask;

    // Generate all possible bitmasks
    for (int bitmask = 0; bitmask < (1 << num_tasks); ++bitmask) {
        int P1_time = 0;
        int P2_time = 0;

        for (int i = 0; i < num_tasks; ++i) {
            if (bitmask & (1 << i)) {  // Check if i-th bit is set
                P1_time += temp[i].GetPj();
            } else {
                P2_time += temp[i].GetPj();
            }
        }

        int Cmax = std::max(P1_time, P2_time);
        if (Cmax < minCmax) {
            minCmax = Cmax;
            best_bitmask = std::vector<int>(num_tasks, 0);
            for (int i = 0; i < num_tasks; ++i) {
                if (bitmask & (1 << i)) {
                    best_bitmask[i] = 1;
                }
            }
        }
    }

    // Print the best schedule
    std::cout << "Best schedule to minimize Cmax:\n";
    for (int i = 0; i < num_tasks; ++i) {
        if (best_bitmask[i] == 1) {
            std::cout << "Task " << temp[i].GetTaskId() << " with processing time " << temp[i].GetPj() << " scheduled on machine 1\n";
        } else {
            std::cout << "Task " << temp[i].GetTaskId() << " with processing time " << temp[i].GetPj() << " scheduled on machine 2\n";
        }
    }
    std::cout << "Minimum Cmax: " << minCmax << std::endl;

}
    /*std::vector<Task> P1,P2;
    std::vector<Task> temp = m_tasks;
    int minCmax = INT_MAX;


    std::vector<std::vector<Task>> permutations;
    std::vector<Task> best_order;
    CompleteReview_alg(temp, 0, permutations);

    for (const auto& perm : permutations){
        
        for (const auto& task : perm) {
            int P1_time = 0;
            int P2_time = 0;
            if (P1_time <= P2_time) {
            P1_time += task.GetPj();
        } else {
            P2_time += task.GetPj();
        }
        int Cmax = std::max(P1_time,P2_time);
        if (Cmax<minCmax){
            minCmax=Cmax;
            best_order = perm;
        }
    }

    std::cout<< "Best order to minimize cmax is:\n Task_id || Processing time";

        for (const auto& task : best_order) {
        std::cout << "Task " << task.GetTaskId() << " with processing time " << task.GetPj() << std::endl;
    }
    std::cout<< " With Cmax= "<<minCmax<<std::endl;


   /* do {
        P1.clear();
        P2.clear();
        for (int i = 0; i < temp.size(); ++i) {
            if (i % 2 == 0) {
                P1.push_back(temp[i]);
                P1_time+=temp[i].GetPj();
            } else {
                P2.push_back(temp[i]);
                P2_time+=temp[i].GetPj();
            }
        }

        // Calculate Cmax for this distribution
        int cmax = std::max(P1_time,P2_time);

        // Update minimum Cmax
        minCmax = std::min(minCmax, cmax);
    } while (std::next_permutation(temp.begin(), temp.end()));

    std::cout << "Minimum Cmax: " << minCmax << std::endl;*/


/*void Problem::CompleteReview_alg(std::vector<Task>& tasks, int start, std::vector<std::vector<Task>>& permutations) {
    if (start == tasks.size() - 1) {
        permutations.push_back(tasks);
        return;
    }
    
    for (int i = start; i < tasks.size(); ++i) {
        std::swap(tasks[start], tasks[i]);
        CompleteReview_alg(tasks, start + 1, permutations);
        std::swap(tasks[start], tasks[i]);
    }
}*/

//Permutation Problem::Dynamic_3() const {}
//Permutation Problem::CompleteReview_3() const {}
//Permutation Problem::PTAS() const {}



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

