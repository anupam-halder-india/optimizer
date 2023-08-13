# Minimum required version of cmake
cmake_minimum_required(VERSION 3.22.1)

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -std=c++11 -ftest-coverage -Werror -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=../bin")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage -std=c++11 -Werror -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=../bin")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

# Project Name
project(optimizer)

# Locate the cpp files
set(SOURCES
  src/main.cpp
  src/include/modules/functions.cpp
  src/include/modules/variables.cpp
)
add_executable(optimizer ${SOURCES})

# Locate where the executable files should be build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

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
include_directories(/usr/include/apt-pkg)
include_directories(/usr/include/rpm)

# Link libraries
target_link_libraries(optimizer PRIVATE ${CURL_LIBRARIES})
