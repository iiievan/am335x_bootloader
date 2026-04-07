cmake_minimum_required(VERSION 3.24)

add_compile_definitions(
        __ARM_ARCH_7A__=1
        __ARM_ARCH_7__=1
        __CORTEX_A=1
)

add_library(RTT STATIC  RTT/RTT/SEGGER_RTT.c
                        RTT/RTT/SEGGER_RTT_printf.c)

target_compile_definitions(RTT PUBLIC -DBUFFER_SIZE_DOWN=64
                                      -DBUFFER_SIZE_UP=4096
                                      -DRTT_USE_ASM=0
                                      -DSEGGER_RTT_CPU_CACHE_LINE_SIZE=0
                                      -DSEGGER_RTT_MEMCPY_USE_BYTELOOP=1
)

#target_compile_definitions(RTT PUBLIC -Dmemcpy=__builtin_memcpy
#        -Dmemset=__builtin_memset
#        -Dstrlen=__builtin_strlen
#)

target_include_directories(RTT
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT/Config
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT/RTT
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(RTT PRIVATE -O0 -g)
endif()

message(STATUS "RTT Library Configuration:")
message(STATUS "  - Architecture: ARMv7-A (Cortex-A8)")
message(STATUS "  - ASM optimizations: Disabled")
message(STATUS "  - Cache line size: 0")