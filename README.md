# Toy Robot Code Challenge.

## Problem Statement
The application is a simulation of a toy robot moving on a square table top, of dimensions 5 units x 5 units. There are no other obstructions on the table surface. The robot is free to roam around the surface of the table, but must be prevented from falling to destruction. Any movement that would result in the robot falling from the table must be prevented, however further valid movement commands must still be allowed.

## Prerequisites
1. CMake
    ```sh
    sudo apt install cmake
    ```
2. GNU C/C++ Compiler
3. Ubuntu 18.04 on Windows.

## Installation
```sh
git clone https://github.com/urulai/toy_robot
```

## Directory structure

```
toy_robot
├── CMakeLists.txt                     --> CMake configuration file
├── readme.md
├── src                                --> source files
    ├── main.cpp
    ├── toy_robot.cpp
    ├── command_parser.cpp
├── include                            --> header files
    ├── toy_robot.h
    ├── command_parser.h
└── tests                              --> unit tests
    ├── acutest.h
    ├── test_suite.cpp
```

## Building the project:
1. After cloning the source files, create a directory ***build*** at the parent directory.
    ```sh
    mkdir build
    ```
2. Change to ***build*** directory.
    ```sh
    cd build
    ```
3. Execute ***cmake*** in the terminal.
    ```sh
    cmake ..
    ```

The following executables are generated in the build directory.
- toy_robot --> Main executable
- run_all_tests --> Test suite

## Running the project:

A sample input file ***'input.txt'*** to run the executable is present in the ***/data*** directory.

1. Change to ***build*** directory, if required.
2. Run the executable by passing the filename as an command-line argument.
    ```sh
    ./toy_robot ./../data/input.txt
    ```

# Running unit tests:
1. Change to ***build*** directory, if required.
2. Run the unit test executable.
    ```sh
    ./run_all_tests
    ```
