set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)
cmake_minimum_required(VERSION 3.24)

# specify cross compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(am335x_bootloader LANGUAGES ASM C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

set(APP ${PROJECT_NAME})

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/init/${APP}.ld)

set(_TARGET_CFLAGS
        -mcpu=cortex-a8
        -mtune=cortex-a8
        -mfpu=neon
)

set(_C_FLAGS ${_TARGET_CFLAGS}
        -mlong-calls
        -fdata-sections
        -funsigned-char
        -ffunction-sections
        -Wall
)

set(_CXX_FLAGS ${_C_FLAGS}
        -fno-exceptions
)

set(_ASM_FLAGS ${_TARGET_CFLAGS}
        -r
        -x assembler-with-cpp
)


set(_EXE_LINKER_FLAGS
        -e Entry
        -u Entry
        -u __aeabi_uidiv
        -u __aeabi_idiv
        -Wl,-gc-sections,--print-memory-usage
        -Wl,-Map,${APP}.map
        -T ${LINKER_SCRIPT}
)

string(REPLACE ";" " " TARGET_C_FLAGS "${_TARGET_CFLAGS}")
string(REPLACE ";" " " CMAKE_C_FLAGS "${_C_FLAGS}")
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${_CXX_FLAGS}")
string(REPLACE ";" " " CMAKE_ASM_FLAGS "${_ASM_FLAGS}")
string(REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS "${_EXE_LINKER_FLAGS}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

include_directories(${PROJECT_SOURCE_DIR}/init)

file(GLOB_RECURSE INIT_SRC
        ${PROJECT_SOURCE_DIR}/init/*.*
)

add_subdirectory(lib)
add_subdirectory(app)


