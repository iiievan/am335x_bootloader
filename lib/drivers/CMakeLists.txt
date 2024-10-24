cmake_minimum_required(VERSION 3.24)
project(drivers
        LANGUAGES C
        DESCRIPTION
        "AM335x drivers library")
set(CMAKE_C_STANDARD 11)

set(COMPILER gcc)

add_library(${PROJECT_NAME} STATIC cppi41dma.c
                                   cpsw.c
                                   dcan.c
                                   dmtimer.c
                                   ecap.c
                                   edma.c
                                   ehrpwm.c
                                   elm.c
                                   gpio_v2.c
                                   gpmc.c
                                   hal_mmu.c
                                   hs_mmcsd.c
                                   hsi2c.c
                                   mailbox.c
                                   mcasp.c
                                   mcspi.c
                                   mdio.c
                                   phy.c
                                   raster.c
                                   rtc.c
                                   tsc_adc.c
                                   uart_irda_cir.c
                                   usb.c
                                   usbphyGS70.c
                                   watchdog.c)

target_link_libraries(${PROJECT_NAME} PRIVATE grlib
                                              usblib)

add_definitions(-Dam335x -Dam335x_15x15 -D${COMPILER})

