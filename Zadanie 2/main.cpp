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
    task.SetPj(values[1]);
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
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  LSA  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::chrono::high_resolution_clock::time_point startLSA = std::chrono::high_resolution_clock::now();
    // problem.LSA();
    // std::chrono::high_resolution_clock::time_point endLSA = std::chrono::high_resolution_clock::now();
    // auto durationLSA = std::chrono::duration_cast<std::chrono::microseconds>(endLSA - startLSA);
    // std::cout << "Time LSA: " << durationLSA.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% LPT %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::chrono::high_resolution_clock::time_point startLPT = std::chrono::high_resolution_clock::now();
    // problem.LPT();
    // std::chrono::high_resolution_clock::time_point endLPT = std::chrono::high_resolution_clock::now();
    // auto durationLPT = std::chrono::duration_cast<std::chrono::microseconds>(endLPT - startLPT);
    // std::cout << "Time LPT: " << durationLPT.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%FPTAS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::chrono::high_resolution_clock::time_point startFPTAS = std::chrono::high_resolution_clock::now();
    // problem.FPTAS(2);
    // std::chrono::high_resolution_clock::time_point endFPTAS = std::chrono::high_resolution_clock::now();
    // auto durationFPTAS = std::chrono::duration_cast<std::chrono::microseconds>(endFPTAS - startFPTAS);
    // std::cout << "Time FPTAS: " << durationFPTAS.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%DYNAMIC PROGRAMING 2%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::chrono::high_resolution_clock::time_point startDynamicProgramming2D = std::chrono::high_resolution_clock::now();
    // problem.DynamicProgramming2D();
    // std::chrono::high_resolution_clock::time_point endDynamicProgramming2D = std::chrono::high_resolution_clock::now();
    // auto durationDynamicProgramming2D = std::chrono::duration_cast<std::chrono::microseconds>(endDynamicProgramming2D - startDynamicProgramming2D);
    // std::cout << "Time DP2: " << durationDynamicProgramming2D.count() << " microseconds" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  DYNAMIC PROGRAMING 3%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    std::chrono::high_resolution_clock::time_point startDynamicProgramming3D = std::chrono::high_resolution_clock::now();
    problem.DynamicProgramming3D();
    std::chrono::high_resolution_clock::time_point endDynamicProgramming3D = std::chrono::high_resolution_clock::now();
    auto durationDynamicProgramming3D = std::chrono::duration_cast<std::chrono::microseconds>(endDynamicProgramming3D - startDynamicProgramming3D);
    std::cout << "Time DP3: " << durationDynamicProgramming3D.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% COMPLETE REVIEV 2%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::chrono::high_resolution_clock::time_point startCompleteReview_2 = std::chrono::high_resolution_clock::now();
    // problem.CompleteReview_2();
    // std::chrono::high_resolution_clock::time_point endCompleteReview_2 = std::chrono::high_resolution_clock::now();
    // auto durationCompleteReview_2 = std::chrono::duration_cast<std::chrono::microseconds>(endCompleteReview_2 - startCompleteReview_2);
    // std::cout << "Time CR2: " << durationCompleteReview_2.count() << " microseconds" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   COMPLETE REVIEV 3%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    std::chrono::high_resolution_clock::time_point startCompleteReview_3 = std::chrono::high_resolution_clock::now();
    problem.CompleteReview_3();
    std::chrono::high_resolution_clock::time_point endCompleteReview_3 = std::chrono::high_resolution_clock::now();
    auto durationCompleteReview_3 = std::chrono::duration_cast<std::chrono::microseconds>(endCompleteReview_3 - startCompleteReview_3);
    std::cout << "Time CR3: " << durationCompleteReview_3.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::chrono::high_resolution_clock::time_point startPTAS_2 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_2(2);
    // std::chrono::high_resolution_clock::time_point endPTAS_2 = std::chrono::high_resolution_clock::now();
    // auto durationPTAS_2 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_2 - startPTAS_2);
    // std::cout << "Time PTAS2: " << durationPTAS_2.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::chrono::high_resolution_clock::time_point startPTAS_3 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_3(2);
    // std::chrono::high_resolution_clock::time_point endPTAS_3 = std::chrono::high_resolution_clock::now();
    // auto durationPTAS_3 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_3 - startPTAS_3);
    // std::cout << "Time PTAS3: " << durationPTAS_3.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;


    return 0;
}
