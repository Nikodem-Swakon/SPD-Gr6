cmake_minimum_required(VERSION 3.0.0)
project(Heap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(Heap main.cpp Src/Heap.cpp)

target_include_directories(Heap PUBLIC ${CMAKE_SOURCE_DIR}/Inc)
