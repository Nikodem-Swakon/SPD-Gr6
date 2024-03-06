#include <iostream>
#include <vector>

#include "Task.hpp"
#include "Solution.hpp"
#include "Problem.hpp"

int main(int argc, char *argv[])
{
    //  TO BE DELETED task test
    std::cout << "Hello SPD." << std::endl;
    Task task1;
    std::cout << "task1: pj " << task1.GetPj() << " rj " << task1.GetRj() << " qj " << task1.GetQj() << std::endl;
    Task task2(1, 2, 3);
    std::cout << "task2: pj " << task2.GetPj() << " rj " << task2.GetRj() << " qj " << task2.GetQj() << std::endl;
    Task task3(task2);
    std::cout << "task2: pj " << task3.GetPj() << " rj " << task3.GetRj() << " qj " << task3.GetQj() << std::endl;

    //  TO BE DELETED problem test
    std::vector<Task> taskVector = {task1, task2, task3};

    Problem problem(taskVector);
    problem.DisplayTasks();

    //  TO BE DELETED solution test
    Solution solution = problem.ExampleAlgorith();
    solution.DisplaySolution();

    return 0;
}
