cmake_minimum_required(VERSION 3.24)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# project settings
project(am335x_bootloader LANGUAGES CXX ASM)
set(CMAKE_CXX_STANDARD 17)

set(NAME sitara)
set(TARGET am335x)
set(TRIPLE arm-none-eabi)

set(APP am335x_bootloader)
set(OBJDUMP objdump)
set(NM nm)
set(READLEF readelf)
set(CPPFILT c++filt)
set(SIZE size)
set(SIZE_OPTIONS -A -t)
set(PATH_APP   src)
set(PATH_BIN   bin)
set(PATH_TMP   tmp)
set(PATH_OBJ   ${PATH_TMP}/obj)
set(PATH_SRC   ${PATH_TMP}/src)
set(PATH_ERR   ${PATH_TMP}/err)

set(LINKER_DEFINITION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${APP}.ld)

include(cmake/gcc-toolchain.cmake)
include(cmake/am335x.cmake)

set(CMAKE_CC_FLAGS "${CFLAGS} ${TARGET_CFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS "${AFLAGS} ${TARGET_CFLAGS} ${TARGET_AFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${CXXFLAGS} ${TARGET_CFLAGS} ${TARGET_CXXFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${LDFLAGS} ${TARGET_LDFLAGS}" CACHE STRING "" FORCE)

add_executable(${APP} ${FILES_TARGET})
#set(SOURCES ${PATH_APP})
#add_executable(${APP} ${SOURCES} ${FILES_TARGET})

target_include_directories(${APP} PUBLIC ${TARGET_INCLUDES} ${PATH_APP})

set_target_properties(${APP}  PROPERTIES OUTPUT_NAME ${APP})
set_target_properties(${APP} PROPERTIES LINKER_LANGUAGE CXX)

# ------------------------------------------------------------------------------
# post build steps
# ------------------------------------------------------------------------------
add_custom_command(TARGET ${APP} POST_BUILD

        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}

        COMMENT "Generating Post Build Artifacts"

        # generate assembly listing
        COMMAND ${OBJDUMP} -h -S ${APP}${CMAKE_EXECUTABLE_SUFFIX} > ${APP}.lss

        # parsing symbols with nm to generate: ${APP}_nm.txt
        COMMAND ${NM} --numeric-sort ${PARSE_SYMBOL_OPTIONS} ${APP}${CMAKE_EXECUTABLE_SUFFIX} > ${APP}_nm.txt

        # demangling symbols with c++filt to generate: ${APP}_cppfilt.txt
        COMMAND ${NM} --numeric-sort ${PARSE_SYMBOL_OPTIONS} ${APP}${CMAKE_EXECUTABLE_SUFFIX} | ${CPPFILT} > ${APP}_cppfilt.txt

        # creating size summary table with size to generate: ${APP}_size.txt
        COMMAND ${SIZE} ${SIZE_OPTIONS} ${APP}${CMAKE_EXECUTABLE_SUFFIX} > ${APP}_size.txt

        # parsing symbols with readelf to generate: ${APP}_readelf.txt
        COMMAND ${POSTBUILD_GEN_SYMBOL_LISTING}

        # creating hex module: ${APP}.hex
        COMMAND ${POSTBUILD_GEN_HEX}

        # creating srec module: ${APP}.s19
        COMMAND ${POSTBUILD_GEN_S19}

        # creating bin module: ${APP}.bin
        COMMAND ${POSTBUILD_GEN_BIN}
)

 install(FILES
         ${CMAKE_BINARY_DIR}/${APP}${CMAKE_EXECUTABLE_SUFFIX}
         ${CMAKE_BINARY_DIR}/${APP}.lss
         ${CMAKE_BINARY_DIR}/${APP}_cppfilt.txt
         ${CMAKE_BINARY_DIR}/${APP}_size.txt
         ${MAP_FILE}
         ${SYMBOL_LISTING_FILE}
         ${HEX_FILE}
         ${BIN_FILE}

         DESTINATION

         ${CMAKE_CURRENT_SOURCE_DIR}/bin/${APP}
 )
