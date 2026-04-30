# am335x_bsp/thirdparty/SEGGER_RTT/CMakeLists.txt (упрощенный)
cmake_minimum_required(VERSION 3.24)
project(SEGGER_RTT LANGUAGES C)

set(RTT_SOURCES
        RTT/SEGGER_RTT.c
        RTT/SEGGER_RTT_printf.c
)

add_library(SEGGER_RTT STATIC ${RTT_SOURCES})

target_compile_definitions(SEGGER_RTT PUBLIC
        BUFFER_SIZE_DOWN=64
        BUFFER_SIZE_UP=4096
        RTT_USE_ASM=0
        SEGGER_RTT_CPU_CACHE_LINE_SIZE=0
        SEGGER_RTT_MEMCPY_USE_BYTELOOP=1
        SEGGER_RTT_SECTION=".rtt"
        SEGGER_RTT_BUFFER_SECTION=".rtt"
        SEGGER_RTT_UNCACHED_OFF=0
)

target_include_directories(SEGGER_RTT PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Config
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT
)

# Оптимизация
target_compile_options(SEGGER_RTT PRIVATE
        $<$<CONFIG:Release>:-O0>
        $<$<CONFIG:Debug>:-Os>
)

# Отключаем экспорт для упрощения
set_target_properties(SEGGER_RTT PROPERTIES
        EXCLUDE_FROM_EXPORT TRUE
)