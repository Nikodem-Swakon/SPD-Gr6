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

    std::cout << "----------------- k = 13" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Dynamic Programming %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::chrono::high_resolution_clock::time_point startFPTAS = std::chrono::high_resolution_clock::now();
    problem.DynamicProgramming3D();
    std::chrono::high_resolution_clock::time_point endFPTAS = std::chrono::high_resolution_clock::now();
    auto durationFPTAS = std::chrono::duration_cast<std::chrono::microseconds>(endFPTAS - startFPTAS);
    std::cout << "Time Dynamic Programming: " << durationFPTAS.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // std::chrono::high_resolution_clock::time_point startPTAS_2 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_2(13);
    // std::chrono::high_resolution_clock::time_point endPTAS_2 = std::chrono::high_resolution_clock::now();
    // auto durationPTAS_2 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_2 - startPTAS_2);
    // std::cout << "Time PTAS2: " << durationPTAS_2.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // std::chrono::high_resolution_clock::time_point startPTAS_3 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_3(5);
    // std::chrono::high_resolution_clock::time_point endPTAS_3 = std::chrono::high_resolution_clock::now();
    // auto durationPTAS_3 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_3 - startPTAS_3);
    // std::cout << "Time PTAS3: " << durationPTAS_3.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::cout << "----------------- k = 17" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%FPTAS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startFPTAS = std::chrono::high_resolution_clock::now();
    // problem.FPTAS(6);
    // endFPTAS = std::chrono::high_resolution_clock::now();
    // durationFPTAS = std::chrono::duration_cast<std::chrono::microseconds>(endFPTAS - startFPTAS);
    // std::cout << "Time FPTAS: " << durationFPTAS.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startPTAS_2 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_2(17);
    // endPTAS_2 = std::chrono::high_resolution_clock::now();
    // durationPTAS_2 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_2 - startPTAS_2);
    // std::cout << "Time PTAS2: " << durationPTAS_2.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startPTAS_3 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_3(6);
    // endPTAS_3 = std::chrono::high_resolution_clock::now();
    // durationPTAS_3 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_3 - startPTAS_3);
    // std::cout << "Time PTAS3: " << durationPTAS_3.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::cout << "----------------- k = 20" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%FPTAS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startFPTAS = std::chrono::high_resolution_clock::now();
    // problem.FPTAS(7);
    // endFPTAS = std::chrono::high_resolution_clock::now();
    // durationFPTAS = std::chrono::duration_cast<std::chrono::microseconds>(endFPTAS - startFPTAS);
    // std::cout << "Time FPTAS: " << durationFPTAS.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startPTAS_2 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_2(20);
    // endPTAS_2 = std::chrono::high_resolution_clock::now();
    // durationPTAS_2 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_2 - startPTAS_2);
    // std::cout << "Time PTAS2: " << durationPTAS_2.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startPTAS_3 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_3(7);
    // endPTAS_3 = std::chrono::high_resolution_clock::now();
    // durationPTAS_3 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_3 - startPTAS_3);
    // std::cout << "Time PTAS3: " << durationPTAS_3.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::cout << "----------------- k = 2" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%FPTAS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startFPTAS = std::chrono::high_resolution_clock::now();
    // problem.FPTAS(2);
    // endFPTAS = std::chrono::high_resolution_clock::now();
    // durationFPTAS = std::chrono::duration_cast<std::chrono::microseconds>(endFPTAS - startFPTAS);
    // std::cout << "Time FPTAS: " << durationFPTAS.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startPTAS_2 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_2(2);
    // endPTAS_2 = std::chrono::high_resolution_clock::now();
    // durationPTAS_2 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_2 - startPTAS_2);
    // std::cout << "Time PTAS2: " << durationPTAS_2.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startPTAS_3 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_3(2);
    // endPTAS_3 = std::chrono::high_resolution_clock::now();
    // durationPTAS_3 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_3 - startPTAS_3);
    // std::cout << "Time PTAS3: " << durationPTAS_3.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::cout << "----------------- k = 3" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%FPTAS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startFPTAS = std::chrono::high_resolution_clock::now();
    // problem.FPTAS(3);
    // endFPTAS = std::chrono::high_resolution_clock::now();
    // durationFPTAS = std::chrono::duration_cast<std::chrono::microseconds>(endFPTAS - startFPTAS);
    // std::cout << "Time FPTAS: " << durationFPTAS.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startPTAS_2 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_2(3);
    // endPTAS_2 = std::chrono::high_resolution_clock::now();
    // durationPTAS_2 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_2 - startPTAS_2);
    // std::cout << "Time PTAS2: " << durationPTAS_2.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startPTAS_3 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_3(3);
    // endPTAS_3 = std::chrono::high_resolution_clock::now();
    // durationPTAS_3 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_3 - startPTAS_3);
    // std::cout << "Time PTAS3: " << durationPTAS_3.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // std::cout << "----------------- k = 4" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%FPTAS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startFPTAS = std::chrono::high_resolution_clock::now();
    // problem.FPTAS(3);
    // endFPTAS = std::chrono::high_resolution_clock::now();
    // durationFPTAS = std::chrono::duration_cast<std::chrono::microseconds>(endFPTAS - startFPTAS);
    // std::cout << "Time FPTAS: " << durationFPTAS.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startPTAS_2 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_2(4);
    // endPTAS_2 = std::chrono::high_resolution_clock::now();
    // durationPTAS_2 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_2 - startPTAS_2);
    // std::cout << "Time PTAS2: " << durationPTAS_2.count() << " microseconds" << std::endl;

    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PTAS 3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    // startPTAS_3 = std::chrono::high_resolution_clock::now();
    // problem.PTAS_3(4);
    // endPTAS_3 = std::chrono::high_resolution_clock::now();
    // durationPTAS_3 = std::chrono::duration_cast<std::chrono::microseconds>(endPTAS_3 - startPTAS_3);
    // std::cout << "Time PTAS3: " << durationPTAS_3.count() << " microseconds" << std::endl;
    // std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    return 0;
}
