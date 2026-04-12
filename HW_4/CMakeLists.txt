cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(1_1 src/1_1sort.cpp)
add_executable(1_2 src/1_2adapter.cpp)
add_executable(2 src/2rec_inst.cpp)
add_executable(3_1 src/3_1dekartovo_product.cpp)
add_executable(3_2 src/3_2linear_recur.cpp)
