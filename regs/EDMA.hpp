#ifndef __EDMA_H
#define __EDMA_H

#include <stdint.h>
#include "utils.h"

namespace REGS
{
    namespace EDMA
    {  
        /*********************************************************************************************************************************/  
        
        /*************************************************** AM335x_EDMA3CC_Type Registers ***********************************************/ 
        
        /*********************************************************************************************************************************/
        /*  @brief      Peripheral Identification Register  
         *  @details    Contains the peripheral identification value for the EDMA3 Channel Controller.
         *              This register provides a unique identifier for the EDMA3 CC module.
        (offset = 0x000) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {                                      
                uint32_t PID    :16;         // bits 0..15   (R) Peripheral identifier uniquely identifies the EDMA3CC and the
                                             //                  specific revision of the EDMA3CC.
                                             //                  Value 0 to 0xFFFFFFFF.Reset value is 0x4C00.
                uint32_t        :16;         // bits 16..31  (R) Reserved. Reset value is 0x4001.        
            } b;                             // bit access  
            uint32_t  reg;                   // raw register  
        } PIDCC_reg_t;
            
        /*  @brief      EDMA3CC Configuration Register  
         *  @details    Provides configuration information about the EDMA3 Channel Controller.
         *              This register reports the hardware configuration of the EDMA3CC instance.
        (offset = 0x004) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {                                      
                uint32_t    NUM_DMACH   :3;         // bits 0..2    (R) Number of DMA channels
                                                    //                  [0x0 = Reserved from 0 to 4;
                                                    //                   0x5 = 64 DMA channels;
                                                    //                   all other = Reserved]
                uint32_t                :1;         // bit 3        (R) Reserved 
                uint32_t    NUM_QDMACH  :3;         // bits 4..6    (R) Number of QDMA channels
                                                    //                  [0x0 = Reserved from 0 to 3;
                                                    //                   0x4 = 8 QDMA channels;
                                                    //                   0x5 = Reserved from 5 to 7;
                                                    //                   all other = Reserved]
                uint32_t                :1;         // bit 7        (R) Reserved 
                uint32_t    NUM_INTCH   :3;         // bits 8..10   (R) Number of interrupt channels
                                                    //                  [0x0 = Reserved from 0 to 3;
                                                    //                   0x4 = 64 interrupt channels;
                                                    //                   0x5 = Reserved from 5 to 7;
                                                    //                   all other = Reserved]
                uint32_t                :1;         // bit 11       (R) Reserved 
                uint32_t    NUM_PAENTRY :3;         // bits 12..14  (R) Number of parameter entries
                                                    //                  [0x0 = Reserved from 0 to 3;
                                                    //                   0x4 = 256 PaRAM sets;
                                                    //                   0x5 = Reserved from 5 to 7;
                                                    //                   all other = Reserved]
                uint32_t                :1;         // bit 15       (R) Reserved 
                uint32_t    NUM_EVQUE   :3;         // bits 16..18  (R) Number of event queues
                                                    //                  [0x5 = 3 EDMA3TCs/Event Queues.
                                                    //                   0x7 = Reserved from 3 to 7;
                                                    //                   all other = Reserved]
                uint32_t                :1;         // bit 19       (R) Reserved 
                uint32_t    NUM_REGN    :2;         // bits 20,21   (R) Number of regions
                                                    //                  [0x2 = 4 regions;
                                                    //                   all other = Reserved]
                uint32_t                :2;         // bits 22,23   (R) Reserved 
                uint32_t    CHMAP_EXIST :1;         // bit 24       (R) Channel map existence
                                                    //                  Indicates if channel mapping registers are implemented.
                                                    //                  [ 0x0 = Reserved;
                                                    //                    0x1 = Channel mapping registers implemented ]
                uint32_t    MP_EXIST    :1;         // bit 25       (R) Memory protection existence
                                                    //                  Indicates if memory protection is implemented.
                                                    //                  [ 0x0 = Reserved;
                                                    //                    0x1 = Memory protection implemented ]
                uint32_t                :6;         // bits 26..31   (R) Reserved.         
            } b;                                    // bit access  
            uint32_t  reg;                          // raw register  
        } CCCFG_reg_t;
            
        /*  @brief      EDMA3CC System Configuration Register  
         *  @details    Controls system-level configuration options for the EDMA3 Channel Controller.
         *              This register configures idle modes and other system-level settings.
        (offset = 0x010) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {                                      
                uint32_t                  :2;         // bits 0,1   (R) Reserved.
                uint32_t    IDLEMODE      :2;         // bits 2,3   (RW) Idle mode configuration [ see e_IDLEMODE]
                uint32_t                  :28;        // bits 4..31 (R) Reserved.         
            } b;                                      // bit access  
            uint32_t  reg;                            // raw register  
        } SYSCONFIGCC_reg_t;
        
        enum e_IDLEMODE : uint32_t
        {
            FORCE_IDLE       = 0x0,     // local target's idle state follows (acknowledges)
                                        // the system's idle requests unconditionally, i.e. regardless of the IP
                                        // module's internal requirements. Backup mode, for debug only.
            NO_IDLE          = 0x1,     // local target never enters idle state. Backup
                                        // mode, for debug only
            SMART_IDLE       = 0x2,     // local target's idle state eventually follows
                                        // (acknowledges) the system's idle requests, depending on the IP
                                        // module's internal requirements. IP module shall not generate (IRQor
                                        // DMA-request-related) wakeup events.
            SMART_IDLE_WKUP  = 0x3      // local target's idle state
                                        // eventually follows (acknowledges) the system's idle requests,
                                        // depending on the IP module's internal requirements. IP module may
                                        // generate (IRQ- or DMA-request-related) wakeup events when in idle
                                        // state. Mode is only relevant if the appropriate IP module "swakeup"
                                        // output(s) is (are) implemented.
        };
            
        /*  @brief      DMA Channel Mapping Register 0..63  
         *  @details    Maps DMA channels to specific PaRAM entries.
         *              This register associates DMA channels with parameter RAM sets.
        (offset = 0x100..0x1FC) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {                                      
                uint32_t              :5;         // bits 0..4      (R) Reserved.
                uint32_t    PAENTRY   :9;         // bits 5..13     (RW) Parameter entry number
                                                  //                     Specifies the PaRAM set number for the DMA channel.
                                                  //                     [0x0 = Parameter entry 0;
                                                  //                      0x1 = Parameter entry 1;
                                                  //                      ...
                                                  //                      0xFF = Parameter entry 511]
                uint32_t              :18;        // bits 14..31    (R) Reserved.         
            } b;                                  // bit access  
            uint32_t  reg;                        // raw register  
        } DCHMAP_reg_t;
            
        /*  @brief      QDMA Channel Mapping Register 0..7  
         *  @details    Each QDMA channel in EDMA3CC can be associated with any PaRAM set available on the device.
         *              Furthermore, the specific trigger word (0-7) of the PaRAM set can be programmed. The PaRAM set
         *              association and trigger word for every QDMA channel register is configurable using the QDMA channel
         *              map register (QCHMAPn). At reset the QDMA channel map registers for all QDMA channels point to
         *              PaRAM set 0. If an application makes use of both a DMA channel that points to PaRAM set 0 and any
         *              QDMA channels, ensure that QCHMAP is programmed appropriately to point to a different PaRAM entry.
        (offset = 0x200..0x21C) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t                  :2;         // bits 0,1     (R)  Reserved.
                uint32_t    TRWORD        :3;         // bits 2..4    (RW) Trigger word selection
                                                      //                   Selects the trigger word within the PaRAM set.
                                                      //                   [0x0 = Trigger word 0;
                                                      //                    0x1 = Trigger word 1;
                                                      //                    ...
                                                      //                    0x7 = Trigger word 7]
                uint32_t    PAENTRY       :9;         // bits 5..13   (RW) Parameter entry number
                                                      //                   [0x0 = Parameter entry 0 through 255, from 0 to FFh.
                                                      //                    0x1 = Reserved, from 100h to 1FFh. Always write 0 to this bit. Writes
                                                      //                    of 1 to this bit are not supported and attempts to do so may result in
                                                      //                    undefine behavior.]
                uint32_t                  :18;        // bits 14..31  (R)  Reserved.         
            } b;                                      // bit access  
            uint32_t  reg;                            // raw register  
        } QCHMAP_reg_t;
            
        /*  @brief      DMA Queue Number Register 0..7  
         *  @details    The DMA channel queue number register (DMAQNUMn) allows programmability of each of the 64 DMA
         *              channels in the EDMA3CC to submit its associated synchronization event to any event queue in the
         *              EDMA3CC. At reset, all channels point to event queue 0. Because the event queues in EDMA3CC have a
         *              fixed association to the transfer controllers, that is, Q0 TRs are submitted to TC0, Q1 TRs are submitted
         *              to TC1, etc., by programming DMAQNUM for a particular DMA channel also dictates which transfer
         *              controller is utilized for the data movement (or which EDMA3TC receives the TR request).
        (offset = 0x240..0x25C) [reset = 0x00000000] */ 
        typedef union 
        {                                       /* WARNING !!! Programming DMAQNUM for an event queue number to a value
                                                 * more then the number of queues available in the EDMA3CC results
                                                 * in undefined behavior!!! 
                                                 */
            struct 
            {    
                        uint32_t    E0  :3;     // bit: 0..2     (RW) . On DMAQNUM[0], E[2] to E[0] is E0.
                                                //                      On DMAQNUM[1], E[2] to E[0] is E8.
                                                //                      On DMAQNUM[2], E[2] to E[0] is E16.
                                                //                      On DMAQNUM[3], E[2] to E[0] is E24.
                                                //                      On DMAQNUM[4], E[2] to E[0] is E32.
                                                //                      On DMAQNUM[5], E[2] to E[0] is E40.
                                                //                      On DMAQNUM[6], E[2] to E[0] is E48.
                                                //                      On DMAQNUM[7], E[2] to E[0] is E56.  [see e_EVENT_QUEUE]
                        uint32_t        :1;     // bit: 3        (R) Reserved.
                        uint32_t    E1  :3;     // bit: 4..6     (RW) . On DMAQNUM[0], E[6] to E[4] is E1.
                                                //                      On DMAQNUM[1], E[6] to E[4] is E9.
                                                //                      On DMAQNUM[2], E[6] to E[4] is E17.
                                                //                      On DMAQNUM[3], E[6] to E[4] is E25.
                                                //                      On DMAQNUM[4], E[6] to E[4] is E33.
                                                //                      On DMAQNUM[5], E[6] to E[4] is E41.
                                                //                      On DMAQNUM[6], E[6] to E[4] is E49.
                                                //                      On DMAQNUM[7], E[6] to E[4] is E57.  [see e_EVENT_QUEUE]
                        uint32_t        :1;     // bit: 7        Reserved                        
                        uint32_t    E2  :3;     // bit: 8..10    (RW) . On DMAQNUM[0], E[10] to E[8] is E2.
                                                //                      On DMAQNUM[1], E[10] to E[8] is E10.
                                                //                      On DMAQNUM[2], E[10] to E[8] is E18.
                                                //                      On DMAQNUM[3], E[10] to E[8] is E26.
                                                //                      On DMAQNUM[4], E[10] to E[8] is E34.
                                                //                      On DMAQNUM[5], E[10] to E[8] is E42.
                                                //                      On DMAQNUM[6], E[10] to E[8] is E50.
                                                //                      On DMAQNUM[7], E[10] to E[8] is E58.  [see e_EVENT_QUEUE]
                        uint32_t        :1;     // bit: 11       (R) Reserved.
                        uint32_t    E3  :3;     // bit: 12..14   (RW) . On DMAQNUM[0], E[14] to E[12] is E3.
                                                //                      On DMAQNUM[1], E[14] to E[12] is E11.
                                                //                      On DMAQNUM[2], E[14] to E[12] is E19.
                                                //                      On DMAQNUM[3], E[14] to E[12] is E27.
                                                //                      On DMAQNUM[4], E[14] to E[12] is E35.
                                                //                      On DMAQNUM[5], E[14] to E[12] is E43.
                                                //                      On DMAQNUM[6], E[14] to E[12] is E51.
                                                //                      On DMAQNUM[7], E[14] to E[12] is E59.  [see e_EVENT_QUEUE]
                        uint32_t        :1;     // bit: 15       (R) Reserved.
                        uint32_t    E4  :3;     // bit: 16..18   (RW) . On DMAQNUM[0], E[18] to E[16] is E4.
                                                //                      On DMAQNUM[1], E[18] to E[16] is E12.
                                                //                      On DMAQNUM[2], E[18] to E[16] is E20.
                                                //                      On DMAQNUM[3], E[18] to E[16] is E28.
                                                //                      On DMAQNUM[4], E[18] to E[16] is E36.
                                                //                      On DMAQNUM[5], E[18] to E[16] is E44.
                                                //                      On DMAQNUM[6], E[18] to E[16] is E52.
                                                //                      On DMAQNUM[7], E[18] to E[16] is E60.  [see e_EVENT_QUEUE]
                        uint32_t        :1;     // bit: 19       (R) Reserved.
                        uint32_t    E5  :3;     // bit: 20..21   (RW) . On DMAQNUM[0], E[22] to E[20] is E5.
                                                //                      On DMAQNUM[1], E[22] to E[20] is E13.
                                                //                      On DMAQNUM[2], E[22] to E[20] is E21.
                                                //                      On DMAQNUM[3], E[22] to E[20] is E29.
                                                //                      On DMAQNUM[4], E[22] to E[20] is E37.
                                                //                      On DMAQNUM[5], E[22] to E[20] is E45.
                                                //                      On DMAQNUM[6], E[22] to E[20] is E53.
                                                //                      On DMAQNUM[7], E[22] to E[20] is E61.  [see e_EVENT_QUEUE]
                        uint32_t        :1;     // bit: 23       (R) Reserved.
                        uint32_t    E6  :3;     // bit: 24..26   (RW) . On DMAQNUM[0], E[26] to E[24] is E6.
                                                //                      On DMAQNUM[1], E[26] to E[24] is E14.
                                                //                      On DMAQNUM[2], E[26] to E[24] is E22.
                                                //                      On DMAQNUM[3], E[26] to E[24] is E30.
                                                //                      On DMAQNUM[4], E[26] to E[24] is E38.
                                                //                      On DMAQNUM[5], E[26] to E[24] is E46.
                                                //                      On DMAQNUM[6], E[26] to E[24] is E54.
                                                //                      On DMAQNUM[7], E[26] to E[24] is E62.  [see e_EVENT_QUEUE]
                        uint32_t        :1;     // bit: 27       (R) Reserved.
                        uint32_t    E7  :3;     // bit: 28..30   (RW) . On DMAQNUM[0], E[30] to E[28] is E7.
                                                //                      On DMAQNUM[1], E[30] to E[28] is E15.
                                                //                      On DMAQNUM[2], E[30] to E[28] is E23.
                                                //                      On DMAQNUM[3], E[30] to E[28] is E39.
                                                //                      On DMAQNUM[4], E[30] to E[28] is E47.
                                                //                      On DMAQNUM[5], E[30] to E[28] is E45.
                                                //                      On DMAQNUM[6], E[30] to E[28] is E55.
                                                //                      On DMAQNUM[7], E[30] to E[28] is E63.  [see e_EVENT_QUEUE]       
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } DMAQNUM_reg_t;
            
        enum e_EVENT_QUEUE : uint32_t
        {
            /*  Selects the event queue for DMA channel events.
             *  Each queue has a fixed association with transfer controllers.
             */
            EVENT_Q0 = 0x00,    // Event is queued on Q0 (associated with TC0)
            EVENT_Q1 = 0x01,    // Event is queued on Q1 (associated with TC1)
            EVENT_Q2 = 0x02,    // Event is queued on Q2 (associated with TC2)
                                // Values 0x03-0x07 are reserved. Always write 0 to this bit; writes of 1 to this bit are
                                // not supported and attempts to do so may result in undefined
                                // behavior.
        };
        
        /*  @brief      QDMA Queue Number Register  
         *  @details    The QDMA channel queue number register (QDMAQNUMn) is used to program all the QDMA channels in
         *              the EDMA3CC to submit the associated QDMA event to any of the event queues in the EDMA3CC.
        (offset = 0x260) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    E0  :3;    // bits 0..2     (RW) Event queue number for QDMA channel 0 [see e_EVENT_QUEUE]
                uint32_t        :1;    // bit 3         (R)  Reserved.
                uint32_t    E1  :3;    // bits 4..6     (RW) Event queue number for QDMA channel 1 [see e_EVENT_QUEUE]
                uint32_t        :1;    // bit 7         (R)  Reserved.
                uint32_t    E2  :3;    // bits 8..10    (RW) Event queue number for QDMA channel 2 [see e_EVENT_QUEUE]
                uint32_t        :1;    // bit 11        (R)  Reserved.
                uint32_t    E3  :3;    // bits 12..14   (RW) Event queue number for QDMA channel 3 [see e_EVENT_QUEUE]
                uint32_t        :1;    // bit 15        (R)  Reserved.
                uint32_t    E4  :3;    // bits 16..18   (RW) Event queue number for QDMA channel 4 [see e_EVENT_QUEUE]
                uint32_t        :1;    // bit 19        (R)  Reserved.
                uint32_t    E5  :3;    // bits 20..22   (RW) Event queue number for QDMA channel 5 [see e_EVENT_QUEUE]
                uint32_t        :1;    // bit 23        (R)  Reserved.
                uint32_t    E6  :3;    // bits 24..26   (RW) Event queue number for QDMA channel 6 [see e_EVENT_QUEUE]
                uint32_t        :1;    // bit 27        (R)  Reserved.
                uint32_t    E7  :3;    // bits 28..30   (RW) Event queue number for QDMA channel 7 [see e_EVENT_QUEUE]
                uint32_t        :1;    // bit 31        (R)  Reserved.           
            } b;                       // bit access  
            uint32_t  reg;             // raw register  
        } QDMAQNUM_reg_t;
            
        /*  @brief      Queue Priority Register  
         *  @details    The queue priority register (QUEPRI) allows you to change the priority of the individual queues and the
         *              priority of the transfer request (TR) associated with the events queued in the queue. Because the queue to
         *              EDMA3TC mapping is fixed, programming QUEPRI essentially governs the priority of the associated
         *              transfer controller(s) read/write commands with respect to the other bus masters in the device. You can
         *              modify the EDMA3TC priority to obtain the desired system performance.
        (offset = 0x284) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    PRIQ0      :3;        // bits 0..2    (RW) Priority for queue 0
                                                  //                   Dictates the priority level used by TC0 relative to other 
                                                  //                   masters in the device.
                                                  //                   [0x0 = Lowest priority;
                                                  //                    ...
                                                  //                    0x7 = Highest priority]
                uint32_t               :1;        // bit 3        (R)  Reserved.
                uint32_t    PRIQ1      :3;        // bits 4..6    (RW) Priority for queue 1
                                                  //                   Dictates the priority level used by TC1 relative to other 
                                                  //                   masters in the device.
                                                  //                   [0x0 = Lowest priority;
                                                  //                    ...
                                                  //                    0x7 = Highest priority]
                uint32_t               :1;        // bit 7        (R)  Reserved.    
                uint32_t    PRIQ2      :3;        // bits 8..10   (RW) Priority for queue 2
                                                  //                   Dictates the priority level used by TC2 relative to other 
                                                  //                   masters in the device.
                                                  //                   [0x0 = Lowest priority;
                                                  //                    ...
                                                  //                    0x7 = Highest priority]
                uint32_t               :21;       // bits 11..31  (R)  Reserved.
            } b;                                  // bit access  
            uint32_t  reg;                        // raw register  
        } QUEPRI_reg_t;
    
        /*  @brief      Event Missed Register  
         *  @details    For a particular DMA channel, if a second event is received prior to the first event getting cleared/serviced,
         *              the bit corresponding to that channel is set/asserted in the event missed registers (EMR/EMRH). All
         *              trigger types are treated individually, that is, manual triggered (ESR/ESRH), chain triggered (CER/CERH),
         *              and event triggered (ER/ERH) are all treated separately. The EMR/EMRH bits for a channel are also set if
         *              an event on that channel encounters a NULL entry (or a NULL TR is serviced). If any EMR/EMRH bit is
         *              set (and all errors, including bits in other error registers (QEMR, CCERR) were previously cleared), the
         *              EDMA3CC generates an error interrupt. For details on EDMA3CC error interrupt generation, see Error
         *              Interrupts. This register is part of a set of registers that provide information on missed DMA and/or QDMA
         *              events, and instances when event queue thresholds are exceeded. If any of the bits in these registers is
         *              set, it results in the EDMA3CC generating an error interrupt.
        (offset = 0x300) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :32;        // bits 0..31        (R) Channel 0 to 31 event missed.
                                                //                       Each bit indicates if an event was missed for the corresponding channel.
                                                //                       [0x0 = Event not missed;
                                                //                        0x1 = Event missed]
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } EMR_reg_t;
            
        /*  @brief      Event Missed Register High  
         *  @details    For a particular DMA channel, if a second event is received prior to the first event getting cleared/serviced,
         *              the bit corresponding to that channel is set/asserted in the event missed registers (EMR/EMRH). All
         *              trigger types are treated individually, that is, manual triggered (ESR/ESRH), chain triggered (CER/CERH),
         *              and event triggered (ER/ERH) are all treated separately. The EMR/EMRH bits for a channel are also set if
         *              an event on that channel encounters a NULL entry (or a NULL TR is serviced). If any EMR/EMRH bit is
         *              set (and all errors, including bits in other error registers (QEMR, CCERR) were previously cleared), the
         *              EDMA3CC generates an error interrupt. For details on EDMA3CC error interrupt generation, see Error
         *              Interrupts. This register is part of a set of registers that provide information on missed DMA and/or QDMA
         *              events, and instances when event queue thresholds are exceeded. If any of the bits in these registers is
         *              set, it results in the EDMA3CC generating an error interrupt.
        (offset = 0x304) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {  
                uint32_t    En      :32;        // bits 0..31      (R) Channel 32 to 63 event missed.
                                                //                     Each bit indicates if an event was missed for the corresponding channel.
                                                //                     [0x0 = Event not missed;
                                                //                      0x1 = Event missed]       
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } EMRH_reg_t;
            
        /*  @brief      Event Missed Clear Register  
         *  @details    Once a missed event is posted in the event missed registers (EMR/EMRH), the bit remains set and you
         *              need to clear the set bit(s). This is done by way of CPU writes to the event missed clear registers
         *              (EMCR/EMCRH). Writing a 1 to any of the bits clears the corresponding missed event (bit) in EMR/EMRH;
         *              writing a 0 has no effect. This register is part of a set of registers that provide information on missed DMA
         *              and/or QDMA events, and instances when event queue thresholds are exceeded. If any of the bits in
         *              these registers is set, it results in the EDMA3CC generating an error interrupt.
        (offset = 0x308) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :32;        // bits 0..31    (W) Event missed 0 to 31 clear.
                                                //                   All error bits must be cleared before additional error interrupts will be
                                                //                   asserted by the EDMA3CC.
                                                //                   Writing 1 clears the corresponding bit in EMR.          
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } EMCR_reg_t;
            
        /*  @brief      Event Missed Clear Register High  
         *  @details    Once a missed event is posted in the event missed registers (EMR/EMRH), the bit remains set and you
         *              need to clear the set bit(s). This is done by way of CPU writes to the event missed clear registers
         *              (EMCR/EMCRH). Writing a 1 to any of the bits clears the corresponding missed event (bit) in EMR/EMRH;
         *              writing a 0 has no effect. This register is part of a set of registers that provide information on missed DMA
         *              and/or QDMA events, and instances when event queue thresholds are exceeded. If any of the bits in
         *              these registers is set, it results in the EDMA3CC generating an error interrupt.
        (offset = 0x30C) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :32;        // bits 0..31        (W) Event missed 32 to 63 clear.
                                                //                       All error bits must be cleared before additional error interrupts will be
                                                //                       asserted by the EDMA3CC.
                                                //                       Writing 1 clears the corresponding bit in EMRH. 
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } EMCRH_reg_t;
            
        /*  @brief      QDMA Event Missed Register  
         *  @details    For a particular QDMA channel, if two QDMA events are detected without the first event getting
         *              cleared/serviced, the bit corresponding to that channel is set/asserted in the QDMA event missed register
         *              (QEMR). The QEMR bits for a channel are also set if a QDMA event on the channel encounters a NULL
         *              entry (or a NULL TR is serviced). If any QEMR bit is set (and all errors, including bits in other error
         *              registers (EMR/EMRH, CCERR) were previously cleared), the EDMA3CC generates an error interrupt. For
         *              details on EDMA3CC error interrupt generation, see Error Interrupts. This register is part of a set of
         *              registers that provide information on missed DMA and/or QDMA events, and instances when event queue
         *              thresholds are exceeded. If any of the bits in these registers is set, it results in the EDMA3CC generating
         *              an error interrupt.
        (offset = 0x310) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :8;         // bits 0..7        (R) Channel 0 to 7 QDMA event missed.
                                                //                      Each bit indicates if a QDMA event was missed.
                                                //                      [0x0 = Event not missed;
                                                //                       0x1 = Event missed]
                uint32_t            :24;        // bits 8..31       (R) Reserved.          
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } QEMR_reg_t;
            
        /*  @brief      QDMA Event Missed Clear Register  
         *  @details    Once a missed event is posted in the QDMA event missed registers (QEMR), the bit remains set and you
         *              need to clear the set bit(s). This is done by way of CPU writes to the QDMA event missed clear registers
         *              (QEMCR). Writing a 1 to any of the bits clears the corresponding missed event (bit) in QEMR; writing a 0
         *              has no effect. This register is part of a set of registers that provide information on missed DMA and/or
         *              QDMA events, and instances when event queue thresholds are exceeded. If any of the bits in these
         *              registers is set, it results in the EDMA3CC generating an error interrupt.
        (offset = 0x314) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :8;         // bits 0..7        (W) QDMA event missed clear
                                                //                      All error bits must be cleared before additional error interrupts will be
                                                //                      asserted by the EDMA3CC.
                                                //                      Writing 1 clears the corresponding bit in QEMR.
                uint32_t            :24;        // bits 8..31       (R) Reserved.        
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } QEMCR_reg_t;
            
        /*  @brief      EDMA3CC Error Register  
         *  @details    The EDMA3CC error register (CCERR) indicates whether or not at any instant of time the number of
         *              events queued up in any of the event queues exceeds or equals the threshold/watermark value that is set
         *              in the queue watermark threshold register (QWMTHRA). Additionally, CCERR also indicates if when the
         *              number of outstanding TRs that have been programmed to return transfer completion code (TRs which
         *              have the TCINTEN or TCCHEN bit in OPT set) to the EDMA3CC has exceeded the maximum allowed
         *              value of 63. If any bit in CCERR is set (and all errors, including bits in other error registers (EMR/EMRH,
         *              QEMR) were previously cleared), the EDMA3CC generates an error interrupt. For details on EDMA3CC
         *              error interrupt generation, see Error Interrupts. Once the error bits are set in CCERR, they can only be
         *              cleared by writing to the corresponding bits in the EDMA3CC error clear register (CCERRCLR). This
         *              register is part of a set of registers that provide information on missed DMA and/or QDMA events, and
         *              instances when event queue thresholds are exceeded. If any of the bits in these registers is set, it results
         *              in the EDMA3CC generating an error interrupt.
        (offset = 0x318) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {     
                uint32_t    QTHRXCD0      :1;         // bit 0        (R) Queue 0 threshold exceeded error
                                                      //                  Indicates if queue 0 threshold was crossed.
                                                      //                  [0x0 = No error;
                                                      //                   0x1 = Error occurred]
                uint32_t    QTHRXCD1      :1;         // bit 1        (R) Queue 1 threshold exceeded error
                                                      //                  Indicates if queue 1 threshold was crossed.
                                                      //                  [0x0 = No error;
                                                      //                   0x1 = Error occurred]
                uint32_t    QTHRXCD2      :1;         // bit 2        (R) Queue 2 threshold exceeded error
                                                      //                  Indicates if queue 2 threshold was crossed.
                                                      //                  [0x0 = No error;
                                                      //                   0x1 = Error occurred]
                uint32_t                  :13;        // bits 3..15   (R) Reserved 
                uint32_t    TCCERR        :1;         // bit 16       (R) Transfer completion code error
                                                      //                  Indicates an invalid transfer completion code.
                                                      //                  [0x0 = No error;
                                                      //                   0x1 = Error occurred]  
                uint32_t                  :15;        // bits 17..31  (R) Reserved.         
            } b;                                      // bit access  
            uint32_t  reg;                            // raw register  
        } CCERR_reg_t;
        
        enum e_CCERR_flags: uint32_t
        {       
            /*  Error flags for the Channel Controller Error Register.
             *  Each flag corresponds to a specific error condition.
             */
            F_QTHRXCD0 = BIT(0),  // Queue 0 threshold crossing error flag
            F_QTHRXCD1 = BIT(1),  // Queue 1 threshold crossing error flag
            F_QTHRXCD2 = BIT(2),  // Queue 2 threshold crossing error flag
            F_TCCERR   = BIT(16)  // Transfer completion code error flag
        };
            
