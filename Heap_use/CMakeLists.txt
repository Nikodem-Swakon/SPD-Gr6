cmake_minimum_required(VERSION 3.0.0)
project(Heap_use LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(Heap)

add_executable(Heap_use main.cpp )

target_link_libraries(Heap_use PRIVATE Heap)

target_include_directories(Heap PUBLIC ${CMAKE_SOURCE_DIR}/Inc)
