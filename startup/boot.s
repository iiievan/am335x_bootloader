@******************************************************************************
@
@ boot.s - Startup code for AM335x
@
@******************************************************************************

@****************************** Global Symbols*******************************
        .global Entry
        .global _stack
        .global _bss_start
        .global _bss_end
        .global main
        .global __libc_init_array
        .global __preinit_array_start
        .global __preinit_array_end
        .global __init_array_start
        .global __init_array_end
        .global _vectors

@************************ Internal Definitions ******************************
@
@ Define the stack sizes for different modes.
@
        .set  UND_STACK_SIZE, 0x8
        .set  ABT_STACK_SIZE, 0x8
        .set  FIQ_STACK_SIZE, 0x8
        .set  IRQ_STACK_SIZE, 0x100
        .set  SVC_STACK_SIZE, 0x8

@
@ to set the mode bits in CPSR for different modes
@
        .set MODE_MSK, 0x1F            @ Bit mask for mode bits in CPSR
        .set  MODE_USR, 0x10
        .set  MODE_FIQ, 0x11
        .set  MODE_IRQ, 0x12
        .set  MODE_SVC, 0x13
        .set  MODE_ABT, 0x17
        .set  MODE_UND, 0x1B
        .set  MODE_SYS, 0x1F

        .equ  I_F_BIT, 0xC0

@**************************** Code Section ***********************************
@ Important: Must be in .text.boot section to be second and vectors.s - first
        .section .text.boot, "ax"
        .code 32

@******************************************************************************
@
@ The reset handler sets up the stack pointers for all the modes.
@ Then clears the BSS section and enters the main function.
@
Entry:
@
@ Set up the Stack for Undefined mode
@
         LDR   r0, =_stack                     @ Read the stack address
         MSR   cpsr_c, #MODE_UND|I_F_BIT       @ switch to undef mode
         MOV   sp, r0                          @ write the stack pointer
         SUB   r0, r0, #UND_STACK_SIZE         @ give stack space
@
@ Set up the Stack for abort mode
@
         MSR   cpsr_c, #MODE_ABT|I_F_BIT       @ Change to abort mode
         MOV   sp, r0                          @ write the stack pointer
         SUB   r0, r0, #ABT_STACK_SIZE         @ give stack space
@
@ Set up the Stack for FIQ mode
@
         MSR   cpsr_c, #MODE_FIQ|I_F_BIT       @ change to FIQ mode
         MOV   sp, r0                          @ write the stack pointer
         SUB   r0, r0, #FIQ_STACK_SIZE         @ give stack space
@
@ Set up the Stack for IRQ mode
@
         MSR   cpsr_c, #MODE_IRQ|I_F_BIT       @ change to IRQ mode
         MOV   sp, r0                          @ write the stack pointer
         SUB   r0, r0, #IRQ_STACK_SIZE         @ give stack space
@
@ Set up the Stack for SVC mode
@
         MSR   cpsr_c, #MODE_SVC|I_F_BIT       @ change to SVC mode
         MOV   sp, r0                          @ write the stack pointer
         SUB   r0, r0, #SVC_STACK_SIZE         @ give stack space
@
@ Set up the Stack for User/System mode
@
         MSR   cpsr_c, #MODE_SYS|I_F_BIT       @ change to system mode
         MOV   sp, r0                          @ write the stack pointer

@
@ Set Vector Base Address Register (VBAR)
@ Указываем, где находится таблица векторов
@
         LDR   r0, =_vectors                  @ Адрес таблицы векторов
         MCR   p15, 0, r0, c12, c0, 0         @ Записываем в VBAR
         DSB                                  @ Data Synchronization Barrier
         ISB                                  @ Instruction Synchronization Barrier

@ Invalidate Branch Prediction
         MOV     r0, #0
         MCR     p15, #0, r0, c7, c5, #6
         ISB

@ НЕ включаем Branch Predictor!
@        MRC     p15, #0, r0, c1, c0, #0
@        ORR     r0, r0, #0x00000800
@        MCR     p15, #0, r0, c1, c0, #0

@ Invalidate TLB
@       MOV     r0, #0x0
@       MCR     p15, 0, r0, c8, c7, 0

@ Invalidate instruction cache
        MOV     r0, #0
        MCR     p15, 0, r0, c7, c5, 0

@ Invalidate Data Cache
        BL      BSP_DCacheInvalidateAll

@ Set domain access
        LDR     r0, =0x55555555
        MCR     p15, 0, r0, c3, c0, 0

@
@ Enable Neon/VFP Co-Processor for C++ floating point
@
        MRC   p15, #0, r1, c1, c0, #2          @ r1 = Access Control Register
        ORR   r1, r1, #(0xf << 20)             @ enable full access for p10,11
        MCR   p15, #0, r1, c1, c0, #2          @ Access Control Register = r1
        MOV   r1, #0
        MCR   p15, #0, r1, c7, c5, #4          @ flush prefetch buffer
        MOV   r0, #0x40000000
        FMXR  FPEXC, r0                        @ Set Neon/VFP Enable bit

@
@ Clear the BSS section here
@
Clear_Bss_Section:
         LDR   r0, =_bss_start                 @ Start address of BSS
         LDR   r1, =_bss_end                   @ End address of BSS
         MOV   r2, #0
Loop:
         STR   r2, [r0], #4                    @ Clear one word in BSS
         CMP   r0, r1
         BLO   Loop                            @ Clear till BSS end

@
@ Call C++ global constructors
@
        LDR   r0, =__libc_init_array
        BLX   r0

@
@ Enter the main function
@
         LDR   r10, =main
         MOV   lr, pc                          @ Dummy return
         BX    r10                             @ Branch to main
         SUB   pc, pc, #0x08                   @ looping

@******************************************************************************
@ Function: BSP_DCacheInvalidateAll
@******************************************************************************
BSP_DCacheInvalidateAll:
        MOV     r0, #0x1FF            @ Load set index
BSP_DCacheInvalidateAll_loop_1:
        MOV     r1, #0x00000003         @ Load number of ways
BSP_DCacheInvalidateAll_loop_2:
        MOV     r2, r1, LSL #30
        ADD     r2, r2, r0, LSL #5
        MCR     p15, 0, r2, c7, c6, 2
        SUBS    r1, r1, #1
        BGE     BSP_DCacheInvalidateAll_loop_2
        SUBS    r0, r0, #1
        BGE     BSP_DCacheInvalidateAll_loop_1
        DSB
        BX      lr

@ End of the file
         .end