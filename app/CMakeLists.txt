
add_executable(${APP}.elf main.cpp ${INIT_SRC})

target_link_libraries(${APP}.elf
        PRIVATE
        ${TARGET_C_FLAGS}
        -nostartfiles
        m #libm
        gcc #libgcc
        starterware
)
target_include_directories(starterware PUBLIC ${PROJECT_SOURCE_DIR}/lib/include
                                              ${PROJECT_SOURCE_DIR}/lib/include/hw
                                              ${PROJECT_SOURCE_DIR}/lib/include/armv7a
                                              ${PROJECT_SOURCE_DIR}/lib/include/armv7a/am335x
                                              ${PROJECT_SOURCE_DIR}/lib/grlib/include
                                              ${PROJECT_SOURCE_DIR}/lib/usblib/include
                                              ${PROJECT_SOURCE_DIR}/lib/mmcsdlib/include)
# ------------------------------------------------------------------------------
# post build steps
# ------------------------------------------------------------------------------
set(HEX_FILE ${APP}.hex)
set(BIN_FILE ${APP}.bin)
add_custom_command(TARGET ${APP}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${APP}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${APP}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
