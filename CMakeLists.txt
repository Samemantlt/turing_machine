cmake_minimum_required(VERSION 3.21)
project(turing_machine C)

set(CMAKE_C_STANDARD 99)

add_executable(turing_machine main.c instruction.c machine.c parser.c stateRegistry.c)
