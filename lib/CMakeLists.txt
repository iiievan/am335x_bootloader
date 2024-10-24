cmake_minimum_required(VERSION 3.24)
project(starterware
        VERSION 2.0.1.1
        LANGUAGES ASM C
        DESCRIPTION
        "AM335x Starterware library")
set(CMAKE_C_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/include/hw
                    ${PROJECT_SOURCE_DIR}/include/armv7a
                    ${PROJECT_SOURCE_DIR}/include/armv7a/am335x
                    ${PROJECT_SOURCE_DIR}/grlib/include
                    ${PROJECT_SOURCE_DIR}/usblib/include
                    ${PROJECT_SOURCE_DIR}/mmcsdlib/include)

add_library(${PROJECT_NAME} STATIC starterware.c)

# Link the master library with the other libraries
target_link_libraries(${PROJECT_NAME} PUBLIC    drivers
                                                mmcsdlib
                                                platform
                                                system
                                                utils)

add_subdirectory(drivers)
add_subdirectory(grlib)
add_subdirectory(mmcsdlib)
add_subdirectory(platform)
add_subdirectory(system)
add_subdirectory(usblib)
add_subdirectory(utils)

