MEMORY
{
    SRAM (rwx) : ORIGIN = 0x402F0400, LENGTH = 0x1FBFF
}

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Entry)

STACK_SIZE = 0x1000;  /* 4KB */
HEAP_SIZE = 0x2000;   /* 8KB */

__SRAM_START = ORIGIN(SRAM);
__SRAM_END = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    /* Начало с векторов */
    . = __SRAM_START;

    .vectors : {
        KEEP(*(.vectors))
    }

    /* ВАЖНО: Продвигаем текущую позицию после векторов */
    . = ALIGN(4);

    /* Код после векторов */
    .text : {
        . = ALIGN(4);
        *(.text.boot)
        *(.text*)
        *(.text.handlers)
    }

    .rodata : {
        . = ALIGN(4);
        *(.rodata*)
    }

    .data : {
        . = ALIGN(4);
        *(.data*)
    }

    /* BSS - после кода и данных */
    .bss : {
        . = ALIGN(4);
        _bss_start = .;
        *(.bss*)
        *(COMMON)
        _bss_end = .;
    }

    .preinit_array : {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    }

    .init_array : {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
    }

    .fini_array : {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
    }

    /* Heap после всех секций */
    .heap : {
        . = ALIGN(4);
        __heap_start = .;
        . += HEAP_SIZE;
        __heap_end = .;
    }

    /* Конец используемой памяти */
    _end = .;

    /* Стек в конце SRAM, выровненный */
    . = __SRAM_END;
    _stack = . - STACK_SIZE;
    __StackTop = _stack;

    /* Проверка */
    ASSERT(_end <= _stack, "Error: Not enough SRAM for code + heap + stack!")
}