@******************************************************************************
@
@ cpu.S - CPU mode switching and interrupt control for AM335x (Cortex-A8)
@
@ Adapted for arm-none-eabi-gcc / GNU Assembler
@ Based on original Texas Instruments StarterWare code
@
@******************************************************************************

@****************************** Global Symbols*********************************
    .global CPUSwitchToPrivilegedMode
    .global CPUSwitchToUserMode
    .global CPUAbortHandler
    .global CPUIntStatus
    .global CPUirqd
    .global CPUirqe
    .global CPUfiqd
    .global CPUfiqe

@**************************** Code section ************************************
    .text
    .align 4
    .syntax unified
    .arch armv7-a
    .arm

@*****************************************************************************
@ Switch from User mode to Privileged (System) mode
@ Uses SWI #458752 as in original TI StarterWare
@*****************************************************************************
CPUSwitchToPrivilegedMode:
    swi     #458752
    bx      lr

@*****************************************************************************
@ Switch from any privileged mode to User mode
@*****************************************************************************
CPUSwitchToUserMode:
    mrs     r0, cpsr
    bic     r0, r0, #0x1F       @ Clear mode bits
    orr     r0, r0, #0x10       @ Set User mode (0b10000)
    msr     cpsr_c, r0
    bx      lr

@*****************************************************************************
@ Abort handler (called on undefined instruction / abort)
@*****************************************************************************
CPUAbortHandler:
    nop
    nop
    nop
    nop
    bx      lr

@*****************************************************************************
@ Return current IRQ and FIQ mask status (bits 7 and 6 of CPSR)
@*****************************************************************************
CPUIntStatus:
    mrs     r0, cpsr
    and     r0, r0, #0xC0       @ Mask I (bit 7) and F (bit 6)
    bx      lr

@*****************************************************************************
@ Disable IRQ
@*****************************************************************************
CPUirqd:
    mrs     r0, cpsr
    orr     r0, r0, #0x80       @ Set I bit
    msr     cpsr_c, r0
    bx      lr

@*****************************************************************************
@ Enable IRQ
@*****************************************************************************
CPUirqe:
    mrs     r0, cpsr
    bic     r0, r0, #0x80       @ Clear I bit
    msr     cpsr_c, r0
    bx      lr

@*****************************************************************************
@ Disable FIQ
@*****************************************************************************
CPUfiqd:
    mrs     r0, cpsr
    orr     r0, r0, #0x40       @ Set F bit
    msr     cpsr_c, r0
    bx      lr

@*****************************************************************************
@ Enable FIQ
@*****************************************************************************
CPUfiqe:
    mrs     r0, cpsr
    bic     r0, r0, #0x40       @ Clear F bit
    msr     cpsr_c, r0
    bx      lr

@******************************************************************************
@
@ End of the file
@
@******************************************************************************
    .end