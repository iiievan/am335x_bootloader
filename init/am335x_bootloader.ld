
/* ld script for AM335x bootloader */

/*
** The stack is kept at end of the image, and its size is 2KB.
** The heap section is placed above the stack to support I/O
** operations using semihosting. The size of the section is 2KB.
*/

MEMORY
{
    IRAM_MEM :   o = 0x402F0400,  l = 0x1FBFF      /* 127k internal Memory */
}

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Entry)

SECTIONS
{

        .rsthand :
        {
            . = ALIGN(4);
            *init.o      (.text)
        } >IRAM_MEM

        .text :
        {
            . = ALIGN(4);
            *(.text*)
            *(.rodata*)
        } >IRAM_MEM

        .data :
        {
            . = ALIGN(4);
            *(.data*)
        } >IRAM_MEM

        .bss :
        {
            . = ALIGN(4);
            _bss_start = .;
            *(.bss)
            *(.bss.*)
            _bss_end = .;
        } >IRAM_MEM

        .heap :
        {
            . = ALIGN(4);
            __end__ = .;
            end = __end__;
            __HeapBase = __end__;
            *(.heap*)
            . = . + 0x800;
            __HeapLimit = .;
        } >IRAM_MEM

        .stack :
        {
            . = ALIGN(256);
            __StackLimit = . ;
            *(.stack*)
            . = . + 0x800;
            __StackTop = .;
        } >IRAM_MEM
        _stack = __StackTop;

}