        /*  @brief      EDMA3CC Error Clear Register  
         *  @details    The EDMA3CC error clear register (CCERRCLR) is used to clear any error bits that are set in the
         *              EDMA3CC error register (CCERR). In addition, CCERRCLR also clears the values of some bit fields in
         *              the queue status registers (QSTATn) associated with a particular event queue. Writing a 1 to any of the
         *              bits clears the corresponding bit in CCERR; writing a 0 has no effect. This register is part of a set of
         *              registers that provide information on missed DMA and/or QDMA events, and instances when event queue
         *              thresholds are exceeded. If any of the bits in these registers is set, it results in the EDMA3CC generating
         *              an error interrupt.
        (offset = 0x31C) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {     
                uint32_t    QTHRXCD0      :1;         // bit 0        (W) Queue 0 threshold exceeded error clear
                                                      //                  Writing 1 clears the QTHRXCD0 bit in CCERR.
                uint32_t    QTHRXCD1      :1;         // bit 1        (W) Queue 1 threshold exceeded error clear
                                                      //                  Writing 1 clears the QTHRXCD1 bit in CCERR.
                uint32_t    QTHRXCD2      :1;         // bit 2        (W) Queue 2 threshold exceeded error clear
                                                      //                  Writing 1 clears the QTHRXCD2 bit in CCERR.
                uint32_t                  :13;        // bits 3..15   (R) Reserved. 
                uint32_t    TCCERR        :1;         // bit 16       (W) Transfer completion code error clear
                                                      //                  Writing 1 clears the TCCERR bit in CCERR.  
                uint32_t                  :15;        // bits 17..31  (R) Reserved.         
            } b;                                      // bit access  
            uint32_t  reg;                            // raw register  
        } CCERRCLR_reg_t;
 
        /*  @brief      Error Evaluate Register  
         *  @details    The EDMA3CC error interrupt is asserted whenever an error bit is set in any of the error registers
         *              (EMR/EMRH, QEMR, and CCERR). For subsequent error bits that get set, the EDMA3CC error interrupt
         *              is reasserted only when transitioning from an all the error bits cleared to at least one error bit is set .
         *              Alternatively, a CPU write of 1 to the EVAL bit in the error evaluation register (EEVAL) results in
         *              reasserting the EDMA3CC error interrupt, if there are any outstanding error bits set due to subsequent
         *              error conditions. Writes of 0 have no effect. This register is part of a set of registers that provide
         *              information on missed DMA and/or QDMA events, and instances when event queue thresholds are
         *              exceeded. If any of the bits in these registers is set, it results in the EDMA3CC generating an error
         *              interrupt.
        (offset = 0x320) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {                                      
                uint32_t    EVAL      :1;         // bit 0       (W) Error interrupt evaluate.
                                                  //                 Writing 1 forces evaluation of pending events.
                                                  //                 [0x0 = No action;
                                                  //                  0x1 = Write 1 to clear interrupts when all error registers have been
                                                  //                  cleared. EDMA3CC error interrupt will remain if any errors have not
                                                  //                  been cleared in any of the error registers (EMR/EMRH, CCERR,
                                                  //                  QEMR)]
                uint32_t              :31;        // bits 1..31  (R) Reserved.         
            } b;                                  // bit access  
            uint32_t  reg;                        // raw register  
        } EEVAL_reg_t;
            
        /*  @brief      DMA Region Access Enable Register for Regions 0..7  
         *  @details    The DMA region access enable register for shadow regions 0..7 is programmed to allow or disallow read/write
         *              accesses on a bit-by-bit bases for all DMA registers in the shadow region 0 view of the DMA channel
         *              registers. Additionally, the DRAE configuration determines completion of which DMA channels will result
         *              in assertion of the shadow regions 0..7 DMA completion interrupt. The DRAE registers are part of the group of
         *              the region access enable registers, which includes DRAEm and QRAEm. Where m is the number of
         *              shadow regions in the EDMA3CC memory map for a device. You can configure these registers to assign
         *              ownership of DMA/QDMA channels to a particular shadow region.
        (offset = 0x340..0x378) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :32;         // bits 0..31       (RW) DMA region access enable for bit 31 to 0 in region 0..7.
                                                 //                       Each bit enables/disables access to a DMA region.
                                                 //                       [0x0 = Region access disabled;
                                                 //                        0x1 = Region access enabled]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } DRAE_reg_t;
            
        /*  @brief      DMA Region Access Enable Register High for regions 0..7  
         *  @details    The DMA region access enable register for shadow regions 0..7 is programmed to allow or disallow read/write
         *              accesses on a bit-by-bit bases for all DMA registers in the shadow regions 0..7 view of the DMA channel
         *              registers. Additionally, the DRAE configuration determines completion of which DMA channels will result
         *              in assertion of the shadow regions 0..7 DMA completion interrupt. The DRAE registers are part of the group of
         *              the region access enable registers, which includes DRAEm and QRAEm. Where m is the number of
         *              shadow regions in the EDMA3CC memory map for a device. You can configure these registers to assign
         *              ownership of DMA/QDMA channels to a particular shadow region.
        (offset = 0x344..0x37C) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {                
                uint32_t    En      :32;         // bits 0..31       (RW) DMA region access enable for bit 63 to 32 in region 0..7.
                                                 //                       Each bit enables/disables access to a DMA region.
                                                 //                       [0x0 = Region access disabled;
                                                 //                        0x1 = Region access enabled]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register   
        } DRAEH_reg_t;
           
        /*  @brief      QDMA Region Access Enable Registers for Region 0..7  
         *  @details    The QDMA region access enable register for shadow region m (QRAEm) is programmed to allow or
         *              disallow read/write accesses on a bit-by-bit bases for all QDMA registers in the shadow region m view of
         *              the QDMA registers. This includes all 4-bit QDMA registers. The QRAE register is part of the group of the
         *              region access enable registers, which includes DRAEm and QRAEm. Where m is the number of shadow
         *              regions in the EDMA3CC memory map for a device. You can configure these registers to assign
         *              ownership of DMA/QDMA channels to a particular shadow region.
        (offset = 0x380..0x39Ñ) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {     
                uint32_t    En      :8;         // bits 0..7       (RW) QDMA region access enable for bit n/QDMA channel n in region m.
                                                //                      Each bit enables/disables access to a QDMA region.
                                                //                      [0x0 = Region access disabled;
                                                //                       0x1 = Region access enabled]  
                uint32_t            :24;        // bits 8..31      (R)  Reserved.
            } b;                                // bit access  
            uint32_t  reg;                      // raw register 
        } QRAE_reg_t;
            
        /*  @brief      Event Queue 0..2 Entry 1..15 Register  
         *  @details    The event queue entry registers (QxEy) exist for all 16 queue entries (the maximum allowed queue
         *              entries) for all event queues in the EDMA3CC. The event queue entry registers range from Q0E0 to
         *              Q0E15, Q1E0 to Q1E15, and Q2E0 to Q2E15. Each register details the event number (ENUM) and the
         *              event type (ETYPE). For example, if the value in Q1E4 is read as 000 004Fh, this means the 4th entry in
         *              queue 1 is a manually-triggered event on DMA channel 15. The Q0E8 register provides visibility into the
         *              event queues and a TR life cycle. These are useful for system debug as they provide in-depth visibility for
         *              the events queued up in the event queue and also provide information on what parts of the EDMA3CC
         *              logic are active once the event has been received by the EDMA3CC.
        (offset = 0x400..0x4BC) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {     
                uint32_t    ENUM      :6;         // bits 0..5      (R) Events entry 0..16 in queues 0..3.
                                                  //                    Event number: QDMA channel number (0 to 3).
                                                  //                    DMA channel/event number (0 to 63).
                                                  //                    Identifies the exception condition.
                uint32_t    ETYPE     :2;         // bits 6,7       (R) Exception type [ see e_QUEUE_EX_TYPE]
                                                  //                    Classifies the exception condition.
                uint32_t              :24;        // bits 8..31     (R) Reserved.
            } b;                                  // bit access  
            uint32_t  reg;                        // raw register  
        } QE_reg_t;
        
        enum e_QUEUE_EX_TYPE: uint32_t
        {
            PERIPH_TRIG = 0x0,  // Event triggered via ER.
            MANUAL_TRIG = 0x1,  // Manual triggered via ESR.
            CHAIN_TRIG  = 0x2,  // Chain triggered via CER
            AUTO_TRIG   = 0x3   // Autotriggered via QER
        };
            
        /*  @brief      Queue Status Register 0..2 
         *  @details    The queue status register (QSTAT) provides visibility into the event queues and a TR life cycle. These are
         *              useful for system debug as they provide in-depth visibility for the events queued up in the event queue
         *              and also provide information on what parts of the EDMA3CC logic are active once the event has been
         *              received by the EDMA3CC.
        (offset = 0x600..0x608) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {     
                uint32_t    STRTPTR     :4;         // bits 0..3      (R) Start pointer.Indicates the start of the queue.
                                                    //                    Legal values are 0 (0th entry) to Fh (15th entry).
                uint32_t                :4;         // bits 4..7      (R) Reserved.
                uint32_t    NUMVAL      :5;         // bits 8..12     (R) Number of valid entries
                                                    //                    [0x0 = Legal values are 0 (empty) to 10h (full);
                                                    //                     0x1 = Reserved, from 11h to 1Fh. Always write 0 to this bit; writes of
                                                    //                     1 to this bit are not supported and attempts to do so may result in
                                                    //                     undefined behavior.]
                uint32_t                :3;         // bits 13..15    (R) Reserved.
                uint32_t    WM          :5;         // bits 16..20    (R) Watermark level.Indicates the watermark level of the queue.
                                                    //                    [0x0 = Legal values are 0 (empty) to 10h (full);
                                                    //                     0x1 = Reserved, from 11h to 1Fh. Always write 0 to this bit; writes of
                                                    //                     1 to this bit are not supported and attempts to do so may result in
                                                    //                     undefined behavior.]
                uint32_t                :3;         // bits 21..23    (R) Reserved.
                uint32_t    THRXCD      :1;         // bit 24         (R) Threshold crossed.Indicates if the queue threshold was crossed.
                                                    //                    [0x0 = Threshold specified by the Qn bit in the queue watermark
                                                    //                            threshold A register (QWMTHRA) has not been exceeded.;
                                                    //                     0x1 = Threshold specified by the Qn bit in the queue watermark
                                                    //                           threshold A register (QWMTHRA) has been exceeded.]
                uint32_t                :7;         // bits 25..31    (R) Reserved.
            } b;                                    // bit access  
            uint32_t  reg;                          // raw register   
        } QSTAT_reg_t;
            
        /*  @brief      Queue Watermark Threshold A Register  
         *  @details    The queue watermark threshold A register (QWMTHRA) provides visibility into the event queues and a TR
         *              life cycle. These are useful for system debug as they provide in-depth visibility for the events queued up in
         *              the event queue and also provide information on what parts of the EDMA3CC logic are active once the
         *              event has been received by the EDMA3CC.
        (offset = 0x620) [reset = 0x00000000] */ 
        typedef union 
        { 
                                                /* Queue threshold for queue 0..2 value.
                                                   The QTHRXCD bit in the EDMA3CC error register (CCERR) and
                                                   the THRXCD bit in the queue status register (QSTAT) are set
                                                   when the number of events in queue 0..2 at an instant in time (visible
                                                   via the NUMVAL bit in QSTAT0) equals or exceeds the value
                                                   specified by Q0..2.*/
            struct 
            {    
                uint32_t    Q0      :5;         // bits 0..4      (RW) Watermark threshold for queue 0
                                                //                     [0x0  = From 0x0 to 0x10, The default is 16 (maximum allowed).
                                                //                      0x11 = Disables the threshold errors.
                                                //                      0x12 = From 12hto 1Fh Reserved. Always write 0 to this bit; writes
                                                //                      of 1 to this bit are not supported and attempts to do so may result in
                                                //                      undefined behavior.]
                uint32_t            :3;         // bits 5..7      (R)  Reserved.
                uint32_t    Q1      :5;         // bits 8..12     (RW) Watermark threshold for queue 1
                                                //                     [0x0  = From 0x0 to 0x10, The default is 16 (maximum allowed).
                                                //                      0x11 = Disables the threshold errors.
                                                //                      0x12 = From 12hto 1Fh Reserved. Always write 0 to this bit; writes
                                                //                      of 1 to this bit are not supported and attempts to do so may result in
                                                //                      undefined behavior.]
                uint32_t            :3;         // bits 13..15    (R)  Reserved.
                uint32_t    Q2      :5;         // bits 16..20    (RW) Watermark threshold for queue 2
                                                //                     [0x0  = From 0x0 to 0x10, The default is 16 (maximum allowed).
                                                //                      0x11 = Disables the threshold errors.
                                                //                      0x12 = From 12hto 1Fh Reserved. Always write 0 to this bit; writes
                                                //                      of 1 to this bit are not supported and attempts to do so may result in
                                                //                      undefined behavior.]
                uint32_t            :11;        // bits 21..31    (R)  Reserved.       
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } QWMTHRA_reg_t;
    
        /*  @brief      EDMA3CC Status Register  
         *  @details    The EDMA3CC status register (CCSTAT) has a number of status bits that reflect which parts of the
         *              EDMA3CC logic is active at any given instant of time. CCSTAT provides visibility into the event queues
         *              and a TR life cycle. These are useful for system debug as they provide in-depth visibility for the events
         *              queued up in the event queue and also provide information on what parts of the EDMA3CC logic are
         *              active once the event has been received by the EDMA3CC.
        (offset = 0x640) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    EVTACTV      :1;         // bit 0        (R) Event active
                                                     //                  Indicates if an event is being processed.
                                                     //                  [0x0 = No event active;
                                                     //                   0x1 = Event active]
                uint32_t    QEVTACTV     :1;         // bit 1        (R) QDMA event active
                                                     //                  Indicates if a QDMA event is being processed.
                                                     //                  [0x0 = No QDMA event active;
                                                     //                   0x1 = QDMA event active]
                uint32_t    TRACTV       :1;         // bit 2        (R) Transfer active
                                                     //                  Indicates if a transfer is in progress.
                                                     //                  [0x0 = No transfer active;
                                                     //                   0x1 = Transfer active]
                uint32_t                 :1;         // bit 3        (R) Reserved.
                uint32_t    ACTV         :1;         // bit 4        (R) Channel controller active.
                                                     //                  Channel controller active is a logical-OR of each of the *ACTV bits.
                                                     //                  [0x0 = Channel is idle;
                                                     //                   0x1 = Channel is busy]
                uint32_t                 :3;         // bits 5..7    (R) Reserved.
                uint32_t    COMPACTV     :6;         // bits 8..13   (R) Completion request active.
                                                     //                  The COMPACTV field reflects the count for the number of
                                                     //                  completion requests submitted to the transfer controllers.
                                                     //                  This count increments every time a TR is submitted and is
                                                     //                  programmed to report completion (the TCINTEN or TCCCHEN bits
                                                     //                  in OPT in the parameter entry associated with the TR are set).
                                                     //                  The counter decrements for every valid TCC received back from the
                                                     //                  transfer controllers.
                                                     //                  If at any time the count reaches a value of 63, the EDMA3CC will not
                                                     //                  service any new TRs until the count is less then 63 (or return a
                                                     //                  transfer completion code from a transfer controller, which would
                                                     //                  decrement the count).
                                                     //                  [0x0 = No completion requests outstanding;
                                                     //                   0x1 = Total of 1 completion request to 63 completion requests are
                                                     //                   outstanding, from 0x1 to 0x3F.]
                uint32_t                 :2;         // bits 14,15   (R) Reserved. 
                uint32_t    QUEACTV0     :1;         // bit 16       (R) Queue 0 active
                                                     //                  Indicates if queue 0 is active.
                                                     //                  [0x0 = Queue idle;
                                                     //                   0x1 = Queue active]
                uint32_t    QUEACTV1     :1;         // bit 17       (R) Queue 1 active
                                                     //                  Indicates if queue 1 is active.
                                                     //                  [0x0 = Queue idle;
                                                     //                   0x1 = Queue active]
                uint32_t    QUEACTV2     :1;         // bit 18       (R) Queue 2 active
                                                     //                  Indicates if queue 2 is active.
                                                     //                  [0x0 = Queue idle;
                                                     //                   0x1 = Queue active]
                uint32_t                 :13;        // bits 19..31  (R) Reserved.        
            } b;                                     // bit access  
            uint32_t  reg;                           // raw register  
        } CCSTAT_reg_t;
            
        /*  @brief      Memory Protection Fault Address Register  
         *  @details    A CPU write of 1 to the MPFCLR bit in the memory protection fault command register (MPFCR) causes
         *              any error conditions stored in MPFAR to be cleared.
        (offset = 0x800) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    FADDR      :32;         // bits 0..31       (R) Fault address
                                                    //                      This 32 bit read-only status register contains the fault address when
                                                    //                      a memory protection violation is detected.
                                                    //                      This register can only be cleared via the memory protection fault
                                                    //                      command register (MPFCR). Value 0x0 to 0xFFFF_FFFF.          
            } b;                                    // bit access  
            uint32_t  reg;                          // raw register  
        } MPFAR_reg_t;
            
        /*  @brief      Memory Protection Fault Status Register  
         *  @details    A CPU write of 1 to the MPFCLR bit in the memory protection fault command register (MPFCR) causes
         *              any error conditions stored in MPFSR to be cleared.
        (offset = 0x804) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    UXE      :1;         // bit 0        (R) User execute fault
                                                 //                  Indicates a user mode execute violation.
                                                 //                  [0x0 = No fault;
                                                 //                   0x1 = User level task attempted to execute from a MP page without
                                                 //                   UX permissions]
                uint32_t    UWE      :1;         // bit 1        (R) User write fault
                                                 //                  Indicates a user mode write violation.
                                                 //                  [0x0 = No fault;
                                                 //                   0x1 = User level task attempted to write to a MP page without UW
                                                 //                   permissions.]
                uint32_t    URE      :1;         // bit 2        (R) User read fault
                                                 //                  Indicates a user mode read violation.
                                                 //                  [0x0 = No fault;
                                                 //                   0x1 = User level task attempted to read from a MP page without UR
                                                 //                   permissions.]
                uint32_t    SXE      :1;         // bit 3        (R) Supervisor execute fault
                                                 //                  Indicates a supervisor mode execute violation.
                                                 //                  [0x0 = No fault;
                                                 //                   0x1 = FSupervisor level task attempted to execute from a MP page
                                                 //                   without SX permissions]
                uint32_t    SWE      :1;         // bit 4        (R) Supervisor write fault
                                                 //                  Indicates a supervisor mode write violation.
                                                 //                  [0x0 = No fault;
                                                 //                   0x1 = Supervisor level task attempted to write to a MP page without
                                                 //                   SW permissions.]
                uint32_t    SRE      :1;         // bit 5        (R) Supervisor read fault
                                                 //                  Indicates a supervisor mode read violation.
                                                 //                  [0x0 = No fault;
                                                 //                   0x1 = Supervisor level task attempted to read from a MP page without
                                                 //                   SR permissions]
                uint32_t             :1;         // bits 6..8    (R) Reserved. 
                uint32_t    FID      :4;         // bits 9..12   (R) Faulted identification.
                                                 //                  FID contains valid information if any of the MP error bits (UXE, UWE,
                                                 //                  URE, SXE, SWE, SRE) are nonzero (that is, if an error has been
                                                 //                  detected.) The FID field contains the privilege ID for the specific
                                                 //                  request/requestor that resulted in an MP error.
                                                 //                  Value 0x0 to 0xF.
                uint32_t             :19;        // bits 13..31  (R) Reserved.         
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } MPFSR_reg_t;
            
        /*  @brief      Memory Protection Fault Command Register  
         *  @details    Clears memory protection fault status.
         *              Writing 1 to this register clears the protection fault status.
        (offset = 0x808) [reset = 0x00000000] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    MPFCLR      :1;         // bit 0       (W) Memory protection fault clear
                                                    //                 Writing 1 clears the protection fault status.
                                                    //                 [0x0 = No action;
                                                    //                  0x1 = Clear fault status in MPFAR and MPFSR]
                uint32_t                :31;        // bits 1..31  (R) Reserved.         
            } b;                                    // bit access  
            uint32_t  reg;                          // raw register  
        } MPFCR_reg_t;
        
        /*  @brief      Memory Protection Page Attribute Register Global  
         *  @details    Controls the memory protection attributes for a specific page in the global address space.
         *              Each bit field defines read, write, and execute permissions for user and supervisor modes.
         *              Also includes extended attribute and access ID fields.
        (offset = 0x80C) [reset = 0x676] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    UX      :1;         // bit: 0        (RW) User execute permission
                                                //                    [0x0 = Execute permission denied in user mode from region M
                                                //                     0x1 = Execute permission granted in user mode from region M]
                uint32_t    UW      :1;         // bit: 1        (RW) User write permission
                                                //                    [0x0 = Write permission denied in user mode from region M
                                                //                     0x1 = Write permission granted in user mode from region M]
                uint32_t    UR      :1;         // bit: 2        (RW) User read permission
                                                //                    [0x0 = Read permission denied in user mode from region M
                                                //                     0x1 = Read permission granted in user mode from region N]
                uint32_t    SX      :1;         // bit: 3        (RW) Supervisor execute permission
                                                //                    [0x0 = Execute permission denied in supervisor mode from region M
                                                //                     0x1 = Execute permission granted in supervisor mode from region M]
                uint32_t    SW      :1;         // bit: 4        (RW) Supervisor write permission
                                                //                    [0x0 = Write permission denied in supervisor mode from region M
                                                //                     0x1 = Write permission granted in supervisor mode from region N]
                uint32_t    SR      :1;         // bit: 5        (RW) Supervisor read permission
                                                //                    [0x0 = Read permission denied in supervisor mode from region M
                                                //                     0x1 = Read permission granted in supervisor mode from region M]
                uint32_t            :3;         // bit: 6..8     (R)  Reserved.
                uint32_t    EXT     :1;         // bit: 9        (RW) Extended attribute
                                                //                    [0x0 = Requests with Privilege ID >= 6 are not allowed to region M,
                                                //                           regardless of permission settings (UW, UR, SW, SR).
                                                //                     0x1 = Requests with Privilege ID >= 6 are permitted, if access type is
                                                //                           allowed as defined by permission settings (UW, UR, SW, SR).]
                uint32_t    AIDm    :6;         // bit: 10..15   (RW) Access ID mask
                                                //                    [0x0 = Requests with Privilege ID == N are not allowed to region M,
                                                //                           regardless of permission settings (UW, UR, SW, SR).
                                                //                     0x1 = Requests with Privilege ID == N are permitted, if access type is
                                                //                           allowed as defined by permission settings (UW, UR, SW, SR).]
                uint32_t            :16;        // bit: 16..31   (R)  Reserved.         
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } MPPAG_reg_t;
        
        /*  @brief      Memory Protection Page Attribute Register 0..7  
         *  @details    Controls the memory protection attributes for a specific page in the alternate address space.
         *              Each bit field defines read, write, and execute permissions for user and supervisor modes.
         *              Also includes extended attribute and access ID fields.
        (offset = 0x810 to 0x82C) [reset = 0x676] */ 
        typedef union 
        { 
            struct
            {    
                uint32_t    UX      :1;         // bit: 0        (RW) User execute permission
                                                //                    [0x0 = Execute permission denied in user mode from region M
                                                //                     0x1 = Execute permission granted in user mode from region M]
                uint32_t    UW      :1;         // bit: 1        (RW) User write permission
                                                //                    [0x0 = Write permission denied in user mode from region M
                                                //                     0x1 = Write permission granted in user mode from region M]
                uint32_t    UR      :1;         // bit: 2        (RW) User read permission
                                                //                    [0x0 = Read permission denied in user mode from region M
                                                //                     0x1 = Read permission granted in user mode from region N]
                uint32_t    SX      :1;         // bit: 3        (RW) Supervisor execute permission
                                                //                    [0x0 = Execute permission denied in supervisor mode from region M
                                                //                     0x1 = Execute permission granted in supervisor mode from region M]
                uint32_t    SW      :1;         // bit: 4        (RW) Supervisor write permission
                                                //                    [0x0 = Write permission denied in supervisor mode from region M
                                                //                     0x1 = Write permission granted in supervisor mode from region N]
                uint32_t    SR      :1;         // bit: 5        (RW) Supervisor read permission
                                                //                    [0x0 = Read permission denied in supervisor mode from region M
                                                //                     0x1 = Read permission granted in supervisor mode from region M]
                uint32_t            :3;         // bit: 6..8     (R)  Reserved.
                uint32_t    EXT     :1;         // bit: 9        (RW) Extended attribute
                                                //                    [0x0 = Requests with Privilege ID >= 6 are not allowed to region M,
                                                //                           regardless of permission settings (UW, UR, SW, SR).
                                                //                     0x1 = Requests with Privilege ID >= 6 are permitted, if access type is
                                                //                           allowed as defined by permission settings (UW, UR, SW, SR).]
                uint32_t    AIDm    :6;         // bit: 10..15   (RW) Access ID mask
                                                //                    [0x0 = Requests with Privilege ID == N are not allowed to region M,
                                                //                           regardless of permission settings (UW, UR, SW, SR).
                                                //                     0x1 = Requests with Privilege ID == N are permitted, if access type is
                                                //                           allowed as defined by permission settings (UW, UR, SW, SR).]
                uint32_t            :16;        // bit: 16..31   (R)  Reserved.         
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } MPPA_reg_t;
        
        /*  @brief      Event Register  
         *  @details    All external events are captured in the event register (ER/ERH). The events are latched even when the
         *              events are not enabled. If the event bit corresponding to the latched event is enabled (EER.En/EERH.En
         *              = 1), then the event is evaluated by the EDMA3CC logic for an associated transfer request submission to
         *              the transfer controllers. The event register bits are automatically cleared (ER.En/ERH.En= 0) once the
         *              corresponding events are prioritized and serviced. If ER.En/ERH.En are already set and another event is
         *              received on the same channel/event, then the corresponding event is latched in the event miss register
         *              (EMR.En/EMRH.En), provided that the event was enabled (EER.En/EERH.En = 1). Event n can be
         *              cleared by the CPU writing a 1 to corresponding event bit in the event clear register (ECR/ECRH). The
         *              setting of an event is a higher priority relative to clear operations (via hardware or software). If set and
         *              clear conditions occur concurrently, the set condition wins. If the event was previously set, then
         *              EMR/EMRH would be set because an event is lost. If the event was previously clear, then the event
         *              remains set and is prioritized for submission to the event queues. The Debug List table provides the type
         *              of synchronization events and the EDMA3CC channels associated to each of these external events. This
         *              register is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels consist of
         *              a set of registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of each
         *              register matches the DMA channel number. Each register is named with the format reg_name that
         *              corresponds to DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32
         *              through 64. For example, the event register (ER) corresponds to DMA channel 0 through 31 and the event
         *              register high register (ERH) corresponds to DMA channel 32 through 63. The register is typically called
         *              the event register. The DMA channel registers are accessible via read/writes to the global address range.
         *              They are also accessible via read/writes to the shadow address range. The read/write ability to the
         *              registers in the shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x1000) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (R) Event 0 to 31.
                                                 //                       Events 0 to 31 are captured by the EDMA3CC and are latched into
                                                 //                       ER.The events are set (En = 1) even when events are disabled (En = 0
                                                 //                       in the event enable register, EER).
                                                 //                       [0x0 = EDMA3CC event is not asserted.
                                                 //                        0x1 = EDMA3CC event is asserted. Corresponding DMA event is
                                                 //                        prioritized versus other pending DMA/QDMA events for submission
                                                 //                        to the EDMA3TC.]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } ER_reg_t;
        
        /*  @brief      Event Register High  
         *  @details    All external events are captured in the event register (ER/ERH). The events are latched even when the
         *              events are not enabled. If the event bit corresponding to the latched event is enabled (EER.En/EERH.En
         *              = 1), then the event is evaluated by the EDMA3CC logic for an associated transfer request submission to
         *              the transfer controllers. The event register bits are automatically cleared (ER.En/ERH.En= 0) once the
         *              corresponding events are prioritized and serviced. If ER.En/ERH.En are already set and another event is
         *              received on the same channel/event, then the corresponding event is latched in the event miss register
         *              (EMR.En/EMRH.En), provided that the event was enabled (EER.En/EERH.En = 1). Event n can be
         *              cleared by the CPU writing a 1 to corresponding event bit in the event clear register (ECR/ECRH). The
         *              setting of an event is a higher priority relative to clear operations (via hardware or software). If set and
         *              clear conditions occur concurrently, the set condition wins. If the event was previously set, then
         *              EMR/EMRH would be set because an event is lost. If the event was previously clear, then the event
         *              remains set and is prioritized for submission to the event queues. The Debug List table provides the type
         *              of synchronization events and the EDMA3CC channels associated to each of these external events. This
         *              register is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels consist of
         *              a set of registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of each
         *              register matches the DMA channel number. Each register is named with the format reg_name that
         *              corresponds to DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32
         *              through 64. For example, the event register (ER) corresponds to DMA channel 0 through 31 and the event
         *              register high register (ERH) corresponds to DMA channel 32 through 63. The register is typically called
         *              the event register. The DMA channel registers are accessible via read/writes to the global address range.
         *              They are also accessible via read/writes to the shadow address range. The read/write ability to the
         *              registers in the shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x1004) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (R) Event pending status
                                                 //                       Event 32 to 63.
                                                 //                       Events 32 to 63 are captured by the EDMA3CC and are latched into
                                                 //                       ERH.The events are set (En = 1) even when events are disabled (En = 0
                                                 //                       in the event enable register high, EERH).
                                                 //                       [0x0 = EDMA3CC event is not asserted.
                                                 //                        0x1 = EDMA3CC event is asserted. Corresponding DMA event is
                                                 //                        prioritized versus other pending DMA/QDMA events for submission
                                                 //                        to the EDMA3TC.]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } ERH_reg_t;
        
        /*  @brief      Event Clear Register  
         *  @details    Once an event has been posted in the event registers (ER/ERH), the event is cleared in two ways. If the
         *              event is enabled in the event enable register (EER/EERH) and the EDMA3CC submits a transfer request
         *              for the event to the EDMA3TC, it clears the corresponding event bit in the event register. If the event is
         *              disabled in the event enable register (EER/EERH), the CPU can clear the event by way of the event clear
         *              registers (ECR/ECRH). Writing a 1 to any of the bits clears the corresponding event; writing a 0 has no
         *              effect. Once an event bit is set in the event register, it remains set until EDMA3CC submits a transfer
         *              request for that event or the CPU clears the event by setting the corresponding bit in ECR/ECRH. This
         *              register is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels consist of
         *              a set of registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of each
         *              register matches the DMA channel number. Each register is named with the format reg_name that
         *              corresponds to DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32
         *              through 64. For example, the event register (ER) corresponds to DMA channel 0 through 31 and the event
         *              register high register (ERH) corresponds to DMA channel 32 through 63. The register is typically called
         *              the event register. The DMA channel registers are accessible via read/writes to the global address range.
         *              They are also accessible via read/writes to the shadow address range. The read/write ability to the
         *              registers in the shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x1008) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (W) Event clear for event 0 to 31.
                                                 //                       Any of the event bits in ECR is set to clear the event (En) in the
                                                 //                       event register (ER).A write of 0 has no effect.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = EDMA3CC event is cleared in the event register (ER).]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } ECR_reg_t;

        /*  @brief      Event Clear Register High  
         *  @details    Once an event has been posted in the event registers (ER/ERH), the event is cleared in two ways. If the
         *              event is enabled in the event enable register (EER/EERH) and the EDMA3CC submits a transfer request
         *              for the event to the EDMA3TC, it clears the corresponding event bit in the event register. If the event is
         *              disabled in the event enable register (EER/EERH), the CPU can clear the event by way of the event clear
         *              registers (ECR/ECRH). Writing a 1 to any of the bits clears the corresponding event; writing a 0 has no
         *              effect. Once an event bit is set in the event register, it remains set until EDMA3CC submits a transfer
         *              request for that event or the CPU clears the event by setting the corresponding bit in ECR/ECRH. This
         *              register is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels consist of
         *              a set of registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of each
         *              register matches the DMA channel number. Each register is named with the format reg_name that
         *              corresponds to DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32
         *              through 64. For example, the event register (ER) corresponds to DMA channel 0 through 31 and the event
         *              register high register (ERH) corresponds to DMA channel 32 through 63. The register is typically called
         *              the event register. The DMA channel registers are accessible via read/writes to the global address range.
         *              They are also accessible via read/writes to the shadow address range. The read/write ability to the
         *              registers in the shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x100C) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (W) Event clear control
                                                 //                       Event clear for event 32 to 63.
                                                 //                       Any of the event bits in ECRH are set to clear the event (En) in the
                                                 //                       event register high (ERH).A write of 0 has no effect.
                                                 //                       [0x0 = No effect.
                                                 //                       0x1 = EDMA3CC event is cleared in the event register high (ERH).]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } ECRH_reg_t;
        
        /*  @brief      Event Set Register  
         *  @details    The event set registers (ESR/ESRH) allow the CPU (EDMA3 programmers) to manually set events to
         *              initiate DMA transfer requests. CPU writes of 1 to any event set register (En) bits set the corresponding
         *              bits in the registers. The set event is evaluated by the EDMA3CC logic for an associated transfer request
         *              submission to the transfer controllers. Writing a 0 has no effect. The event set registers operate
         *              independent of the event registers (ER/ERH), and a write of 1 is always considered a valid event
         *              regardless of whether the event is enabled (the corresponding event bits are set or cleared in
         *              EER.En/EERH.En). Once the event is set in the event set registers, it cannot be cleared by CPU writes, in
         *              other words, the event clear registers (ECR/ECRH) have no effect on the state of ESR/ESRH. The bits will
         *              only be cleared once the transfer request corresponding to the event has been submitted to the transfer
         *              controller. The setting of an event is a higher priority relative to clear operations (via hardware). If set and
         *              clear conditions occur concurrently, the set condition wins. If the event was previously set, then
         *              EMR/EMRH would be set because an event is lost. If the event was previously clear, then the event
         *              remains set and is prioritized for submission to the event queues. Manually-triggered transfers via writes
         *              to ESR/ESRH allow the CPU to submit DMA requests in the system, these are relevant for memory-tomemory
         *              transfer scenarios. If the ESR.En/ESRH.En bit is already set and another CPU write of 1 is
         *              attempted to the same bit, then the corresponding event is latched in the event missed registers
         *              (EMR.En/EMRH.En = 1). This register is part of a set of registers that pertain to the 64 DMA channels.
         *              The 64 DMA channels consist of a set of registers (with exception of DMAQNUMn) that each have 64 bits
         *              and the bit position of each register matches the DMA channel number. Each register is named with the
         *              format reg_name that corresponds to DMA channels 0 through 31 and reg_name_High that corresponds
         *              to DMA channels 32 through 64. For example, the event register (ER) corresponds to DMA channel 0
         *              through 31 and the event register high register (ERH) corresponds to DMA channel 32 through 63. The
         *              register is typically called the event register. The DMA channel registers are accessible via read/writes to
         *              the global address range. They are also accessible via read/writes to the shadow address range. The
         *              read/write ability to the registers in the shadow region are controlled by the DMA region access registers
        (DRAEm/DRAEHm).
        (offset = 0x1010) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (RW) Event set for event 0 to 31.
                                                 //                        [0x0 = No effect.
                                                 //                         0x1 = Corresponding DMA event is prioritized versus other pending
                                                 //                             DMA/QDMA events for submission to the EDMA3TC.]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register 
        } ESR_reg_t;
         
        /*  @brief      Event Set Register High  
         *  @details    The event set registers (ESR/ESRH) allow the CPU (EDMA3 programmers) to manually set events to
         *              initiate DMA transfer requests. CPU writes of 1 to any event set register (En) bits set the corresponding
         *              bits in the registers. The set event is evaluated by the EDMA3CC logic for an associated transfer request
         *              submission to the transfer controllers. Writing a 0 has no effect. The event set registers operate
         *              independent of the event registers (ER/ERH), and a write of 1 is always considered a valid event
         *              regardless of whether the event is enabled (the corresponding event bits are set or cleared in
         *              EER.En/EERH.En). Once the event is set in the event set registers, it cannot be cleared by CPU writes, in
         *              other words, the event clear registers (ECR/ECRH) have no effect on the state of ESR/ESRH. The bits will
         *              only be cleared once the transfer request corresponding to the event has been submitted to the transfer
         *              controller. The setting of an event is a higher priority relative to clear operations (via hardware). If set and
         *              clear conditions occur concurrently, the set condition wins. If the event was previously set, then
         *              EMR/EMRH would be set because an event is lost. If the event was previously clear, then the event
         *              remains set and is prioritized for submission to the event queues. Manually-triggered transfers via writes
         *              to ESR/ESRH allow the CPU to submit DMA requests in the system, these are relevant for memory-tomemory
         *              transfer scenarios. If the ESR.En/ESRH.En bit is already set and another CPU write of 1 is
         *              attempted to the same bit, then the corresponding event is latched in the event missed registers
         *              (EMR.En/EMRH.En = 1). This register is part of a set of registers that pertain to the 64 DMA channels.
         *              The 64 DMA channels consist of a set of registers (with exception of DMAQNUMn) that each have 64 bits
         *              and the bit position of each register matches the DMA channel number. Each register is named with the
         *              format reg_name that corresponds to DMA channels 0 through 31 and reg_name_High that corresponds
         *              to DMA channels 32 through 64. For example, the event register (ER) corresponds to DMA channel 0
         *              through 31 and the event register high register (ERH) corresponds to DMA channel 32 through 63. The
         *              register is typically called the event register. The DMA channel registers are accessible via read/writes to
         *              the global address range. They are also accessible via read/writes to the shadow address range. The
         *              read/write ability to the registers in the shadow region are controlled by the DMA region access registers
         *              (DRAEm/DRAEHm).
        (offset = 0x1014) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31       (RW) Event set for event 32 to 63.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Corresponding DMA event is prioritized versus other pending
                                                 //                              DMA/QDMA events for submission to the EDMA3TC.]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } ESRH_reg_t;
        
        /*  @brief      Chained Event Register  
         *  @details    When the OPTIONS parameter for a PaRAM entry is programmed to returned a chained completion code
         *              (ITCCHEN = 1 and/or TCCHEN = 1), then the value dictated by the TCC[5:0] (also programmed in OPT)
         *              forces the corresponding event bit to be set in the chained event registers (CER/CERH). The set chained
         *              event is evaluated by the EDMA3CC logic for an associated transfer request submission to the transfer
         *              controllers. This results in a chained-triggered transfer. The chained event registers do not have any
         *              enables. The generation of a chained event is essentially enabled by the PaRAM entry that has been
         *              configured for intermediate and/or final chaining on transfer completion. The En bit is set (regardless of
         *              the state of EER.En/EERH.En) when a chained completion code is returned from one of the transfer
         *              controllers or is generated by the EDMA3CC via the early completion path. The bits in the chained event
         *              register are cleared when the corresponding events are prioritized and serviced. If the En bit is already set
         *              and another chaining completion code is return for the same event, then the corresponding event is
         *              latched in the event missed registers (EMR.En/EMRH.En= 1). The setting of an event is a higher priority
         *              relative to clear operations (via hardware). If set and clear conditions occur concurrently, the set condition
         *              wins. If the event was previously set, then EMR/EMRH would be set because an event is lost. If the event
         *              was previously clear, then the event remains set and is prioritized for submission to the event queues.
         *              This register is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels
         *              consist of a set of registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of
         *              each register matches the DMA channel number. Each register is named with the format reg_name that
         *              corresponds to DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32
         *              through 64. For example, the event register (ER) corresponds to DMA channel 0 through 31 and the event
         *              register high register (ERH) corresponds to DMA channel 32 through 63. The register is typically called
         *              the event register. The DMA channel registers are accessible via read/writes to the global address range.
         *              They are also accessible via read/writes to the shadow address range. The read/write ability to the
        registers in the shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x1018) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (RW) Chained event for event 0 to 31.
                                                 //                        [0x0 = No effect.
                                                 //                         0x1 = Corresponding DMA event is prioritized versus other pending
                                                 //                               DMA/QDMA events for submission to the EDMA3TC.]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register 
        } CER_reg_t;
        
        /*  @brief      Chained Event Register High  
         *  @details    When the OPTIONS parameter for a PaRAM entry is programmed to returned a chained completion code
         *              (ITCCHEN = 1 and/or TCCHEN = 1), then the value dictated by the TCC[5:0] (also programmed in OPT)
         *              forces the corresponding event bit to be set in the chained event registers (CER/CERH). The set chained
         *              event is evaluated by the EDMA3CC logic for an associated transfer request submission to the transfer
         *              controllers. This results in a chained-triggered transfer. The chained event registers do not have any
         *              enables. The generation of a chained event is essentially enabled by the PaRAM entry that has been
         *              configured for intermediate and/or final chaining on transfer completion. The En bit is set (regardless of
         *              the state of EER.En/EERH.En) when a chained completion code is returned from one of the transfer
         *              controllers or is generated by the EDMA3CC via the early completion path. The bits in the chained event
         *              register are cleared when the corresponding events are prioritized and serviced. If the En bit is already set
         *              and another chaining completion code is return for the same event, then the corresponding event is
         *              latched in the event missed registers (EMR.En/EMRH.En= 1). The setting of an event is a higher priority
         *              relative to clear operations (via hardware). If set and clear conditions occur concurrently, the set condition
         *              wins. If the event was previously set, then EMR/EMRH would be set because an event is lost. If the event
         *              was previously clear, then the event remains set and is prioritized for submission to the event queues.
         *              This register is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels
         *              consist of a set of registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of
         *              each register matches the DMA channel number. Each register is named with the format reg_name that
         *              corresponds to DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32
         *              through 64. For example, the event register (ER) corresponds to DMA channel 0 through 31 and the event
         *              register high register (ERH) corresponds to DMA channel 32 through 63. The register is typically called
         *              the event register. The DMA channel registers are accessible via read/writes to the global address range.
         *              They are also accessible via read/writes to the shadow address range. The read/write ability to the
         *              registers in the shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x101C) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (R) Chained event set for event 32 to 63.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Corresponding DMA event is prioritized versus other pending
                                                 //                             DMA/QDMA events for submission to the EDMA3TC.]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } CERH_reg_t;
        
        /*  @brief      Event Enable Register  
         *  @details    The EDMA3CC provides the option of selectively enabling/disabling each event in the event registers
         *              (ER/ERH) by using the event enable registers (EER/EERH). If an event bit in EER/EERH is set (using the
         *              event enable set registers, EESR/EESRH), it will enable that corresponding event. Alternatively, if an
         *              event bit in EER/EERH is cleared (using the event enable clear registers, EECR/EECRH), it will disable
         *              the corresponding event. The event registers latch all events that are captured by EDMA3CC, even if the
         *              events are disabled (although EDMA3CC does not process it). Enabling an event with a pending event
         *              already set in the event registers enables the EDMA3CC to process the already set event like any other
         *              new event. The EER/EERH settings do not have any effect on chained events (CER.En/CERH.En= 1) and
         *              manually set events (ESR.En/ESRH.En= 1). This register is part of a set of registers that pertain to the 64
         *              DMA channels. The 64 DMA channels consist of a set of registers (with exception of DMAQNUMn) that
         *              each have 64 bits and the bit position of each register matches the DMA channel number. Each register is
         *              named with the format reg_name that corresponds to DMA channels 0 through 31 and reg_name_High
         *              that corresponds to DMA channels 32 through 64. For example, the event register (ER) corresponds to
         *              DMA channel 0 through 31 and the event register high register (ERH) corresponds to DMA channel 32
         *              through 63. The register is typically called the event register. The DMA channel registers are accessible
         *              via read/writes to the global address range. They are also accessible via read/writes to the shadow
         *              address range. The read/write ability to the registers in the shadow region are controlled by the DMA
         *              region access registers (DRAEm/DRAEHm).
        (offset = 0x1020) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (R) Event enable for events 0 to 31.
                                                 //                       [0x0 = Event is not enabled. An external event latched in the event
                                                 //                              register (ER) is not evaluated by the EDMA3CC.
                                                 //                        0x1 = Event is enabled. An external event latched in the event
                                                 //                              register (ER) is evaluated by the EDMA3CC.]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } EER_reg_t;
        
        /*  @brief      Event Enable Register High  
         *  @details    The EDMA3CC provides the option of selectively enabling/disabling each event in the event registers
         *              (ER/ERH) by using the event enable registers (EER/EERH). If an event bit in EER/EERH is set (using the
         *              event enable set registers, EESR/EESRH), it will enable that corresponding event. Alternatively, if an
         *              event bit in EER/EERH is cleared (using the event enable clear registers, EECR/EECRH), it will disable
         *              the corresponding event. The event registers latch all events that are captured by EDMA3CC, even if the
         *              events are disabled (although EDMA3CC does not process it). Enabling an event with a pending event
         *              already set in the event registers enables the EDMA3CC to process the already set event like any other
         *              new event. The EER/EERH settings do not have any effect on chained events (CER.En/CERH.En= 1) and
         *              manually set events (ESR.En/ESRH.En= 1). This register is part of a set of registers that pertain to the 64
         *              DMA channels. The 64 DMA channels consist of a set of registers (with exception of DMAQNUMn) that
         *              each have 64 bits and the bit position of each register matches the DMA channel number. Each register is
         *              named with the format reg_name that corresponds to DMA channels 0 through 31 and reg_name_High
         *              that corresponds to DMA channels 32 through 64. For example, the event register (ER) corresponds to
         *              DMA channel 0 through 31 and the event register high register (ERH) corresponds to DMA channel 32
         *              through 63. The register is typically called the event register. The DMA channel registers are accessible
         *              via read/writes to the global address range. They are also accessible via read/writes to the shadow
         *              address range. The read/write ability to the registers in the shadow region are controlled by the DMA
         *              region access registers (DRAEm/DRAEHm).
        (offset = 0x1024) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (R) Event enable for events 32 to 63.
                                                 //                       [0x0 = Event is not enabled. An external event latched in the event
                                                 //                              register high (ERH) is not evaluated by the EDMA3CC.
                                                 //                        0x1 = Event is enabled. An external event latched in the event
                                                 //                              register high (ERH) is evaluated by the EDMA3CC.]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register 
        } EERH_reg_t;
        
        /*  @brief      Event Enable Clear Register  
         *  @details    The event enable registers (EER/EERH) cannot be modified by directly writing to them. The intent is to
         *              ease the software burden for the case where multiple tasks are attempting to simultaneously modify these
         *              registers. The event enable clear registers (EECR/EECRH) are used to disable events. Writes of 1 to the
         *              bits in EECR/EECRH clear the corresponding event bits in EER/EERH; writes of 0 have no effect. This
         *              register is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels consist of
         *              a set of registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of each
         *              register matches the DMA channel number. Each register is named with the format reg_name that
         *              corresponds to DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32
         *              through 64. For example, the event register (ER) corresponds to DMA channel 0 through 31 and the event
         *              register high register (ERH) corresponds to DMA channel 32 through 63. The register is typically called
         *              the event register. The DMA channel registers are accessible via read/writes to the global address range.
         *              They are also accessible via read/writes to the shadow address range. The read/write ability to the
         *              registers in the shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x1028) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (W) Event enable clear for events 0 to 31.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Event is disabled. Corresponding bit in the event enable
                                                 //                       register (EER) is cleared (En = 0).]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register 
        } EECR_reg_t;

        /*  @brief      Event Enable Clear Register High  
         *  @details    The event enable registers (EER/EERH) cannot be modified by directly writing to them. The intent is to
         *              ease the software burden for the case where multiple tasks are attempting to simultaneously modify these
         *              registers. The event enable clear registers (EECR/EECRH) are used to disable events. Writes of 1 to the
         *              bits in EECR/EECRH clear the corresponding event bits in EER/EERH; writes of 0 have no effect. This
         *              register is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels consist of
         *              a set of registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of each
         *              register matches the DMA channel number. Each register is named with the format reg_name that
         *              corresponds to DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32
         *              through 64. For example, the event register (ER) corresponds to DMA channel 0 through 31 and the event
         *              register high register (ERH) corresponds to DMA channel 32 through 63. The register is typically called
         *              the event register. The DMA channel registers are accessible via read/writes to the global address range.
         *              They are also accessible via read/writes to the shadow address range. The read/write ability to the
         *              registers in the shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x102C) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (W) Event enable clear for events 32 to 63.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Event is disabled. Corresponding bit in the event enable
                                                 //                              register high (EERH) is cleared (En = 0).]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register 
        } EECRH_reg_t;
        
        /*  @brief      Event Enable Set Register  
         *  @details    The event enable registers (EER/EERH) cannot be modified by directly writing to them. The intent is to
         *              ease the software burden for the case where multiple tasks are attempting to simultaneously modify these
         *              registers. The event enable set registers (EESR/EESRH) are used to enable events. Writes of 1 to the bits
         *              in EESR/EESRH set the corresponding event bits in EER/EERH; writes of 0 have no effect. This register
         *              is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels consist of a set of
         *              registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of each register
         *              matches the DMA channel number. Each register is named with the format reg_name that corresponds to
         *              DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32 through 64. For
         *              example, the event register (ER) corresponds to DMA channel 0 through 31 and the event register high
         *              register (ERH) corresponds to DMA channel 32 through 63. The register is typically called the event
         *              register. The DMA channel registers are accessible via read/writes to the global address range. They are
         *              also accessible via read/writes to the shadow address range. The read/write ability to the registers in the
         *              shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x1030) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (W) Event enable set for events 0 to 31.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Event is enabled. Corresponding bit in the event enable register
                                                 //                       (EER) is set (En = 1).]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } EESR_reg_t;
        
        /*  @brief      Event Enable Set Register High  
         *  @details    The event enable registers (EER/EERH) cannot be modified by directly writing to them. The intent is to
         *              ease the software burden for the case where multiple tasks are attempting to simultaneously modify these
         *              registers. The event enable set registers (EESR/EESRH) are used to enable events. Writes of 1 to the bits
         *              in EESR/EESRH set the corresponding event bits in EER/EERH; writes of 0 have no effect. This register
         *              is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels consist of a set of
         *              registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of each register
         *              matches the DMA channel number. Each register is named with the format reg_name that corresponds to
         *              DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32 through 64. For
         *              example, the event register (ER) corresponds to DMA channel 0 through 31 and the event register high
         *              register (ERH) corresponds to DMA channel 32 through 63. The register is typically called the event
         *              register. The DMA channel registers are accessible via read/writes to the global address range. They are
         *              also accessible via read/writes to the shadow address range. The read/write ability to the registers in the
         *              shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x1034) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31       (W) Event enable set for events 32 to 63.
                                                 //                      [0x0 = No effect.
                                                 //                       0x1 = Event is enabled. Corresponding bit in the event enable register
                                                 //                             high (EERH) is set (En= 1).]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } EESRH_reg_t;
        
        /*  @brief      Secondary Event Register  
         *  @details    The secondary event registers (SER/SERH) provide information on the state of a DMA channel or event
         *              (0 through 63). If the EDMA3CC receives a TR synchronization due to a manual-trigger, event-trigger, or
         *              chained-trigger source (ESR.En/ESRH.En= 1, ER.En/ERH.En= 1, or CER.En/CERH.En= 1), which results
         *              in the setting of a corresponding event bit in SER/SERH (SER.En/SERH.En = 1), it implies that the
         *              corresponding DMA event is in the queue. Once a bit corresponding to an event is set in SER/SERH, the
         *              EDMA3CC does not prioritize additional events on the same DMA channel. Depending on the condition
         *              that lead to the setting of the SER bits, either the EDMA3CC hardware or the software (using
         *              SECR/SECRH) needs to clear the SER/SERH bits for the EDMA3CC to evaluate subsequent events
         *              (subsequent transfers) on the same channel. For additional conditions that can cause the secondary event
         *              registers to be set, see EDMA Overview. This register is part of a set of registers that pertain to the 64
         *              DMA channels. The 64 DMA channels consist of a set of registers (with exception of DMAQNUMn) that
         *              each have 64 bits and the bit position of each register matches the DMA channel number. Each register is
         *              named with the format reg_name that corresponds to DMA channels 0 through 31 and reg_name_High
         *              that corresponds to DMA channels 32 through 64. For example, the event register (ER) corresponds to
         *              DMA channel 0 through 31 and the event register high register (ERH) corresponds to DMA channel 32
         *              through 63. The register is typically called the event register. The DMA channel registers are accessible
         *              via read/writes to the global address range. They are also accessible via read/writes to the shadow
         *              address range. The read/write ability to the registers in the shadow region are controlled by the DMA
         *              region access registers (DRAEm/DRAEHm).
        (offset = 0x1038) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (R) Secondary event register.
                                                 //                       The secondary event register is used along with the event register
                                                 //                       (ER) to provide information on the state of an event.
                                                 //                       [0x0 = Event is not currently stored in the event queue.
                                                 //                        0x1 = Event is currently stored in the event queue. Event arbiter will
                                                 //                              not prioritize additional events.]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register 
        } SER_reg_t;
        
        /*  @brief      Secondary Event Register High  
         *  @details    The secondary event registers (SER/SERH) provide information on the state of a DMA channel or event
         *              (0 through 63). If the EDMA3CC receives a TR synchronization due to a manual-trigger, event-trigger, or
         *              chained-trigger source (ESR.En/ESRH.En= 1, ER.En/ERH.En= 1, or CER.En/CERH.En= 1), which results
         *              in the setting of a corresponding event bit in SER/SERH (SER.En/SERH.En = 1), it implies that the
         *              corresponding DMA event is in the queue. Once a bit corresponding to an event is set in SER/SERH, the
         *              EDMA3CC does not prioritize additional events on the same DMA channel. Depending on the condition
         *              that lead to the setting of the SER bits, either the EDMA3CC hardware or the software (using
         *              SECR/SECRH) needs to clear the SER/SERH bits for the EDMA3CC to evaluate subsequent events
         *              (subsequent transfers) on the same channel. For additional conditions that can cause the secondary event
         *              registers to be set, see EDMA Overview. This register is part of a set of registers that pertain to the 64
         *              DMA channels. The 64 DMA channels consist of a set of registers (with exception of DMAQNUMn) that
         *              each have 64 bits and the bit position of each register matches the DMA channel number. Each register is
         *              named with the format reg_name that corresponds to DMA channels 0 through 31 and reg_name_High
         *              that corresponds to DMA channels 32 through 64. For example, the event register (ER) corresponds to
         *              DMA channel 0 through 31 and the event register high register (ERH) corresponds to DMA channel 32
         *              through 63. The register is typically called the event register. The DMA channel registers are accessible
         *              via read/writes to the global address range. They are also accessible via read/writes to the shadow
         *              address range. The read/write ability to the registers in the shadow region are controlled by the DMA
         *              region access registers (DRAEm/DRAEHm).
        (offset = 0x103C) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (R) Secondary event register.
                                                 //                       The secondary event register is used along with the event register
                                                 //                       high (ERH) to provide information on the state of an event.
                                                 //                       [0x0 = Event is not currently stored in the event queue.
                                                 //                        0x1 = Event is currently stored in the event queue. Event
                                                 //                              submission/prioritization logic will not prioritize 
                                                 //                              additional events.]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } SERH_reg_t;
        
        /*  @brief      Secondary Event Clear Register  
         *  @details    The secondary event clear registers (SECR/SECRH) clear the status of the secondary event registers
         *              (SER/SERH). CPU writes of 1 clear the corresponding set bits in SER/SERH. Writes of 0 have no effect.
         *              This register is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels
         *              consist of a set of registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of
         *              each register matches the DMA channel number. Each register is named with the format reg_name that
         *              corresponds to DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32
         *              through 64. For example, the event register (ER) corresponds to DMA channel 0 through 31 and the event
         *              register high register (ERH) corresponds to DMA channel 32 through 63. The register is typically called
         *              the event register. The DMA channel registers are accessible via read/writes to the global address range.
         *              They are also accessible via read/writes to the shadow address range. The read/write ability to the
         *              registers in the shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x1040) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (W) Secondary event clear register.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Corresponding bit in the secondary event register (SER) is
                                                 //                              cleared (En = 0).]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register 
        } SECR_reg_t;
        
        /*  @brief      Secondary Event Clear Register High  
         *  @details    The secondary event clear registers (SECR/SECRH) clear the status of the secondary event registers
        *               (SER/SERH). CPU writes of 1 clear the corresponding set bits in SER/SERH. Writes of 0 have no effect.
        *               This register is part of a set of registers that pertain to the 64 DMA channels. The 64 DMA channels
        *               consist of a set of registers (with exception of DMAQNUMn) that each have 64 bits and the bit position of
        *               each register matches the DMA channel number. Each register is named with the format reg_name that
        *               corresponds to DMA channels 0 through 31 and reg_name_High that corresponds to DMA channels 32
        *               through 64. For example, the event register (ER) corresponds to DMA channel 0 through 31 and the event
        *               register high register (ERH) corresponds to DMA channel 32 through 63. The register is typically called
        *               the event register. The DMA channel registers are accessible via read/writes to the global address range.
        *               They are also accessible via read/writes to the shadow address range. The read/write ability to the
        *               registers in the shadow region are controlled by the DMA region access registers (DRAEm/DRAEHm).
        (offset = 0x1044) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    En      :32;         // bit: 0..31        (W) Secondary event clear register.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Corresponding bit in the secondary event registers high (SERH)
                                                 //                              is cleared (En = 0).]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } SECRH_reg_t;
        
        /*  @brief      Interrupt Enable Register  
         *  @details    Interrupt enable registers (IER/IERH) are used to enable/disable the transfer completion interrupt
         *              generation by the EDMA3CC for all DMA/QDMA channels. The IER/IERH cannot be written to directly. To
         *              set any interrupt bit in IER/IERH, a 1 must be written to the corresponding interrupt bit in the interrupt
         *              enable set registers (IESR/IESRH). Similarly, to clear any interrupt bit in IER/IERH, a 1 must be written to
         *              the corresponding interrupt bit in the interrupt enable clear registers (IECR/IECRH). All DMA/QDMA
         *              channels can be set to assert an EDMA3CC completion interrupt to the CPU on transfer completion, by
         *              appropriately configuring the PaRAM entry associated with the channels. This register is used for the
         *              transfer completion interrupt reporting/generating by the EDMA3CC. For more details on EDMA3CC
         *              completion interrupt generation, see EDMA3 Interrupts.
        (offset = 0x1050) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    In_      :32;        // bit: 0..31        (R) Interrupt enable for channels 0 to 31.
                                                 //                       [0x0 = Interrupt is not enabled.
                                                 //                        0x1 = Interrupt is enabled.]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } IER_reg_t;
        
        /*  @brief      Interrupt Enable Register High  
         *  @details    Interrupt enable registers (IER/IERH) are used to enable/disable the transfer completion interrupt
         *              generation by the EDMA3CC for all DMA/QDMA channels. The IER/IERH cannot be written to directly. To
         *              set any interrupt bit in IER/IERH, a 1 must be written to the corresponding interrupt bit in the interrupt
         *              enable set registers (IESR/IESRH). Similarly, to clear any interrupt bit in IER/IERH, a 1 must be written to
         *              the corresponding interrupt bit in the interrupt enable clear registers (IECR/IECRH). All DMA/QDMA
         *              channels can be set to assert an EDMA3CC completion interrupt to the CPU on transfer completion, by
         *              appropriately configuring the PaRAM entry associated with the channels. This register is used for the
         *              transfer completion interrupt reporting/generating by the EDMA3CC. For more details on EDMA3CC
         *              completion interrupt generation, see EDMA3 Interrupts.
        (offset = 0x1054) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    In      :32;         // bit: 0..31        (R) Interrupt enable for channels 32 to 63.
                                                 //                       [0x0 = Interrupt is not enabled.
                                                 //                        0x1 = Interrupt is enabled.]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register 
        } IERH_reg_t;

        /*  @brief      Interrupt Enable Clear Register  
         *  @details    The interrupt enable clear registers (IECR/IECRH) are used to clear interrupts. Writes of 1 to the bits in
         *              IECR/IECRH clear the corresponding interrupt bits in the interrupt enable registers (IER/IERH); writes of 0
         *              have no effect. All DMA/QDMA channels can be set to assert an EDMA3CC completion interrupt to the
         *              CPU on transfer completion, by appropriately configuring the PaRAM entry associated with the channels.
         *              This register is used for the transfer completion interrupt reporting/generating by the EDMA3CC. For more
         *              details on EDMA3CC completion interrupt generation, see EDMA3 Interrupts.
        (offset = 0x1058) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    In      :32;         // bit: 0..31        (R) Interrupt enable clear for channels 0 to 31.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Corresponding bit in the interrupt enable register (IER) is
                                                 //                              cleared (In = 0).]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } IECR_reg_t;
          
        /*  @brief      Interrupt Enable Clear Register High 
         *              The interrupt enable clear registers (IECR/IECRH) are used to clear interrupts. Writes of 1 to the bits in
         *              IECR/IECRH clear the corresponding interrupt bits in the interrupt enable registers (IER/IERH); writes of 0
         *              have no effect. All DMA/QDMA channels can be set to assert an EDMA3CC completion interrupt to the
         *              CPU on transfer completion, by appropriately configuring the PaRAM entry associated with the channels.
         *              This register is used for the transfer completion interrupt reporting/generating by the EDMA3CC. For more
         *              details on EDMA3CC completion interrupt generation, see EDMA3 Interrupts. 
        (offset = 0x105C) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    In      :32;         // bit: 0..31        (W) Interrupt enable clear for channels 32 to 63.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Corresponding bit in the interrupt enable register high (IERH) is
                                                 //                              cleared (In = 0).]         
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } IECRH_reg_t;
        
        /*  @brief      Interrupt Enable Set Register  
         *  @details    The interrupt enable set registers (IESR/IESRH) are used to enable interrupts. Writes of 1 to the bits in
         *              IESR/IESRH set the corresponding interrupt bits in the interrupt enable registers (IER/IERH); writes of 0
         *              have no effect. All DMA/QDMA channels can be set to assert an EDMA3CC completion interrupt to the
         *              CPU on transfer completion, by appropriately configuring the PaRAM entry associated with the channels.
         *              This register is used for the transfer completion interrupt reporting/generating by the EDMA3CC. For more
         *              details on EDMA3CC completion interrupt generation, see EDMA3 Interrupts.
        (offset = 0x1060) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    In      :32;         // bit: 0..31        (W) Interrupt enable set for channels 0 to 31.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Corresponding bit in the interrupt enable register (IER) 
                                                 //                              is set (In = 1).]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } IESR_reg_t;
        
        /*  @brief      Interrupt Enable Set Register High  
         *  @details    The interrupt enable set registers (IESR/IESRH) are used to enable interrupts. Writes of 1 to the bits in
         *              IESR/IESRH set the corresponding interrupt bits in the interrupt enable registers (IER/IERH); writes of 0
         *              have no effect. All DMA/QDMA channels can be set to assert an EDMA3CC completion interrupt to the
         *              CPU on transfer completion, by appropriately configuring the PaRAM entry associated with the channels.
         *              This register is used for the transfer completion interrupt reporting/generating by the EDMA3CC. For more
         *              details on EDMA3CC completion interrupt generation, see EDMA3 Interrupts.
        (offset = 0x1064) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    In      :32;         // bit: 0..31        (W) Interrupt enable clear for channels 32 to 63.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Corresponding bit in the interrupt enable register high (IERH) is
                                                 //                              set (In = 1).]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } IESRH_reg_t;
        
        /*  @brief      Interrupt Pending Register  
         *  @details    If the TCINTEN and/or ITCINTEN bit in the channel option parameter (OPT) is set in the PaRAM entry
         *              associated with the channel (DMA or QDMA), then the EDMA3TC (for normal completion) or the
         *              EDMA3CC (for early completion) returns a completion code on transfer or intermediate transfer
         *              completion. The value of the returned completion code is equal to the TCC bit in OPT for the PaRAM
         *              entry associated with the channel. When an interrupt transfer completion code with TCC = n is detected
         *              by the EDMA3CC, then the corresponding bit is set in the interrupt pending register (IPR.In, if n = 0 to 31;
         *              IPRH.In, if n = 32 to 63). Note that once a bit is set in the interrupt pending registers, it remains set; it is
         *              your responsibility to clear these bits. The bits set in IPR/IPRH are cleared by writing a 1 to the
         *              corresponding bits in the interrupt clear registers (ICR/ICRH). All DMA/QDMA channels can be set to
         *              assert an EDMA3CC completion interrupt to the CPU on transfer completion, by appropriately configuring
         *              the PaRAM entry associated with the channels. This register is used for the transfer completion interrupt
         *              reporting/generating by the EDMA3CC. For more details on EDMA3CC completion interrupt generation,
         *              see EDMA3 Interrupts.
        (offset = 0x1068) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    In      :32;         // bit: 0..31        (R) Interrupt pending for TCC = 0 to 31.
                                                 //                       [0x0 = Interrupt transfer completion code is not detected or was
                                                 //                             cleared.
                                                 //                        0x1 = Interrupt transfer completion code is detected (In = 1, n =
                                                 //                              EDMA3TC[2:0]).]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } IPR_reg_t;
        
        /*  @brief      Interrupt Pending Register High  
         *  @details    If the TCINTEN and/or ITCINTEN bit in the channel option parameter (OPT) is set in the PaRAM entry
         *              associated with the channel (DMA or QDMA), then the EDMA3TC (for normal completion) or the
         *              EDMA3CC (for early completion) returns a completion code on transfer or intermediate transfer
         *              completion. The value of the returned completion code is equal to the TCC bit in OPT for the PaRAM
         *              entry associated with the channel. When an interrupt transfer completion code with TCC = n is detected
         *              by the EDMA3CC, then the corresponding bit is set in the interrupt pending register (IPR.In, if n = 0 to 31;
         *              IPRH.In, if n = 32 to 63). Note that once a bit is set in the interrupt pending registers, it remains set; it is
         *              your responsibility to clear these bits. The bits set in IPR/IPRH are cleared by writing a 1 to the
         *              corresponding bits in the interrupt clear registers (ICR/ICRH). All DMA/QDMA channels can be set to
         *              assert an EDMA3CC completion interrupt to the CPU on transfer completion, by appropriately configuring
         *              the PaRAM entry associated with the channels. This register is used for the transfer completion interrupt
         *              reporting/generating by the EDMA3CC. For more details on EDMA3CC completion interrupt generation,
         *              see EDMA3 Interrupts.
        (offset = 0x106C) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    In      :32;         // bit: 0..31        (R) Interrupt pending for TCC = 32 to 63.
                                                 //                       [0x0 = Interrupt transfer completion code is not detected or was
                                                 //                              cleared.
                                                 //                        0x1 = Interrupt transfer completion code is detected (In = 1, n =
                                                 //                              EDMA3TC[2:0]).]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register 
        } IPRH_reg_t;
        
        /*  @brief     Interrupt Clear Register  
         *  @details   The bits in the interrupt pending registers (IPR/IPRH) are cleared by writing a 1 to the corresponding bits
         *             in the interrupt clear registers(ICR/ICRH). Writes of 0 have no effect. All set bits in IPR/IPRH must be
         *             cleared to allow EDMA3CC to assert additional transfer completion interrupts. All DMA/QDMA channels
         *             can be set to assert an EDMA3CC completion interrupt to the CPU on transfer completion, by
         *             appropriately configuring the PaRAM entry associated with the channels. This register is used for the
         *             transfer completion interrupt reporting/generating by the EDMA3CC. For more details on EDMA3CC
         *             completion interrupt generation, see EDMA3 Interrupts.
        (offset = 0x1070) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    In      :32;         // bit: 0..31        (W) Interrupt clear register for TCC = 0 to 31.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Corresponding bit in the interrupt pending register (IPR) is
                                                 //                              cleared (In = 0).]          
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } ICR_reg_t;

        /*  @brief      Interrupt Clear Register High  
         *  @details    The bits in the interrupt pending registers (IPR/IPRH) are cleared by writing a 1 to the corresponding bits
         *              in the interrupt clear registers(ICR/ICRH). Writes of 0 have no effect. All set bits in IPR/IPRH must be
         *              cleared to allow EDMA3CC to assert additional transfer completion interrupts. All DMA/QDMA channels
         *              can be set to assert an EDMA3CC completion interrupt to the CPU on transfer completion, by
         *              appropriately configuring the PaRAM entry associated with the channels. This register is used for the
         *              transfer completion interrupt reporting/generating by the EDMA3CC. For more details on EDMA3CC
         *              completion interrupt generation, see EDMA3 Interrupts.
        (offset = 0x1074) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    In      :32;         // bit: 0..31        (W) Interrupt clear register for TCC = 32 to 63.
                                                 //                       [0x0 = No effect.
                                                 //                        0x1 = Corresponding bit in the interrupt pending register high (IPRH)
                                                 //                              is cleared (In = 0).]           
            } b;                                 // bit access  
            uint32_t  reg;                       // raw register  
        } ICRH_reg_t;
        
        /*  @brief      Interrupt evaluate Register  
         *  @details    The interrupt evaluate register (IEVAL) is the only register that physically exists in both the global region
         *              and the shadow regions. In other words, the read/write accessibility for the shadow region IEVAL is not
         *              affected by the DMA/QDMA region access registers (DRAEm/DRAEHm, QRAEn/QRAEHn). IEVAL is
         *              needed for robust ISR operations to ensure that interrupts are not missed by the CPU. All DMA/QDMA
         *              channels can be set to assert an EDMA3CC completion interrupt to the CPU on transfer completion, by
         *              appropriately configuring the PaRAM entry associated with the channels. This register is used for the
         *              transfer completion interrupt reporting/generating by the EDMA3CC. For more details on EDMA3CC
         *              completion interrupt generation, see EDMA3 Interrupts.
        (offset = 0x1078) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    EVAL      :1;         // bit: 0       (W) Interrupt evaluate.
                                                  //                  The EDMA3CC completion interrupt that is pulsed depends on which
                                                  //                  IEVAL is being exercised.
                                                  //                  For example, writing to the EVAL bit in IEVAL pulses the global
                                                  //                  completion interrupt, but writing to the EVAL bit in IEVAL0 pulses the
                                                  //                  region 0 completion interrupt.
                                                  //                  [0x0 = No effect.
                                                  //                   0x1 = Causes EDMA3CC completion interrupt to be pulsed, if any
                                                  //                         enabled (IERn/IERHn = 1) interrupts are still pending (IPRn/IPRHn = 1).]
                uint32_t              :31;        // bit: 1..31   (R) Reserved.         
            } b;                                  // bit access  
            uint32_t  reg;                        // raw register  
        } IEVAL_reg_t;
        
        /*  @brief      QDMA Event Register  
         *  @details    The QDMA event register (QER) channel n bit is set (En = 1) when the CPU or any EDMA3 programmer
         *              (including EDMA3) performs a write to the trigger word (using the QDMA channel mapping register
         *              (QCHMAPn)) in the PaRAM entry associated with QDMA channel n (which is also programmed using
         *              QCHMAPn). The En bit is also set when the EDMA3CC performs a link update on a PaRAM address that
         *              matches the QCHMAPn settings. The QDMA event is latched only if the QDMA event enable register
         *              (QEER) channel n bit is also enabled (QEER.En = 1). Once a bit is set in QER, then the corresponding
         *              QDMA event (auto-trigger) is evaluated by the EDMA3CC logic for an associated transfer request
         *              submission to the transfer controllers. For additional conditions that can lead to the setting of QER bits,
         *              see EDMA Overview. The setting of an event is a higher priority relative to clear operations (via
         *              hardware). If set and clear conditions occur concurrently, the set condition wins. If the event was
         *              previously set, then the QDMA event missed register (QEMR) would be set because an event is lost. If the
         *              event was previously clear, then the event remains set and is prioritized for submission to the event
         *              queues. The set bits in QER are only cleared when the transfer request associated with the corresponding
         *              channels has been processed by the EDMA3CC and submitted to the transfer controller. If the En bit is
         *              already set and a QDMA event for the same QDMA channel occurs prior to the original being cleared,
         *              then the second missed event is latched in QEMR (En = 1). QER is part of a set of register that control the
         *              QDMA channels in EDMA3CC. QDMA channels (with the exception of the QDMA queue number register)
         *              consist of a set of registers, each of which have a bit location. Each bit position corresponds to a QDMA
         *              channel number. The QDMA channel registers are accessible via read/writes to the global address range.
         *              They are also accessible via read/writes to the shadow address range. The read/write accessibility in the
         *              shadow region address region is controlled by the QDMA region access registers (QRAEn/QRAEHn).
        (offset = 0x1080) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :8;         // bit: 0..7     (R) QDMA event for channels 0 to 7.
                                                //                   [0x0 = No effect.
                                                //                    0x1 = Corresponding QDMA event is prioritized versus other pending
                                                //                         MA/QDMA events for submission to the EDMA3TC.]
                uint32_t            :24;        // bit: 8..31    (R) Reserved.         
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } QER_reg_t;
        
        /*  @brief      QDMA Event Enable Registerr  
         *  @details    The EDMA3CC provides the option of selectively enabling/disabling each channel in the QDMA event
         *              register (QER) by using the QDMA event enable register (QEER). If any of the event bits in QEER is set
         *              (using the QDMA event enable set register, QEESR), it will enable that corresponding event. Alternatively,
         *              if any event bit in QEER is cleared (using the QDMA event enable clear register, QEECR), it will disable
         *              the corresponding QDMA channel. The QDMA event register will not latch any event for a QDMA channel,
         *              if it is not enabled via QEER. QEER is part of a set of register that control the QDMA channels in
         *              EDMA3CC. QDMA channels (with the exception of the QDMA queue number register) consist of a set of
         *              registers, each of which have a bit location. Each bit position corresponds to a QDMA channel number.
         *              The QDMA channel registers are accessible via read/writes to the global address range. They are also
         *              accessible via read/writes to the shadow address range. The read/write accessibility in the shadow region
         *              address region is controlled by the QDMA region access registers (QRAEn/QRAEHn).
        (offset = 0x1084) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :8;         // bit: 0..7     (R) QDMA event enable for channels 0 to 7.
                                                //                   [0x0 = QDMA channel n is not enabled. QDMA event will not be
                                                //                          recognized and will not latch in the QDMA event register (QER).
                                                //                    0x1 = QDMA channel n is enabled. QDMA events will be recognized
                                                //                          and will get latched in the QDMA event register (QER).]
                uint32_t            :24;        // bit: 8..31    (R) Reserved.          
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } QEER_reg_t;
        
        /*  @brief      QDMA Event Enable Clear Register  
         *  @details    The QDMA event enable register (QEER) cannot be modified by directly writing to the register, to ease the
         *              software burden when multiple tasks are attempting to simultaneously modify these registers. The QDMA
         *              event enable clear register (QEECR) is used to disable events. Writes of 1 to the bits in QEECR clear the
         *              corresponding QDMA channel bits in QEER; writes of 0 have no effect. QEECR is part of a set of register
         *              that control the QDMA channels in EDMA3CC. QDMA channels (with the exception of the QDMA queue
         *              number register) consist of a set of registers, each of which have a bit location. Each bit position
         *              corresponds to a QDMA channel number. The QDMA channel registers are accessible via read/writes to
         *              the global address range. They are also accessible via read/writes to the shadow address range. The
         *              read/write accessibility in the shadow region address region is controlled by the QDMA region access
         *              registers (QRAEn/QRAEHn).
        (offset = 0x1088) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :8;         // bit: 0..7     (R) QDMA event enable clear for channels 0 to 7.
                                                //                   [0x0 = No effect.
                                                //                    0x1 = QDMA event is disabled. Corresponding bit in the QDMA event
                                                //                          enable register (QEER) is cleared (En = 0).]
                uint32_t            :24;        // bit: 8..31    (R) Reserved.           
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } QEECR_reg_t;
        
        /*  @brief      QDMA Event Enable Set Register  
         *  @details    The QDMA event enable register (QEER) cannot be modified by directly writing to the register, to ease the
         *              software burden when multiple tasks are attempting to simultaneously modify these registers. The QDMA
         *              event enable set register (QEESR) is used to enable events. Writes of 1 to the bits in QEESR set the
         *              corresponding QDMA channel bits in QEER; writes of 0 have no effect.
        (offset = 0x108C) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :8;         // bit: 0..7     (R) QDMA event enable set for channels 0 to 7.
                                                //                   [0x0 = No effect.
                                                //                    0x1 = QDMA event is enabled. Corresponding bit in the QDMA event
                                                //                          enable register (QEER) is set (En = 1).]
                uint32_t            :24;        // bit: 8..31    (R) Reserved.           
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } QEESR_reg_t;

        /*  @brief      QDMA Secondary Event Register  
         *  @details    The QDMA secondary event register (QSER) provides information on the state of a QDMA event. If at any
         *              time a bit corresponding to a QDMA channel is set in QSER, that implies that the corresponding QDMA
         *              event is in the queue. Once a bit corresponding to a QDMA channel is set in QSER, the EDMA3CC does
         *              not prioritize additional events on the same QDMA channel. Depending on the condition that lead to the
         *              setting of the QSER bits, either the EDMA3CC hardware or the software (using QSECR) needs to clear
         *              the QSER bits for the EDMA3CC to evaluate subsequent QDMA events on the channel. Based on
         *              whether the associated TR request is valid, or it is a null or dummy TR, the implications on the state of
         *              QSER and the required user actions to submit another QDMA transfer might be different. For additional
         *              conditions that can cause the secondary event registers (QSER\SER) to be set, see EDMA Overview.
         *              QSER is part of a set of register that control the QDMA channels in EDMA3CC. QDMA channels (with the
         *              exception of the QDMA queue number register) consist of a set of registers, each of which have a bit
         *              location. Each bit position corresponds to a QDMA channel number. The QDMA channel registers are
         *              accessible via read/writes to the global address range. They are also accessible via read/writes to the
         *              shadow address range. The read/write accessibility in the shadow region address region is controlled by
         *              the QDMA region access registers (QRAEn/QRAEHn).
        (offset = 0x1090) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :8;         // bit: 0..7     (R) QDMA secondary event register for channels 0 to 7.
                                                //                   [0x0 = QDMA event is not currently stored in the event queue.
                                                //                    0x1 = QDMA event is currently stored in the event queue. EDMA3CC
                                                //                          will not prioritize additional events.]
                uint32_t            :24;        // bit: 8..31    (R) Reserved.           
            } b;                                // bit access  
            uint32_t  reg;                      // raw register  
        } QSER_reg_t;
        
        /*  @brief      QDMA Secondary Event Clear Register  
         *  @details    The QDMA secondary event clear register (QSECR) clears the status of the QDMA secondary event
         *              register (QSER) and the QDMA event register (QER). CPU writes of 1 clear the corresponding set bits in
         *              QSER and QER. Writes of 0 have no effect. Note that this differs from the secondary event clear register
         *              (SECR) operation, which only clears the secondary event register (SER) bits and does not affect the event
         *              registers. QESCR is part of a set of register that control the QDMA channels in EDMA3CC. QDMA
         *              channels (with the exception of the QDMA queue number register) consist of a set of registers, each of
         *              which have a bit location. Each bit position corresponds to a QDMA channel number. The QDMA channel
         *              registers are accessible via read/writes to the global address range. They are also accessible via
         *              read/writes to the shadow address range. The read/write accessibility in the shadow region address region
         *              is controlled by the QDMA region access registers (QRAEn/QRAEHn).
        (offset = 0x1094) [reset = 0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    En      :8;         // bit: 0..7     (W) QDMA secondary event clear register for channels 0 to 7.
                                                //                   [0x0 = No effect.
                                                //                    0x1 = Corresponding bit in the QDMA secondary event register
                                                //                          (QSER) and the QDMA event register (QER) is cleared (En = 0).]
                uint32_t            :24;        // bit: 8..31    (R) Reserved.          
            } b;                                // bit access  
            uint32_t  reg;                      // raw register 
        } QSECR_reg_t;            
        
            
        /******************************************************************************************************************************************/  
        
        /****************************************************** AM335x_EDMA3TC_Type Registers *****************************************************/ 
        
        /******************************************************************************************************************************************/
     
        /*  @brief      Peripheral Identification Register  
         *  @details    Contains the peripheral identification value that uniquely identifies
         *              the EDMA controller. This read-only register provides the JEP106
         *              identification code and part number for the peripheral.
         (offset = 0x00) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    PID      :16;   // bits 0..15  (R) Peripheral identifier uniquely identifies the EDMA3CC and the
                                            //                 specific revision of the EDMA3CC.
                                            //                 Value 0x0 to 0xFFFF_FFFFh.
                                            //                 Reset value for PID[31] to PID[16] is 0x4001.
                                            //                 Peripheral identifier uniquely identifies the EDMA3CC and the
                                            //                 specific revision of the EDMA3CC.
                                            //                 Value 0x0 to 0xFFFF_FFFFh.
                                            //                 Reset value for PID[15] to PID[0] is 0x4C00.
                uint32_t             :16;   // bits 16..31 (R) Reserved          
            } b;                            // bit access 
            uint32_t  reg;                  // raw register
        } PIDTC_reg_t; 
        
        /*  @brief      EDMA3TC Configuration Register  
         *  @details    Configures the transfer controller parameters including FIFO size,
         *              bus width, and register depth. These parameters are fixed by hardware
         *              and are read-only.
         (offset = 0x04) [reset = 224h] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    FIFOSIZE       :3;    // bits 0..2   (R) FIFO size configuration
                                                  //              Indicates the number of 32-bit words in the FIFO
                                                  //              [ 0x4 = 512 byte FIFO
                                                  //                all other = reserved ]
                uint32_t                   :1;    // bit  3      (R) Reserved 
                uint32_t    BUSWIDTH       :2;    // bits 4,5    (R) Bus width configuration
                                                  //              Indicates the data bus width
                                                  //              [ 0x2 = 128-bit
                                                  //                all other = reserved ]
                uint32_t                   :2;    // bits 6,7    (R) Reserved 
                uint32_t    DREGDEPTH      :2;    // bits 8,9    (R) Register file depth
                                                  //              Indicates the number of registers in the register file
                                                  //              [ 0x2 = 4 entry (for TC0, TC1, and TC2)
                                                  //                all other = reserved ]
                uint32_t                   :22;   // bits 10..31 (R) Reserved          
            } b;                                  // bit access 
            uint32_t  reg;                        // raw register
        } TCCFG_reg_t;
        
        /*  @brief      EDMA3TC System Configuration Register  
         *  @details    Controls the power management modes for the transfer controller,
         *              including idle and standby mode configurations.
         (offset = 0x10) [reset = 28h] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t                  :2;   // bits 0,1    (R)  Reserved. 
                uint32_t    IDLEMODE      :2;   // bits 2,3    (RW) Idle mode configuration [see e_SYSC_IDLEMODE]
                uint32_t    STANDBYMODE   :2;   // bits 4,5    (RW) Standby mode configuration [see e_SYSC_STANDBYMODE]
                uint32_t                  :26;  // bits 6..31  (R)  Reserved          
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } SYSCONFIGTC_reg_t;
        
        /* Enums for multi-value fields */
        enum e_SYSC_IDLEMODE : uint32_t
        {
            /*  Force-idle mode: The transfer controller is forced into idle mode immediately
             *  regardless of activity. All clocks are gated off in this mode.
             */
            SYSC_FORCE_IDLE     = 0x0,
            /*  No-idle mode: The transfer controller is never placed in idle mode.
             *  Clocks remain active regardless of activity.
             */
            SYSC_NOIDLE         = 0x1,
            /*  Smart-idle mode: The transfer controller is placed in idle mode when
             *  there is no transfer activity. Clocks are gated off when idle.
             */
            SYSC_SMARTIDLE      = 0x2,
        };
        
        enum e_SYSC_STANDBYMODE : uint32_t
        {
            /*  Force-standby mode: The transfer controller is forced into standby mode
             *  immediately. All clocks and power domains are turned off.
             */
            SYSC_FORCE_STBY     = 0x0,
            /*  No-standby mode: The transfer controller is never placed in standby mode.
             *  Power domains remain active.
             */
            SYSC_NOSTBY         = 0x1,
            /*  Smart-standby mode: The transfer controller is placed in standby mode
             *  when there is no transfer activity. Power domains are turned off when idle.
             */
            SYSC_SMARTSTBY      = 0x2,
        };
        
        /*  @brief      EDMA3TC Channel Status Register  
         *  @details    Provides status information about the transfer controller,
         *              including activity indicators and programming status.
         (offset = 0x100) [reset = 100] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    PROGBUSY      :1;     // bit  0      (R) Program register set busy
                                                  //                 [0x0 = Program set idle and is available for programming by the
                                                  //                        EDMA3CC.
                                                  //                 0x1 = Program set busy]
                uint32_t    SRCACTV       :1;     // bit  1      (R) Source active state
                                                  //                 [0x0 = Source controller is idle. Source active register set contains a
                                                  //                        previously processed transfer request.
                                                  //                  0x1 = Source controller is busy servicing a transfer request]
                uint32_t    WSACTV        :1;     // bit  2      (R) Write status active
                                                  //                 [0x0 = Write status is not pending. Write status has been received for
                                                  //                        all previously issued write commands.
                                                  //                  0x1 = Write status is pending. Write status has not been received for
                                                  //                        all previously issued write commands.]
                uint32_t                  :1;     // bit  3      (R) Reserved.
                uint32_t    DSTACTV       :3;     // bits 4..6   (R) Destination active state. [ see e_DSTACTV_state ]
                uint32_t                  :1;     // bits 7..11  (R) Reserved.
                uint32_t    DFSTRTPTR     :1;     // bits 12,13  (R) Destination FIFO start pointer.
                                                  //                 Represents the offset to the head entry of the destination register
                                                  //                 FIFO, in units of entries.
                                                  //                 Values 0x0..0x3.
                uint32_t                  :18;    // bits 14..31 (R) Reserved          
            } b;                                  // bit access 
            uint32_t  reg;                        // raw register
        } TCSTAT_reg_t;
        
        enum e_DSTACTV_state : uint32_t
        {
                        /*
                         * Specifies the number of transfer requests (TRs) that are resident in
                         * the destination register FIFO at a given instant.
                         * This bit field can be primarily used for advanced debugging.
                         * Legal values are constrained by the destination register FIFO depth
                         * parameterization (DSTREGDEPTH) parameter. 
                         */
            TR_EMPTY  = 0x0,    // Destination FIFO is empty.
            TRs_NUM_1 = 0x1,    // Destination FIFO contains 1 TR.
            TRs_NUM_2 = 0x2,    // Destination FIFO contains 2 TRs.
            TRs_NUM_3 = 0x3,    // Destination FIFO contains 3 TRs.
            TRs_NUM_4 = 0x4     // Destination FIFO contains 4 TRs. (Full if DSTREGDEPTH==4).
                                // If the destination register FIFO is empty, then any TR written to Prog
                                // Set immediately transitions to the destination register FIFO. If the
                                // destination register FIFO is not empty and not full, then any TR
                                // written to Prog Set immediately transitions to the destination register
                                // FIFO set if the source active state (SRCACTV) bit is set to idle. If the
                                // destination register FIFO is full, then TRs cannot transition to the
                                // destination register FIFO. The destination register FIFO becomes not
                                // full when the TR at the head of the destination register FIFO is
                                // completed.
        
            /* all other values reserved */
        };      
        
        
        /*  @brief      Error Register  
         *  @details    Reports error conditions detected by the transfer controller,
         *              including bus errors and transfer errors.
         (offset = 0x120) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    BUSERR      :1;     // bit  0      (R) Bus error event.
                                                //                 [0x0 = Condition is not detected.
                                                //                  0x1 = EDMA3TC has detected an error at source or destination
                                                //                        address. Error information can be read from the error details register
                                                //                        (ERRDET).]
                uint32_t                :1;     // bit  1      (R) Reserved. 
                uint32_t    TRERR       :1;     // bit  2      (R) Transfer request (TR) error event.
                                                //                 [0x0 = Condition is not detected.
                                                //                  0x1 = TR detected that violates constant addressing mode transfer
                                                //                        (SAM or DAM is set) alignment rules or has ACNT or BCNT == 0.]
                uint32_t    MMRAERR     :1;     // bit  3      (R) MMR address error.
                                                //                 [0x0 = Condition is not detected.
                                                //                  0x1 = User attempted to read or write to an invalid address in
                                                //                        configuration memory map.]
                uint32_t                :28;    // bits 4..31  (R) Reserved          
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } ERRSTAT_reg_t;
        
        /*  @brief      Error Enable Register  
         *  @details    Controls which error conditions generate interrupts,
         *              allowing selective enabling of error reporting.
         (offset = 0x124) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    BUSERR      :1;     // bit  0      (RW) Interrupt enable for bus error (BUSERR).
                                                //                  [0x0 = BUSERR is disabled.
                                                //                   0x1 = BUSERR is enabled and contributes to the state of EDMA3TC
                                                //                         error interrupt generation.]
                uint32_t                :1;     // bit  1      (R)  Reserved. 
                uint32_t    TRERR       :1;     // bit  2      (RW) Interrupt enable for transfer request error (TRERR).
                                                //                  [0x0 = TRERR is disabled.
                                                //                   0x1 = TRERR is enabled and contributes to the state of EDMA3TC
                                                //                         error interrupt generation.]
                uint32_t    MMRAERR     :1;     // bit  3      (RW) Interrupt enable for MMR address error (MMRAERR).
                                                //                  [0x0 = MMRAERR is disabled.
                                                //                   0x1 = MMRAERR is enabled and contributes to the state of
                                                //                         EDMA3TC error interrupt generation]
                uint32_t                :28;    // bits 4..31  (R)  Reserved           
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } ERREN_reg_t; 
        
        /*  @brief      Error Clear Register  
         *  @details    Allows clearing of error status flags by writing 1 to the
         *              corresponding bit positions.
         (offset = 0x128) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    BUSERR      :1;     // bit  0      (W) Interrupt clear for the BUSERR bit in the error status register
                                                //                 (ERRSTAT).
                                                //                 [0x0 = No effect.
                                                //                  0x1 = Clears the BUSERR bit in ERRSTAT and clears the error
                                                //                        details register (ERRDET).]
                uint32_t                :1;     // bit  1      (R) Reserved. 
                uint32_t    TRERR       :1;     // bit  2      (W) Interrupt enable clear for the TRERR bit in the error status register
                                                //                 (ERRSTAT).
                                                //                 [0x0 = No effect.
                                                //                  0x1 = Clears the TRERR bit in ERRSTAT but does not clear the error
                                                //                        details register (ERRDET).]
                uint32_t    MMRAERR     :1;     // bit  3      (W) Interrupt enable clear for the MMRAERR bit in the error status
                                                //                 register (ERRSTAT).
                                                //                 [0x0 = No effect.
                                                //                  0x1 = Clears the MMRAERR bit in ERRSTAT but does not clear the
                                                //                        error details register (ERRDET).]
                uint32_t                :28;    // bits 4..31  (R) Reserved          
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } ERRCLR_reg_t;
        
        /*  @brief      Error Details Register  
         *  @details    Provides detailed information about error conditions,
         *              including status codes and transfer controller channel information.
         (offset = 0x12C) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    STAT      :4;     // bits 0..3    (R) Transaction status.
                                              //                  Stores the nonzero status/error code that was detected on the read
                                              //                  status or write status bus.
                                              //                  If read status and write status are returned on the same cycle, then
                                              //                  the EDMA3TC chooses nonzero version.
                                              //                  If both are nonzero, then the write status is treated as higher priority.
                                              //                  [0x0 = No error.
                                              //                   0x1 = From 0x1 to 0x7, Read error.
                                              //                   0x8 = From 0x8 to 0xF, Write error.]
                uint32_t              :4;     // bits 4..7    (R) Reserved.
                uint32_t    TCC       :6;     // bits 8..13   (R) Transfer complete code.
                                              //                  Contains the TCC value in the channel options parameter (OPT)
                                              //                  programmed by the channel controller for the read or write
                                              //                  transaction that resulted in an error.
                uint32_t              :2;     // bits 14,15   (R) Reserved.
                uint32_t    TCINTEN   :1;     // bit  16      (R) Transfer completion interrupt enable.
                                              //                  Contains the TCINTEN value in the channel options parameter
                                              //                  (OPT) programmed by the channel controller for the read or write
                                              //                  transaction that resulted in an error
                uint32_t    TCCHEN    :1;     // bit  17      (R) Transfer completion chaining enable.
                                              //                  Contains the TCCHEN value in the channel options parameter
                                              //                  (OPT) programmed by the channel controller for the read or write
                                              //                  transaction that resulted in an error.
                uint32_t              :14;    // bits 18..31  (R) Reserved          
            } b;                              // bit access 
            uint32_t  reg;                    // raw register
        } ERRDET_reg_t;
        
        /*  @brief      Error Interrupt Command Register  
         *  @details    Controls error evaluation and handling by the transfer controller.
         *              Writing 1 to the EVAL bit triggers error evaluation.
         (offset = 0x130) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    EVAL      :1;     // bit  0      (W) Error evaluate
                                              //                 [0x0 = No effect
                                              //                  0x1 = EDMA3TC error line is pulsed if any of the error status register
                                              //                        (ERRSTAT) bits are set.]
                uint32_t              :31;    // bits 1..31  (R) Reserved          
            } b;                              // bit access 
            uint32_t  reg;                    // raw register
        } ERRCMD_reg_t;
        
        /*  @brief      Read Rate Register  
         *  @details    The EDMA3 transfer controller issues read commands at a rate controlled by the read rate register
         *              (RDRATE). The RDRATE defines the number of idle cycles that the read controller must wait before
         *              issuing subsequent commands. This applies both to commands within a transfer request packet (TRP)
         *              and for commands that are issued for different transfer requests (TRs). For instance, if RDRATE is set to
         *              4 cycles between reads, there are 3 inactive cycles between reads. RDRATE allows flexibility in transfer
         *              controller access requests to an endpoint. For an application, RDRATE can be manipulated to slow down
         *              the access rate, so that the endpoint may service requests from other masters during the inactive
         *              EDMA3TC cycles. Note: The RDRATE value for a transfer controller is expected to be static, as it is
         *              decided based on the application requirement. It is not recommended to change the RDRATE value on
         *              the fly.
         (offset = 0x140) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    RDRATE      :3;     // bits 0..2    (W) Read rate.
                                                //                  Controls the number of cycles between read commands.
                                                //                  This is a global setting that applies to all TRs for this EDMA3TC. [ see e_READRATE ]
                uint32_t                :29;    // bits 3..31   (R) Reserved          
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } RDRATE_reg_t;
        
        enum e_READRATE : uint32_t
        {
           READ_FAST     = 0x0, // Reads issued as fast as possible.
           READ_4CYCLES  = 0x1, // 4 cycles between reads.
           READ_8CYCLES  = 0x2, // 8 cycles between reads.
           READ_16CYCLES = 0x3, // 16 cycles between reads.
           READ_32CYCLES = 0x4  // 32 cycles between reads.
        
           /* all other values reserved !!! */
        };
        
