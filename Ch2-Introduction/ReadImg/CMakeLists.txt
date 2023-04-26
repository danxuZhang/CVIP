cmake_minimum_required(VERSION 3.5)
project(ReadImg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Add include directories
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    include
)

# Set source files
set(SRC_FILES
    src/main.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link with OpenCV libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
