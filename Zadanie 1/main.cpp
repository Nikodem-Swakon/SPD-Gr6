#include <iostream>
#include "Task.hpp"
#include "Solution.hpp"
#include "Problem.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Hello SPD." << std::endl;
    Task task1;
    std::cout << "task1: pj " <<  task1.GetPj() << " rj " << task1.GetRj() << " qj " << task1.GetQj() << std::endl; 
    Task task2(1,2,3);
    std::cout << "task2: pj " <<  task2.GetPj() << " rj " << task2.GetRj() << " qj " << task2.GetQj() << std::endl; 
    Task task3(task2);
    std::cout << "task2: pj " <<  task3.GetPj() << " rj " << task3.GetRj() << " qj " << task3.GetQj() << std::endl; 

    return 0;
}
