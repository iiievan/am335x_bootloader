/* am335x_boot.ld - GCC Linker Script */

MEMORY
{
    SRAM (rwx) : ORIGIN = 0x402F0400, LENGTH = 0x1FBFF
    RTT_RAM (rw) : ORIGIN = 0x40300000, LENGTH = 0x10000
    /* 64KB as in segger documentation
       Гранулярность MMU страниц: На ARMv7-A минимальный размер страницы MMU - 4KB (small page) или 64KB (large page).
       Когда память кешируется/не кешируется, это делается на уровне страниц MMU.
       RTT буфер должен быть в NON-CACHED памяти: Чтобы отладчик (J-Link/Ozone) мог читать данные
       без проблем с когерентностью кеша.
       SEGGER рекомендует выравнивание 64KB: Чтобы можно было легко настроить
       атрибуты MMU для этого региона, не затрагивая соседние данные.
     */
}

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Entry)

/* Размеры стеков и кучи (как в IAR .icf) */
CSTACK_SIZE     = 0x1000;   /* 4KB */
SVC_STACK_SIZE  = 0x8;
IRQ_STACK_SIZE  = 0x1000;   /* 4KB */
FIQ_STACK_SIZE  = 0x8;
UND_STACK_SIZE  = 0x8;
ABT_STACK_SIZE  = 0x8;
HEAP_SIZE       = 0x0;      /* 0b */

RTT_BUFFER_SIZE = 0x1000;   /* 4KB */

__SRAM_START = ORIGIN(SRAM);
__SRAM_END = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    . = __SRAM_START;

    /* Startup code - должен быть первым */
    .text.startup : ALIGN(4) {
        KEEP(*(.text.startup))
    } > SRAM

    /* Остальной код */
    .text : ALIGN(4) {
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata.*)
    } > SRAM

    /* Инициализированные данные */
    .data : ALIGN(4) {
        *(.data)
        *(.data.*)
    } > SRAM

    /* BSS (неинициализированные данные) */
    .bss : ALIGN(4) {
        __bss_start = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        __bss_end = .;
    } > SRAM

    /* C++ конструкторы/деструкторы */
    .preinit_array : ALIGN(4) {
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array*))
        PROVIDE_HIDDEN(__preinit_array_end = .);
    } > SRAM

    .init_array : ALIGN(4) {
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        PROVIDE_HIDDEN(__init_array_end = .);
    } > SRAM

    .fini_array : ALIGN(4) {
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP(*(.fini_array*))
        KEEP(*(SORT(.fini_array.*)))
        PROVIDE_HIDDEN(__fini_array_end = .);
    } > SRAM

    .stack_svc (NOLOAD) : ALIGN(8) {
        __svc_stack_start = .;
        . += SVC_STACK_SIZE;
        __svc_stack_end = .;
    } > SRAM

    .stack_abt (NOLOAD) : ALIGN(8) {
        __abt_stack_start = .;
        . += ABT_STACK_SIZE;
        __abt_stack_end = .;
    } > SRAM

    .stack_und (NOLOAD) : ALIGN(8) {
        __und_stack_start = .;
        . += UND_STACK_SIZE;
        __und_stack_end = .;
    } > SRAM

    .stack_fiq (NOLOAD) : ALIGN(8) {
        __fiq_stack_start = .;
        . += FIQ_STACK_SIZE;
        __fiq_stack_end = .;
    } > SRAM

    .stack_irq (NOLOAD) : ALIGN(8) {
        __irq_stack_start = .;
        . += IRQ_STACK_SIZE;
        __irq_stack_end = .;
    } > SRAM

    .stack_main (NOLOAD) : ALIGN(8) {
        __stack_start = .;
        . += CSTACK_SIZE;
        __stack_end = .;
    } > SRAM

    /* ============================================================ */
    /* HEAP (размер 0, но секция присутствует) */
    /* ============================================================ */
    .heap (NOLOAD) : ALIGN(8) {
        __heap_start = .;
        . += HEAP_SIZE;
        __heap_end = .;
    } > SRAM

    PROVIDE(end = __heap_end);
    PROVIDE(_end = __heap_end);
    PROVIDE(__end = __heap_end);

    .rtt (NOLOAD) : ALIGN(64) {  /* Выравнивание по 64 байта (размер кэш-линии) */
        __rtt_start = .;
        KEEP(*(.rtt))
        KEEP(*(.rtt.*))
        . = ALIGN(64);
        __rtt_end = .;
    } > RTT_RAM

    /* Конец используемой памяти */
    __end_of_memory = .;

    /* Проверка переполнения */
    ASSERT(__end_of_memory <= __SRAM_END, "Error: SRAM overflow!")
}