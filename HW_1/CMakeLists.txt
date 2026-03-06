cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(struct_list src/PROFILER_list.cpp)
add_executable(struct_vector src/PROFILER_vector.cpp)

target_include_directories(struct_list PRIVATE include)
target_include_directories(struct_vector PRIVATE include)