        /*  @brief      Source Active Options Register  
         *  @details    The Source Active Options Register (SAOPT) is an EDMA3TC channel register. This EDMA3TC channel
         *              register is part of the Source Active Register Set. It is read-only and provided to facilitate debugging by
         *              providing a window into how the transfer controller (TC) was programmed by the channel controller (CC),
         *              as well as showing the status of the transfer controller (TC) during a transfer.
         (offset = 0x240) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    SAM         :1;     // bit  0      (R) Source address mode within an array
                                                //                 [0x0 = Increment (INCR) mode. Source addressing within an array
                                                //                        increments.
                                                //                  0x1 = Constant addressing (CONST) mode. Source addressing within
                                                //                        an array wraps around upon reaching FIFO width.]
                uint32_t    DAM         :1;     // bit  1      (R) Destination address mode within an array
                                                //                 [0x0 = Increment (INCR) mode. Destination addressing within an array
                                                //                        increments.
                                                //                  0x1 = Constant addressing (CONST) mode. Destination addressing
                                                //                        within an array wraps around upon reaching FIFO width.]
                uint32_t                :2;     // bits 2,3    (R) Reserved.
                uint32_t    PRI         :3;     // bits 4..6   (R) Transfer priority.
                                                //                 Reflects the values programmed in the QUEPRI register in the EDMACC. [ see e_PRI ]
                uint32_t                :1;     // bit  7      (R) Reserved.
                uint32_t    FWID        :3;     // bits 8..10  (R) FIFO width.
                                                //                 Applies if either SAM or DAM is set to constant addressing mode. [see e_FIFO_width ]
                uint32_t                :1;     // bit  11     (R) Reserved.
                uint32_t    TCC         :6;     // bits 12..17 (R) Transfer complete code.
                                                //                 This 6 bit code is used to set the relevant bit in CER or IPR of the EDMA3PCC module.
                uint32_t                :2;     // bits 18,19  (R) Reserved.
                uint32_t    TCINTEN     :1;     // bit  20     (R) Transfer complete interrupt enable.
                                                //                 [0x0 = Transfer complete interrupt is disabled.
                                                //                  0x1 = Transfer complete interrupt is enabled.]
                uint32_t                :1;     // bit  21     (R) Reserved.
                uint32_t    TCCHEN      :1;     // bit  22     (R) Transfer complete chaining enable
                                                //                 [0x0 = Transfer complete chaining is disabled.
                                                //                  0x1 = Transfer complete chaining is enabled.]
                uint32_t                :9;     // bits 23..31 (R) Reserved          
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } SAOPT_reg_t; 
        
        
        enum e_PRI : uint32_t
        {
           PRIORITY_0 = 0x0, // Priority 0 - Highest priority
           PRIORITY_1 = 0x1, // 
           PRIORITY_2 = 0x2, // 
           PRIORITY_3 = 0x3, // 
           PRIORITY_4 = 0x4, // 
           PRIORITY_5 = 0x5, // 
           PRIORITY_6 = 0x6, // 
           PRIORITY_7 = 0x7, // Priority 7 - Lowest priority
        };
        
        enum e_FIFO_width : uint32_t
        {
           FIFOw_8bit   = 0x0, // FIFO width is 8-bit.
           FIFOw_16bit  = 0x1, // FIFO width is 16-bit.
           FIFOw_32bit  = 0x2, // FIFO width is 32-bit.
           FIFOw_64bit  = 0x3, // FIFO width is 64-bit.
           FIFOw_128bit = 0x4, // FIFO width is 128-bit.
           FIFOw_256bit = 0x5, // FIFO width is 256-bit.
        
           /* all other values reserved !!! */
        };
        
        
        /*  @brief      Source Active Source Address Register  
         *  @details    The Source Active Source Address Register (SASRC) is an EDMA3TC channel register. This EDMA3TC
         *              channel register is part of the Source Active Register Set. It is read-only and provided to facilitate
         *              debugging by providing a window into how the transfer controller (TC) was programmed by the channel
         *              controller (CC), as well as showing the status of the transfer controller (TC) during a transfer.
         (offset = 0x244) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    SADDR      :32;     // bits 0..31  (R) Source address for Source Active Register Set.
                                                //                 EDMA3TC updates value according to source addressing mode
                                                //                 (SAM bit in the source active options register, SAOPT).
                                                //                 This register does not update during a transfer.
                                                //                 Value 0x0 to 0xFFFF.         
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } SASRC_reg_t;
        
        /*  @brief      Source Active Count Register  
         *  @details    The Source Active Count Register (SACNT) is an EDMA3TC channel register. This EDMA3TC channel
         *              register is part of the Source Active Register Set. It is read-only and provided to facilitate debugging by
         *              providing a window into how the transfer controller (TC) was programmed by the channel controller (CC),
         *              as well as showing the status of the transfer controller (TC) during a transfer.
         (offset = 0x248) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    ACNT      :16;     // bits 0..15   (R) A dimension count remaining for the Source Active Register Set.
                                               //                  Number of bytes to be transferred in first dimension.
                                               //                  Represents the amount of data remaining to be read.
                                               //                  TC decrements ACNT as necessary after each read command is
                                               //                  issued.
                                               //                  The final value should be 0 when TR is complete.
                uint32_t    BCNT      :16;     // bits 16..31  (R) B dimension count remaining for the Source Active Register Set.
                                               //                  Number of arrays to be transferred, where each array is ACNT in
                                               //                  length.
                                               //                  TC decrements BCNT as necessary after each read command is
                                               //                  issued.
                                               //                  The final value should be 0 when TR is complete.
                                               //                  Note that BCNT is always read as 0x0 in the Source Address
                                               //                  Register Set.          
            } b;                               // bit access 
            uint32_t  reg;                     // raw register
        } SACNT_reg_t;
        
        /*  @brief      Source Active Destination Address Register  
         *  @details    The Source Active Destination Address Register (SADST) is an EDMA3TC channel register. This
         *              EDMA3TC channel register is part of the Source Active Register Set. It is read-only and provided to
         *              facilitate debugging by providing a window into how the transfer controller (TC) was programmed by the
         *              channel controller (CC), as well as showing the status of the transfer controller (TC) during a transfer.
         *              Note: Destination address is not applicable for Source Active Register Set. Read returns 0.
         (offset = 0x24C) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t  RESERVED       :32;  // bits 0..31 (R) Reserved          
            } b;                               // bit access 
            uint32_t  reg;                     // raw register
        } SADST_reg_t;
        
        /*  @brief      Source Active Source B-Index Register  
         *  @details    The Source Active Source B-Dimension Index Register (SABIDX) is an EDMA3TC channel register. This
         *              EDMA3TC channel register is part of the Source Active Register Set. It is read-only and provided to
         *              facilitate debugging by providing a window into how the transfer controller (TC) was programmed by the
         *              channel controller (CC), as well as showing the status of the transfer controller (TC) during a transfer.
         (offset = 0x250) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    SBIDX      :16;     // bits 0..15   (R) B-Index offset between source arrays.
                                                //                  Represents the offset in bytes between the starting address of each
                                                //                  source array (there are BCNT arrays of ACNT elements).
                                                //                  SBIDX is always used regardless of whether SAM is in Increment or
                                                //                  FIFO mode.
                                                //                  Value 0x0 to 0xFFFF.
                uint32_t    DBIDX      :16;     // bits 16..31  (R) B-Index offset between destination arrays.
                                                //                  Represents the offset in bytes between the starting address of each
                                                //                  destination array (there are BCND arrays of ACNT elements).
                                                //                  DBIDX is always used regardless of whether DAM is in Increment or
                                                //                  FIFO mode.           
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } SABIDX_reg_t;
        
        /*  @brief      Source Active Memory Protection Proxy Register  
         *  @details    The Source Active Memory Protection Proxy Register (SAMPPRXY) is an EDMA3TC channel register.
         *              This EDMA3TC channel register is part of the Source Active Register Set. It is read-only and provided to
         *              facilitate debugging by providing a window into how the transfer controller (TC) was programmed by the
         *              channel controller (CC), as well as showing the status of the transfer controller (TC) during a transfer.
         (offset = 0x254) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    PRIVID      :4;     // bits 0..3   (R) Privilege ID.
                                                //                 This contains the privilege ID of the host that set up the parameter
                                                //                 entry in the channel controller.
                                                //                 This field is set up when the associated TR is submitted to the
                                                //                 EDMA3TC.
                                                //                 This PRIVID value is used while issuing read and write commands to
                                                //                 the target endpoints so that the target endpoints can perform
                                                //                 memory protection checks based on the PRIVID of the host that set
                                                //                 up the DMA transaction.
                                                //                 Value 0x0 to 0xF.
                uint32_t                :4;     // bits 4..7   (R) Reserved.
                uint32_t    PRIV        :1;     // bit  8      (R) Privilege level.
                                                //                 The privilege level used by the host to set up the parameter entry in
                                                //                 the channel controller.
                                                //                 This field is set up when the associated TR is submitted to the
                                                //                 EDMA3TC.
                                                //                 The privilege ID is used while issuing read and write command to the
                                                //                 target endpoints so that the target endpoints can perform memory
                                                //                 protection checks based on the PRIV of the host that set up the
                                                //                 DMA transaction.
                                                //                 [0x0 = User-level privilege.
                                                //                  0x1 = Supervisor-level privilege.]
                uint32_t                :23;    // bits 9..31  (R) Reserved           
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } SAMPPRXY_reg_t; 
        
        /*  @brief      Source Active Count Reload Registerr  
         *  @details    The Source Active Count Reload Register (SACNTRLD) is an EDMA3TC channel register. This
         *              EDMA3TC channel register is part of the Source Active Register Set. It is read-only and provided to
         *              facilitate debugging by providing a window into how the transfer controller (TC) was programmed by the
         *              channel controller (CC), as well as showing the status of the transfer controller (TC) during a transfer.
         (offset = 0x258) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    ACNTRLD      :16;     // bits 0..15  (R) A-count reload value.
                                                  //                 Represents the originally programmed value of ACNT.
                                                  //                 The reload value is used to reinitialize ACNT after each array is
                                                  //                 serviced (that is, ACNT decrements to 0) by the source offset in
                                                  //                 bytes between the starting address or each source array (there are
                                                  //                 BCNT arrays of ACNT bytes).
                                                  //                 Value 0x0 to 0xFFFF.
                uint32_t                 :16;     // bits 16..31 (R) Reserved          
            } b;                                  // bit access 
            uint32_t  reg;                        // raw register
        } SACNTRLD_reg_t;
        
        /*  @brief      Source Active Source Address B-Reference Register  
         *  @details    The Source Active Source Address B-Reference Register (SASRCBREF) is an EDMA3TC channel
         *              register. This EDMA3TC channel register is part of the Source Active Register Set. It is read-only and
         *              provided to facilitate debugging by providing a window into how the transfer controller (TC) was
         *              programmed by the channel controller (CC), as well as showing the status of the transfer controller (TC)
         *              during a transfer.
         (offset = 0x25C) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    SADDRBREF      :32;     // bits 0..31 (R) Source address B-reference.
                                                    //                Represents the starting address for the array currently being read.
                                                    //                The next array's starting address is calculated as the reference
                                                    //                address plus the source b-idx value.
                                                    //                Value 0x0 to 0xFFFF_FFFF.           
            } b;                                    // bit access 
            uint32_t  reg;                          // raw register
        } SASRCBREF_reg_t;
        
        /*  @brief      Source Active Destination Address B-Reference Register  
         *  @details    The Source Active Destination Address B-Reference Register (SADSTBREF) is an EDMA3TC channel
         *              register. This EDMA3TC channel register is part of the Source Active Register Set. It is read-only and
         *              provided to facilitate debugging by providing a window into how the transfer controller (TC) was
         *              programmed by the channel controller (CC), as well as showing the status of the transfer controller (TC)
         *              during a transfer.
         *              Note: Destination address is not applicable for Source Active Register Set. Read returns 0.
         (offset = 0x260) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t   RESERVED      :32;    // bits 0..31 (R) Reserved          
            } b;                                 // bit access 
            uint32_t  reg;                       // raw register
        } SADSTBREF_reg_t;
        
        /*  @brief      Destination FIFO Set Count Reload  
         *  @details    The Destination FIFO Count Reload Register (DFCNTRLD) is an EDMA3TC channel register. This
         *              EDMA3TC channel register is part of the Destination Register FIFO Register Set. It is read-only and
         *              provided to facilitate debugging by providing a window into how the transfer controller (TC) was
         *              programmed by the channel controller (CC), as well as showing status of the transfer controller (TC)
         *              during a transfer. The number of destination FIFO register sets depends on the destination FIFO depth.
         *              TC0, TC1, and TC2 each have a destination FIFO depth of 4, so there are four sets of destination FIFO
         *              registers for each of these transfer controllers.
         (offset = 0x280) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    ACNTRLD      :16;     // bits 0..15 (R) A-count reload value for the Destination FIFO Register Set.
                                                  //                Represents the originally programmed value of ACNT.
                                                  //                The reload value is used to reinitialize ACNT after each array is
                                                  //                serviced (that is, ACNT decrements to 0) by the source offset in
                                                  //                bytes between the starting address of each source array (there are
                                                  //                BCNT arrays of ACNT bytes).
                                                  //                Value 0x0 to 0xFFFF.
                uint32_t                 :16;     // bits 16..31 (R) Reserved           
            } b;                                  // bit access 
            uint32_t  reg;                        // raw register
        } DFCNTRLD_reg_t;
        
        /*  @brief      Destination FIFO Set Destination Address B Reference Register  
         *  @details    The Destination FIFO Source Address B-Reference Register (DFSRCBREF) is an EDMA3TC channel
         *              register. This EDMA3TC channel register is part of the Destination Register FIFO Register Set. It is readonly
         *              and provided to facilitate debugging by providing a window into how the transfer controller (TC) was
         *              programmed by the channel controller (CC), as well as showing status of the transfer controller (TC)
         *              during a transfer. The number of destination FIFO register sets depends on the destination FIFO depth.
         *              TC0, TC1, and TC2 each have a destination FIFO depth of 4, so there are four sets of destination FIFO
         *              registers for each of these transfer controllers.
         *              Note: Source address reference is not applicable for Destination FIFO Register Set. Read returns 0.
         (offset = 0x284) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t   RESERVED    :32;      // bits 0..31 (R) Reserved          
            } b;                                 // bit access 
            uint32_t  reg;                       // raw register
        } DFSRCBREF_reg_t; 
        
        /*  @brief      Destination FIFO Set Destination Address B Reference Register 
         *  @details    The Destination FIFO Destination Address B-Reference Register (DFDSTBREF) is an EDMA3TC channel
         *              register. This EDMA3TC channel register is part of the Destination Register FIFO Register Set. It is readonly
         *              and provided to facilitate debugging by providing a window into how the transfer controller (TC) was
         *              programmed by the channel controller (CC), as well as showing status of the transfer controller (TC)
         *              during a transfer. The number of destination FIFO register sets depends on the destination FIFO depth.
         *              TC0, TC1, and TC2 each have a destination FIFO depth of 4, so there are four sets of destination FIFO
         *              registers for each of these transfer controllers.
         (offset = 0x288) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t   DADDRBREF  :32;      // bits 0..31 (R) Destination address reference for the destination FIFO register set.
                                                //                Represents the starting address for the array currently being written.
                                                //                The next array's starting address is calculated as the reference
                                                //                address plus the destination B-Index value.
                                                //                Value 0x0 to 0xFFFF_FFFF.           
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } DFDSTBREF_reg_t;
        
        /*  @brief      Destination FIFO Options Register 0..3  
         *  @details    The Destination FIFO Options Register (DFOPT) is an EDMA3TC channel register. This EDMA3TC
         *              channel register is part of the Destination Register FIFO Register Set. It is read-only and provided to
         *              facilitate debugging by providing a window into how the transfer controller (TC) was programmed by the
         *              channel controller (CC), as well as showing status of the transfer controller (TC) during a transfer. The
         *              number of destination FIFO register sets depends on the destination FIFO depth. TC0, TC1, and TC2
         *              each have a destination FIFO depth of 4, so there are four sets of destination FIFO registers for each of
         *              these transfer controllers.
         (offset = 0x300,0x340,0x380,0x3C0) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    SAM         :1;     // bit  0      (R) Source address mode within an array
                                                //                 [0x0 = Increment (INCR) mode. Source addressing within an array
                                                //                        increments.
                                                //                  0x1 = Constant addressing (CONST) mode. Source addressing within
                                                //                        an array wraps around upon reaching FIFO width.]
                uint32_t    DAM         :1;     // bit  1      (R) Destination address mode within an array
                                                //                 [0x0 = Increment (INCR) mode. Destination addressing within an array
                                                //                        increments.
                                                //                  0x1 = Constant addressing (CONST) mode. Destination addressing
                                                //                        within an array wraps around upon reaching FIFO width.]
                uint32_t                :2;     // bits 2,3    (R) Reserved.
                uint32_t    PRI         :3;     // bits 4..6   (R) Transfer priority [ see e_PRI ]
                uint32_t                :1;     // bit  7      (R) Reserved.
                uint32_t    FWID        :3;     // bits 8..10  (R) FIFO width.
                                                //                 Applies if either SAM or DAM is set to constant addressing mode. [see e_FIFO_width ]
                uint32_t                :1;     // bit  11     (R) Reserved.
                uint32_t    TCC         :6;     // bits 12..17 (R) Transfer complete code.
                                                //                 This 6 bit code is used to set the relevant bit in CER or IPR of the
                                                //                 EDMA3PCC module.
                uint32_t                :2;     // bits 18,19  (R) Reserved.
                uint32_t    TCINTEN     :1;     // bit  20     (R) Transfer complete interrupt enable.
                                                //                 [0x0 = Transfer complete interrupt is disabled.
                                                //                  0x1 = Transfer complete interrupt is enabled.]
                uint32_t                :1;     // bit  21     (R) Reserved.
                uint32_t    TCCHEN      :1;     // bit  22     (R) Transfer complete chaining enable
                                                //                 [0x0 = Transfer complete chaining is disabled
                                                //                  0x1 = Transfer complete chaining is enabled]
                uint32_t                :9;     // bits 23..31 (R) Reserved           
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } DFOPT_reg_t;
        
        /*  @brief      Destination FIFO Source Address Register 0..3  
         *  @details    The Destination FIFO Source Address Register (DFSRC) is an EDMA3TC channel register. This
         *              EDMA3TC channel register is part of the Destination Register FIFO Register Set. It is read-only and
         *              provided to facilitate debugging by providing a window into how the transfer controller (TC) was
         *              programmed by the channel controller (CC), as well as showing status of the transfer controller (TC)
         *              during a transfer. The number of destination FIFO register sets depends on the destination FIFO depth.
         *              TC0, TC1, and TC2 each have a destination FIFO depth of 4, so there are four sets of destination FIFO
         *              registers for each of these transfer controllers.
         *              Note: Source address reference is not applicable for Destination FIFO Register Set. Read returns 0.
         (offset = 0x304,0x344,0x384,0x3C4) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    RESERVED    :32;    // bits 0..32 (R) Reserved         
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } DFSRC_reg_t;
        
        /*  @brief      Destination FIFO Count Register 0..3  
         *  @details    The Destination FIFO Count Register (DFCNT) is an EDMA3TC channel register. This EDMA3TC channel
         *              register is part of the Destination Register FIFO Register Set. It is read-only and provided to facilitate
         *              debugging by providing a window into how the transfer controller (TC) was programmed by the channel
         *              controller (CC), as well as showing status of the transfer controller (TC) during a transfer. The number of
         *              destination FIFO register sets depends on the destination FIFO depth. TC0, TC1, and TC2 each have a
         *              destination FIFO depth of 4, so there are four sets of destination FIFO registers for each of these transfer
         *              controllers.
         (offset = 0x308,0x348,0x388,0x3C8) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {    
                uint32_t    ACNT      :16;    // bits 0..15  (R) A-dimension count remaining for Destination Register Set.
                                              //                 Represents the amount of data remaining to be written.
                                              //                 For the final TR in the Destination Register FIFO: TC decrements
                                              //                 ACNT and BCNT as necessary after each write dataphase is issued.
                                              //                 The final value should be 0 when TR is complete.
                                              //                 For a non-final TR in the Destination Register FIFO: CNT will hold
                                              //                 the originally programmed value or the optimized BCNT value after
                                              //                 2D optimization calculation.
                                              //                 Value 0x0 to 0xFFFF.
                uint32_t    BCNT      :16;    // bits 16..31 (R) B-dimension count remaining for Destination Register Set.
                                              //                 Represents the amount of data remaining to be written.
                                              //                 For the final TR in the Destination Register FIFO: TC decrements
                                              //                 ACNT and BCNT as necessary after each write dataphase is issued.
                                              //                 The final value should be 0 when TR is complete.
                                              //                 For a non-final TR in the Destination Register FIFO: CNT will hold
                                              //                 the originally programmed value or the optimized BCNT value after
                                              //                 2D optimization calculation.         
            } b;                              // bit access 
            uint32_t  reg;                    // raw register
        } DFCNT_reg_t;
        
        /*  @brief      Destination FIFO Destination Address Register 0..3  
         *  @details    The Destination FIFO Destination Address Register (DFDST) is an EDMA3TC channel register. This
         *              EDMA3TC channel register is part of the Destination Register FIFO Register Set. It is read-only and
         *              provided to facilitate debugging by providing a window into how the transfer controller (TC) was
         *              programmed by the channel controller (CC), as well as showing status of the transfer controller (TC)
         *              during a transfer. The number of destination FIFO register sets depends on the destination FIFO depth.
         *              TC0, TC1, and TC2 each have a destination FIFO depth of 4, so there are four sets of destination FIFO
         *              registers for each of these transfer controllers.
         (offset = 0x30C,0x34C,0x38C,0x3CC) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    DADDR      :32;     // bits 0..31 (R) Destination address for the destination FIFO register set.
                                                //                TC updates the value according to both the destination addressing
                                                //                mode (OPT.SAM) or destination index value (BIDX.DBIDX) after
                                                //                each write command is issued.
                                                //                When a TR is complete, the final value should be the address of the
                                                //                last write command issued.
                                                //                Note: If DAM == CONST, the 'active' address will increment
                                                //                internally as if the transfer were an 'Increment' transfer.
                                                //                The address issued on the write command interface will correctly
                                                //                issue the same address programmed by the user.           
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } DFDST_reg_t; 
        
        /*  @brief      Destination FIFO BIDX Register 0..3  
         *  @details    The Destination FIFO B-Index Register (DFBIDX) is an EDMA3TC channel register. This EDMA3TC
         *              channel register is part of the Destination Register FIFO Register Set. It is read-only and provided to
         *              facilitate debugging by providing a window into how the transfer controller (TC) was programmed by the
         *              channel controller (CC), as well as showing status of the transfer controller (TC) during a transfer. The
         *              number of destination FIFO register sets depends on the destination FIFO depth. TC0, TC1, and TC2
         *              each have a destination FIFO depth of 4, so there are four sets of destination FIFO registers for each of
         *              these transfer controllers.
         (offset = 0x310,0x350,0x390,0x3D0) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    SBIDX      :16;    // bits 0..15  (R) B-Index offset between source arrays for the Destination FIFO
                                               //                 Register Set.
                                               //                 Represents the offset in bytes between the starting address of each
                                               //                 source array (there are BCNT arrays of ACNT elements).
                                               //                 SBIDX is always used regardless of whether SAM is in Increment or
                                               //                 FIFO mode.
                uint32_t    DBIDX      :16;    // bits 16..31 (R) B-Index offset between destination arrays for the Destination FIFO
                                               //                 Register Set.
                                               //                 Represents the offset in bytes between the starting address of each
                                               //                 destination array (there are BCNT arrays of ACNT elements).
                                               //                 DBIDX is always used regardless of whether DAM is in Increment or
                                               //                 FIFO mode.
                                               //                 Value 0x0 to 0xFFFF.         
            } b;                               // bit access 
            uint32_t  reg;                     // raw register
        } DFBIDX_reg_t;
        
        /*  @brief      Destination FIFO Memory Protection Proxy Register 0..3  
         *  @details    The Destination FIFO Memory Protection Proxy Register (DFMPPRXY) is an EDMA3TC channel register.
         *              This EDMA3TC channel register is part of the Destination Register FIFO Register Set. It is read-only and
         *              provided to facilitate debugging by providing a window into how the transfer controller (TC) was
         *              programmed by the channel controller (CC), as well as showing status of the transfer controller (TC)
         *              during a transfer. The number of destination FIFO register sets depends on the destination FIFO depth.
         *              TC0, TC1, and TC2 each have a destination FIFO depth of 4, so there are four sets of destination FIFO
         *              registers for each of these transfer controllers.
         (offset = 0x314,0x354,0x394,0x3D4) [reset = 0x0] */ 
        typedef union 
        { 
            struct 
            {   
                uint32_t    PRIVID      :4;     // bits 0..3  (R) Privilege ID.
                                                //                This contains the Privilege ID of the EDMA3 programmer that set up
                                                //                the parameter entry in the channel controller.
                                                //                This field is set up when the associated TR is submitted to the
                                                //                EDMA3TC.
                                                //                This PRIVID value is used while issuing read and write commands to
                                                //                the target endpoints so that the target endpoints can perform
                                                //                memory protection checks based on the PRIVID of the host that set
                                                //                up the DMA transaction.
                                                //                Value 0x0 to 0xF.
                uint32_t                :4;     // bits 4..7  (R) Reserved.
                uint32_t    PRIV        :1;     // bit  8     (R) Privilege level.
                                                //                This contains the Privilege level used by the EDMA3 programmer to
                                                //                set up the parameter entry in the channel controller.
                                                //                This field is set up when the associated TR is submitted to the
                                                //                EDMA3TC.
                                                //                The privilege ID is used while issuing read and write command to the
                                                //                target endpoints so that the target endpoints can perform memory
                                                //                protection checks based on the PRIV of the host that set up the
                                                //                DMA transaction.
                                                //                [0x0 = User-level privilege
                                                //                 0x1 = Supervisor-level privilege]
                uint32_t                :23;    // bits 9..31 (R) Reserved          
            } b;                                // bit access 
            uint32_t  reg;                      // raw register
        } DFMPPRXY_reg_t;
               
