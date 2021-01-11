set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
cmake_minimum_required(VERSION 3.17)
project(example_particle_tmc5160)

set(CMAKE_CXX_STANDARD 14)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    message(FATAL_ERROR "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS TARGETS)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Particle)
include_directories(include)

if (APP STREQUAL "accel")
    particle_app(accel)
elseif (APP STREQUAL "pwm")
    particle_app(pwm)
else ()
    particle_app(simple)
endif ()
