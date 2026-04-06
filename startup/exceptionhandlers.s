@******************************************************************************
@ exception_handlers_gcc.s - Exception handlers for GCC
@******************************************************************************

.global UndefInstHandler
.global SVC_Handler
.global AbortHandler
.global IRQHandler
.global FIQHandler

.section .text.handlers, "ax"
.code 32

@ Undefined Instruction Handler
UndefInstHandler:
    @ Можно добавить отладочный код
    bkpt #0
    b infinite_loop

@ SVC Handler - как в IAR, поддерживает переключение в System режим
SVC_Handler:
    STMFD sp!, {r0-r1, lr}
    SUB sp, sp, #4
    LDR r0, [lr, #-4]
    BIC r0, r0, #0xFF000000
    CMP r0, #458752
    MRSEQ r1, spsr
    ORREQ r1, r1, #0x1F
    MSREQ spsr_cf, r1
    ADD sp, sp, #4
    LDMFD sp!, {r0-r1, pc}^

@ Data and Prefetch Abort Handler
AbortHandler:
    bkpt #0
    b infinite_loop

@ IRQ Handler - минимальный для начала
IRQHandler:
    SUB lr, lr, #4
    SRSDB sp!, #0x12
    RFEIA sp!

@ FIQ Handler
FIQHandler:
    subs pc, lr, #4

infinite_loop:
    WFI
    b infinite_loop