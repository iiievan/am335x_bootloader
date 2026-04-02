cmake_minimum_required(VERSION 3.24)
project(am335x_regs
        VERSION 0.1.0
        LANGUAGES CXX
        DESCRIPTION
        "Registers description for am335x MPU")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB REGS_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${REGS_SOURCES}
        am335x_regs.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
