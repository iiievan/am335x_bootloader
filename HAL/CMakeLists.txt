cmake_minimum_required(VERSION 3.24)
project(HAL
        VERSION 0.1.0
        LANGUAGES CXX
        DESCRIPTION
        "Drivers for TI AM335x processor peripherals")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DRV_HEADERS INTC.hpp
        hwTimer.hpp
        sysTimer.hpp)

set(DRV_SOURCES INTC.cpp
        hwTimer.cpp
)

add_library(${PROJECT_NAME} STATIC ${DRV_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
        startup
        REGS
        RTT
)
target_compile_definitions(${PROJECT_NAME} PUBLIC  am335x)


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                                  ${CMAKE_CURRENT_SOURCE_DIR}/..)
