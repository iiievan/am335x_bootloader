;******************************************************************************
;
; init.S - Init code routines
;
;
;******************************************************************************
;
; Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
;
;
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions
;  are met:
;
;    Redistributions of source code must retain the above copyright
;    notice, this list of conditions and the following disclaimer.
;
;    Redistributions in binary form must reproduce the above copyright
;    notice, this list of conditions and the following disclaimer in the
;    documentation and/or other materials provided with the
;    distribution.
;
;    Neither the name of Texas Instruments Incorporated nor the names of
;    its contributors may be used to endorse or promote products derived
;    from this software without specific prior written permission.
;
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
;  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
;  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
;  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
;  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
;  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
;  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;******************************************************************************

	MODULE INIT
;****************************** Global Symbols*********************************
        PUBLIC Entry  

        ; Forward declaration of sections.
        SECTION IRQ_STACK:DATA:NOROOT(3)
        SECTION FIQ_STACK:DATA:NOROOT(3)
        SECTION SVC_STACK:DATA:NOROOT(3)
        SECTION ABT_STACK:DATA:NOROOT(3)
        SECTION UND_STACK:DATA:NOROOT(3)
        SECTION CSTACK:DATA:NOROOT(3)
        EXTWEAK __iar_init_core
        EXTWEAK __iar_init_vfp
        EXTERN  __cmain
 
        SECTION .bss:CODE:NOROOT(3)
        SECTION SYSTEMSTART:CODE (4)
;************************ Internal Definitions ********************************

;
; to set the mode bits in CPSR for different modes
;        
MODE_MSK DEFINE 0x1F            ; Bit mask for mode bits in CPSR
MODE_USR DEFINE 0x10            
MODE_FIQ DEFINE 0x11
MODE_IRQ DEFINE 0x12
MODE_SVC DEFINE 0x13
MODE_ABT DEFINE 0x17
MODE_UND DEFINE 0x1B
MODE_SYS DEFINE 0x1F            

I_F_BIT DEFINE 0xC0  
CP_DIS_MASK DEFINE  0xFFFFEFFA             

;******************************************************************************
; This source file is assembled for ARM instructions
        CODE32
;******************************************************************************

;
; The reset handler in StarterWare is named as 'Entry'.
; The reset handler sets up the stack pointers for all the modes. The FIQ and
; IRQ shall be disabled during this. Then clear the BSS sections and finally
; switch to the function calling the main() function.
;
Entry:
;
; Set up the Stack for Supervisor mode
;
         mrs     r0,cpsr                       ; Original PSR value
         bic     r0,r0,#MODE_MSK               ; Clear the mode bits
         orr     r0,r0,#MODE_SVC|I_F_BIT       ; Set Supervisor mode bits
         msr     cpsr_c,r0                     ; Change the mode
         ldr     sp,=SFE(SVC_STACK)            ; End of SVC_STACK
			 		 
         bic     r0,r0,#MODE_MSK               ; Clear the mode bits
         orr     r0,r0,#MODE_ABT|I_F_BIT       ; Set Abort mode bits
         msr     cpsr_c,r0                     ; Change the mode
         ldr     sp,=SFE(ABT_STACK)            ; End of ABT_STACK

         bic     r0,r0,#MODE_MSK               ; Clear the mode bits
         orr     r0,r0,#MODE_UND|I_F_BIT       ; Set Undefined mode bits
         msr     cpsr_c,r0                     ; Change the mode
         ldr     sp,=SFE(UND_STACK)            ; End of UND_STACK

         bic     r0,r0,#MODE_MSK               ; Clear the mode bits
         orr     r0,r0,#MODE_FIQ|I_F_BIT       ; Set FIQ mode bits
         msr     cpsr_c,r0                     ; Change the mode
         ldr     sp,=SFE(FIQ_STACK)            ; End of FIQ_STACK

         bic     r0,r0,#MODE_MSK               ; Clear the mode bits
         orr     r0,r0,#MODE_IRQ|I_F_BIT       ; Set IRQ mode bits
         msr     cpsr_c,r0                     ; Change the mode
         ldr     sp,=SFE(IRQ_STACK)            ; End of IRQ_STACK

         bic     r0,r0,#MODE_MSK               ; Clear the mode bits
         orr     r0,r0,#MODE_SYS|I_F_BIT       ; Set System mode bits
         msr     cpsr_c,r0                     ; Change the mode
         ldr     sp,=SFE(CSTACK)               ; End of CSTACK

         ; Invalidate Branch Prediction
         MOV     r0, #0                    
         MCR     p15, #0, r0, c7, c5, #6
         ISB
         
         ; Enable branch predictor
         ;MRC     p15, #0, r0, c1, c0, #0
         ;ORR     r0, r0, #0x00000800
         ;MCR     p15, #0, r0, c1, c0, #0
     
         ;MOV     r0, #0x0
         ;MCR     p15, 0, r0, c8, c7, 0        ; Invalidate TLB
     
         MOV     r0, #0
         MCR     p15, 0, r0, c7, c5, 0         ; Invalidate instruction cache
         
         BL      BSP_DCacheInvalidateAll
         
         ; Set domain access
         MRC     p15, 0, r0, c3, c0, 0         ; Read Domain Access Control Register
         LDR     r0, =0x55555555               ; Set all Domains to Client
         MCR     p15, 0, r0, c3, c0, 0         ; Write Domain Access Control Register 
     
     
         ; Turn on core features assumed to be enabled.
         BL      __iar_init_core
     
         ; Initialize VFP (if needed).
         BL      __iar_init_vfp

         ;Clear the BSS section here. 
         LDR   r0, =SFB(.bss)                  ; Start address of BSS
         LDR   r1, =SFE(.bss)                  ; End address of BSS
         MOV   r2, #0
loop_zi_copy:
         STR   r2, [r0], #4                    ; Clear one word in BSS
         CMP   r0, r1
         BLE   loop_zi_copy                    ; Clear till BSS end

         ; Continue to ?main for more IAR specific system startup
         B       __cmain
        
BSP_DCacheInvalidateAll:
        ; Invalidate L1 data cache
        MOV32     r0, #0x1FF            ; Load set index
BSP_DCacheInvalidateAll_loop_1:
        MOV     r1, #0x00000003         ; Load number of ways
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
        
         END    
    



