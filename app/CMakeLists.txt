
add_executable(${APP}.elf main.cpp ${INIT_SRC})

target_link_libraries(${APP}.elf
        ${TARGET_C_FLAGS}
        -nostartfiles
        m #libm
        gcc #libgcc
)

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
