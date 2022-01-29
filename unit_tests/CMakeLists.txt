cmake_minimum_required(VERSION 2.8.7)
project (UnitTests)

# Check for CppUTest and bail out if they don't have it
if(DEFINED ENV{CPPUTEST_HOME})
  message("Using CppUTest found in $ENV{CPPUTEST_HOME}")
else()
  message("CPPUTEST_HOME is not set; You must tell CMake where to find CppUTest")
  message("CPPUTEST is a submodule of this repo in /tools.")
  return()
endif()

enable_language(C)
enable_language(CXX)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/../src)
include_directories(${PROJECT_SOURCE_DIR}/)
# include CppUTest headers
include_directories($ENV{CPPUTEST_HOME}/include)

add_library(imp_cpputest STATIC IMPORTED)
set_property(TARGET imp_cpputest PROPERTY
             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/src/CppUTest/libCppUTest.a)

add_library(packet_parser_tests ./packet_parser_tests.cpp ../src/packet_parser.c)
add_library(calculations_tests ./calculations_tests.cpp ../src/calculations.c)

add_executable(RunAllTests RunAllTests.cpp)
target_link_libraries(RunAllTests imp_cpputest packet_parser_tests calculations_tests)
