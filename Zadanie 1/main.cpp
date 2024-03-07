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
   /*//  TO BE DELETED task test
    std::cout << "Hello SPD." << std::endl;
    Task task1;
    std::cout << "task1: pj " << task1.GetPj() << " rj " << task1.GetRj() << " qj " << task1.GetQj() << " taskId " << task1.GetTaskId() << std::endl;
    Task task2(0, 1, 2, 3);
    std::cout << "task2: pj " << task2.GetPj() << " rj " << task2.GetRj() << " qj " << task2.GetQj() << " taskId " << task2.GetTaskId() << std::endl;
    Task task3(task2);
    std::cout << "task3: pj " << task3.GetPj() << " rj " << task3.GetRj() << " qj " << task3.GetQj() << " taskId " << task3.GetTaskId() << std::endl;
    */
    Task task1(5, 10, 7,  1);
    Task task2(6, 13, 26, 2);
    Task task3(7, 11, 24, 3);
    Task task4(4, 20, 21, 4);
    Task task5(3, 30, 8, 5);
    Task task6(6, 0, 17, 6);
    Task task7(2, 30, 0, 7);


    //  TO BE DELETED problem test
    std::vector<Task> taskVector = {task1, task2, task3, task4, task5, task6, task7};

    Problem problem(taskVector);
    Solution solution = problem.AlgorithmSortRj();
    solution.DisplaySolution();
    //problem.DisplayTasks();

    //  TO BE DELETED solution test
    //Solution solution = problem.ExampleAlgorith();
    //solution.DisplaySolution();

    // READ FROM FILE TEST
    /*
    std::ifstream file(FILE_PATH); // Open the input file
    std::vector<Task> taskVector2;
    if (ReadFromFile(file, taskVector2) == 1)
        return 1;

    for (int i = 0; i < taskVector2.size(); i++)
    {
        std::cout << "task: pj " << taskVector2[i].GetPj() << " rj " << taskVector2[i].GetRj() << " qj " << taskVector2[i].GetQj() << " taskId " << taskVector2[i].GetTaskId() << std::endl;
    }
    */
    return 0;
}
