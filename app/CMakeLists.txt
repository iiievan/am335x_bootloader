set(APP_SOURCES init.cpp
                main.cpp
                ddr_calibration.cpp
)

add_executable(${APP}.elf ${APP_SOURCES})

target_link_libraries(${APP}.elf
        startup
        am335x_regs
        rtt_log
)

target_link_options(${APP}.elf PRIVATE
        -nostartfiles
        -lc
        -lgcc
        -Wl,--no-warn-rwx-segments
)

set(HEX_FILE ${APP}.hex)
set(BIN_FILE ${APP}.bin)

add_custom_command(TARGET ${APP}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${APP}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${APP}.elf> ${BIN_FILE}
        COMMAND ${SIZE} $<TARGET_FILE:${APP}.elf>
        COMMENT "Building ${HEX_FILE}\nBuilding ${BIN_FILE}\nSize information:"
)