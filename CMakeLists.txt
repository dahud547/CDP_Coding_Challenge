cmake_minimum_required(VERSION 3.18.4)
project(monitoring_pwr_states)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMKAE_VERBOSE_MAKEFILE ON)

add_compile_options(-Wall -Wextra -Wconversion -Wcast-align -Wcast-qual)
add_compile_options(-Wdouble-promotion -Wduplicated-cond -Wfloat-equal -std=c11)
add_compile_options(-Wlogical-op -Wnull-dereference -Wold-style-definition)
add_compile_options(-Wredundant-decls -Wshadow -Wswitch-default -Wwrite-strings)
add_compile_options(-Wno-unknown-pragmas -Wno-unused-function -Wjump-misses-init)
add_compile_options(-Wmissing-prototypes -Wstrict-prototypes -Wpointer-arith)

# The code for compiling lives here
add_subdirectory(src)
