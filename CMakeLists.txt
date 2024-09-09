cmake_minimum_required(VERSION 3.10)

# Project name
project(BumperGame)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML package (graphics, window, and system components are needed)
find_package(SFML COMPONENTS graphics window system REQUIRED)

# Add include directories
include_directories(${SFML_INCLUDE_DIR})

# Add the source files
set(SOURCES
    src/Bumper.cpp
    src/Collision.cpp
    src/main.cpp
    src/Ball.cpp
    src/CVPinball.cpp
    src/Flipper.cpp
)

set(HEADERS
    src/Bumper.h
    src/Collision.h
    src/Ball.h 
    src/CVPinball.h
    src/Flipper.h
    src/Obstacle.h
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Optional: Set the output directory for binaries
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

