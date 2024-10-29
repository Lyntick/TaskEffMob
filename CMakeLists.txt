cmake_minimum_required(VERSION 3.30)
project(TestTaskEffMob)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(BMPReader)

add_executable(TestTaskEffMob main.cpp)

target_link_libraries(TestTaskEffMob BMPReader)
