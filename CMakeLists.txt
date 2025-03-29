cmake_minimum_required(VERSION 3.26)
project(DA_T03_G04)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source files
set(SOURCES
    main.cpp
    menu.cpp
    loader.cpp
        data_structures/Location.cpp
        data_structures/Distance.cpp
        routes/IndependentRoute.cpp
        routes/RestrictedRoute.cpp
        routes/EcoRoute.cpp
)

# Add executable
add_executable(DA_T03_G04 ${SOURCES})

# Include directories
include_directories(
        ${CMAKE_SOURCE_DIR}/data_sets
        ${CMAKE_SOURCE_DIR}/data_structures
        ${CMAKE_SOURCE_DIR}/routes
)

# Link necessary libraries (if needed)
# target_link_libraries(DA_T03_G04 gtest gtest_main gmock gmock_main)
