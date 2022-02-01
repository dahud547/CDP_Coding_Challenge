#!/bin/bash

set -e

if [ ! -d ./unit_tests/build ]; then
    mkdir ./unit_tests/build
fi

export CPPUTEST_HOME=$PWD/tools/cpputest

cd ./unit_tests/build
cmake ..

if [ ! -f ./Makefile ]; then
    echo "ERR: CMake failed to create Makefile"
    exit -1
else
    make
    ./bin/RunAllTests
fi
