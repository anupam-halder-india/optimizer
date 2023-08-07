# Minimum required version of cmake
cmake_minimum_required(VERSION 3.10)

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

# Project Name
project(optimizer)

# Locate the cpp files
add_executable(optimizer src/main.cpp)

# Locate where the executable files should be build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# Specifyiing cmake generator
set(CMAKE_GENERATOR "Ninja")
# This are the Commands For Caching
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the custom target to run Cpplint
add_custom_target(
    cpplint
    COMMAND cpplint --recursive --filter=-,+${CMAKE_SOURCE_DIR}/.cpplint ${CMAKE_SOURCE_DIR}/src/main.cpp
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Cpplint on C++ source files"
)

# Make Cpplint target dependent on your build target(s)
add_dependencies(cpplint optimizer)

# Packages
find_package(CURL REQUIRED)

# Link libraries
target_link_libraries(optimizer PRIVATE ${CURL_LIBRARIES})
