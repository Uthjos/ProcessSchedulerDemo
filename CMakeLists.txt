cmake_minimum_required(VERSION 4.0)
project(ProcessSchedulerDemo C)

set(CMAKE_C_STANDARD 23)

add_executable(ProcessSchedulerDemo main.c
        process.h)