        struct AM335x_EDMA3CC_Type
        {                                                                                      
            __R   PIDCC_reg_t           PID;            // (0x00)  Peripheral Identification Register
            __R   CCCFG_reg_t           CCCFG;          // (0x04)  EDMA3CC Configuration Register
            __R   uint32_t              RESERVED1[2];
            __RW  SYSCONFIGCC_reg_t     SYSCONFIG;      // (0x10)  EDMA3CC System Configuration Register
            __R   uint32_t              RESERVED2[59]; 
            __RW  DCHMAP_reg_t          DCHMAP[64];     // (0x100..0x1FC) DMA Channel Mapping Register 0..63
            __RW  QCHMAP_reg_t          QCHMAP[8];      // (0x200..0x21C) QDMA Channel Mapping Register 0..7
            __R   uint32_t              RESERVED3[8]; 
            __RW  DMAQNUM_reg_t         DMAQNUM[8];     // (0x240..0x25C) DMA Queue Number Register 0..7
            __RW  QDMAQNUM_reg_t        QDMAQNUM;       // (0x260) QDMA Queue Number Register
            __R   uint32_t              RESERVED4[8];  
            __RW  QUEPRI_reg_t          QUEPRI;         // (0x284) Queue Priority Register
            __R   uint32_t              RESERVED5[30]; 
            __R   EMR_reg_t             EMR;            // (0x300) Event Missed Register
            __R   EMRH_reg_t            EMRH;           // (0x304) Event Missed Register High 
            __W   EMCR_reg_t            EMCR;           // (0x308) Event Missed Clear Register
            __W   EMCRH_reg_t           EMCRH;          // (0x30C) Event Missed Clear Register High 
            __R   QEMR_reg_t            QEMR;           // (0x310) QDMA Event Missed Register 
            __W   QEMCR_reg_t           QEMCR;          // (0x314) QDMA Event Missed Clear Register 
            __R   CCERR_reg_t           CCERR;          // (0x318) EDMA3CC Error Register 
            __W   CCERRCLR_reg_t        CCERRCLR;       // (0x31C) EDMA3CC Error Clear Register 
            __W   EEVAL_reg_t           EEVAL;          // (0x320) Error Evaluate Register
            __R   uint32_t              RESERVED6[7]; 
            __RW  DRAE_reg_t            DRAE0;          // (0x340) DMA Region Access Enable Register for Region 0    
            __RW  DRAEH_reg_t           DRAEH0;         // (0x344) DMA Region Access Enable Register High for Region 0 
            __RW  DRAE_reg_t            DRAE1;          // (0x348) DMA Region Access Enable Register for Region 1 
            __RW  DRAEH_reg_t           DRAEH1;         // (0x34C) DMA Region Access Enable Register High for Region 1
            __RW  DRAE_reg_t            DRAE2;          // (0x350) DMA Region Access Enable Register for Region 2
            __RW  DRAEH_reg_t           DRAEH2;         // (0x354) DMA Region Access Enable Register High for Region 2  
            __RW  DRAE_reg_t            DRAE3;          // (0x358) DMA Region Access Enable Register for Region 3
            __RW  DRAEH_reg_t           DRAEH3;         // (0x35C) DMA Region Access Enable Register High for Region 3
            __RW  DRAE_reg_t            DRAE4;          // (0x360) DMA Region Access Enable Register for Region 4 
            __RW  DRAEH_reg_t           DRAEH4;         // (0x364) DMA Region Access Enable Register High for Region 4
            __RW  DRAE_reg_t            DRAE5;          // (0x368) DMA Region Access Enable Register for Region 5 
            __RW  DRAEH_reg_t           DRAEH5;         // (0x36C) DMA Region Access Enable Register High for Region 5 
            __RW  DRAE_reg_t            DRAE6;          // (0x370) DMA Region Access Enable Register for Region 6
            __RW  DRAEH_reg_t           DRAEH6;         // (0x374) DMA Region Access Enable Register High for Region 6
            __RW  DRAE_reg_t            DRAE7;          // (0x378) DMA Region Access Enable Register for Region 7
            __RW  DRAEH_reg_t           DRAEH7;         // (0x37C) DMA Region Access Enable Register High for Region 7
            __RW  QRAE_reg_t            QRAE[8];        // (0x380..0x39Ñ) QDMA Region Access Enable Registers for Region 0..7
            __R   uint32_t              RESERVED7[24];  
            __R   QE_reg_t              Q0E0;           // (0x400) Event Queue 0 Entry 0 Register 
            __R   QE_reg_t              Q0E1;           // (0x404) Event Queue 0 Entry 1 Register 
            __R   QE_reg_t              Q0E2;           // (0x408) Event Queue 0 Entry 2 Register 
            __R   QE_reg_t              Q0E3;           // (0x40C) Event Queue 0 Entry 3 Register 
            __R   QE_reg_t              Q0E4;           // (0x410) Event Queue 0 Entry 4 Register 
            __R   QE_reg_t              Q0E5;           // (0x414) Event Queue 0 Entry 5 Register 
            __R   QE_reg_t              Q0E6;           // (0x418) Event Queue 0 Entry 6 Register
            __R   QE_reg_t              Q0E7;           // (0x41C) Event Queue 0 Entry 7 Register 
            __R   QE_reg_t              Q0E8;           // (0x420) Event Queue 0 Entry 8 Register 
            __R   QE_reg_t              Q0E9;           // (0x424) Event Queue 0 Entry 9 Register 
            __R   QE_reg_t              Q0E10;          // (0x428) Event Queue 0 Entry 10 Register 
            __R   QE_reg_t              Q0E11;          // (0x42C) Event Queue 0 Entry 11 Register
            __R   QE_reg_t              Q0E12;          // (0x430) Event Queue 0 Entry 12 Register 
            __R   QE_reg_t              Q0E13;          // (0x434) Event Queue 0 Entry 13 Register
            __R   QE_reg_t              Q0E14;          // (0x438) Event Queue 0 Entry 14 Register 
            __R   QE_reg_t              Q0E15;          // (0x43C) Event Queue 0 Entry 15 Register 
            __R   QE_reg_t              Q1E0;           // (0x440) Event Queue 1 Entry 0 Register   
            __R   QE_reg_t              Q1E1;           // (0x444) Event Queue 1 Entry 1 Register   
            __R   QE_reg_t              Q1E2;           // (0x448) Event Queue 1 Entry 2 Register   
            __R   QE_reg_t              Q1E3;           // (0x44C) Event Queue 1 Entry 3 Register   
            __R   QE_reg_t              Q1E4;           // (0x450) Event Queue 1 Entry 4 Register  
            __R   QE_reg_t              Q1E5;           // (0x454) Event Queue 1 Entry 5 Register   
            __R   QE_reg_t              Q1E6;           // (0x458) Event Queue 1 Entry 6 Register  
            __R   QE_reg_t              Q1E7;           // (0x45C) Event Queue 1 Entry 7 Register   
            __R   QE_reg_t              Q1E8;           // (0x460) Event Queue 1 Entry 8 Register   
            __R   QE_reg_t              Q1E9;           // (0x464) Event Queue 1 Entry 9 Register   
            __R   QE_reg_t              Q1E10;          // (0x468) Event Queue 1 Entry 10 Register  
            __R   QE_reg_t              Q1E11;          // (0x46C) Event Queue 1 Entry 11 Register 
            __R   QE_reg_t              Q1E12;          // (0x470) Event Queue 1 Entry 12 Register  
            __R   QE_reg_t              Q1E13;          // (0x474) Event Queue 1 Entry 13 Register  
            __R   QE_reg_t              Q1E14;          // (0x478) Event Queue 1 Entry 14 Register  
            __R   QE_reg_t              Q1E15;          // (0x47C) Event Queue 1 Entry 15 Register  
            __R   QE_reg_t              Q2E0;           // (0x480) Event Queue 2 Entry 0 Register   
            __R   QE_reg_t              Q2E1;           // (0x484) Event Queue 2 Entry 1 Register   
            __R   QE_reg_t              Q2E2;           // (0x488) Event Queue 2 Entry 2 Register  
            __R   QE_reg_t              Q2E3;           // (0x48C) Event Queue 2 Entry 3 Register   
            __R   QE_reg_t              Q2E4;           // (0x490) Event Queue 2 Entry 4 Register   
            __R   QE_reg_t              Q2E5;           // (0x494) Event Queue 2 Entry 5 Register   
            __R   QE_reg_t              Q2E6;           // (0x498) Event Queue 2 Entry 6 Register  
            __R   QE_reg_t              Q2E7;           // (0x49C) Event Queue 2 Entry 7 Register   
            __R   QE_reg_t              Q2E8;           // (0x4A0) Event Queue 2 Entry 8 Register   
            __R   QE_reg_t              Q2E9;           // (0x4A4) Event Queue 2 Entry 9 Register  
            __R   QE_reg_t              Q2E10;          // (0x4A8) Event Queue 2 Entry 10 Register  
            __R   QE_reg_t              Q2E11;          // (0x4AC) Event Queue 2 Entry 11 Register  
            __R   QE_reg_t              Q2E12;          // (0x4B0) Event Queue 2 Entry 12 Register 
            __R   QE_reg_t              Q2E13;          // (0x4B4) Event Queue 2 Entry 13 Register  
            __R   QE_reg_t              Q2E14;          // (0x4B8) Event Queue 2 Entry 14 Register  
            __R   QE_reg_t              Q2E15;          // (0x4BC) Event Queue 2 Entry 15 Register 
            __R   uint32_t              RESERVED8[80]; 
            __R   QSTAT_reg_t           QSTAT_0;        // (0x600) Queue Status Registers 0
            __R   QSTAT_reg_t           QSTAT_1;        // (0x604) Queue Status Registers 1 
            __R   QSTAT_reg_t           QSTAT_2;        // (0x608) Queue Status Registers 2
            __R   uint32_t              RESERVED9[5]; 
            __RW  QWMTHRA_reg_t         QWMTHRA;        // (0x620) Queue Watermark Threshold A Register
            __R   uint32_t              RESERVED10[7]; 
            __R   CCSTAT_reg_t          CCSTAT;         // (0x640) EDMA3CC Status Register
            __R   uint32_t              RESERVED11[111]; 
            __R   MPFAR_reg_t           MPFAR;          // (0x800) Memory Protection Fault Address Register
            __R   MPFSR_reg_t           MPFSR;          // (0x804) Memory Protection Fault Status Register
            __W   MPFCR_reg_t           MPFCR;          // (0x808) Memory Protection Fault Command Register 
            __RW  MPPAG_reg_t           MPPAG;          // (0x80C) Memory Protection Page Attribute Register Global 
            __RW  MPPA_reg_t            MPPA_0;         // (0x810) Memory Protection Page Attribute Register 0
            __RW  MPPA_reg_t            MPPA_1;         // (0x814) Memory Protection Page Attribute Register 1
            __RW  MPPA_reg_t            MPPA_2;         // (0x818) Memory Protection Page Attribute Register 2 
            __RW  MPPA_reg_t            MPPA_3;         // (0x81C) Memory Protection Page Attribute Register 3 
            __RW  MPPA_reg_t            MPPA_4;         // (0x820) Memory Protection Page Attribute Register 4
            __RW  MPPA_reg_t            MPPA_5;         // (0x824) Memory Protection Page Attribute Register 5 
            __RW  MPPA_reg_t            MPPA_6;         // (0x828) Memory Protection Page Attribute Register 6
            __RW  MPPA_reg_t            MPPA_7;         // (0x82C) Memory Protection Page Attribute Register 7
            __R   uint32_t              RESERVED12[500]; 
            __R   ER_reg_t              ER;             // (0x1000) Event Register  
            __R   ERH_reg_t             ERH;            // (0x1004) Event Register High 
            __W   ECR_reg_t             ECR;            // (0x1008) Event Clear Register 
            __W   ECRH_reg_t            ECRH;           // (0x100C) Event Clear Register High 
            __RW  ESR_reg_t             ESR;            // (0x1010) Event Set Register 
            __RW  ESRH_reg_t            ESRH;           // (0x1014) Event Set Register High 
            __R   CER_reg_t             CER;            // (0x1018) Chained Event Register  
            __R   CERH_reg_t            CERH;           // (0x101C) Chained Event Register High 
            __R   EER_reg_t             EER;            // (0x1020) Event Enable Register
            __R   EERH_reg_t            EERH;           // (0x1024) Event Enable Register High 
            __W   EECR_reg_t            EECR;           // (0x1028) Event Enable Clear Register  
            __W   EECRH_reg_t           EECRH;          // (0x102C) Event Enable Clear Register High 
            __W   EESR_reg_t            EESR;           // (0x1030) Event Enable Set Register 
            __W   EESRH_reg_t           EESRH;          // (0x1034) Event Enable Set Register High
            __R   SER_reg_t             SER;            // (0x1038) Secondary Event Register 
            __R   SERH_reg_t            SERH;           // (0x103C) Secondary Event Register High 
            __W   SECR_reg_t            SECR;           // (0x1040) Secondary Event Clear Register 
            __W   SECRH_reg_t           SECRH;          // (0x1044) Secondary Event Clear Register High
            __R   uint32_t              RESERVED13[2]; 
            __R   IER_reg_t             IER;            // (0x1050) Interrupt Enable Register
            __R   IERH_reg_t            IERH;           // (0x1054) Interrupt Enable Register High 
            __W   IECR_reg_t            IECR;           // (0x1058) Interrupt Enable Clear Register
            __W   IECRH_reg_t           IECRH;          // (0x105C) Interrupt Enable Clear Register High  
            __W   IESR_reg_t            IESR;           // (0x1060) Interrupt Enable Set Register 
            __W   IESRH_reg_t           IESRH;          // (0x1064) Interrupt Enable Set Register High 
            __R   IPR_reg_t             IPR;            // (0x1068) Interrupt Pending Register 
            __R   IPRH_reg_t            IPRH;           // (0x106C) Interrupt Pending Register High 
            __W   ICR_reg_t             ICR;            // (0x1070) Interrupt Clear Register 
            __W   ICRH_reg_t            ICRH;           // (0x1074) Interrupt Clear Register High
            __W   IEVAL_reg_t           IEVAL;          // (0x1078) Interrupt Evaluate Register
            __R   uint32_t              RESERVED14[1]; 
            __R   QER_reg_t             QER;            // (0x1080) QDMA Event Register 
            __R   QEER_reg_t            QEER;           // (0x1084) QDMA Event Enable Register
            __W   QEECR_reg_t           QEECR;          // (0x1088) QDMA Event Enable Clear Register 
            __W   QEESR_reg_t           QEESR;          // (0x108C) QDMA Event Enable Set Register  
            __R   QSER_reg_t            QSER;           // (0x1090) QDMA Secondary Event Register 
            __W   QSECR_reg_t           QSECR;          // (0x1094) QDMA Secondary Event Clear Register
        };
    
