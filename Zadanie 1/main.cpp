#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <filesystem>

#include "Task.hpp"
#include "Solution.hpp"
#include "Problem.hpp"
#include "Heap.hpp"
#include "Permutation.hpp"
#include "Pair.hpp"

#define FILE_PATH "../text.txt"

void extract(const std::string &line, Task &task)
{

    std::istringstream iss(line);
    int value;
    std::vector<int> values;
    while (iss >> value)
    { // read all values in the line
        values.push_back(value);
    }
    task.SetTaskId(values[0]);
    task.SetRj(values[1]);
    task.SetPj(values[2]);
    task.SetQj(values[3]);
}

int readFromFile(std::string &filename, std::vector<Task> &tasksVec)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    // std::vector<std::vector<int>> Machine;  //vector of vectors

    std::string line;        // For skipping first line
    bool isFirstLine = true; // For skipping first line

    while (std::getline(file, line))
    { // Read file line by line

        if (isFirstLine)
        { // For skipping first line
            std::istringstream iss(line);
            std::string word;
            while (iss >> word)
            {
                //++numColumns;
            }
            isFirstLine = false; // For skipping first line
            continue;            // Skip the first line
        }

        Task task;
        extract(line, task); // Extract numbers from the line
        tasksVec.push_back(task);
    }

    file.close();
    return 0;
}

void heapTest(std::vector<Task> tasks)
{
    std::cout << "Heap sort test." << std::endl;

    Structure::Heap<Task> h;
    h.BuildHeap(tasks);
    h.PrintHeap(0);
    Task t = h.EraseMaximum();
    std::cout << "Earsed " << t << std::endl;
    h.PrintHeap(0);

    Structure::HeapSort(tasks);
    for (int i = 0; i < tasks.size(); i++)
    {
        std::cout << " Id. " << tasks[i] << "   ";
    }
    std::cout << std::endl;
}

void schrageTest(std::vector<Task> tasks, Problem problem)
{
    std::cout << "Schrage algorithm test." << std::endl;

    Permutation permutation = problem.AlgorithmSchrage();
    Solution *solution = &permutation;
    solution->DisplaySolution();
    solution->DisplayGanttChart();
}

void schrageTestSep(std::vector<Task> tasks, Problem problem)
{
    std::cout << "Schrage with preemption algorithm test." << std::endl;

    Pair pair = problem.AlgorithmSchrageSep();
    Solution *solution = &pair;
    solution->DisplaySolution();
    solution->DisplayGanttChart();
}

void qjTest(std::vector<Task> tasks, Problem problem)
{
    std::cout << "Test Qj" << std::endl;

    Permutation permutation = problem.AlgorithmSortQj();
    Solution *solution = &permutation;
    solution->DisplaySolution();
    solution->DisplayGanttChart();
}

void rjTest(std::vector<Task> tasks, Problem problem)
{
    std::cout << "Test Rj" << std::endl;

    Permutation permutation = problem.AlgorithmSortRj();
    Solution *solution = &permutation;
    solution->DisplaySolution();
    solution->DisplayGanttChart();
}

void completeReviewtest(std::vector<Task> tasks, Problem problem)
{
    std::cout << "Test complete review" << std::endl;
    Permutation permutation = problem.AlgorithmCompleteReview();
    Solution *solution = &permutation;
    solution->DisplaySolution();
    solution->DisplayGanttChart();
}

void OurAlgorithm(std::vector<Task> tasks, Problem problem)
{
    std::cout << "Test OurAlgorithm" << std::endl;
    Permutation permutation = problem.OurAlgorithm();
    Solution *solution = &permutation;
    solution->DisplaySolution();
    solution->DisplayGanttChart();  
}

int main(int argc, char *argv[])

{

    std::cout << "tests" << std::endl;
    std::string currentpath = std::filesystem::current_path().string();
    std::string folderPath = currentpath + "/../Input";

    // Display list of files in the folder
    std::cout << "Files available as input data:" << std::endl;
    int index = 1;
    for (const auto &entry : std::filesystem::directory_iterator(folderPath))
    {
        std::cout << index << ". " << entry.path().filename() << std::endl;
        ++index;
    }

    int choice;
    std::cout << "Enter the number of the file for input data: ";
    std::cin >> choice;

    // Invalid choice handling
    if (choice < 1 || choice >= index)
    {
        std::cerr << "Invalid choice." << std::endl;
        return 1;
    }

    std::string filename;
    index = 1;
    for (const auto &entry : std::filesystem::directory_iterator(folderPath))
    {
        if (index == choice)
        {
            filename = entry.path().string();
            break;
        }
        ++index;
    }

    std::vector<Task> taskVector;
    readFromFile(filename, taskVector);
    Problem problem(taskVector);

    // heapTest(taskVector);
    // schrageTest(taskVector, problem);
    // qjTest(taskVector, problem);
    // rjTest(taskVector, problem);
    // completeReviewtest(taskVector, problem);
    // schrageTestSep(taskVector, problem);
    // OurAlgorithm(taskVector, problem);
    std::cout << "Poczatek" << std::endl;
    problem.AlgorithmCarlier();

    return 0;
}
