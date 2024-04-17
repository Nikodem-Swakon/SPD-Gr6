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

void Combination(std::vector<int> a, int reqLen, int start, int currLen, std::vector<bool> check, int len, int **&matrix, int rows)
{
    // Return if the currLen is more than the required length.
    if (currLen > reqLen)
        return;
    // If currLen is equal to required length then print the sequence.
    else if (currLen == reqLen)
    {
        int sum = 0;
        for (int i = 0; i < len; i++)
        {
            if (check[i] == true)
            {
                sum += a[i];
            }
        }
        for (int i = len - 1; i < rows; i++)
        {
            matrix[i][sum] = 1;
        }
        return;
    }
    // If start equals to len then return since no further element left.
    if (start == len)
    {
        return;
    }
    // For every index we have two options.
    // First is, we select it, means put true in check[] and increment currLen and start.
    check[start] = true;
    Combination(a, reqLen, start + 1, currLen + 1, check, len, matrix, rows);
    // Second is, we don't select it, means put false in check[] and only start incremented.
    check[start] = false;
    Combination(a, reqLen, start + 1, currLen, check, len, matrix, rows);
}

void Problem::DynamicProgramming2D()
{
    // prepare dimentions
    int pSum = 0;
    for (int i = 0; i < m_tasks.size(); i++)
        pSum += m_tasks[i].GetPj();
    int rows = m_tasks.size(), cols = pSum;

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
    // full fill the matr
    std::vector<bool> check = {};
    std::vector<int> arr = {};

    for (int r = 0; r < rows; r++)
    {
        check.push_back(false);
        arr.push_back(m_tasks[r].GetPj());

        // for each length of sub-array, call the Combination().
        for (int i = 0; i < r; i++)
        {
            // find all combinations os pj sum and fill the matrix
            Combination(arr, i + 1, 0, 0, check, r, matrix, rows);
        }
    }

    // find tasks which should be added to first machine
    std::vector<int> tasksIdFrorMachine1 = {};
    int r = rows - 1;
    int c = cols / 2;
    int taskId = -1;
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
        tasksIdFrorMachine1.push_back(r);
        // move to next colum directed by Pj
        c = c - m_tasks[r].GetPj();
    }

    // remove duplicats
    sort(tasksIdFrorMachine1.begin(), tasksIdFrorMachine1.end());
    tasksIdFrorMachine1.erase(unique(tasksIdFrorMachine1.begin(), tasksIdFrorMachine1.end()), tasksIdFrorMachine1.end());

    // devide on machines
    for (int i = 0; i < m_tasks.size(); i++)
    {
        auto it = std::find(tasksIdFrorMachine1.begin(), tasksIdFrorMachine1.end(), (m_tasks[i].GetTaskId() - 1)); // there is numeration from 1
        if (it != tasksIdFrorMachine1.end())
            m_machine1.push_back(m_tasks[i]);
        else
            m_machine2.push_back(m_tasks[i]);
    }

    // display information
    int machine1 = 0;
    std::cout << "machine 1" << std::endl;
    for (int i = 0; i < m_machine1.size(); i++)
    {
        std::cout << m_machine1[i] << " ";
        machine1+=m_machine1[i].GetPj();
    }
    std::cout << std::endl;
    int machine2 = 0;
    std::cout << "machine 2" << std::endl;
    for (int i = 0; i < m_machine2.size(); i++)
    {
        std::cout << m_machine2[i] << " ";
        machine2+=m_machine2[i].GetPj();
    }
    std::cout << std::endl;
    std::cout << "criterion " << std::max(machine2, machine1) << std::endl;

}
