cmake_minimum_required(VERSION 3.0.0)
project(Scheduling LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(
    Solution
    Problem
    Task
)

add_executable(Scheduling main.cpp )

target_link_libraries(Scheduling 
    PRIVATE 
    Solution
    Problem
    Task
)