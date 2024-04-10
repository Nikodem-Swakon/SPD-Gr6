#include <algorithm>
#include "Problem.hpp"

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
//Permutation Problem::CompleteReview_2() const {}
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

