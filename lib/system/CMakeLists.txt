cmake_minimum_required(VERSION 3.24)
project(system
        LANGUAGES ASM C
        DESCRIPTION
        "AM335x system library")
set(CMAKE_C_STANDARD 11)

add_library(${PROJECT_NAME} STATIC cache.c
                                   clock.c
                                   cp15.s
                                   cpu.c
                                   device.c
                                   exceptionhandler.s
                                   init.s
                                   interrupt.c
                                   mmu.c)

add_definitions(-Dam335x)