        struct AM335x_EDMA3TC_Type
        {                                                                                      
            __R   PIDTC_reg_t         PID;                // (0x00)   Peripheral Identification Register
            __R   TCCFG_reg_t         TCCFG;              // (0x04)   EDMA3TC Configuration Register
            __R   uint32_t            RESERVED1[2];
            __RW  SYSCONFIGTC_reg_t   SYSCONFIG;          // (0x10)   EDMA3TC System Configuration Register  
            __R   uint32_t            RESERVED2[59];
            __R   TCSTAT_reg_t        TCSTAT;             // (0x100)  EDMA3TC Channel Status Register
            __R   uint32_t            RESERVED3[7];  
            __R   ERRSTAT_reg_t       ERRSTAT;            // (0x120)  Error Register 
            __RW  ERREN_reg_t         ERREN;              // (0x124)  Error Enable Register 
            __W   ERRCLR_reg_t        ERRCLR;             // (0x128)  Error Clear Register 
            __R   ERRDET_reg_t        ERRDET;             // (0x12C)  Error Details Register 
            __W   ERRCMD_reg_t        ERRCMD;             // (0x130)  Error Interrupt Command Register 
            __R   uint32_t            RESERVED4[3]; 
            __RW  RDRATE_reg_t        RDRATE;             // (0x140)  Read Rate Register
            __R   uint32_t            RESERVED5[63];
            __R   SAOPT_reg_t         SAOPT;              // (0x240)  Source Active Options Register 
            __R   SASRC_reg_t         SASRC;              // (0x244)  Source Active Source Address Register
            __R   SACNT_reg_t         SACNT;              // (0x248)  Source Active Count Register  
            __R   SADST_reg_t         SADST;              // (0x24C)  Source Active Destination Address Register 
            __R   SABIDX_reg_t        SABIDX;             // (0x250)  Source Active Source B-Index Register
            __R   SAMPPRXY_reg_t      SAMPPRXY;           // (0x254)  Source Active Memory Protection Proxy Register  
            __R   SACNTRLD_reg_t      SACNTRLD;           // (0x258)  Source Active Count Reload Register
            __R   SASRCBREF_reg_t     SASRCBREF;          // (0x25C)  Source Active Source Address B-Reference Register 
            __R   SADSTBREF_reg_t     SADSTBREF;          // (0x260)  Source Active Destination Address B-Reference Register
            __R   uint32_t            RESERVED6[7];
            __R   DFCNTRLD_reg_t      DFCNTRLD;           // (0x280)  Destination FIFO Set Count Reload
            __R   DFSRCBREF_reg_t     DFSRCBREF;          // (0x284)  Destination FIFO Set Destination Address B Reference Register
            __R   DFDSTBREF_reg_t     DFDSTBREF;          // (0x288)  Destination FIFO Set Destination Address B Reference Register
            __R   uint32_t            RESERVED7[29];
            __R   DFOPT_reg_t         DFOPT0;             // (0x300)  Destination FIFO Options Register 0
            __R   DFSRC_reg_t         DFSRC0;             // (0x304)  Destination FIFO Source Address Register 0
            __R   DFCNT_reg_t         DFCNT0;             // (0x308)  Destination FIFO Count Register 0
            __R   DFDST_reg_t         DFDST0;             // (0x30C)  Destination FIFO Destination Address Register 0
            __R   DFBIDX_reg_t        DFBIDX0;            // (0x310)  Destination FIFO BIDX Register 0
            __R   DFMPPRXY_reg_t      DFMPPRXY0;          // (0x314)  Destination FIFO Memory Protection Proxy Register 0
            __R   uint32_t            RESERVED8[10];
            __R   DFOPT_reg_t         DFOPT1;             // (0x340)  Destination FIFO Options Register 1
            __R   DFSRC_reg_t         DFSRC1;             // (0x344)  Destination FIFO Source Address Register 1
            __R   DFCNT_reg_t         DFCNT1;             // (0x348)  Destination FIFO Count Register 1
            __R   DFDST_reg_t         DFDST1;             // (0x34C)  Destination FIFO Destination Address Register 1
            __R   DFBIDX_reg_t        DFBIDX1;            // (0x350)  Destination FIFO BIDX Register 1
            __R   DFMPPRXY_reg_t      DFMPPRXY1;          // (0x354)  Destination FIFO Memory Protection Proxy Register 1
            __R   uint32_t            RESERVED9[10];
            __R   DFOPT_reg_t         DFOPT2;             // (0x380)  Destination FIFO Options Register 2
            __R   DFSRC_reg_t         DFSRC2;             // (0x384)  Destination FIFO Source Address Register 2
            __R   DFCNT_reg_t         DFCNT2;             // (0x388)  Destination FIFO Count Register 2
            __R   DFDST_reg_t         DFDST2;             // (0x38C)  Destination FIFO Destination Address Register 2
            __R   DFBIDX_reg_t        DFBIDX2;            // (0x390)  Destination FIFO BIDX Register 2
            __R   DFMPPRXY_reg_t      DFMPPRXY2;          // (0x394)  Destination FIFO Memory Protection Proxy Register 2
            __R   uint32_t            RESERVED10[10];
            __R   DFOPT_reg_t         DFOPT3;             // (0x3C0)  Destination FIFO Options Register 3
            __R   DFSRC_reg_t         DFSRC3;             // (0x3C4)  Destination FIFO Source Address Register 3
            __R   DFCNT_reg_t         DFCNT3;             // (0x3C8)  Destination FIFO Count Register 3
            __R   DFDST_reg_t         DFDST3;             // (0x3CC)  Destination FIFO Destination Address Register 3
            __R   DFBIDX_reg_t        DFBIDX3;            // (0x3D0)  Destination FIFO BIDX Register 3
            __R   DFMPPRXY_reg_t      DFMPPRXY3;          // (0x3D4)  Destination FIFO Memory Protection Proxy Register 3 
        };
        
