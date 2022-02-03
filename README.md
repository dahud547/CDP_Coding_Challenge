CDP Coding Challenge: Packet Parser
===================================

Coding Challenge for Cambridge Design Partnership where this program converts
two different packets to a text output.

## Toolchains Used
- GCC version 11.2.0
- CMake version 3.18.4 (Can use as low as 3.4 to compile though)
- Doxygen version 1.9.4
- cpputest version 4.0

## Building the Application
This project uses CMake to autogenerate the needed compiler configuration files
to build the application. This project was built and tested with GCC so CMake
generates a GNU makefile but CMake can autogenate build files for another
compilers just as easily if so desired. To use other compilers or build systems,
you will need to run CMake manual.

### Building using the Bash Script
To easily build this program, open up a bash terminal in the project folder and
simply run the following script:

    ./make_program.sh

This script will run cmake and make then outputs the executable to
`${project_folder}/build/bin`
### Building "by hand"
These are the steps to run CMake and build the program without the script. These
steps will assume a bash terminal is used, but can be adapted to your own terminal.
1. Open a bash terminal in the project folder
2. Make a folder called "build" and enter that folder

        mkdir ./build
        cd ./build

3. Run CMake while pointing to the project directory

        cmake ../

4. This should generate a makefile in the build folder, so next run make

        make

5. If successful, this should generate an executable located `${project_folder}/build/bin`

## Running the application
The program needs an input bin file containing the data to be parsed. It should
be passed as the only argument to the program on the command line. In a bash
terminal, it should look something like (assuming run from in the bin folder):

    ./pwr_and_batt_packet_converter /path/to/input/file

There is a test input file located at `${project_folder}/test_input_file/CodingTest.bin`
for demostration purposes.
