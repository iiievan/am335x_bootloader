cmake_minimum_required(VERSION 3.24)
project(utils
        LANGUAGES C
        DESCRIPTION
        "AM335x utils library")
set(CMAKE_C_STANDARD 11)

set(COMPILER gcc)

add_library(${PROJECT_NAME} STATIC ascii.c
                                   board.c
                                   cmdline.c
                                   consoleUtils.c
                                   delay.c
                                   misc.c
                                   perf.c
                                   systick.c
                                   uartStdio.c)

add_definitions(-D${COMPILER})

