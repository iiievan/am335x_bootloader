#ifndef __WDT_HPP
#define __WDT_HPP

#include <stdint.h>
#include "utils.h"

namespace REGS
{ 
    namespace WDT
    {    
        
    /*******************************************************************************************************************************************************************************/  
    
    /*************************************************************************** AM335x_WATCHDOG_Type Registers **********************************************************************/ 
    
    /*******************************************************************************************************************************************************************************/      

        /*  (offset = 0x00) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WIDR - Watchdog Identification Register
                                                 */
            struct
            {
                uint32_t REVISION        :32;    // bits 0..31  (R)  IP Revision
                                                 //                  Contains the revision identifier of the watchdog timer IP
            } b;
            uint32_t reg;
        } WDT_WIDR_reg_t;
        
        /*  (offset = 0x10) [reset = 0x00000010] */
        typedef union
        {                                       /* WDT_WDSC - Watchdog System Control Register
                                                   */
            struct
            {
                uint32_t                :6;     // bits 0..5   (R)  Reserved
                uint32_t EMUFREE        :1;     // bit  6      (R/W) Sensitivity to emulation suspend [see e_IDLEMODE]
                                                //                   Controls behavior during debug suspend events
                                                //                   0x0 = Timer counter frozen during debug suspend event
                                                //                   0x1 = Timer counter free-running, ignores debug suspend
                uint32_t IDLEMODE       :2;     // bits 7..8   (R/W) Local target state management mode [see e_IDLEMODE]
                uint32_t                :1;     // bit  9      (R)  Reserved
                uint32_t SOFTRESET      :1;     // bit  10     (R/W) Software reset control
                                                //                   0x0 (W) = No action
                                                //                   0x0 (R) = Reset done, no pending action
                                                //                   0x1 (W) = Initiate software reset
                                                //                   0x1 (R) = Reset (software or other) ongoing
                uint32_t                :21;    // bits 11..31 (R)   Reserved
            } b;
            uint32_t reg;
        } WDT_WDSC_reg_t;
        
        /* Enums for multi-value fields */
        enum e_IDLEMODE : uint32_t 
        {
            /*  Configuration of the local target state management mode. Target can handle transactions when not in IDLE state
             *  0x0 = Force-idle mode: follows system idle requests unconditionally (debug only)
             *  0x1 = No-idle mode: never enters idle state (debug only)
             *  0x2 = Smart-idle mode: follows system idle requests based on IP module's requirements
             *  0x3 = Smart-idle wakeup-capable mode: follows system idle requests and can generate wakeup events
             */
            IDLEMODE_FORCE_IDLE = 0x0,
            IDLEMODE_NO_IDLE = 0x1,
            IDLEMODE_SMART_IDLE = 0x2,
            IDLEMODE_SMART_IDLE_WAKEUP = 0x3
        };
        
        /*  (offset = 0x14) [reset = 0x00000001] */
        typedef union
        {                                       /* WDT_WDST - Watchdog Status Register
                                                 */
            struct
            {
                uint32_t                :31;    // bits 0..30  (R)  Reserved
                uint32_t RESETDONE      :1;     // bit  31     (R)  Internal module reset monitoring
                                                //                  0x0 = Internal module reset is ongoing
                                                //                  0x1 = Reset completed
            } b;
            uint32_t reg;
        } WDT_WDST_reg_t;
        
