#include <algorithm>
#include "Problem.hpp"
#include <climits>
#include <iostream>
#include <chrono>
#include <tuple>
#include <numeric>
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

/*
void Problem::LPT() const
{ 
    std::vector<Task> rankedTasks = m_tasks;
    std::vector<Task> P1; // Machine 1
    std::vector<Task> P2; // Machine 2
    int P1_time = 0;      // Time of processing for machine 1
    int P2_time = 0;      // Time of processing for machine 2

    std::sort(rankedTasks.begin(), rankedTasks.end(), [](const Task &a, const Task &b)
              { return a.GetPj() > b.GetPj(); }); // ascending order

    for (int i = 0; i < rankedTasks.size(); i++)
    {
        if (P2_time >= P1_time)
        {
            P1.push_back(rankedTasks[i]);
            P1_time += rankedTasks[i].GetPj();
        }
        else
        {
            P2.push_back(rankedTasks[i]);
            P2_time += rankedTasks[i].GetPj();
        }
    }

    int criterion = std::max(P2_time, P1_time);
    std::cout << "Criterion: " << criterion << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Machine_nr_1: ";
    for (int x = 0; x < P1.size(); x++)
    {
        std::cout << P1[x].GetTaskId() << ", ";
    }
    std::cout << std::endl
              << "Machine_nr_2: ";
    for (int y = 0; y < P2.size(); y++)
    {
        std::cout << P2[y].GetTaskId() << ", ";
    }
    std::cout << std::endl;
    // Permutation solution(criterion, sortedTasks);
    // return solution;
}
*/


    // Na 3.0

int Problem::calculateMakespan(const std::vector<Task>& sequence) const {
    if (sequence.empty()) return 0;

    int numJobs = sequence.size();
    int numMachines = sequence[0].GetValues().size();

    std::vector<std::vector<int>> completionTimes(numJobs, std::vector<int>(numMachines, 0));

    // Initialize the first job's completion times
    completionTimes[0][0] = sequence[0].GetValueAt(0);
    for (int j = 1; j < numMachines; ++j) {
        completionTimes[0][j] = completionTimes[0][j - 1] + sequence[0].GetValueAt(j);
    }

    // Calculate completion times for the rest of the jobs
    for (int i = 1; i < numJobs; ++i) {
        completionTimes[i][0] = completionTimes[i - 1][0] + sequence[i].GetValueAt(0);
        for (int j = 1; j < numMachines; ++j) {
            completionTimes[i][j] = std::max(completionTimes[i - 1][j], completionTimes[i][j - 1]) + sequence[i].GetValueAt(j);
        }
    }

    return completionTimes[numJobs - 1][numMachines - 1];
}

void Problem::NEH() const{
    std::vector<Task> rankedTasks = m_tasks;
    int N = m_tasks.size();
    if (N==0) return;

     //   for (const auto &task : rankedTasks) {std::cout << task << std::endl;} // PRINTING ALL PJ VALUES FOR EACH TASK
    //std::cout<<N<<std::endl;  // PRINT AMOUNT OF TASKS
    
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

    // Step 3: Build the sequence using the NEH heuristic
    std::vector<Task> sequence;
    for (const auto& [totalTime, task] : totalProcessingTimes) {
        std::vector<Task> bestSequence = sequence;
        int bestMakespan = std::numeric_limits<int>::max();

        // Try inserting the task at all positions in the current sequence
        for (size_t i = 0; i <= sequence.size(); ++i) {
            std::vector<Task> tempSequence = sequence;
            tempSequence.insert(tempSequence.begin() + i, task);
            int makespan = calculateMakespan(tempSequence);

            if (makespan < bestMakespan) {
                bestMakespan = makespan;
                bestSequence = tempSequence;
            }
        }

        sequence = bestSequence;
    }

    // Print the final sequence and makespan
    std::cout << "Final task sequence:\n";
    for (const auto& task : sequence) {
        std::cout << task << std::endl;
    }
    std::cout << "Final makespan: " << calculateMakespan(sequence) << std::endl;
}

void Problem::Complete_Review() const{
    if (m_tasks.empty()) return;

    std::vector<Task> bestSequence = m_tasks;
    int bestMakespan = std::numeric_limits<int>::max();

    std::vector<Task> currentSequence = m_tasks;
    int x = 0;
    // Generate all permutations of the task sequence
    do {
        int currentMakespan = calculateMakespan(currentSequence);
        if (currentMakespan < bestMakespan) {
            bestMakespan = currentMakespan;
            bestSequence = currentSequence;
            std::cout<<"Current perm num: "<<x<<std::endl;
            x++;
        }
    } while (std::next_permutation(currentSequence.begin(), currentSequence.end(), [](const Task& a, const Task& b) {
        return a.GetValues() < b.GetValues(); // Comparison based on execution times
    }));

    // Print the best sequence and its makespan
    std::cout << "Best task sequence:\n";
    for (const auto& task : bestSequence) {
        std::cout << task << std::endl;
    }
    std::cout << "Best makespan: " << bestMakespan << std::endl;
}
    // Na 3.0

    // Na 3.5
    // Na 3.5

    // Na 4.0
    // Na 4.0

    // Na 4.5
    // Na 4.5

    // Na 5.0
    // Na 5.0