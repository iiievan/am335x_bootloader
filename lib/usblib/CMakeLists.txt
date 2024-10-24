cmake_minimum_required(VERSION 3.24)
project(usblib
        LANGUAGES C
        DESCRIPTION
        "AM335x usb library")
set(CMAKE_C_STANDARD 11)

set(COMPILER gcc)

add_library(${PROJECT_NAME} STATIC  device/usbdbulk.c
                                    device/usbdcdc.c
                                    device/usbdcdesc.c
                                    device/usbdcomp.c
                                    device/usbdconfig.c
                                    device/usbdenum.c
                                    device/usbdhandler.c
                                    device/usbdhid.c
                                    device/usbdhidmouse.c
                                    device/usbdmsc.c
                                    host/usbhhid.c
                                    host/usbhhidkeyboard.c
                                    host/usbhhidmouse.c
                                    host/usbhmsc.c
                                    host/usbhostenum.c
                                    host/usbhscsi.c
                                    usbbuffer.c
                                    usbdata.c
                                    usbdesc.c
                                    usbkeyboardmap.c
                                    usbringbuf.c
                                    usbtick.c)


add_definitions(-Dam335x -D${COMPILER})


