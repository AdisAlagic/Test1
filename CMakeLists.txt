cmake_minimum_required(VERSION 3.15)
project(Test1)

set(CMAKE_CXX_STANDARD 20)
find_package (Threads)
add_executable(Test1 main.cpp)
target_link_libraries (Test1 ${CMAKE_THREAD_LIBS_INIT})