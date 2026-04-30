cmake_minimum_required(VERSION 3.24)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/am335x_bsp/cmake/toolchain.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/am335x_bsp/cmake/toolchain.cmake)
elseif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)
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

add_subdirectory(am335x_bsp)

set(APP_SOURCES app/init.cpp
                app/main.cpp
                app/ddr_calibration.cpp)

add_executable(${APP}.elf ${APP_SOURCES})

target_link_libraries(${APP}.elf am335x_bsp )

target_link_options(${APP}.elf PRIVATE
        -nostartfiles
        -lc
        -lgcc
)

set(HEX_FILE ${APP}.hex)
set(BIN_FILE ${APP}.bin)
add_custom_command(TARGET ${APP}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${APP}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${APP}.elf> ${BIN_FILE}
        COMMAND ${SIZE} $<TARGET_FILE:${APP}.elf>
        COMMENT "Building ${HEX_FILE}\nBuilding ${BIN_FILE}\nSize information:"
)

# ============================================================
# Release-only: MLO generation (ПРОСТОЙ РАБОЧИЙ ВАРИАНТ)
# ============================================================
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Проверяем есть ли gen_mlo.c
    set(GEN_MLO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/am335x_bsp/tools/gen_mlo/gen_mlo.c)
    set(GEN_MLO_EXE ${CMAKE_CURRENT_BINARY_DIR}/gen_mlo)

    # Добавляем команду прямо в POST_BUILD основного таргета
    add_custom_command(TARGET ${APP}.elf POST_BUILD
            # Компилируем gen_mlo если он еще не скомпилирован
            COMMAND test -f ${GEN_MLO_EXE} || gcc -O2 -Wall -o ${GEN_MLO_EXE} ${GEN_MLO_SRC}
            # Создаем MLO
            COMMAND ${CMAKE_COMMAND} -E echo "=========================================="
            COMMAND ${CMAKE_COMMAND} -E echo "🔨 Generating MLO from ${BIN_FILE}"
            COMMAND ${CMAKE_COMMAND} -E echo "=========================================="
            COMMAND ${GEN_MLO_EXE} ${CMAKE_CURRENT_BINARY_DIR}/${BIN_FILE} ${CMAKE_CURRENT_BINARY_DIR}/MLO
            COMMAND ${CMAKE_COMMAND} -E echo "✅ MLO created at ${CMAKE_CURRENT_BINARY_DIR}/MLO"
            COMMAND ${CMAKE_COMMAND} -E echo "   Size: "
            COMMAND ls -lh ${CMAKE_CURRENT_BINARY_DIR}/MLO
            COMMAND ${CMAKE_COMMAND} -E echo "=========================================="
            COMMENT "Building MLO boot image for SD card"
    )
endif()

