cmake_minimum_required(VERSION 3.24)
project(RTT LANGUAGES C)

add_compile_definitions(
        __ARM_ARCH_7A__=1
        __ARM_ARCH_7__=1
        __CORTEX_A=1
)

set(RTT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT/RTT/SEGGER_RTT.c
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT/RTT/SEGGER_RTT_printf.c
)

add_library(${PROJECT_NAME} STATIC ${RTT_SOURCES})

# Явно указываем флаги, не используя переменные
target_compile_options(${PROJECT_NAME} PRIVATE
        -mcpu=cortex-a8
        -mtune=cortex-a8
        -mfloat-abi=hard
        -mfpu=neon
        -mlong-calls
        -fdata-sections
        -funsigned-char
        -ffunction-sections
        -Wall
        -Wextra
        -g
        -ffreestanding
)

# Все определения для RTT
target_compile_definitions(${PROJECT_NAME} PUBLIC   BUFFER_SIZE_DOWN=64
                                                    BUFFER_SIZE_UP=4096
                                                    RTT_USE_ASM=0
                                                    SEGGER_RTT_CPU_CACHE_LINE_SIZE=0
                                                    SEGGER_RTT_MEMCPY_USE_BYTELOOP=1
                                                    SEGGER_RTT_SECTION=".rtt"
                                                    SEGGER_RTT_BUFFER_SECTION=".rtt"
                                                    SEGGER_RTT_UNCACHED_OFF=0
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT/Config
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT/RTT
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -O0)
endif()