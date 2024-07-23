cmake_minimum_required(VERSION 3.24)

# project settings
project(am335x_bootloader LANGUAGES ASM C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

# specify cross compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(APP ${PROJECT_NAME})

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/${APP}.ld)

set(_TARGET_CFLAGS
        -mtune=cortex-a8
        -march=armv7-a
        -mfloat-abi=hard
        -mfpu=neon
)



set(_C_FLAGS ${_TARGET_CFLAGS}
        -mlong-calls
        -fdata-sections
        -funsigned-char
        -ffunction-sections
        -Wall
)

set(_CXX_FLAGS ${_C_FLAGS})

set(_ASM_FLAGS
        -r
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

string(REPLACE ";" " " CMAKE_C_FLAGS "${_C_FLAGS}")
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${_CXX_FLAGS}")
string(REPLACE ";" " " CMAKE_ASM_FLAGS "${_ASM_FLAGS}")
string(REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS "${_EXE_LINKER_FLAGS}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

add_executable(${APP} src/init.s src/main.c)

# ------------------------------------------------------------------------------
# post build steps
# ------------------------------------------------------------------------------

#set(HEX_FILE ${APP}.hex)
#set(BIN_FILE ${APP}.bin)
#add_custom_command(TARGET ${APP}.elf POST_BUILD
#        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${APP}.elf> ${HEX_FILE}
#        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${APP}.elf> ${BIN_FILE}
#        COMMENT "Building ${HEX_FILE}
#Building ${BIN_FILE}")

