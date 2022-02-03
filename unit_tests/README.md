Unit Testing
============
This guide for building and running the unit tests.

## Building Unit Tests
**NOTE**: This assumes CppUTest has already been setup. See CppUTest Setup section
for more details on how to make that environment. This guide also assumes that
the unit tests will be run using a bash terminal and GCC make environment.

Steps to build the unit tests:
1. Open up a bash terminal in the unit tests folder
2. Make a folder called "build" and enter that folder

        mkdir ./build
        cd ./build

3. Run CMake while pointing to the project directory

        cmake ../

4. This should generate a makefile in the build folder, so next run make

        make

5. If successful, this should generate an executable located `${project_folder}/unit_tests/build/bin`

## Running the Unit Tests
To run the unit tests, run the executable on the command line. This should output
the results of running the tests.

    ${project_folder}/unit_tests/build/bin/RunAllTests

Output should look something like:

    ...........................
    OK (27 tests, 27 ran, 893 checks, 0 ignored, 0 filtered out, 0 ms)

## CppUTest Setup
If CppUTest isn't installed system wide then it has been included as a submodule
of this project. To make sure the submodule downloaded, run the following command
from the project directory:

    git submodule init
    git submodule update --recursive

This is checkout the CppUTest repository into `${project_folder}/tools/cpputest`

Steps to build CppUTest:
1. Open a bash terminal inside of the tools/cpputest directory
2. Run autoreconfig

        autoreconfig . -i

3. Run configure

        ./configure

4. Compile using the makefile

        make

5. Set the CPPUTEST_HOME environemnt variable to point to `${project_folder}/tools/cpputest`

CppUTest can also be installed on Windows to work with Visual Stuido using CMake.
See CppUTest's website for more information on that: http://cpputest.github.io/
