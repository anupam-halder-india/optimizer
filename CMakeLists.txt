# Minimum required version of cmake
cmake_minimum_required(VERSION 3.10)

# Project name
project(optimizer)

# Locate the cpp files
add_executable(optimizer src/main.cpp)

# Locate where executable files should be built
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)