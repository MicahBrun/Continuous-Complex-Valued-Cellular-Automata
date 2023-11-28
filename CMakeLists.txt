cmake_minimum_required(VERSION 3.12)
project(ContinuousComplexValuedCellularAutomata
    VERSION 0.1
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)  # or 14, 17, etc., depending on your requirements

# Header files
include_directories(include)

# External dependencies (Eigen)
include_directories(external/Eigen)

include_directories(src)

# Add executable
add_executable(CCVCA src/main.cpp)