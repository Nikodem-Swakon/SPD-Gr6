cmake_minimum_required(VERSION 3.0.0)
project(Heap LANGUAGES CXX)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Heap main.cpp Src/Heap.cpp)

target_include_directories(Heap PUBLIC ${CMAKE_SOURCE_DIR}/Inc)