        constexpr uint32_t PARAM_ENTRY_FIELDS = 0x8u;
                  uint32_t* get_paRAM_ptr(uint32_t n);
            
        struct paRAM_entry_t
        {
            // Transfer configuration options
            union 
            {
                struct 
                {  
                    uint32_t    SAM       :1;   // bit: 0          (RW) Source address mode. [0x0 = Increment (INCR) mode; 0x1 = Constant addressing (CONST) mode.]
                                                //                      Increment (INCR) mode. Source addressing within an array increments. Source is not a FIFO.
                                                //                      Constant addressing (CONST) mode. Source addressing within an array wraps around upon reaching FIFO width.
                    uint32_t    DAM       :1;   // bit: 1          (RW) Destination address mode. [ 0x0 = Increment (INCR) mode; 0x1 = Constant addressing (CONST) mode. ]
                                                //                      Increment (INCR) mode. Destination addressing within an array increments. Destination is not a FIFO.
                                                //                      Constant addressing (CONST) mode. Destination addressing within an array wraps around upon reaching FIFO width.
                    uint32_t    SYNCDIM   :1;   // bit: 2          (RW) Transfer synchronization dimension. [ 0x0 = A-synchronized; 0x1 = AB-synchronized. ]
                    uint32_t    STATIC    :1;   // bit: 3          (RW) Static set. [0x0 = Set is not static; 0x1 = Set is static. ]
                                                //                      Set is not static. The PaRAM set is updated or linked after a TR is submitted. A value of 0 should be
                                                //                      used for DMA channels and for non-final transfers in a linked list of QDMA transfers.
                                                //                      1 Set is static. The PaRAM set is not updated or linked after a TR is submitted. A value of 1 should be
                                                //                      used for isolated QDMA transfers or for the final transfer in a linked list of QDMA transfers.
                    uint32_t              :4;   // bit: 4..7       Reserved 
                    uint32_t    FWID      :3;   // bit: 8..10      (RW) FIFO Width. Applies if either SAM or DAM is set to constant addressing mode. [ see e_paRAM_FIFO_MODE ]
                    uint32_t    TCCMODE   :1;   // bit: 11         (RW) Transfer complete code mode. Indicates the point at which a transfer is considered completed for
                                                //                      chaining and interrupt generation.
                                                //                      [0x0 = Normal completion; 0x1 = Early completion]
                    uint32_t    TCC       :6;   // bit: 12..17     (RW) Transfer complete code. This 6-bit code sets the relevant bit in the chaining enable register (CER [TCC]
                                                //                      CERH [TCC]) for chaining or in the interrupt pending register (IPR [TCC] / IPRH [TCC]) for interrupts.
                                                //                      [ 0-3Fh]
                    uint32_t              :2;   // bit: 18,19      Reserved          
                    uint32_t    TCINTEN   :1;   // bit: 20         (RW) Transfer complete interrupt enable. [ 0x0 = disabled; 0x1 = enabled ] 
                    uint32_t    ITCINTEN  :1;   // bit: 21         (RW) Intermediate transfer completion interrupt enable. [ 0x0 = disabled; 0x1 = enabled ] 
                    uint32_t    TCCHEN    :1;   // bit: 22         (RW) Transfer complete chaining enable. [ 0x0 = disabled; 0x1 = enabled ]
                    uint32_t    ITCCHEN   :1;   // bit: 23         (RW) Intermediate transfer completion chaining enable. [ 0x0 = disabled; 0x1 = enabled ]
                    uint32_t    PRIVID    :4;   // bit: 24..27     (R) Privilege identification for the external host/CPU/DMA that programmed this PaRAM set. This value is
                                                //                     set with the EDMA3 master’s privilege identification value when any part of the PaRAM set is written.
                    uint32_t              :3;   // bit: 28..30     Reserved
                    uint32_t    PRIV      :1;   // bit: 31         (R) Privilege level (supervisor versus user) for the host/CPU/DMA that programmed this PaRAM set. This
                                                //                     value is set with the EDMA3 master’s privilege value when any part of the PaRAM set is written.
                                                //                     [ 0x0 = User level privilege.; 0x1 = Supervisor level privilege. ] 
                } b;                            // Structure used for bit access 
                uint32_t  reg;                  // Type used for register access
            } OPT;
    
