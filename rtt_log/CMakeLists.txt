cmake_minimum_required(VERSION 3.24)
project(rtt_log LANGUAGES C)

set(LOG_SOURCES rtt_log.c
        rtt_log_CAPI.cpp
        rtt_log_CAPI.hpp)

add_library(${PROJECT_NAME} STATIC ${LOG_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
                                      RTT
                                      HAL)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})