#!/bin/bash

set -e

if [ ! -d ./build ]; then
    mkdir ./build
fi

cd ./build
cmake ..

if [ ! -f ./Makefile ]; then
    echo "ERR: CMake failed to create Makefile"
    exit -1
else
    make
    echo "$PWD/bin/pwr_and_batt_packet_converter is where the executable is located"
    echo "To run, open up a terminal and run ./pwr_and_batt_packet_converter /path/to/file/to/be/converted"
fi
