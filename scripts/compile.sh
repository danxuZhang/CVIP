#!/bin/sh

if [ -z "$1" ]; then
    echo "No program file name"
    exit 1
fi

program_file=$1

if [ ! -e "${program_file}.cpp" ]; then
    echo "Cannot find source file ${program_file}.cpp"
    exit 1
fi

echo "Compiling..."
g++ "${program_file}.cpp" -std=c++17 -Wall -o ${program_file} $(pkg-config --cflags --libs opencv4)
echo "Compilation finished"
