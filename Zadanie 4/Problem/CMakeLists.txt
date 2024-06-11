add_library(Problem src/Problem.cpp src/Function.cpp)

target_include_directories(Problem PUBLIC inc ../Task/inc ../Solution/inc ../Heap/Inc ../Node/inc)
