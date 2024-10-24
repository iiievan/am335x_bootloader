cmake_minimum_required(VERSION 3.24)
project(system
        LANGUAGES ASM C
        DESCRIPTION
        "AM335x system library")
set(CMAKE_C_STANDARD 11)

set(COMPILER gcc)

add_library(${PROJECT_NAME} STATIC cache.c
                                   clock.c
                                   cp15.S
                                   cpu.c
                                   device.c
                                   exceptionhandler.S
                                   init.S
                                   interrupt.c
                                   mmu.c)

add_definitions(-Dam335x -D${COMPILER})

