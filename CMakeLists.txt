cmake_minimum_required(VERSION 3.24)

if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake)
    include(${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake)
endif()

# project settings
project(am335x_boot LANGUAGES ASM C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

set(APP ${PROJECT_NAME})
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/${APP}.ld)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-gc-sections,--print-memory-usage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map,${APP}.map")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-warn-rwx-segments")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-e,Entry")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-u,Entry")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-u,__aeabi_uidiv")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-u,__aeabi_idiv")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

add_subdirectory(startup)
add_subdirectory(REGS)
add_subdirectory(HAL)
add_subdirectory(app)
add_subdirectory(thirdparty)
add_subdirectory(rtt_log)