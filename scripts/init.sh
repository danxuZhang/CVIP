#!/bin/bash

# Default values
project_name=""
src_dir="src"
doc_dir="doc"
include_dir="include"
main_file="${src_dir}/main.cpp"
cpp_std="17"

# Check if clang++ is installed, otherwise use g++
if command -v clang++ >/dev/null; then
    compiler="clang++"
else
    compiler="g++"
fi

# Check if gnu-sed(gsed) is installed, otherwise use sed
if command -v gsed >/dev/null; then
    sed="gsed"
else
    sed="sed"
fi

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
    --std)
        cpp_std="$2"
        shift # past argument
        shift # past value
        ;;
    *)
        project_name="$1"
        shift # past argument
        ;;
    esac
done

# Check if project name is provided
if [ -z "${project_name}" ]; then
    echo "Please provide a project name"
    exit 1
fi

# Check if OpenCV is installed
if ! command -v pkg-config >/dev/null; then
    echo "pkg-config not found. Please install it before proceeding."
    exit 1
fi

if ! pkg-config --exists opencv && ! pkg-config --exists opencv4; then
    echo "OpenCV not found. Please install OpenCV before proceeding."
    exit 1
fi

# Create folders
mkdir -p ${src_dir}
mkdir -p ${doc_dir}
mkdir -p ${include_dir}

# Create main.cpp file
cat >${main_file} <<EOF
#include <iostream>
#include <opencv2/opencv.hpp> 

int main() {
    std::cout << "Hello World!" << std::endl;
    return 0;
}
EOF

# Create run shell script
cat >run.sh <<EOF
#!/bin/sh
mkdir -p build 
cd build
cmake ..
make
./${project_name}
EOF


# Create CMakeLists.txt file
cat >CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.5)
project(${project_name} LANGUAGES CXX)

EOF

# Add C++ standard
echo "set(CMAKE_CXX_STANDARD ${cpp_std})" >>CMakeLists.txt

cat >>CMakeLists.txt <<EOF

# Find OpenCV
find_package(OpenCV REQUIRED)

# Add include directories
include_directories(
    \${OpenCV_INCLUDE_DIRS}
    ${include_dir}
)

# Set source files
set(SRC_FILES
    ${src_dir}/main.cpp
)

# Create executable
add_executable(\${PROJECT_NAME} \${SRC_FILES})

# Link with OpenCV libraries
target_link_libraries(\${PROJECT_NAME} \${OpenCV_LIBS})
EOF

# Replace placeholder text with project name
${sed} -i "s#OPENCV_PROJECT_NAME#${project_name}#g" CMakeLists.txt
