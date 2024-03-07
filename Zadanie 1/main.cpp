#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>

#include "Task.hpp"
#include "Solution.hpp"
#include "Problem.hpp"

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

int ReadFromFile(std::ifstream &file, std::vector<Task> &tasksVec)
{

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

int main(int argc, char *argv[])
{
    // TEST 1
    Task task1(1, 0, 1, 1);
    Task task2(2, 3, 3, 2);

    Problem problem1({task1, task2});
    Solution solution = problem1.ExampleAlgorith();
    solution.DisplaySolution(); // 8

    // TEST 2
    Problem problem2({task2, task1});
    solution = problem2.ExampleAlgorith();
    solution.DisplaySolution(); // 8

    // TEST 3
    Task task3(2, 1, 5, 3); // 3 + 5
    Task task4(1, 9, 1, 4); // 10 + 1
    Task task5(3, 8, 3, 5); // 13 + 3

    Problem problem3({task3, task4, task5});
    solution = problem3.ExampleAlgorith();
    solution.DisplaySolution(); // 16

    return 0;
}
