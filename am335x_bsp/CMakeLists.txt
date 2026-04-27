# am335x_bsp/CMakeLists.txt (упрощенная версия)
cmake_minimum_required(VERSION 3.24)

if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake)
    include(${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake)
endif()

project(am335x_bsp VERSION 1.0.0 LANGUAGES ASM C CXX)

# Настройки
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# Опции сборки
option(BSP_USE_HARD_FLOAT "Use hardware floating point" ON)

if(NOT CMAKE_C_COMPILER MATCHES "arm-none-eabi")
    message(WARNING "Expected arm-none-eabi-gcc, found ${CMAKE_C_COMPILER}")
    message(WARNING "Please set CMAKE_TOOLCHAIN_FILE or use proper compiler")
endif()

add_subdirectory(thirdparty/SEGGER_RTT)

# Список исходников
set(BSP_SOURCES
        src/hal/INTC.cpp
        src/hal/hwTimer.cpp
        src/hal/serial.cpp
        src/hal/pins/am335x_pins.cpp
        src/hal/boards/beaglebone_black.cpp
        src/regs/CONTROL_MODULE.cpp
        src/regs/REGS.cpp
        src/rtt/rtt_log.c
        src/rtt/rtt_log_capi.cpp
        src/startup/startup.s
        src/startup/cp15.s
        src/startup/cpu.s
        src/startup/exceptionhandlers.s
        src/startup/cxx_support.cpp
        include/hal/UART.hpp
        src/hal/UART.cpp
)


add_library(am335x_bsp STATIC ${BSP_SOURCES})


target_link_libraries(am335x_bsp PUBLIC SEGGER_RTT)

if(CMAKE_C_COMPILER MATCHES "arm-none-eabi")
    target_compile_options(am335x_bsp PRIVATE
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
            -ffreestanding
    )
else()
    message(WARNING "Skipping ARM-specific flags for ${CMAKE_C_COMPILER}")
endif()

target_compile_options(am335x_bsp PRIVATE
        $<$<CONFIG:Debug>:-O0 -g3 -DDEBUG>
        $<$<CONFIG:Release>:-Os -g0 -DNDEBUG>
)


target_compile_options(am335x_bsp PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions -fno-rtti -fno-use-cxa-atexit>
)


target_compile_options(am335x_bsp PRIVATE
        $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>
)


target_compile_definitions(am335x_bsp PUBLIC
        __ARM_ARCH_7A__=1
        __ARM_ARCH_7__=1
        __CORTEX_A=1
        am335x
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Debug: без оптимизации, volatile overloads не нужны
    target_compile_definitions(am335x_bsp PUBLIC
            BSP_VOLATILE_OVERLOADS=0
            BSP_BUILD_TYPE="Debug"
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    # RelWithDebInfo: с оптимизацией (-Os), volatile overloads нужны
    target_compile_definitions(am335x_bsp PUBLIC
            BSP_VOLATILE_OVERLOADS=1
            BSP_BUILD_TYPE="RelWithDebInfo"
    )
else()
    # Release и другие: с оптимизацией, volatile overloads нужны
    target_compile_definitions(am335x_bsp PUBLIC
            BSP_VOLATILE_OVERLOADS=1
            BSP_BUILD_TYPE="Release"
    )
endif()


target_include_directories(am335x_bsp PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

message(STATUS "Building am335x_bsp version ${PROJECT_VERSION}")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  CXX Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Include: ${CMAKE_CURRENT_SOURCE_DIR}/include")