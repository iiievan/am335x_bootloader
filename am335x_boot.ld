/* ld script for AM335x bootloader */

MEMORY
{
    SRAM (rwx) : ORIGIN = 0x402F0400, LENGTH = 0x1FBFF  /* 130047 bytes internal Memory */
}

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Entry)

SECTIONS
{
    . = ORIGIN(SRAM);

    /* Таблица векторов должна быть первой в памяти */
    .vectors : {
        . = ALIGN(32);
        KEEP(*(.vectors))
    } > SRAM

    /* Startup code must be SECOND (после таблицы векторов) */
    .startup : {
        . = ALIGN(4);
        KEEP(*(.text.boot))
    } > SRAM

    .data : {
        . = ALIGN(4);
        *(.data*)
    } > SRAM

    .bss : {
        . = ALIGN(4);
        _bss_start = .;
        *(.bss*)
        *(COMMON)
        _bss_end = .;
    } > SRAM

    /* C++ Constructors and Destructors */
    .preinit_array : {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    } > SRAM

    .init_array : {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
    } > SRAM

    .fini_array : {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } > SRAM

    /* Stack section - placed at the end of SRAM */
    .stack (NOLOAD) : {
        . = ALIGN(4);
        . = . + 0x1000;  /* 4KB stack for C++ */
        _stack = .;
        __StackTop = .;
    } > SRAM

    /* Heap section for dynamic allocation */
    .heap (NOLOAD) : {
        . = ALIGN(4);
        __heap_start = .;
        . = . + 0x2000;  /* 8KB heap */
        __heap_end = .;
    } > SRAM
}