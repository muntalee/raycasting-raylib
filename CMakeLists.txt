cmake_minimum_required(VERSION 3.0)
project(Raycast)

# Specify the location of header files
include_directories(include)

# Specify the location of libraries
link_directories(lib)

# Gather all source files
file(GLOB SOURCES src/*.c)

# Create an executable
add_executable(output ${SOURCES})

# Link against the Raylib library
target_link_libraries(output raylib)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
