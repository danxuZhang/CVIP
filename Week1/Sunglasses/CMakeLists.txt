cmake_minimum_required(VERSION 3.14)
set(THIS Sunglasses)
project(${THIS} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(SRC_FILES
    src/main.cc
)

add_executable(${THIS} ${SRC_FILES})

target_link_libraries(${THIS} ${OpenCV_LIBS})
