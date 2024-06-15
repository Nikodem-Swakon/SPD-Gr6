#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <filesystem>
#include <chrono>

#include "Task.hpp"
#include "Solution.hpp"
#include "Problem.hpp"
#include "Pair.hpp"

#define FILE_PATH "../text.txt"

// Full fill tasksVec with time of its operations
int readFromFile(std::string &filename, std::vector<Task> &tasksVec)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;        // For skipping first line
    bool isFirstLine = true; // For skipping first line
    int taskId = 1;

    while (std::getline(file, line))
    { // Read file line by line

        if (isFirstLine)
        {                        // For skipping first line
            isFirstLine = false; // For skipping first line
            continue;            // Skip the first line
        }

        std::istringstream iss(line);
        std::vector<int> values;
        int value;
        while (iss >> value)
        {
            iss >> value;
            values.push_back(value); // Extract numbers from the line
            // std::cout<<value<<std::endl;
        }
        Task task(values, taskId++);
        tasksVec.push_back(task);
    }

    file.close();
    return 0;
}

void displayTasks(std::vector<Task> &tasks)
{
    std::cout << "Tasks from the instance: " << std::endl;
    for (int i = 0; i < tasks.size(); i++)
    {
        std::cout << tasks[i] << std::endl;
    }
}

void Jhnson(Problem &problem)
{
    std::cout << "--------------------------------- " << "\033[0;35m Algorytm Jhnson'a \033[0m" << std::endl;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    problem.Jhonson();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\033[0;36m Time: \033[1;36m  " << duration.count() << "\033[0;36m microseconds \033[0m" << std::endl;
}

void Neh(Problem &problem)
{
    std::cout << "--------------------------------- " << "\033[0;35m Algorytm NEH \033[0m" << std::endl;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    problem.NEH();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\033[0;36m Time: \033[1;36m  " << duration.count() << "\033[0;36m microseconds \033[0m" << std::endl;
}

void CompleteReview(Problem &problem)
{
    if (problem.GetTasksNum() > 11)
        return;
    std::cout << "--------------------------------- " << "\033[0;35m Algorytm Complete review \033[0m" << std::endl;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    problem.CompleteReview();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\033[0;36m Time: \033[1;36m  " << duration.count() << "\033[0;36m microseconds \033[0m" << std::endl;
}

void FNEH(Problem &problem)
{
    std::cout << "--------------------------------- " << "\033[0;35m Algorytm FNEH \033[0m" << std::endl;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    problem.FNEH();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\033[0;36m Time: \033[1;36m  " << duration.count() << "\033[0;36m microseconds \033[0m" << std::endl;
}

void BoundAndBrnahc(Problem &problem)
{
    if (problem.GetTasksNum() > 11)
        return;
    std::cout << "--------------------------------- " << "\033[0;35m Algorytm Bound And Brnach \033[0m" << std::endl;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    problem.BranchAndBound();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\033[0;36m Time: \033[1;36m  " << duration.count() << "\033[0;36m microseconds \033[0m" << std::endl;
}

std::string ChoseFile()
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
        return "";
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

    return filename;
}

int main(int argc, char *argv[])

{
    std::string filename = ChoseFile();
    if (filename == "")
        return 1;

    std::vector<Task> taskVector;

    readFromFile(filename, taskVector);
    Problem problem(taskVector);

    displayTasks(taskVector);

    // tests:
    CompleteReview(problem);
    BoundAndBrnahc(problem);
    Neh(problem);
    FNEH(problem);
    Jhnson(problem);

    return 0;
}

/* ZOSTAWIONE JAKO WZÓR
 * std::cout <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  LSA  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<std::endl;
 *
 *    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
 *    problem.LSA();
 *    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
 *    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
 * std::cout << "Time LSA: " << duration.count() << " microseconds" << std::endl;
 */
