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

int ReadFromFile(std::string& filename, std::vector<Task> &tasksVec)
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
    std::string currentpath = std::filesystem::current_path().string();
    std::string folderPath=currentpath+"/../Input";


    // Display list of files in the folder
    std::cout << "Files available as input data:" << std::endl;
    int index = 1;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        std::cout << index << ". " << entry.path().filename() << std::endl;
        ++index;
    }

    int choice;
    std::cout << "Enter the number of the file for input data: ";
    std::cin >> choice;


    // Invalid choice handling
    if (choice < 1 || choice >= index) {
        std::cerr << "Invalid choice." << std::endl;
        return 1;
    }

    std::string filename;
    index = 1;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (index == choice) {
            filename = entry.path().string();
            break;
        }
        ++index;
    }

    std::vector<Task> taskVector;
    ReadFromFile(filename,taskVector);
    Problem problem(taskVector);
    

    std::cout << "Test Qj" << std::endl;
    Solution solution=problem.AlgorithmSortQj();

    solution.DisplaySolution();
    solution.DisplayGanttChart();

    std::cout << "Test Rj" << std::endl;
    solution=problem.AlgorithmSortRj();
    solution.DisplaySolution();
    solution.DisplayGanttChart();

    std::cout << "Test complete review" << std::endl;
    solution=problem.AlgorithmCompleteReview();
    solution.DisplaySolution();
    solution.DisplayGanttChart();
   

    
    //  User input for picking sorting algorithm
        // WARNING - Does not work. Correct deafault constructor for "solution" is needed, that can be overwritten by functions inside cases
    /*
    
    std::cout<<"Enter the number of the sorting algorithm: "<<std::endl;
    std::cout<<"1. Rj_sort"<<std::endl;
    std::cout<<"2. Qj_sort"<<std::endl;
    std::cout<<"3. Complete_Review"<<std::endl;
    int sortChoice;
    std::cin>>sortChoice;
    */

        // "IF CASES"
    /*
    Solution solution;
    if(sortChoice=1){ solution = problem.AlgorithmSortRj();solution.DisplaySolution();solution.DisplayGanttChart(); }
    else if(sortChoice=2){ solution = problem.AlgorithmSortQj();solution.DisplaySolution();solution.DisplayGanttChart(); }
    //else if (sortChoice=3){ solution = problem.AlgorithmCompleteReview();solution.DisplaySolution();solution.DisplayGanttChart(); }
    else{std::cout<<"Invalid choice!"<<std::endl;}
    */

        // "SWITCH CASES"
    /*
     switch(sortChoice) {
    case 1:
        std::cout << "Using RJ_sort" << std::endl;
        solution = problem.AlgorithmSortRj(); 
        solution.DisplaySolution();
        solution.DisplayGanttChart();
        break;
    case 2:
        std::cout << "Using QJ_sort" << std::endl;
        solution = problem.AlgorithmSortQj(); 
        solution.DisplaySolution();
        solution.DisplayGanttChart();
        break;
    case 3:
        std::cout << "Using Complete_Review" << std::endl;
        solution = problem.AlgorithmCompleteReview(); 
        solution.DisplaySolution();
        solution.DisplayGanttChart();
        break;
    default:
        std::cerr << "Invalid sorting method choice." << std::endl;
        return 1;
     */
    

    return 0;
}