            uint32_t  SRC { 0 };    // The byte address from which data is transferred 
            
            uint16_t  ACNT { 0 };   // Unsigned value specifying the number of contiguous bytes
                                    // within an array (first dimension of the transfer). Valid values
                                    // range from 1 to 65 535.
            
            uint16_t  BCNT { 0 };   // Unsigned value specifying the number of arrays in a frame,
                                    // where an array is ACNT bytes. Valid values range from 1 to 65 535.
            
            uint32_t  DST { 0 };    // The byte address to which data is transferred
            
             int16_t  SRCBIDX { 0 };// Signed value specifying the byte address offset between
                                    // source arrays within a frame (2nd dimension). Valid values range from –32 768 and 32 767.
             
             int16_t  DSTBIDX { 0 };// Signed value specifying the byte address offset between
                                    // destination arrays within a frame (2nd dimension). Valid
                                    // values range from –32 768 and 32 767.
             
            uint16_t  LINK { 0 };   // The PaRAM address containing the PaRAM set to be linked
                                    // (copied from) when the current PaRAM set is exhausted. A
                                    // value of FFFFh specifies a null link.
            
            uint16_t  BCNTRLD { 0 };// The count value used to reload BCNT when BCNT
                                    // decrements to 0 (TR is submitted for the last array in 2nd
                                    // dimension). Only relevant in A-synchronized transfers.
            
