cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(list src/list_profiler.cpp)
add_executable(matrix src/matrix_with_subvector.cpp)
add_executable(vector src/vector_prof.cpp)

target_include_directories(list PRIVATE include)
target_include_directories(matrix PRIVATE include)
target_include_directories(vector PRIVATE include)
