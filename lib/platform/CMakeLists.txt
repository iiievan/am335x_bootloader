cmake_minimum_required(VERSION 3.24)
project(platform
        LANGUAGES C
        DESCRIPTION
        "AM335x platform library")
set(CMAKE_C_STANDARD 11)

set(COMPILER gcc)

add_library(${PROJECT_NAME} STATIC board.c
                                   cpsw.c
                                   ctlregcontext.c
                                   dmtimer.c
                                   edma.c
                                   eeprom.c
                                   gpio.c
                                   hs_mmcsd.c
                                   hsi2c.c
                                   rtc.c
                                   sysdelay.c
                                   sysperf.c
                                   timertick.c
                                   uart.c
                                   uartConsole.c
                                   usb.c
                                   watchdog.c)

add_definitions(-Dam335x -Dbeaglebone -D${COMPILER})

