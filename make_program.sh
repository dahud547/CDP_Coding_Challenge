#!/bin/bash

set -e

# Create a build directory is one doesn't exist
if [ ! -d ./build ]; then
    mkdir ./build
fi

# Generate build files
cd ./build
cmake ..

# Make the program if successful
if [ ! -f ./Makefile ]; then
    echo "ERR: CMake failed to create Makefile"
    exit -1
else
    make
    echo "$PWD/bin/pwr_and_batt_packet_converter is where the executable is located"
    echo "To run, open up a terminal and run ./pwr_and_batt_packet_converter /path/to/file/to/be/converted"
fi