             int16_t  SRCCIDX { 0 };// Signed value specifying the byte address offset between
                                    // frames within a block (3rd dimension). Valid values range
                                    // from –32 768 and 32 767.
                                    // A-synchronized transfers: The byte address offset from the
                                    // beginning of the last source array in a frame to the
                                    // beginning of the first source array in the next frame.
                                    // AB-synchronized transfers: The byte address offset from the
                                    // beginning of the first source array in a frame to the
                                    // beginning of the first source array in the next frame.
             
             int16_t  DSTCIDX { 0 };// Signed value specifying the byte address offset between
                                    // frames within a block (3rd dimension). Valid values range
                                    // from –32 768 and 32 767.
                                    // A-synchronized transfers: The byte address offset from the
                                    // beginning of the last destination array in a frame to the
                                    // beginning of the first destination array in the next frame.
                                    // AB-synchronized transfers: The byte address offset from the
                                    // beginning of the first destination array in a frame to the
                                    // beginning of the first destination array in the next frame.
             
            uint16_t  CCNT { 0 };   // Unsigned value specifying the number of frames in a block,
                                    // where a frame is BCNT arrays of ACNT bytes. Valid values range from 1 to 65 535.
            
            uint16_t  RESERVED;     // Reserved. Always write 0 to this bit; writes of 1 to this bit are
                                    // not supported and attempts to do so may result in undefined behavior.
    
            paRAM_entry_t() { OPT.reg = 0; }
    
            paRAM_entry_t& operator =(const paRAM_entry_t &right)
            {
                OPT.reg  = right.OPT.reg;
                    SRC  = right.SRC;
                   ACNT  = right.ACNT;
                   BCNT  = right.BCNT;
                    DST  = right.DST;
                SRCBIDX  = right.SRCBIDX;
                DSTBIDX  = right.DSTBIDX;
                   LINK  = right.LINK;
                BCNTRLD  = right.BCNTRLD;
                SRCCIDX  = right.SRCCIDX;
                DSTCIDX  = right.DSTCIDX;
                   CCNT  = right.CCNT;
            
               return *this;
            }
        };
    
        enum e_paRAM_FIFO_WIDTH : uint32_t
        {
            FIFO_WIDTH_8BIT     = 0x0,
            FIFO_WIDTH_16BIT    = 0x1,
            FIFO_WIDTH_32BIT    = 0x2,
            FIFO_WIDTH_64BIT    = 0x3,
            FIFO_WIDTH_128BIT   = 0x4,
            FIFO_WIDTH_256BIT   = 0x5
        };
    
        constexpr uint32_t AM335x_EDMA3CC_BASE     = 0x49000000;   
        constexpr uint32_t AM335x_EDMA3TC0_BASE    = 0x49800000;
        constexpr uint32_t AM335x_EDMA3TC1_BASE    = 0x49900000;
        constexpr uint32_t AM335x_EDMA3TC2_BASE    = 0x49A00000;
        constexpr uint32_t PARAM_BASE              = 0x4000;
        constexpr uint32_t COMPL_HANDLER_RETRY_COUNT = 10u;
        constexpr uint32_t ERR_HANDLER_RETRY_COUNT   = 10u;
        
        constexpr uint32_t EVTQUE_AVAIL  = 2u;  // Number of Event Queues available 
    
        constexpr AM335x_EDMA3CC_Type * AM335X_EDMA3CC_regs  = reinterpret_cast<AM335x_EDMA3CC_Type *>(AM335x_EDMA3CC_BASE);
        constexpr AM335x_EDMA3TC_Type * AM335X_EDMA3TC0_regs = reinterpret_cast<AM335x_EDMA3TC_Type *>(AM335x_EDMA3TC0_BASE);
        constexpr AM335x_EDMA3TC_Type * AM335X_EDMA3TC1_regs = reinterpret_cast<AM335x_EDMA3TC_Type *>(AM335x_EDMA3TC1_BASE);
        constexpr AM335x_EDMA3TC_Type * AM335X_EDMA3TC2_regs = reinterpret_cast<AM335x_EDMA3TC_Type *>(AM335x_EDMA3TC2_BASE);
    
        constexpr uint32_t SET_ALL_BITS = 0xFFFFFFFFu;
        constexpr uint32_t CLR_ALL_BITS = 0x00000000u;
        
        enum e_REGION_ID : uint32_t
        {
            REGION_0 = 0x0,
            REGION_1 = 0x1,
            REGION_2 = 0x2,
            REGION_3 = 0x3,
            REGION_4 = 0x4,
            REGION_5 = 0x5,
            REGION_6 = 0x6,
            REGION_7 = 0x7        
        };
    
        enum e_EDMA3_CH_TYPE : uint32_t
        {
            CHANNEL_TYPE_DMA  = 0u,
            CHANNEL_TYPE_QDMA = 1u
        };
    
        enum e_EDMA3_TRIG_MODE_TYPE : uint32_t
        {
            TRIG_MODE_MANUAL = 0x0,
            TRIG_MODE_QDMA   = 0x1,
            TRIG_MODE_EVENT  = 0x2
        };
    
        enum e_EDMA3_CHANNEL_MAP : uint32_t
        {        
            CH_MCASP1_TX             = 10, // Events for McASP 1
            CH_MCASP1_RX             = 11, // Events for McASP 1
            CH_MCSPI0_CH0_TX  = 16, // MCSPI0 Channel 0 transmit event 
            CH_MCSPI0_CH0_RX  = 17, // MCSPI0 Channel 0 receive event 
            CH_MCSPI0_CH1_TX  = 18, // MCSPI0 Channel 1 transmit event 
            CH_MCSPI0_CH1_RX  = 19, // MCSPI0 Channel 1 receive event 
            CH_MMCSD0_TX      = 24, // MMCSD0 transmit event. 
            CH_MMCSD0_RX      = 25, // MMCSD0 receive event.
            CH_UART0_TX       = 26, // UART0 Transmit Event.
            CH_UART0_RX       = 27, // UART0 Receive Event. 
            CH_UART1_TX       = 28, // UART1 Transmit Event.
            CH_UART1_RX       = 29, // UART1 Receive Event.
            CH_UART2_TX       = 30, // UART2 Transmit Event.
            CH_UART2_RX       = 31, // UART2 Receive Event.
            CH_MCSPI1_CH0_TX  = 42, // MCSPI1 Channel 0 transmit event  
            CH_MCSPI1_CH0_RX  = 43, // MCSPI1 Channel 0 receive event
            CH_MCSPI1_CH1_TX  = 44, // MCSPI1 Channel 1 transmit event
            CH_MCSPI1_CH1_RX  = 45, // MCSPI1 Channel 1 receive event 
            CH_I2C0_TX        = 58, // I2C0 Transmit Event 
            CH_I2C0_RX        = 59, // I2C0 Receive Event 
            CH_I2C1_TX        = 60, // I2C1 Receive Event
            CH_I2C1_RX        = 61  // I2C1 Transmit Event 
        };
        
       constexpr uint32_t  EDMA_REVID                = 0x01u;
       constexpr uint32_t  AM335X_DMACH_MAX          = 64;
       constexpr uint32_t  AM335X_QDMACH_MAX         = 8; 
    
       constexpr uint32_t  PARAM_ENTRY_OPT            = 0x0u;       //The OPT field (Offset Address 0x0 Bytes)
       constexpr uint32_t  PARAM_ENTRY_SRC            = 0x1u;       //The SRC field (Offset Address 0x4 Bytes)
       constexpr uint32_t  PARAM_ENTRY_ACNT_BCNT      = 0x2u;       //The (ACNT+BCNT) field (Offset Address 0x8 Bytes)
       constexpr uint32_t  PARAM_ENTRY_DST            = 0x3u;       //The DST field (Offset Address 0xC Bytes)
       constexpr uint32_t  PARAM_ENTRY_SRC_DST_BIDX   = 0x4u;       //The (SRCBIDX+DSTBIDX) field (Offset Address 0x10 Bytes)
       constexpr uint32_t  PARAM_ENTRY_LINK_BCNTRLD   = 0x5u;       //The (LINK+BCNTRLD) field (Offset Address 0x14 Bytes)
       constexpr uint32_t  PARAM_ENTRY_SRC_DST_CIDX   = 0x6u;       //The (SRCCIDX+DSTCIDX) field (Offset Address 0x18 Bytes)
       constexpr uint32_t  PARAM_ENTRY_CCNT           = 0x7u;       //The (CCNT+RSVD) field (Offset Address 0x1C Bytes)
       constexpr uint32_t  PARAM_FIELD_OFFSET         = 0x4u;       //The offset for each PaRAM Entry field
        
        // Structure to store the EDMA context
        typedef struct edma_context 
        {    
             uint32_t  dch_map[AM335X_DMACH_MAX];       // Channel mapping reg Val      
             uint32_t  dma_Qnum[AM335X_QDMACH_MAX];     // DMA Queue Number Register Val
             
             uint32_t  reg_acc_enable_low;       // DMA Region Access Enable Register val    
             uint32_t  reg_acc_enable_high;      // DMA Region Access Enable Register val 
               
             uint32_t  event_set_reg_low;        // Event Set Register value  
             uint32_t  event_set_reg_high;       // Event Set Register value 
                
             uint32_t  enable_evt_set_reg_low;    // Enable Event Set Register value 
             uint32_t  enable_evt_set_reg_high;   // Enable Event Set Register value 
                      
             uint32_t  int_enable_set_reg_low;    // Interrupt Enable Set Register value      
             uint32_t  int_enable_set_reg_high;   // Interrupt Enable Set Register value   
            
        paRAM_entry_t  dma_par_entry[256];    
            
        } EDMACONTEXT_t;
    
         DRAE_reg_t*& get_DRAE_ptr(e_REGION_ID region_id);
        DRAEH_reg_t*& get_DRAEH_ptr(e_REGION_ID region_id);    
            uint32_t  DMAQNUM_CLR(uint32_t count);
            uint32_t  DMAQNUM_SET(uint32_t count, e_EVENT_QUEUE que_num);
            uint32_t  QDMAQNUM_CLR(uint32_t count);
            uint32_t  QDMAQNUM_SET(uint32_t count, e_EVENT_QUEUE que_num);
    
           ER_reg_t*& get_S_ER_ptr(e_REGION_ID region_id);
        //ERH_reg_t*& get_S_ERH_ptr(e_REGION_ID region_id); 
          ECR_reg_t*& get_S_ECR_ptr(e_REGION_ID region_id); 
         ECRH_reg_t*& get_S_ECRH_ptr(e_REGION_ID region_id); 
          ESR_reg_t*& get_S_ESR_ptr(e_REGION_ID region_id);
         ESRH_reg_t*& get_S_ESRH_ptr(e_REGION_ID region_id); 
          CER_reg_t*& get_S_CER_ptr(e_REGION_ID region_id); 
       //CERH_reg_t*& get_S_CERH_ptr(e_REGION_ID region_id); 
          EER_reg_t*& get_S_EER_ptr(e_REGION_ID region_id);
         EERH_reg_t*& get_S_EERH_ptr(e_REGION_ID region_id); 
         EECR_reg_t*& get_S_EECR_ptr(e_REGION_ID region_id); 
        EECRH_reg_t*& get_S_EECRH_ptr(e_REGION_ID region_id); 
         EESR_reg_t*& get_S_EESR_ptr(e_REGION_ID region_id); 
        EESRH_reg_t*& get_S_EESRH_ptr(e_REGION_ID region_id);
          SER_reg_t*& get_S_SER_ptr(e_REGION_ID region_id); 
         SERH_reg_t*& get_S_SERH_ptr(e_REGION_ID region_id);
         SECR_reg_t*& get_S_SECR_ptr(e_REGION_ID region_id); 
        SECRH_reg_t*& get_S_SECRH_ptr(e_REGION_ID region_id);
          IER_reg_t*& get_S_IER_ptr(e_REGION_ID region_id);    
         IERH_reg_t*& get_S_IERH_ptr(e_REGION_ID region_id);   
         IECR_reg_t*& get_S_IECR_ptr(e_REGION_ID region_id);   
        IECRH_reg_t*& get_S_IECRH_ptr(e_REGION_ID region_id);  
         IESR_reg_t*& get_S_IESR_ptr(e_REGION_ID region_id);   
        IESRH_reg_t*& get_S_IESRH_ptr(e_REGION_ID region_id);  
          IPR_reg_t*& get_S_IPR_ptr(e_REGION_ID region_id);    
         IPRH_reg_t*& get_S_IPRH_ptr(e_REGION_ID region_id);   
          ICR_reg_t*& get_S_ICR_ptr(e_REGION_ID region_id);    
         ICRH_reg_t*& get_S_ICRH_ptr(e_REGION_ID region_id);   
        IEVAL_reg_t*& get_S_IEVAL_ptr(e_REGION_ID region_id);  
          QER_reg_t*& get_S_QER_ptr(e_REGION_ID region_id);   
         QEER_reg_t*& get_S_QEER_ptr(e_REGION_ID region_id);  
        QEECR_reg_t*& get_S_QEECR_ptr(e_REGION_ID region_id); 
        QEESR_reg_t*& get_S_QEESR_ptr(e_REGION_ID region_id); 
         QSER_reg_t*& get_S_QSER_ptr(e_REGION_ID region_id);  
        QSECR_reg_t*& get_S_QSECR_ptr(e_REGION_ID region_id);
        
            uint32_t* get_paRAM_ptr(uint32_t n);                
            uint32_t* get_SRC_ptr(uint32_t n);                
            uint32_t* get_A_B_CNT_ptr(uint32_t n);            
            uint32_t* get_DST_ptr(uint32_t n);                
            uint32_t* get_SRC_DST_BIDX_ptr(uint32_t n);       
            uint32_t* get_LINK_BCNTRLD_ptr(uint32_t n);       
            uint32_t* get_SRC_DST_CIDX_ptr(uint32_t n);       
            uint32_t* get_CCNT_ptr(uint32_t n);
    
        inline DRAE_reg_t*& get_DRAE_ptr(e_REGION_ID region_id) 
        {
            uint32_t DRAE = (AM335x_EDMA3CC_BASE + 0x340 + (region_id * 8));      
            return (DRAE_reg_t*&)DRAE;
        }
        
        inline DRAEH_reg_t*& get_DRAEH_ptr(e_REGION_ID region_id) 
        {
            uint32_t DRAEH = (AM335x_EDMA3CC_BASE + 0x344 + (region_id * 8));        
            return (DRAEH_reg_t*&)DRAEH;
        }
    
        inline uint32_t  DMAQNUM_CLR(uint32_t ch_num)
        { return (~(0x7u << (((ch_num)%8u)*4u))); }
    
        inline uint32_t  DMAQNUM_SET(uint32_t ch_num, e_EVENT_QUEUE que_num)
        { return ((0x7u & ((uint32_t)que_num)) << (((ch_num)%8u)*4u)); }
    
        inline uint32_t  QDMAQNUM_CLR(uint32_t ch_num)
        { return (~(0x7u << (ch_num*4u))); }
    
        inline uint32_t  QDMAQNUM_SET(uint32_t ch_num, e_EVENT_QUEUE que_num)
        { return ((0x7u & ((uint32_t)que_num)) << (ch_num*4u)); }
    
        inline   ER_reg_t*& get_S_ER_ptr(e_REGION_ID region_id)
        {
            uint32_t ER = AM335x_EDMA3CC_BASE + 0x2000 +  (0X200*region_id);        
            return (ER_reg_t*&)ER;
        }
    
        inline  ECR_reg_t*& get_S_ECR_ptr(e_REGION_ID region_id) 
        {
            uint32_t ECR = AM335x_EDMA3CC_BASE + 0x2008 +  (0X200*region_id);        
            return (ECR_reg_t*&)ECR;
        }
    
        inline ECRH_reg_t*& get_S_ECRH_ptr(e_REGION_ID region_id) 
        {
            uint32_t ECRH = AM335x_EDMA3CC_BASE + 0x200C +  (0X200*region_id);        
            return (ECRH_reg_t*&)ECRH;
        }
    
        inline  ESR_reg_t*& get_S_ESR_ptr(e_REGION_ID region_id)
        {
            uint32_t ESR = AM335x_EDMA3CC_BASE + 0x2010 +  (0X200*region_id);        
            return (ESR_reg_t*&)ESR;
        }
    
        inline ESRH_reg_t*& get_S_ESRH_ptr(e_REGION_ID region_id)
        {
            uint32_t ESRH = AM335x_EDMA3CC_BASE + 0x2014 +  (0X200*region_id);        
            return (ESRH_reg_t*&)ESRH;
        }
    
        inline  CER_reg_t*& get_S_CER_ptr(e_REGION_ID region_id) 
        {
            uint32_t CER = AM335x_EDMA3CC_BASE + 0x2018 +  (0X200*region_id);        
            return (CER_reg_t*&)CER;
        }
    
        inline  EER_reg_t*& get_S_EER_ptr(e_REGION_ID region_id)
        {
            uint32_t EER = AM335x_EDMA3CC_BASE + 0x2020 +  (0X200*region_id);        
            return (EER_reg_t*&)EER;
        }
    
        inline EERH_reg_t*& get_S_EERH_ptr(e_REGION_ID region_id)
        {
            uint32_t EERH = AM335x_EDMA3CC_BASE + 0x2024 +  (0X200*region_id);        
            return (EERH_reg_t*&)EERH;
        }
    
        inline EECR_reg_t*& get_S_EECR_ptr(e_REGION_ID region_id)
        {
            uint32_t EECR = AM335x_EDMA3CC_BASE + 0x2028 +  (0X200*region_id);        
            return (EECR_reg_t*&)EECR;
        }
    
        inline EECRH_reg_t*& get_S_EECRH_ptr(e_REGION_ID region_id)
        {
            uint32_t EECRH = AM335x_EDMA3CC_BASE + 0x202C +  (0X200*region_id);        
            return (EECRH_reg_t*&)EECRH;
        }
    
        inline EESR_reg_t*& get_S_EESR_ptr(e_REGION_ID region_id)
        {
            uint32_t EESR = AM335x_EDMA3CC_BASE + 0x2030 +  (0X200*region_id);        
            return (EESR_reg_t*&)EESR;
        }
    
        inline EESRH_reg_t*& get_S_EESRH_ptr(e_REGION_ID region_id)
        {
            uint32_t EESRH = AM335x_EDMA3CC_BASE + 0x2034 +  (0X200*region_id);        
            return (EESRH_reg_t*&)EESRH;
        }
    
        inline  SER_reg_t*& get_S_SER_ptr(e_REGION_ID region_id) 
        {
            uint32_t SER = AM335x_EDMA3CC_BASE + 0x2038 +  (0X200*region_id);        
            return (SER_reg_t*&)SER;
        }
    
        inline SERH_reg_t*& get_S_SERH_ptr(e_REGION_ID region_id)
        {
            uint32_t SERH = AM335x_EDMA3CC_BASE + 0x203C +  (0X200*region_id);        
            return (SERH_reg_t*&)SERH;
        }
    
        inline SECR_reg_t*& get_S_SECR_ptr(e_REGION_ID region_id)
        {
            uint32_t SECR = AM335x_EDMA3CC_BASE + 0x2040 +  (0X200*region_id);        
            return (SECR_reg_t*&)SECR;
        }
    
        inline SECRH_reg_t*& get_S_SECRH_ptr(e_REGION_ID region_id)
        {
            uint32_t SECRH = AM335x_EDMA3CC_BASE + 0x2044 +  (0X200*region_id);        
            return (SECRH_reg_t*&)SECRH;
        }
    
        inline  IER_reg_t*& get_S_IER_ptr(e_REGION_ID region_id)
        {
            uint32_t IER = AM335x_EDMA3CC_BASE + 0x2050 +  (0X200*region_id);        
            return (IER_reg_t*&)IER;
        }
    
        inline IERH_reg_t*& get_S_IERH_ptr(e_REGION_ID region_id)
        {
            uint32_t IERH = AM335x_EDMA3CC_BASE + 0x2054 +  (0X200*region_id);        
            return (IERH_reg_t*&)IERH;
        }
    
        inline IECR_reg_t*& get_S_IECR_ptr(e_REGION_ID region_id)
        {
            uint32_t IECR = AM335x_EDMA3CC_BASE + 0x2058 +  (0X200*region_id);        
            return (IECR_reg_t*&)IECR;
        }
    
        inline IECRH_reg_t*& get_S_IECRH_ptr(e_REGION_ID region_id) 
        {
            uint32_t IECRH = AM335x_EDMA3CC_BASE + 0x205C +  (0X200*region_id);        
            return (IECRH_reg_t*&)IECRH;
        }
    
        inline IESR_reg_t*& get_S_IESR_ptr(e_REGION_ID region_id)
        {
            uint32_t IESR = AM335x_EDMA3CC_BASE + 0x2060 +  (0X200*region_id);        
            return (IESR_reg_t*&)IESR;
        }
    
        inline IESRH_reg_t*& get_S_IESRH_ptr(e_REGION_ID region_id)
        {
            uint32_t IESRH = AM335x_EDMA3CC_BASE + 0x2064 +  (0X200*region_id);        
            return (IESRH_reg_t*&)IESRH;
        }
    
        inline  IPR_reg_t*& get_S_IPR_ptr(e_REGION_ID region_id)
        {
            uint32_t IPR = AM335x_EDMA3CC_BASE + 0x2068 +  (0X200*region_id);        
            return (IPR_reg_t*&)IPR;
        }
    
        inline IPRH_reg_t*& get_S_IPRH_ptr(e_REGION_ID region_id)
        {
            uint32_t IPRH = AM335x_EDMA3CC_BASE + 0x206C +  (0X200*region_id);        
            return (IPRH_reg_t*&)IPRH;
        }
    
        inline  ICR_reg_t*& get_S_ICR_ptr(e_REGION_ID region_id)
        {
            uint32_t ICR = AM335x_EDMA3CC_BASE + 0x2070 +  (0X200*region_id);        
            return (ICR_reg_t*&)ICR;
        }
    
        inline ICRH_reg_t*& get_S_ICRH_ptr(e_REGION_ID region_id)
        {
            uint32_t ICRH = AM335x_EDMA3CC_BASE + 0x2074 +  (0X200*region_id);        
            return (ICRH_reg_t*&)ICRH;
        }
    
        inline IEVAL_reg_t*& get_S_IEVAL_ptr(e_REGION_ID region_id)
        {
            uint32_t IEVAL = AM335x_EDMA3CC_BASE + 0x2078 +  (0X200*region_id);        
            return (IEVAL_reg_t*&)IEVAL;
        }
    
        inline  QER_reg_t*& get_S_QER_ptr(e_REGION_ID region_id) 
        {
            uint32_t QER = AM335x_EDMA3CC_BASE + 0x2080 +  (0X200*region_id);        
            return (QER_reg_t*&)QER;
        }
    
        inline QEER_reg_t*& get_S_QEER_ptr(e_REGION_ID region_id)
        {
            uint32_t QEER = AM335x_EDMA3CC_BASE + 0x2084 +  (0X200*region_id);        
            return (QEER_reg_t*&)QEER;
        }
    
        inline QEECR_reg_t*& get_S_QEECR_ptr(e_REGION_ID region_id)
        {
            uint32_t QEECR = AM335x_EDMA3CC_BASE + 0x2088 +  (0X200*region_id);        
            return (QEECR_reg_t*&)QEECR;
        }
    
        inline QEESR_reg_t*& get_S_QEESR_ptr(e_REGION_ID region_id)
        {
            uint32_t QEESR = AM335x_EDMA3CC_BASE + 0x208C +  (0X200*region_id);        
            return (QEESR_reg_t*&)QEESR;
        }
    
        inline QSER_reg_t*& get_S_QSER_ptr(e_REGION_ID region_id)
        {
            uint32_t QSER = AM335x_EDMA3CC_BASE + 0x2090 +  (0X200*region_id);        
            return (QSER_reg_t*&)QSER;
        }
    
        inline QSECR_reg_t*& get_S_QSECR_ptr(e_REGION_ID region_id)
        {
            uint32_t QSECR = AM335x_EDMA3CC_BASE + 0x2094 +  (0X200*region_id);        
            return (QSECR_reg_t*&)QSECR;
        }
    
        inline uint32_t* get_paRAM_ptr(uint32_t n)         
        { 
            return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + (0x20 * n)); 
        }
        
        inline uint32_t* get_SRC_ptr(uint32_t n)           
        { 
          return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x4 + (0x20 * n)); 
        }

        inline uint32_t* get_A_B_CNT_ptr(uint32_t n)       { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x8 + (0x20 * n)); }
        inline uint32_t* get_DST_ptr(uint32_t n)           { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0xC + (0x20 * n)); }
        inline uint32_t* get_SRC_DST_BIDX_ptr(uint32_t n)  { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x10 + (0x20 * n)); }
        inline uint32_t* get_LINK_BCNTRLD_ptr(uint32_t n)  { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x14 + (0x20 * n)); }
        inline uint32_t* get_SRC_DST_CIDX_ptr(uint32_t n)  { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x18 + (0x20 * n)); }
        inline uint32_t* get_CCNT_ptr(uint32_t n)          { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x1C + (0x20 * n)); }
    
    }   // namespace EDMA
}   // namespace REGS

#endif //__EDMA_H
