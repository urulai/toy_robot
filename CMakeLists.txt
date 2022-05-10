cmake_minimum_required(VERSION 3.10.2)

# Builds the application.
project (toy_robot)
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(toy_robot ${SOURCES})
target_compile_options(toy_robot PRIVATE "-Wall;-Werror")

# Build unit tests executable.
project (unit_tests)
include_directories(include)

file(GLOB CODE_TO_TEST "src/toy_robot.cpp" "src/command_parser.cpp")
add_executable(run_all_tests ${CODE_TO_TEST} "tests/test_suite.cpp")