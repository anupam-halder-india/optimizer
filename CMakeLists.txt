# Minimum required version of cmake
cmake_minimum_required(VERSION 3.10)

# Project name
project(optimizer)

# for caching
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Locate the cpp files
add_executable(optimizer src/main.cpp)

# Locate where executable files should be built
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

# packages
find_package(CURL REQUIRED)

# Link libraries
target_link_libraries(optimizer PRIVATE ${CURL_LIBRARIES})
