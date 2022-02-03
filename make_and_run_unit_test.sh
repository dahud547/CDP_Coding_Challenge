#!/bin/bash

set -e

# Create a build directory is one doesn't exist
if [ ! -d ./unit_tests/build ]; then
    mkdir ./unit_tests/build
fi

# Make sure we have a path to the cpputest home directory
if [ -z "${CPPUTEST_HOME}" ]; then
    export CPPUTEST_HOME=$PWD/tools/cpputest
fi

# Generate build files
cd ./unit_tests/build
cmake ..

# Make the tests and run them if successful.
# This should also be caught by setting of -e at the top of the script
if [ ! -f ./Makefile ]; then
    echo "ERR: CMake failed to create Makefile"
    exit -1
else
    make
    if [ ! -f ./bin/RunAllTests ]; then
        echo "ERR: Unit tests did not compile"
        exit -1
    else
        ./bin/RunAllTests
    fi
fi
