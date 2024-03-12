cmake_minimum_required(VERSION 3.0.0)
project(Scheduling LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Solution)
add_subdirectory(Task)
add_subdirectory(Problem)


add_executable(Scheduling main.cpp)

target_link_libraries(Scheduling 
    PRIVATE 
    Solution
    Task
    Problem
)