        /*  (offset = 0x18) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WISR - Watchdog Interrupt Status Register
                                                   */
            struct
            {
                uint32_t                :30;    // bits 0..29  (R)   Reserved
                uint32_t DLY_IT_FLAG    :1;     // bit  30     (R/W) Pending delay interrupt status
                                                //                   0x0 (W) = Status unchanged
                                                //                   0x0 (R) = No delay interrupt pending
                                                //                   0x1 (W) = Status bit cleared
                                                //                   0x1 (R) = Delay interrupt pending
                uint32_t OVF_IT_FLAG    :1;     // bit  31     (R/W) Pending overflow interrupt status
                                                //                   0x0 (W) = Status unchanged
                                                //                   0x0 (R) = No overflow interrupt pending
                                                //                   0x1 (W) = Status bit cleared
                                                //                   0x1 (R) = Overflow interrupt pending
            } b;
            uint32_t reg;
        } WDT_WISR_reg_t;
        
        /*  (offset = 0x1C) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WIER - Watchdog Interrupt Enable Register
                                                 */
            struct
            {
                uint32_t                :30;    // bits 0..29  (R)   Reserved
                uint32_t DLY_IT_ENA     :1;     // bit  30     (R/W) Delay interrupt enable
                                                //                   0x0 = Disable delay interrupt
                                                //                   0x1 = Enable delay interrupt
                uint32_t OVF_IT_ENA     :1;     // bit  31     (R/W) Overflow interrupt enable
                                                //                   0x0 = Disable overflow interrupt
                                                //                   0x1 = Enable overflow interrupt
            } b;
            uint32_t reg;
        } WDT_WIER_reg_t;
        
        /*  (offset = 0x24) [reset = 0x00000020] */
        typedef union
        {                                       /* WDT_WCLR - Watchdog Control Register
                                                 */
            struct
            {
                uint32_t                :6;     // bits 0..5   (R)   Reserved
                uint32_t PRE            :1;     // bit  6      (R/W) Prescaler enable
                                                //                   0x0 = Prescaler disabled
                                                //                   0x1 = Prescaler enabled
                uint32_t PTV            :3;     // bits 7..9   (R/W) Prescaler value
                                                //                   Timer counter is prescaled with the value: 2^PTV
                                                //                   Example: PTV = 3 then counter increases after 8 clock periods
                uint32_t                :22;    // bits 10..31 (R)   Reserved
            } b;
            uint32_t reg;
        } WDT_WCLR_reg_t;
        
        /*  (offset = 0x28) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WCRR - Watchdog Counter Register
                                                 */
            struct
            {
                uint32_t TIMER_COUNTER  :32;    // bits 0..31  (R/W) Value of the timer counter register
                                                //                   Holds the current value of the internal counter
            } b;
            uint32_t reg;
        } WDT_WCRR_reg_t;
        
        /*  (offset = 0x2C) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WLDR - Watchdog Load Register
                                                 */
            struct
            {
                uint32_t TIMER_LOAD     :32;    // bits 0..31  (R/W) Value of the timer load register
                                                //                   Holds the reload value for the watchdog timer
            } b;
            uint32_t reg;
        } WDT_WLDR_reg_t;
        
        /*  (offset = 0x30) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WTGR - Watchdog Trigger Register
                                                 */
            struct
            {
                uint32_t TTGR_VALUE     :32;    // bits 0..31  (R/W) Value of the trigger register
                                                //                   Writing a different value reloads the watchdog counter
            } b;
            uint32_t reg;
        } WDT_WTGR_reg_t;
        
        /*  (offset = 0x34) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WWPS - Watchdog Write Posting Bits Register
                                                   */
            struct
            {
                uint32_t                :6;     // bits 0..5   (R)  Reserved
                uint32_t W_PEND_WDLY    :1;     // bit  6      (R)  Write pending for WDLY register
                                                //                  0x0 = No register write pending
                                                //                  0x1 = Register write pending
                uint32_t W_PEND_WSPR    :1;     // bit  7      (R)  Write pending for WSPR register
                                                //                  0x0 = No register write pending
                                                //                  0x1 = Register write pending
                uint32_t W_PEND_WTGR    :1;     // bit  8      (R)  Write pending for WTGR register
                                                //                  0x0 = No register write pending
                                                //                  0x1 = Register write pending
                uint32_t W_PEND_WLDR    :1;     // bit  9      (R)  Write pending for WLDR register
                                                //                  0x0 = No register write pending
                                                //                  0x1 = Register write pending
                uint32_t W_PEND_WCRR    :1;     // bit  10     (R)  Write pending for WCRR register
                                                //                  0x0 = No register write pending
                                                //                  0x1 = Register write pending
                uint32_t W_PEND_WCLR    :1;     // bit  11     (R)  Write pending for WCLR register
                                                //                  0x0 = No register write pending
                                                //                  0x1 = Register write pending
                uint32_t                :20;    // bits 12..31 (R)  Reserved
            } b;
            uint32_t reg;
        } WDT_WWPS_reg_t;
        
        /*  (offset = 0x44) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WDLY - Watchdog Delay Configuration Register
                                                 */
            struct
            {
                uint32_t WDLY_VALUE     :32;    // bits 0..31  (R/W) Value of the delay register
                                                //                   Controls internal pre-overflow event detection
            } b;
            uint32_t reg;
        } WDT_WDLY_reg_t;
        
        /*  (offset = 0x48) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WSPR - Watchdog Start/Stop Register
                                                 */
            struct
            {
                uint32_t WSPR_VALUE     :32;    // bits 0..31  (R/W) Value of the start-stop register
                                                //                   Controls the internal start-stop finite state machine
            } b;
            uint32_t reg;
        } WDT_WSPR_reg_t;
        
        /*  (offset = 0x54) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WIROSTATRAW - Watchdog Raw Interrupt Status Register
                                                 */
            struct
            {
                uint32_t                :30;    // bits 0..29  (R)  Reserved
                uint32_t EVENT_DLY      :1;     // bit  30     (R/W1S) Settable raw status for delay event
                                                //                     0x0 (W) = No action
                                                //                     0x0 (R) = No event pending
                                                //                     0x1 (W) = Set event (debug)
                                                //                     0x1 (R) = Event pending
                uint32_t EVENT_OVF      :1;     // bit  31     (R/W1S) Settable raw status for overflow event
                                                //                     0x0 (W) = No action
                                                //                     0x0 (R) = No event pending
                                                //                     0x1 (W) = Set event (debug)
                                                //                     0x1 (R) = Event pending
            } b;
            uint32_t reg;
        } WDT_WIROSTATRAW_reg_t;
        
        /*  (offset = 0x58) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WIROSTAT - Watchdog Interrupt Status Register
                                                 */
            struct
            {
                uint32_t                :30;    // bits 0..29  (R)  Reserved
                uint32_t EVENT_DLY      :1;     // bit  30     (R/W1C) Clearable status for delay event
                                                //                     0x0 (W) = No action
                                                //                     0x0 (R) = No (enabled) event pending
                                                //                     0x1 (W) = Clear (raw) event
                                                //                     0x1 (R) = Event pending
                uint32_t EVENT_OVF      :1;     // bit  31     (R/W1C) Clearable status for overflow event
                                                //                     0x0 (W) = No action
                                                //                     0x0 (R) = No (enabled) event pending
                                                //                     0x1 (W) = Clear (raw) event
                                                //                     0x1 (R) = Event pending
            } b;
            uint32_t reg;
        } WDT_WIROSTAT_reg_t;
        
        /*  (offset = 0x5C) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WIROENSET - Watchdog Interrupt Enable Set Register
                                                 */
            struct
            {
                uint32_t                :30;    // bits 0..29  (R)     Reserved
                uint32_t ENABLE_DLY     :1;     // bit  30     (R/W1S) Enable for delay event
                                                //                     0x0 (W) = No action
                                                //                     0x0 (R) = Interrupt disabled (masked)
                                                //                     0x1 (W) = Enable interrupt
                                                //                     0x1 (R) = Interrupt enabled
                uint32_t ENABLE_OVF     :1;     // bit  31     (R/W1S) Enable for overflow event
                                                //                     0x0 (W) = No action
                                                //                     0x0 (R) = Interrupt disabled (masked)
                                                //                     0x1 (W) = Enable interrupt
                                                //                     0x1 (R) = Interrupt enabled
            } b;
            uint32_t reg;
        } WDT_WIROENSET_reg_t;
        
        /*  (offset = 0x60) [reset = 0x00000000] */
        typedef union
        {                                       /* WDT_WIROENCLR - Watchdog Interrupt Enable Clear Register
                                                 */
            struct
            {
                uint32_t                :30;    // bits 0..29  (R)    Reserved
                uint32_t ENABLE_DLY     :1;     // bit  30     (R/W1C) Disable for delay event
                                                //                     0x0 (W) = No action
                                                //                     0x0 (R) = Interrupt disabled (masked)
                                                //                     0x1 (W) = Disable interrupt
                                                //                     0x1 (R) = Interrupt enabled
                uint32_t ENABLE_OVF     :1;     // bit  31     (R/W1C) Disable for overflow event
                                                //                     0x0 (W) = No action
                                                //                     0x0 (R) = Interrupt disabled (masked)
                                                //                     0x1 (W) = Disable interrupt
                                                //                     0x1 (R) = Interrupt enabled
            } b;
            uint32_t reg;
        } WDT_WIROENCLR_reg_t;

        struct AM335x_WATCHDOG_Type
        {
            __  WIDR_reg_t         WIDR;                // (0x00) Watchdog Identification Register
            __R  uint32_t          RESERVED1[3];    
            __  WDSC_reg_t         WDSC;                // (0x10) Watchdog System Control Register
            __  WDST_reg_t         WDST;                // (0x14) Watchdog Status Register
            __  WISR_reg_t         WISR;                // (0x18) Watchdog Interrupt Status Register
            __  WIER_reg_t         WIER;                // (0x1C) Watchdog Interrupt Enable Register
            __R  uint32_t          RESERVED2[1];   
            __  WCLR_reg_t         WCLR;                // (0x24) Watchdog Control Register
            __  WCRR_reg_t         WCRR;                // (0x28) Watchdog Counter Register
            __  WLDR_reg_t         WLDR;                // (0x2C) Watchdog Load Register
            __  WTGR_reg_t         WTGR;                // (0x30) Watchdog Trigger Register
            __  WWPS_reg_t         WWPS;                // (0x34) Watchdog Write Posting Bits Register
            __R  uint32_t          RESERVED3[3];   
            __  WDLY_reg_t         WDLY;                // (0x44) Watchdog Delay Configuration Register
            __  WSPR_reg_t         WSPR;                // (0x48) Watchdog Start/Stop Register
            __R  uint32_t          RESERVED4[2];   
            __  WIROSTATRAW_reg_t  WIROSTATRAW;         // (0x54) Watchdog Raw Interrupt Status Register
            __  WIROSTAT_reg_t     WIROSTAT;            // (0x58) Watchdog Interrupt Status Register
            __  WIROENSET_reg_t    WIROENSET;           // (0x5C) Watchdog Interrupt Enable Set Register
            __  WIROENCLR_reg_t    WIROENCLR;           // (0x60) Watchdog Interrupt Enable Clear Register
        };

    }   //namespace WDT

}   //namespace REGS

#endif //__WDT_HPP