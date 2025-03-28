cmake_minimum_required(VERSION 3.26)
project(DA_T03_G04)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source files
set(SOURCES
    main.cpp
    menu.cpp
    Distance.cpp
    Location.cpp
    loader.cpp
    IndependentRoute.cpp
    RestrictedRoute.cpp
)

# Add executable
add_executable(DA_T03_G04 ${SOURCES})

# Include directories
include_directories(
    data_structures 
)

# Link necessary libraries (if needed)
# target_link_libraries(DA_T03_G04 gtest gtest_main gmock gmock_main)
