cmake_minimum_required(VERSION 3.24)
project(startup LANGUAGES ASM CXX)

set(STARTUP_SOURCES startup.s
                    cp15.s
                    exceptionhandlers.s
                    cxx_support.cpp
)

add_library(${PROJECT_NAME} STATIC ${STARTUP_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
        am335x_registers
        RTT
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(${PROJECT_NAME} PRIVATE
        -mcpu=cortex-a8
        -mtune=cortex-a8
        -mfloat-abi=hard
        -mfpu=neon
        -ffreestanding
        -fno-exceptions
        -fno-rtti
        -mlong-calls
        -fdata-sections
        -funsigned-char
        -ffunction-sections
        -Wall
        -Wextra
        -g
)

target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>
)