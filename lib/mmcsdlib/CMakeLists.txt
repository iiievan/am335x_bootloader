cmake_minimum_required(VERSION 3.24)
project(mmcsdlib
        LANGUAGES C
        DESCRIPTION
        "AM335x mmc library")
set(CMAKE_C_STANDARD 11)

set(COMPILER gcc)

add_library(${PROJECT_NAME} STATIC  hs_mmcsdlib.c
                                    mmcsd_proto.c)


add_definitions(-D${COMPILER})


