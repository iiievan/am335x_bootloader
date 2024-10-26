cmake_minimum_required(VERSION 3.24)
project(fatfs
        VERSION 0.04    #R0.04b
        LANGUAGES C
        DESCRIPTION
        "ChaN fatfs library")
set(CMAKE_C_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} STATIC  src/ff.c)




