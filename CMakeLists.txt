cmake_minimum_required(VERSION 3.12)
project(ContinuousComplexValuedCellularAutomata
    VERSION 0.1
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)  # or 14, 17, etc., depending on your requirements

set(EXEC_SRC
    src/main.cpp
    src/grid.cpp
    src/ComplexMatToColor.cpp
    src/Transforms.cpp
    src/SpaceState.cpp
    )

set(EXEC_INCLUDE
    include/Grid.hpp
    include/ComplexMatToColor.hpp
    include/Transforms.hpp
    include/SpaceState.hpp
    )

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# External dependencies
include_directories(external/Eigen)

add_subdirectory(external)

# Add executable
add_executable(${PROJECT_NAME} ${EXEC_SRC} ${EXEC_INCLUDE} )

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics ${OpenCV_LIBS})

