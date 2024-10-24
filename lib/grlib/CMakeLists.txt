cmake_minimum_required(VERSION 3.24)
project(grlib
        LANGUAGES C
        DESCRIPTION
        "AM335x graphics library")
set(CMAKE_C_STANDARD 11)

set(COMPILER gcc)

file(GLOB_RECURSE FONTS_SRC ${PROJECT_SOURCE_DIR}/grlib/fonts/*.c)

add_library(${PROJECT_NAME} STATIC ${FONTS_SRC}
                                    canvas.c
                                    checkbox.c
                                    circle.c
                                    container.c
                                    context.c
                                    image.c
                                    imgbutton.c
                                    line.c
                                    listbox.c
                                    offscr1bpp.c
                                    offscr4bpp.c
                                    offscr8bpp.c
                                    offscr16bpp.c
                                    offscr24bpp.c
                                    pushbutton.c
                                    radiobutton.c
                                    rectangle.c
                                    slider.c
                                    string.c
                                    widget.c)


add_definitions(-D${COMPILER})


