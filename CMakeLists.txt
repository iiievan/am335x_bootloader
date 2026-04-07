cmake_minimum_required(VERSION 3.24)

if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake)
    include(${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake)
endif()

# project settings
project(am335x_boot LANGUAGES ASM C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)


set(APP ${PROJECT_NAME})
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/${APP}.ld)

set(_EXE_LINKER_FLAGS
        -e Entry
        -u Entry
        -u __aeabi_uidiv
        -u __aeabi_idiv
        -Wl,-gc-sections,--print-memory-usage
        -Wl,-Map,${APP}.map
        -T ${LINKER_SCRIPT}
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_INIT} ${_EXE_LINKER_FLAGS}")

string(REPLACE ";" " " TARGET_C_FLAGS "${CMAKE_COMMON_FLAGS_INIT}")
string(REPLACE ";" " " CMAKE_C_FLAGS "${CMAKE_C_FLAGS_INIT}")
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT}")
string(REPLACE ";" " " CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS_INIT}")
string(REPLACE ";" " " CMAKE_EXE_LINKER_FLAGS "${_EXE_LINKER_FLAGS}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

include_directories(${PROJECT_SOURCE_DIR}/startup)

add_subdirectory(am335x_regs)

file(GLOB_RECURSE INIT_SRC
        ${PROJECT_SOURCE_DIR}/startup/*.s
        ${PROJECT_SOURCE_DIR}/startup/*.cpp
)

add_subdirectory(app)
add_subdirectory(thirdparty)