#ifndef _EMIF_H_
#define _EMIF_H_

#include <stdint.h>

namespace REGS
{
    //This is EMIF namespace
    namespace EMIF
    { 
    /*******************************************************************************************************************************************************************************/  
    
    /*************************************************************************** AM335x_DDR23mPHY_Type Registers **********************************************************************/ 
    
    /*******************************************************************************************************************************************************************************/      
        
        /* [reset state = 0x80] [offset = 0x01C, 0x050, 0x084]*/
        typedef union 
        {                                            /* 
                                                      */
            struct 
            {                                         
                uint32_t    CMD_SLAVE_RATIO  :10;     // bit: 0..9   (W) Ratio value for address/command launch timing in DDR PHY macro. This is the fraction of a
                                                      //                 clock cycle represented by the shift to be applied to the read DQS in units of 256ths. In other
                                                      //                 words, the full-cycle tap value from the master DLL will be scaled by this number over 256 to
                                                      //                 get the delay value for the slave delay line.
                                                      //                 [values 0-100h]
                uint32_t                     :22;     // bit: 10..31 (R)  Reserved             
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } CSR0_reg_t;

        /* [reset state = 0x4] [offset = 0x028, 0x05C, 0x090]*/
        typedef union 
        {                                 /* This register should
                                           * be left at its default value and should not be altered for proper operation.
                                           */
            struct 
            {                                         
                uint32_t    DLL_LOCK_DIFF  :4;      // bit: 0..3  (W) The max number of delay line taps variation allowed while maintaining the master DLL lock.This is
                                                    //                calculated as total jitter/ delay line tap size, where total jitter is half of (incoming clock jitter (pp) +
                                                    //                delay line jitter (pp)). 
                                                    //                [values 0-4h]
                uint32_t                   :28;     // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } DLD0_reg_t;

        /* [reset state = 0x0] [offset = 0x0x02C, 0x060, 0x094]*/
        typedef union 
        {                                           /* 
                                                     */
            struct 
            {                                         
                uint32_t    INVERT_CLK_SEL  :1;      // bit: 0     (W) Inverts the polarity of DRAM clock.
                                                     //                [0x0 = Core clock is passed on to DRAM, 
                                                     //                 0x1 = inverted core clock is passed on to DRAM]
                uint32_t                    :31;     // bit: 1..31 (R)  Reserved             
            } b;                                     // Structure used for bit access 
            uint32_t  reg;                           // Type used for register access 
        } ICLK0_reg_t;

        /* [reset state = 0x04010040] [offset = 0x0C8, 0x16C]*/
        typedef union 
        {                                            /* 
                                                      */
            struct 
            {                                         
                uint32_t    RD_DQS_SLAVE_RATIO_CS0  :10;    // bit: 0..9   (W) Ratio value for Read DQS slave DLL for CS0.
                                                            //                 40h This is the fraction of a clock cycle represented by the shift to be applied to the read DQS in units of
                                                            //                 256ths. In other words, the full-cycle tap value from the master DLL will be scaled by this number
                                                            //                 over 256 to get the delay value for the slave delay line. 
                                                            //                 [values 0-40h]
                uint32_t                            :22;    // bit: 10..31 (R)  Reserved             
            } b;                                            // Structure used for bit access 
            uint32_t  reg;                                  // Type used for register access 
        } RDQSSR0_reg_t;

        /* [reset state = 0x0] [offset = 0x0DC, 0x180]*/
        typedef union 
        {                                            /* 
                                                      */
            struct 
            {                                         
                uint32_t    WR_DQS_SLAVE_RATIO_CS0  :10;      // bit: 0..9   (W) Ratio value for Write DQS slave DLL for CS0.
                                                              //                 This is the fraction of a clock cycle represented by the shift to be applied to the write DQS in
                                                              //                 units of 256ths. In other words, the full-cycle tap value from the master DLL will be scaled by
                                                              //                 this number over 256 to get the delay value for the slave delay line. [values 0-40h]
                uint32_t                            :22;      // bit: 10..31 (R)  Reserved             
            } b;                                              // Structure used for bit access 
            uint32_t  reg;                                    // Type used for register access 
        } WDQSSR0_reg_t;

        /* [reset state = 0x0] [offset = 0x0F0, 0x194]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    WRLVL_INIT_RATIO_CS0  :10;      // bit: 0..9   (W)  The user programmable init ratio used by Write Leveling FSM when
                                                            //                  DATA0/1_REG_PHY_WRLVL_INIT_MODE_0 register value set to 1

                uint32_t                          :22;      // bit: 10..31 (R)  Reserved             
            } b;                                            // Structure used for bit access 
            uint32_t  reg;                                  // Type used for register access 
        } MWRLVLINI_RATIO_reg_t;

        /* [reset state = 0x0] [offset = 0x0F8, 0x19C]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    WRLVL_INIT_MODE_SEL  :1;        // bit: 0       (W) The user programmable init ratio selection mode for Write Leveling FSM.
                                                            //                  [0x0 = Selects a starting ratio value based on Write Leveling of previous data slice;
                                                            //                   0x1 = Selects a starting ratio value based in register DATA0/1_REG_PHY_WRLVL_INIT_RATIO_0 value programmed by the user.]                
                uint32_t                         :31;       // bit: 1..31   (R)  Reserved             
            } b;                                            // Structure used for bit access 
            uint32_t  reg;                                  // Type used for register access 
        } MWRLVLINI_MODE_reg_t;

        /* [reset state = 0x0] [offset = 0x0FC, 0x1A0]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    GATELVL_INIT_RATIO_CS0  :10;    // bit: 0..9    (W) The user programmable init ratio used by DQS Gate Training FSM when
                                                            //                  DATA0/1/_REG_PHY_GATELVL_INIT_MODE_0 register value set to 1.
                uint32_t                            :22;    // bit: 10..31  (R)  Reserved             
            } b;                                            // Structure used for bit access 
            uint32_t  reg;                                  // Type used for register access 
        } DQSGTI_RATIO_reg_t;

        /* [reset state = 0x0] [offset = 0x104, 0x1A8]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    GATELVL_INIT_MODE_SEL  :1;      // bit: 0       (W)  User programmable init ratio selection mode for DQS Gate Training FSM.
                                                            //                  [0x0 Selects a starting ratio value based on Write Leveling of the same data slice;
                                                            //                   0x1 selects a starting ratio value based on DATA0/1_REG_PHY_GATELVL_INIT_RATIO_0 value programmed by the user]
                uint32_t                           :31;     // bit: 1..31   (R)  Reserved             
            } b;                                            // Structure used for bit access 
            uint32_t  reg;                                  // Type used for register access 
        } DQS_GTI_MODE_reg_t;

        /* [reset state = 0x0] [offset = 0x108, 0x1AC]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    FIFO_WE_SLAVE_RATIO_CS0     :10;    // bit: 0..9    (W) Ratio value for fifo we for CS0.
                uint32_t                                :22;    // bit: 10..31  (R) Reserved             
            } b;                                                // Structure used for bit access 
            uint32_t  reg;                                      // Type used for register access 
        } DQS_GS_RATIO_reg_t;

        /* [reset state = 0x4] [offset = 0x11C, 0x1C0]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    OFFSET  :7;     // bit: 0..6   (RW) Default value 40 equates to a 90 degree shift.
                uint32_t            :25;    // bit: 7..31 (R)  Reserved             
            } b;                            // Structure used for bit access 
            uint32_t  reg;                  // Type used for register access 
        } DQS_T_DQ_OFFSET_reg_t;

        /* [reset state = 0x04010040] [offset = 0x120, 0x1C4] */
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    WR_DATA_SLAVE_RATIO_CS0     :10;    // bit: 0..9    (W) Ratio value for write data slave DLL for CS0.
                                                                //                  This is the fraction of a clock cycle represented by the shift to be applied to
                                                                //                  the write DQ muxes in units of 256ths. In other words, the full-cycle tap
                                                                //                  value from the master DLL will be scaled by this number over 256 to get the
                                                                //                  delay value for the slave delay line.
                                                                //                  [values 0-40h]
                uint32_t                                :22;    // bit: 10..31  (R) Reserved             
            } b;                                                // Structure used for bit access 
            uint32_t  reg;                                      // Type used for register access 
        } WDS_RATIO_reg_t;

        /* [reset state = 0x0] [offset = 0x134, 0x1D8]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    RANK0_DELAY    :1;      // bit: 0       (W) Delay Selection
                                                    //                  [0x0 = Each Rank uses its own delay. (Recommended). This is applicable only in case of DDR3;
                                                    //                   0x1 = Rank 0 delays are used for all ranks. This must be set to 1 for DDR2 and mDDR.]

                uint32_t                    :31;    // bit: 1..31   (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } DELAY_SEL_reg_t;

        /* [reset state = 0x4] [offset = 0x138, 0x1DC]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    DLL_LOCK_DIFF   :4;     // bit: 0..3  (W) The max number of delay line taps variation allowed while maintaining the master DLL lock.This is
                                                    //               calculated as total jitter/ delay line tap size, where total jitter is half of (incoming clock jitter (pp) +
                                                    //               delay line jitter (pp)).
                                                    //               [values 0-4h]
                uint32_t                    :28;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } DLL_LOCK_DIFF_reg_t; 

    /*******************************************************************************************************************************************************************************/  
    
    /*************************************************************************** AM335x_EMIF4D_Type Registers **********************************************************************/ 
    
    /*******************************************************************************************************************************************************************************/      

        /* (offset = 0x0) [reset = 0x40443403] */
        typedef union 
        {
                                                  /* EMIF_MOD_ID_REV
                                                   */
            struct 
            {                                      
                uint32_t    MINOR_REV    : 6;      // bits 0..5   (R) Minor Revision
                uint32_t                 : 2;      // bits 6..7   (R) Reserved 
                uint32_t    MAJOR_REV    : 3;      // bits 8..10  (R) Major Revision
                uint32_t    RTL_VERSION  : 5;      // bits 11..15 (R) RTL Version
                uint32_t    MODULE_ID    :12;      // bits 16..27 (R) EMIF module ID
                uint32_t                 : 2;      // bits 28..29 (R) Reserved
                uint32_t    SCHEME       : 2;      // bits 30..31 (R) Scheme indicator [0x1 = old scheme; 0x2 = current scheme]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } EMIF_MOD_ID_REV_reg_t;
        
        /* (offset = 0x4) [reset = 0x40000000] */
        typedef union 
        {
                                                  /* STATUS
                                                   */
            struct 
            {                                      
                uint32_t                 : 2;      // bits 0..1   (R) Reserved
                uint32_t    PHY_DLL_READY: 1;      // bit  2      (R) DDR PHY Ready [0x0 = not ready; 0x1 = ready]
                uint32_t                 :26;      // bits 3..28  (R) Reserved
                uint32_t    FAST_INIT    : 1;      // bit  29     (R) Fast Init enabled [0x0 = disabled; 0x1 = enabled]
                uint32_t    DUAL_CLK_MODE: 1;      // bit  30     (R) Dual Clock mode [0x0 = synchronous; 0x1 = asynchronous]
                uint32_t    BE           : 1;      // bit  31     (R) Big Endian mode [0x0 = little endian; 0x1 = big endian]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } STATUS_reg_t;
        
        /* (offset = 0x8) [reset = 0x4104BAB2] */
        typedef union 
        {
                                                  /* SDRAM_CONFIG
                                                   */
            struct 
            {                                      
                uint32_t    PAGESIZE     : 3;      // bits 0..2   (RW) Page Size [see e_PAGESIZE]
                uint32_t    EBANK        : 1;      // bit  3      (RW) External chip select [0x0 = CS0 only; 0x1 = CS0 and CS1]
                uint32_t    IBANK        : 3;      // bits 4..6   (RW) Internal Bank setup [see e_IBANK]
                uint32_t    ROWSIZE      : 3;      // bits 7..9   (RW) Row Size [see e_ROWSIZE]
                uint32_t    CL           : 4;      // bits 10..13 (RW) CAS Latency [see e_CL]
                uint32_t    NARROW_MODE  : 2;      // bits 14..15 (RW) Data bus width [0x0 = 32-bit; 0x1 = 16-bit]
                uint32_t    CWL          : 2;      // bits 16..17 (RW) CAS Write latency [see e_CWL]
                uint32_t    SDRAM_DRIVE  : 2;      // bits 18..19 (RW) Drive strength [see e_SDRAM_DRIVE]
                uint32_t    DDR_DISABLE_DLL:1;     // bit  20     (RW) Disable DLL select [0x0 = enabled; 0x1 = disabled]
                uint32_t    DYN_ODT      : 2;      // bits 21..22 (RW) Dynamic ODT [see e_DYN_ODT]
                uint32_t    DDR2_DDQS    : 1;      // bit  23     (RW) DDR2 diff DQS enable [0x0 = single ended; 0x1 = differential]
                uint32_t    DDR_TERM     : 3;      // bits 24..26 (RW) Termination resistor [see e_DDR_TERM]
                uint32_t    IBANK_POS    : 2;      // bits 27..28 (RW) Internal bank position [see e_IBANK_POS]
                uint32_t    SDRAM_TYPE   : 3;      // bits 29..31 (RW) SDRAM Type selection [see e_SDRAM_TYPE]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_CONFIG_reg_t;
        
        /* Enums for multi-value fields */
        enum e_PAGESIZE : uint32_t 
        {
            PAGE_256_WORDS = 0x0,
            PAGE_512_WORDS = 0x1,
            PAGE_1024_WORDS = 0x2,
            PAGE_2048_WORDS = 0x3
        };
        
        enum e_IBANK : uint32_t 
        {
            BANK_1 = 0x0,
            BANK_2 = 0x1,
            BANK_4 = 0x2,
            BANK_8 = 0x3
        };
        
        enum e_ROWSIZE : uint32_t 
        {
            ROW_9_BITS = 0x0,
            ROW_10_BITS = 0x1,
            ROW_11_BITS = 0x2,
            ROW_12_BITS = 0x3,
            ROW_13_BITS = 0x4,
            ROW_14_BITS = 0x5,
            ROW_15_BITS = 0x6,
            ROW_16_BITS = 0x7
        };
        
        enum e_CL : uint32_t 
        {
            CL_2 = 0x2,
            CL_3 = 0x3,
            CL_4 = 0x4,
            CL_5 = 0x5,
            CL_6 = 0x6,
            CL_8 = 0x8,
            CL_10 = 0xA,
            CL_12 = 0xC,
            CL_14 = 0xE
        };
        
        enum e_CWL : uint32_t 
        {
            CWL_5 = 0x0,
            CWL_6 = 0x1,
            CWL_7 = 0x2,
            CWL_8 = 0x3
        };
        
        enum e_SDRAM_DRIVE : uint32_t 
        {
            DRIVE_NORMAL = 0x0,
            DRIVE_WEAK = 0x1,
            DRIVE_RZQ6 = 0x0,
            DRIVE_RZQ7 = 0x1,
            DRIVE_FULL = 0x0,
            DRIVE_HALF = 0x1,
            DRIVE_QUARTER = 0x2,
            DRIVE_EIGHTH = 0x3
        };
        
        enum e_DYN_ODT : uint32_t 
        {
            ODT_OFF = 0x0,
            ODT_RZQ4 = 0x1,
            ODT_RZQ2 = 0x2
        };
        
        enum e_DDR_TERM : uint32_t 
        {
            TERM_DISABLED = 0x0,
            TERM_75_OHM = 0x1,
            TERM_150_OHM = 0x2,
            TERM_50_OHM = 0x3,
            TERM_RZQ4 = 0x1,
            TERM_RZQ2 = 0x2,
            TERM_RZQ6 = 0x3,
            TERM_RZQ12 = 0x4,
            TERM_RZQ8 = 0x5
        };
        
        enum e_IBANK_POS : uint32_t 
        {
            IBANK_LOWER = 0x0,
            IBANK_HIGHER1 = 0x1,
            IBANK_HIGHER2 = 0x2,
            IBANK_HIGHER3 = 0x3
        };
        
        enum e_SDRAM_TYPE : uint32_t 
        {
            DDR1 = 0x0,
            LPDDR1 = 0x1,
            DDR2 = 0x2,
            DDR3 = 0x3
        };
        
        /* (offset = 0xC) [reset = 0x0] */
        typedef union 
        {
                                                  /* SDRAM_CONFIG_2
                                                   */
            struct 
            {                                      
                uint32_t                 : 5;      // bits 0..4   (R) Reserved
                uint32_t                 : 2;      // bits 5..6   (RW) Reserved
                uint32_t                 : 1;      // bit  7      (R) Reserved
                uint32_t                 :19;      // bits 8..26  (R) Reserved
                uint32_t    EBANK_POS    : 1;      // bit  27     (RW) External bank position [0x0 = lower OCP address; 0x1 = higher OCP address]
                uint32_t                 : 4;      // bits 28..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_CONFIG_2_reg_t;
        
        /* (offset = 0x10) [reset = 0x80001388] */
        typedef union 
        {
                                                  /* SDRAM_REF_CTRL
                                                   */
            struct 
            {                                      
                uint32_t    REFRESH_RATE :16;      // bits 0..15  (RW) Refresh Rate
                uint32_t                 : 7;      // bits 16..22 (R) Reserved
                uint32_t    PASR         : 3;      // bits 23..25 (RW) Partial Array Self Refresh [see e_PASR]
                uint32_t                 : 1;      // bit  26     (R) Reserved
                uint32_t    ASR          : 1;      // bit  27     (RW) Auto Self Refresh [0x0 = manual; 0x1 = auto]
                uint32_t    STR          : 1;      // bit  28     (RW) Self-refresh temp range [0x0 = normal; 0x1 = extended]
                uint32_t                 : 1;      // bit  29     (R) Reserved
                uint32_t    INITREF_DIS  : 1;      // bit  30     (RW) Init/Refresh disable [0x0 = enabled; 0x1 = disabled]
                uint32_t                 : 1;      // bit  31     (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_REF_CTRL_reg_t;
        
        /* Enums for multi-value fields */
        enum e_PASR : uint32_t 
        {
            PASR_FULL = 0x0,
            PASR_HALF = 0x1,
            PASR_QUARTER = 0x2,
            PASR_EIGHTH = 0x5,
            PASR_SIXTEENTH = 0x6,
            PASR_3QUARTERS = 0x4
        };
        
        /* (offset = 0x14) [reset = 0x00001388] */
        typedef union 
        {
                                                  /* SDRAM_REF_CTRL_SHDW
                                                   */
            struct 
            {                                      
                uint32_t    REFRESH_RATE_SHADOW:16;// bits 0..15  (RW) Shadow refresh rate
                uint32_t                 :16;      // bits 16..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_REF_CTRL_SHDW_reg_t;
        
        /* (offset = 0x18) [reset = 0x08891599] */
        typedef union 
        {
                                                  /* SDRAM_TIM_1
                                                   */
            struct 
            {                                      
                uint32_t    WTR          : 3;      // bits 0..2   (RW) Write to Read delay
                uint32_t    RRD          : 3;      // bits 3..5   (RW) Activate to Activate delay
                uint32_t    RC           : 6;      // bits 6..11  (RW) Activate to Activate
                uint32_t    RAS          : 5;      // bits 12..16 (RW) Activate to Pre-charge
                uint32_t    WR           : 4;      // bits 17..20 (RW) Write to Pre-charge
                uint32_t    RCD          : 4;      // bits 21..24 (RW) Activate to Read/Write
                uint32_t    RP           : 4;      // bits 25..28 (RW) Precharge to Activate
                uint32_t                 : 3;      // bits 29..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_TIM_1_reg_t;
        
        /* (offset = 0x1C) [reset = 0x08891599] */
        typedef union 
        {
                                                  /* SDRAM_TIM_1_SHDW
                                                   */
            struct 
            {                                      
                uint32_t    WTR_SHADOW   : 3;      // bits 0..2   (RW) Shadow WTR
                uint32_t    RRD_SHADOW   : 3;      // bits 3..5   (RW) Shadow RRD
                uint32_t    RC_SHADOW    : 6;      // bits 6..11  (RW) Shadow RC
                uint32_t    RAS_SHADOW   : 5;      // bits 12..16 (RW) Shadow RAS
                uint32_t    WR_SHADOW    : 4;      // bits 17..20 (RW) Shadow WR
                uint32_t    RCD_SHADOW   : 4;      // bits 21..24 (RW) Shadow RCD
                uint32_t    RP_SHADOW    : 4;      // bits 25..28 (RW) Shadow RP
                uint32_t                 : 3;      // bits 29..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_TIM_1_SHDW_reg_t;
        
        /* (offset = 0x20) [reset = 0x148B31CA] */
        typedef union 
        {
                                                  /* SDRAM_TIM_2
                                                   */
            struct 
            {                                      
                uint32_t    CKE          : 3;      // bits 0..2   (RW) CKE changes delay
                uint32_t    RTP          : 3;      // bits 3..5   (RW) Read to Precharge
                uint32_t    XSRD         :10;      // bits 6..15  (RW) Self-Refresh exit to Read
                uint32_t    XSNR         : 9;      // bits 16..24 (RW) Self-Refresh exit delay
                uint32_t                 : 3;      // bits 25..27 (RW) Reserved
                uint32_t    XP           : 3;      // bits 28..30 (RW) Powerdown exit delay
                uint32_t                 : 1;      // bit  31     (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_TIM_2_reg_t;
        
        /* (offset = 0x24) [reset = 0x148B31CA] */
        typedef union 
        {
                                                  /* SDRAM_TIM_2_SHDW
                                                   */
            struct 
            {                                      
                uint32_t    CKE_SHADOW   : 3;      // bits 0..2   (RW) Shadow CKE
                uint32_t    RTP_SHADOW   : 3;      // bits 3..5   (RW) Shadow RTP
                uint32_t    XSRD_SHADOW  :10;      // bits 6..15  (RW) Shadow XSRD
                uint32_t    XSNR_SHADOW  : 9;      // bits 16..24 (RW) Shadow XSNR
                uint32_t                 : 3;      // bits 25..27 (RW) Reserved
                uint32_t    XP_SHADOW    : 3;      // bits 28..30 (RW) Shadow XP
                uint32_t                 : 1;      // bit  31     (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_TIM_2_SHDW_reg_t;
        
        /* (offset = 0x28) [reset = 0x00FFE82F] */
        typedef union 
        {
                                                  /* SDRAM_TIM_3
                                                   */
            struct 
            {                                      
                uint32_t    RAS_MAX      : 4;      // bits 0..3   (RW) Max Activate to Precharge
                uint32_t    RFC          : 9;      // bits 4..12  (RW) Refresh/Activate delay
                uint32_t                 : 2;      // bits 13..14 (RW) Reserved
                uint32_t    ZQ_ZQCS      : 6;      // bits 15..20 (RW) ZQCS command cycles
                uint32_t                 : 3;      // bits 21..23 (RW) Reserved
                uint32_t                 : 4;      // bits 24..27 (R) Reserved
                uint32_t    PDLL_UL      : 4;      // bits 28..31 (RW) PHY DLL unlock cycles
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_TIM_3_reg_t;
        
        /* (offset = 0x2C) [reset = 0x00FFE82F] */
        typedef union 
        {
                                                  /* SDRAM_TIM_3_SHDW
                                                   */
            struct 
            {                                      
                uint32_t    RAS_MAX_SHADOW:4;      // bits 0..3   (RW) Shadow RAS_MAX
                uint32_t    RFC_SHADOW   : 9;      // bits 4..12  (RW) Shadow RFC
                uint32_t                 : 2;      // bits 13..14 (RW) Reserved
                uint32_t    ZQ_ZQCS_SHADOW:6;     // bits 15..20 (RW) Shadow ZQ_ZQCS
                uint32_t                 : 3;      // bits 21..23 (RW) Reserved
                uint32_t                 : 4;      // bits 24..27 (R) Reserved
                uint32_t    PDLL_UL_SHADOW:4;     // bits 28..31 (RW) Shadow PDLL_UL
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_TIM_3_SHDW_reg_t;
        
        /* (offset = 0x38) [reset = 0x00000000] */
        typedef union 
        {
                                                  /* PWR_MGMT_CTRL
                                                   */
            struct 
            {                                      
                uint32_t    CS_TIM       : 4;      // bits 0..3   (RW) Clock Stop timer [see e_PWR_TIMER]
                uint32_t    SR_TIM       : 4;      // bits 4..7   (RW) Self Refresh timer [see e_PWR_TIMER]
                uint32_t    LP_MODE      : 3;      // bits 8..10  (RW) Power Management mode [see e_LP_MODE]
                uint32_t    DPD_EN       : 1;      // bit  11     (RW) Deep Power Down enable [0x0 = disabled; 0x1 = enabled]
                uint32_t    PD_TIM       : 4;      // bits 12..15 (RW) Power-Down timer [see e_PWR_TIMER]
                uint32_t                 :16;      // bits 16..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PWR_MGMT_CTRL_reg_t;
        
        /* Enums for multi-value fields */
        enum e_PWR_TIMER : uint32_t 
        {
            PWR_TIMER_IMMEDIATE = 0x0,
            PWR_TIMER_16 = 0x1,
            PWR_TIMER_32 = 0x2,
            PWR_TIMER_64 = 0x3,
            PWR_TIMER_128 = 0x4,
            PWR_TIMER_256 = 0x5,
            PWR_TIMER_512 = 0x6,
            PWR_TIMER_1024 = 0x7,
            PWR_TIMER_2048 = 0x8,
            PWR_TIMER_4096 = 0x9,
            PWR_TIMER_8192 = 0xA,
            PWR_TIMER_16384 = 0xB,
            PWR_TIMER_32768 = 0xC,
            PWR_TIMER_65536 = 0xD,
            PWR_TIMER_131072 = 0xE,
            PWR_TIMER_262144 = 0xF
        };
        
        enum e_LP_MODE : uint32_t 
        {
            LP_DISABLED = 0x0,
            LP_CLOCK_STOP = 0x1,
            LP_SELF_REFRESH = 0x2,
            LP_POWER_DOWN = 0x4
        };
        
        /* (offset = 0x3C) [reset = 0x00000000] */
        typedef union 
        {
                                                  /* PWR_MGMT_CTRL_SHDW
                                                   */
            struct 
            {                                      
                uint32_t    CS_TIM_SHADOW:4;       // bits 0..3   (RW) Shadow CS_TIM [see e_PWR_TIMER]
                uint32_t    SR_TIM_SHADOW:4;       // bits 4..7   (RW) Shadow SR_TIM [see e_PWR_TIMER]
                uint32_t                 : 4;      // bits 8..11  (R) Reserved
                uint32_t    PD_TIM_SHADOW:4;       // bits 12..15 (RW) Shadow PD_TIM [see e_PWR_TIMER]
                uint32_t                 :16;      // bits 16..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PWR_MGMT_CTRL_SHDW_reg_t;
        
        /* (offset = 0x54) [reset = 0x00FFFFFF] */
        typedef union 
        {
                                                  /* OCP_CONFIG
                                                   */
            struct 
            {                                      
                uint32_t    PR_OLD_COUNT : 8;      // bits 0..7   (RW) Priority Raise Old Counter
                uint32_t    COS_COUNT_2  : 8;      // bits 8..15  (RW) Priority Counter COS 2
                uint32_t    COS_COUNT_1  : 8;      // bits 16..23 (RW) Priority Counter COS 1
                uint32_t                 : 8;      // bits 24..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } OCP_CONFIG_reg_t;
        
        /* (offset = 0x58) [reset = 0x8000140A] */
        typedef union 
        {
                                                  /* OCP_CFG_VAL_1
                                                   */
            struct 
            {                                      
                uint32_t    CMD_FIFO_DEPTH:8;     // bits 0..7   (R) Command FIFO depth
                uint32_t    WR_FIFO_DEPTH:8;      // bits 8..15  (R) Write Data FIFO depth
                uint32_t                 :14;      // bits 16..29 (R) Reserved
                uint32_t    SYS_BUS_WIDTH:2;      // bits 30..31 (R) L3 OCP data bus width [see e_SYS_BUS_WIDTH]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } OCP_CFG_VAL_1_reg_t;
        
        /* Enums for multi-value fields */
        enum e_SYS_BUS_WIDTH : uint32_t 
        {
            BUS_WIDTH_32 = 0x0,
            BUS_WIDTH_64 = 0x1,
            BUS_WIDTH_128 = 0x2,
            BUS_WIDTH_256 = 0x3
        };
        
        /* (offset = 0x5C) [reset = 0x00021616] */
        typedef union 
        {
                                                  /* OCP_CFG_VAL_2
                                                   */
            struct 
            {                                      
                uint32_t    RCMD_FIFO_DEPTH:8;    // bits 0..7   (R) Read Command FIFO depth
                uint32_t    RSD_FIFO_DEPTH:8;     // bits 8..15  (R) SDRAM Read Data FIFO depth
                uint32_t    RREG_FIFO_DEPTH:8;    // bits 16..23 (R) Register Read FIFO depth
                uint32_t                 : 8;      // bits 24..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } OCP_CFG_VAL_2_reg_t;
        
        /* (offset = 0x80) [reset = 0x00592A49] */
        typedef union 
        {
                                                  /* PERF_CNT_1
                                                   */
            struct 
            {                                      
                uint32_t    COUNTER1     :32;      // bits 0..31  (R) Performance counter 1
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PERF_CNT_1_reg_t;
        
        /* (offset = 0x84) [reset = 0x0001FEB9] */
        typedef union 
        {
                                                  /* PERF_CNT_2
                                                   */
            struct 
            {                                      
                uint32_t    COUNTER2     :32;      // bits 0..31  (R) Performance counter 2
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PERF_CNT_2_reg_t;
        
        /* (offset = 0x88) [reset = 0x00010000] */
        typedef union 
        {
                                                  /* PERF_CNT_CFG
                                                   */
            struct 
            {                                      
                uint32_t    CNTR1_CFG    : 4;      // bits 0..3   (RW) Counter 1 config
                uint32_t                 :10;      // bits 4..13  (R) Reserved
                uint32_t    CNTR1_REGION_EN:1;     // bit  14     (RW) Counter 1 region enable [0x0 = disabled; 0x1 = enabled]
                uint32_t    CNTR1_MCONNID_EN:1;    // bit  15     (RW) Counter 1 MConnID enable [0x0 = disabled; 0x1 = enabled]
                uint32_t    CNTR2_CFG    : 4;      // bits 16..19 (RW) Counter 2 config
                uint32_t                 : 6;      // bits 20..25 (R) Reserved
                uint32_t    CNTR2_REGION_EN:1;     // bit  26     (RW) Counter 2 region enable [0x0 = disabled; 0x1 = enabled]
                uint32_t    CNTR2_MCONNID_EN:1;    // bit  27     (RW) Counter 2 MConnID enable [0x0 = disabled; 0x1 = enabled]
                uint32_t                 : 4;      // bits 28..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PERF_CNT_CFG_reg_t;
        
        /* (offset = 0x8C) [reset = 0x0] */
        typedef union 
        {
                                                  /* PERF_CNT_SEL
                                                   */
            struct 
            {                                      
                uint32_t    REGION_SEL1  : 2;      // bits 0..1   (RW) MMddrSpace for Counter 1
                uint32_t                 : 6;      // bits 2..7   (R) Reserved
                uint32_t    MCONNID1     : 8;      // bits 8..15  (RW) MConnID for Counter 1
                uint32_t    REGION_SEL2  : 2;      // bits 16..17 (RW) MMddrSpace for Counter 2
                uint32_t                 : 6;      // bits 18..23 (R) Reserved
                uint32_t    MCONNID2     : 8;      // bits 24..31 (RW) MConnID for Counter 2
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PERF_CNT_SEL_reg_t;
        
        /* (offset = 0x90) [reset = 0xA484D432] */
        typedef union 
        {
                                                  /* PERF_CNT_TIM
                                                   */
            struct 
            {                                      
                uint32_t    TOTAL_TIME   :32;      // bits 0..31  (R) Total m_clk cycles counter
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PERF_CNT_TIM_reg_t;
        
        /* (offset = 0x98) [reset = 0x00050000] */
        typedef union 
        {
                                                  /* READ_IDLE_CTRL
                                                   */
            struct 
            {                                      
                uint32_t    READ_IDLE_INTERVAL:9;  // bits 0..8   (RW) Read idle interval
                uint32_t                 : 7;      // bits 9..15  (R) Reserved
                uint32_t    READ_IDLE_LEN:4;       // bits 16..19 (RW) Read idle length
                uint32_t                 :12;      // bits 20..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } READ_IDLE_CTRL_reg_t;
        
        /* (offset = 0x9C) [reset = 0x00050000] */
        typedef union 
        {
                                                  /* READ_IDLE_CTRL_SHDW
                                                   */
            struct 
            {                                      
                uint32_t    READ_IDLE_INTERVAL_SHADOW:9;// bits 0..8 (RW) Shadow interval
                uint32_t                 : 7;      // bits 9..15  (R) Reserved
                uint32_t    READ_IDLE_LEN_SHADOW:4;// bits 16..19 (RW) Shadow length
                uint32_t                 :12;      // bits 20..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } READ_IDLE_CTRL_SHDW_reg_t;
        
        /* (offset = 0xA4) [reset = 0x0] */
        typedef union 
        {
                                                  /* IRQSTATUS_RAW_SYS
                                                   */
            struct 
            {                                      
                uint32_t    ERR_SYS      : 1;      // bit  0      (RW) System error raw status [0x0 = no error; 0x1 = error]
                uint32_t    TA_SYS       : 1;      // bit  1      (RW) System TA raw status [0x0 = no error; 0x1 = error]
                uint32_t                 :30;      // bits 2..31  (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } IRQSTATUS_RAW_SYS_reg_t;
        
        /* (offset = 0xAC) [reset = 0x0] */
        typedef union 
        {
                                                  /* IRQSTATUS_SYS
                                                   */
            struct 
            {                                      
                uint32_t    ERR_SYS      : 1;      // bit  0      (RW) System error status [0x0 = no error; 0x1 = error]
                uint32_t    TA_SYS       : 1;      // bit  1      (RW) System TA status [0x0 = no error; 0x1 = error]
                uint32_t                 :30;      // bits 2..31  (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } IRQSTATUS_SYS_reg_t;
        
        /* (offset = 0xB4) [reset = 0x0] */
        typedef union 
        {
                                                  /* IRQENABLE_SET_SYS
                                                   */
            struct 
            {                                      
                uint32_t    EN_ERR_SYS   : 1;      // bit  0      (RW) System error enable set [0x0 = disabled; 0x1 = enabled]
                uint32_t    EN_TA_SYS    : 1;      // bit  1      (RW) System TA enable set [0x0 = disabled; 0x1 = enabled]
                uint32_t                 :30;      // bits 2..31  (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } IRQENABLE_SET_SYS_reg_t;
        
        /* IRQENABLE_CLR_SYS (offset = 0xBC) [reset = 0x0] */
        typedef union 
        {
                                                  /* IRQENABLE_CLR_SYS
                                                   */
            struct 
            {                                      
                uint32_t    EN_ERR_SYS   : 1;      // bit  0      (RW) System error enable clear [0x0 = no effect; 0x1 = disable]
                uint32_t    EN_TA_SYS    : 1;      // bit  1      (RW) System TA enable clear [0x0 = no effect; 0x1 = disable]
                uint32_t                 :30;      // bits 2..31  (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } IRQENABLE_CLR_SYS_reg_t;
        
        /* (offset = 0xC8) [reset = 0x0] */
        typedef union 
        {
                                                  /* ZQ_CONFIG
                                                   */
            struct 
            {                                      
                uint32_t    REFINTERVAL  :16;      // bits 0..15  (RW) Refresh periods between ZQCS
                uint32_t    ZQCL_MULT    : 2;      // bits 16..17 (RW) ZQCL multiplier [see e_ZQ_MULT]
                uint32_t    ZQINIT_MULT  : 2;      // bits 18..19 (RW) ZQINIT multiplier [see e_ZQ_MULT]
                uint32_t                 : 8;      // bits 20..27 (R) Reserved
                uint32_t    SFEXITEN     : 1;      // bit  28     (RW) ZQCL on power-down exit [0x0 = disabled; 0x1 = enabled]
                uint32_t    DUALCALEN    : 1;      // bit  29     (RW) Dual Calibration enable [0x0 = disabled; 0x1 = enabled]
                uint32_t    CS0EN        : 1;      // bit  30     (RW) ZQ cal for CS0 enable [0x0 = disabled; 0x1 = enabled]
                uint32_t    CS1EN        : 1;      // bit  31     (RW) ZQ cal for CS1 enable [0x0 = disabled; 0x1 = enabled]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } ZQ_CONFIG_reg_t;
        
        /* Enums for multi-value fields */
        enum e_ZQ_MULT : uint32_t 
        {
            ZQ_MULT_1 = 0x0,
            ZQ_MULT_2 = 0x1,
            ZQ_MULT_3 = 0x2,
            ZQ_MULT_4 = 0x3
        };

        /* (offset = 0xD4) [reset = 0x00000000] */ 
        typedef union 
        {                                             /* ReadWriteLevelingRampWindow
                                                       */
            struct 
            {                                      
                uint32_t RDWRLVLINC_RMP_WIN :13;    // bits 0..12  (R)  Incremental leveling ramp window in number of refresh periods (value = programmed -1)
                uint32_t                    :19;    // bits 13..31 (R)  Reserved 
            } b;                                    // bit access
            uint32_t reg;                           // raw register
        } EMIF_RDWRLVL_RAMP_WIN_reg_t;
        
        /*  (offset = 0xD8) [reset = 0x00000000] */ 
        typedef union 
        {                                             /* ReadWriteLevelingRampControl
                                                       */
            struct 
            {                                      
                uint32_t WRLVLINC_RMP_INT   :8;     // bits 0..7   (RW) Incremental write leveling interval during ramp window [0x0 = disabled]
                uint32_t RDLVLGATEINC_RMP_INT:8;    // bits 8..15  (RW) Incremental read DQS gate training interval during ramp window [0x0 = disabled]
                uint32_t RDLVLINC_RMP_INT   :8;     // bits 16..23 (RW) Incremental read data eye training interval during ramp window [0x0 = disabled]
                uint32_t RDWRLVLINC_RMP_PRE :7;     // bits 24..30 (RW) Incremental leveling pre-scalar in refresh periods (value = programmed -1)
                uint32_t RDWRLVL_EN        :1;      // bit  31     (RW) Read-Write Leveling enable [0x0 = disable; 0x1 = enable]
            } b;                                    // bit access
            uint32_t reg;                           // raw register
        } EMIF_RDWRLVL_RAMP_CTRL_reg_t;

        /* (offset = 0xDC) [reset = 0x00000000] */ 
        typedef union 
        {                                             /* ReadWriteLevelingControl
                                                       */
            struct 
            {                                      
                uint32_t WRLVLINC_INT      :8;        // bits 0..7   (RW) Incremental write leveling interval [0x0 = disabled]
                uint32_t RDLVLGATEINC_INT  :8;        // bits 8..15  (RW) Incremental read DQS gate training interval [0x0 = disabled]
                uint32_t RDLVLINC_INT      :8;        // bits 16..23 (RW) Incremental read data eye training interval [0x0 = disabled]
                uint32_t RDWRLVLINC_PRE    :7;        // bits 24..30 (RW) Incremental leveling pre-scalar in refresh periods (value = programmed -1)
                uint32_t RDWRLVLFULL_START :1;        // bit  31     (RW) Full leveling trigger [0x1 = trigger (self-clearing)]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } EMIF_RDWRLVL_CTRL_reg_t;
        
        /* (offset = 0xE4) [reset = 0x0] */
        typedef union 
        {
                                                  /* DDR_PHY_CTRL_1
                                                   */
            struct 
            {                                      
                uint32_t    READ_LATENCY : 5;      // bits 0..4   (RW) Read data latency
                uint32_t                 : 3;      // bits 5..7   (R) Reserved
                uint32_t    RD_LOCAL_ODT : 2;      // bits 8..9   (RW) Read local ODT value [see e_LOCAL_ODT]
                uint32_t    WR_LOCAL_ODT : 2;      // bits 10..11 (RW) Write local ODT value [see e_LOCAL_ODT]
                uint32_t    IDLE_LOCAL_ODT:2;      // bits 12..13 (RW) Idle local ODT value [see e_LOCAL_ODT]
                uint32_t                 : 1;      // bit  14     (R) Reserved
                uint32_t    PHY_RST_N    : 1;      // bit  15     (RW) PHY reset control [0x0 = reset; 0x1 = normal]
                uint32_t                 : 4;      // bits 16..19 (R) Reserved
                uint32_t    ENABLE_DYNAMIC_PWRDN:1;// bit  20     (RW) Dynamic IO power down [0x0 = always on; 0x1 = dynamic]
                uint32_t                 :11;      // bits 21..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } DDR_PHY_CTRL_1_reg_t;
        
        /* Enums for multi-value fields */
        enum e_LOCAL_ODT : uint32_t 
        {
            ODT_OFF = 0x0,
            ODT_FULL = 0x2,
            ODT_HALF = 0x3
        };
        
        /* (offset = 0xE8) [reset = 0x0] */
        typedef union 
        {
                                                  /* DDR_PHY_CTRL_1_SHDW
                                                   */
            struct 
            {                                      
                uint32_t    READ_LATENCY_SHADOW:5; // bits 0..4   (RW) Shadow read latency
                uint32_t                 : 3;      // bits 5..7   (R) Reserved
                uint32_t    RD_LOCAL_ODT_SHADOW:2; // bits 8..9   (RW) Shadow read ODT [see e_LOCAL_ODT]
                uint32_t    WR_LOCAL_ODT_SHADOW:2; // bits 10..11 (RW) Shadow write ODT [see e_LOCAL_ODT]
                uint32_t    IDLE_LOCAL_ODT_SHADOW:2;// bits 12..13 (RW) Shadow idle ODT [see e_LOCAL_ODT]
                uint32_t                 : 1;      // bit  14     (R) Reserved
                uint32_t    PHY_RST_N_SHADOW:1;    // bit  15     (RW) Shadow PHY reset [0x0 = reset; 0x1 = normal]
                uint32_t                 :16;      // bits 16..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } DDR_PHY_CTRL_1_SHDW_reg_t;
        
        /* (offset = 0x100) [reset = 0x0] */
        typedef union 
        {
                                                  /* PRIORITY_TO_COS_MAPPING
                                                   */
            struct 
            {                                      
                uint32_t    PRI_0_COS    : 2;      // bits 0..1   (RW) Priority 0 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_1_COS    : 2;      // bits 2..3   (RW) Priority 1 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_2_COS    : 2;      // bits 4..5   (RW) Priority 2 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_3_COS    : 2;      // bits 6..7   (RW) Priority 3 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_4_COS    : 2;      // bits 8..9   (RW) Priority 4 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_5_COS    : 2;      // bits 10..11 (RW) Priority 5 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_6_COS    : 2;      // bits 12..13 (RW) Priority 6 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_7_COS    : 2;      // bits 14..15 (RW) Priority 7 COS mapping [see e_COS_MAPPING]
                uint32_t                 :15;      // bits 16..30 (R) Reserved
                uint32_t    PRI_COS_MAP_EN:1;      // bit  31     (RW) Priority mapping enable [0x0 = disabled; 0x1 = enabled]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PRIORITY_TO_COS_MAPPING_reg_t;
        
        /* Enums for multi-value fields */
        enum e_COS_MAPPING : uint32_t 
        {
            COS_NONE = 0x0,
            COS_1 = 0x1,
            COS_2 = 0x2,
            COS_INVALID = 0x3
        };
        
        /* (offset = 0x104) [reset = 0x0] */
        typedef union 
        {
                                                  /* CONNID_TO_COS_1_MAPPING
                                                   */
            struct 
            {                                      
                uint32_t    MSK_3_COS_1  : 2;      // bits 0..1   (RW) Mask for ConnID 3 COS 1 [see e_CONNID_MASK]
                uint32_t    CONNID_3_COS_1:8;      // bits 2..9   (RW) ConnID value 3 COS 1
                uint32_t    MSK_2_COS_1  : 2;      // bits 10..11 (RW) Mask for ConnID 2 COS 1 [see e_CONNID_MASK]
                uint32_t    CONNID_2_COS_1:8;      // bits 12..19 (RW) ConnID value 2 COS 1
                uint32_t    MSK_1_COS_1  : 3;      // bits 20..22 (RW) Mask for ConnID 1 COS 1 [see e_CONNID_MASK_EXT]
                uint32_t    CONNID_1_COS_1:8;      // bits 23..30 (RW) ConnID value 1 COS 1
                uint32_t    CONNID_COS_1_MAP_EN:1; // bit  31     (RW) ConnID mapping enable [0x0 = disabled; 0x1 = enabled]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } CONNID_TO_COS_1_MAPPING_reg_t;
        
        /* Enums for multi-value fields */
        enum e_CONNID_MASK : uint32_t 
        {
            MASK_NONE = 0x0,
            MASK_BIT0 = 0x1,
            MASK_BITS1_0 = 0x2,
            MASK_BITS2_0 = 0x3
        };
        
        enum e_CONNID_MASK_EXT : uint32_t 
        {
            MASK_EXT_NONE = 0x0,
            MASK_EXT_BIT0 = 0x1,
            MASK_EXT_BITS1_0 = 0x2,
            MASK_EXT_BITS2_0 = 0x3,
            MASK_EXT_BITS3_0 = 0x4,
            MASK_EXT_BITS4_0 = 0x5,
            MASK_EXT_BITS5_0 = 0x6,
            MASK_EXT_BITS6_0 = 0x7
        };
        
        /* (offset = 0x108) [reset = 0x0] */
        typedef union 
        {
                                                  /* CONNID_TO_COS_2_MAPPING
                                                   */
            struct 
            {                                      
                uint32_t    MSK_3_COS_2  : 2;      // bits 0..1   (RW) Mask for ConnID 3 COS 2 [see e_CONNID_MASK]
                uint32_t    CONNID_3_COS_2:8;      // bits 2..9   (RW) ConnID value 3 COS 2
                uint32_t    MSK_2_COS_2  : 2;      // bits 10..11 (RW) Mask for ConnID 2 COS 2 [see e_CONNID_MASK]
                uint32_t    CONNID_2_COS_2:8;      // bits 12..19 (RW) ConnID value 2 COS 2
                uint32_t    MSK_1_COS_2  : 3;      // bits 20..22 (RW) Mask for ConnID 1 COS 2 [see e_CONNID_MASK_EXT]
                uint32_t    CONNID_1_COS_2:8;      // bits 23..30 (RW) ConnID value 1 COS 2
                uint32_t    CONNID_COS_2_MAP_EN:1; // bit  31     (RW) ConnID mapping enable [0x0 = disabled; 0x1 = enabled]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } CONNID_TO_COS_2_MAPPING_reg_t;

        /* (offset = 0x120) [reset = 0x00000305] */
        typedef union 
        {
                                                  /* READ_WRITE_EXEC_THRESHOLD
                                                   */
            struct 
            {                                      
                uint32_t    RD_THRSH     : 5;      // bits 0..4   (RW) Read threshold
                uint32_t                 : 3;      // bits 5..7   (R) Reserved
                uint32_t    WR_THRSH     : 5;      // bits 8..12  (RW) Write threshold
                uint32_t                 :19;      // bits 13..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } READ_WRITE_EXEC_THRESHOLD_reg_t;

        struct AM335x_EMIF4D_Type
        {                                                                                      
            __   EMIF_MOD_ID_REV_reg_t          EMIF_MOD_ID_REV;        // (0x0) 
            __   STATUS_reg_t                   STATUS;                 // (0x4)
            __   SDRAM_CONFIG_reg_t             SDRAM_CONFIG;           // (0x8)
            __   SDRAM_CONFIG_2_reg_t           SDRAM_CONFIG_2;         // (0xC)
            __   SDRAM_REF_CTRL_reg_t           SDRAM_REF_CTRL;         // (0x10)
            __   SDRAM_REF_CTRL_SHDW_reg_t      SDRAM_REF_CTRL_SHDW;    // (0x14)
            __   SDRAM_TIM_1_reg_t              SDRAM_TIM_1;            // (0x18)
            __   SDRAM_TIM_1_SHDW_reg_t         SDRAM_TIM_1_SHDW;       // (0x1C)
            __   SDRAM_TIM_2_reg_t              SDRAM_TIM_2;            // (0x20)
            __   SDRAM_TIM_2_SHDW_reg_t         SDRAM_TIM_2_SHDW;       // (0x24)  
            __   SDRAM_TIM_3_reg_t              SDRAM_TIM_3;            // (0x28) 
            __   SDRAM_TIM_3_SHDW_reg_t         SDRAM_TIM_3_SHDW;       // (0x2C)
            __R   uint32_t                      RESERVED1[2];
            __   PWR_MGMT_CTRL_reg_t            PWR_MGMT_CTRL;          // (0x38)
            __   PWR_MGMT_CTRL_SHDW_reg_t       PWR_MGMT_CTRL_SHDW;     // (0x3C)
            __R   uint32_t                      RESERVED2[5];
            __   OCP_CONFIG_reg_t               OCP_CONFIG;             // (0x54)
            __   OCP_CFG_VAL_1_reg_t            OCP_CFG_VAL_1;          // (0x58)
            __   OCP_CFG_VAL_2_reg_t            OCP_CFG_VAL_2;          // (0x5C)
            __R   uint32_t                      RESERVED3[8];
            __   PERF_CNT_1_reg_t               PERF_CNT_1;             // (0x80)
            __   PERF_CNT_2_reg_t               PERF_CNT_2;             // (0x84)
            __   PERF_CNT_CFG_reg_t             PERF_CNT_CFG;           // (0x88)
            __   PERF_CNT_SEL_reg_t             PERF_CNT_SEL;           // (0x8C) 
            __   PERF_CNT_TIM_reg_t             PERF_CNT_TIM;           // (0x90)
            __R   uint32_t                      RESERVED4[1];
            __   READ_IDLE_CTRL_reg_t           READ_IDLE_CTRL;         // (0x98)
            __   READ_IDLE_CTRL_SHDW_reg_t      READ_IDLE_CTRL_SHDW;    // (0x9C)
            __R   uint32_t                      RESERVED5[1];
            __   IRQSTATUS_RAW_SYS_reg_t        IRQSTATUS_RAW_SYS;      // (0xA4)
            __R   uint32_t                      RESERVED6[1];
            __   IRQSTATUS_SYS_reg_t            IRQSTATUS_SYS;          // (0xAC)
            __R   uint32_t                      RESERVED7[1];
            __   IRQENABLE_SET_SYS_reg_t        IRQENABLE_SET_SYS;      // (0xB4)
            __R   uint32_t                      RESERVED8[1];
            __   IRQENABLE_CLR_SYS_reg_t        IRQENABLE_CLR_SYS;      // (0xBC)
            __R   uint32_t                      RESERVED9[2];
            __   ZQ_CONFIG_reg_t                ZQ_CONFIG;              // (0xC8)
            __R   uint32_t                      RESERVED10[1];
            __   RW_LEV_RMP_WINDOW_reg_t        RW_LEV_RMP_WINDOW;      // (0xD4) 
            __   RW_LEV_RMP_CTRL_reg_t          RW_LEV_RMP_CTRL;        // (0xD8) 
            __   RW_LEV_CTRL_reg_t              RW_LEV_CTRL;            // (0xDC)
            __R   uint32_t                      RESERVED11[1];
            __   DDR_PHY_CTRL_1_reg_t           DDR_PHY_CTRL_1;         // (0xE4)
            __   DDR_PHY_CTRL_1_SHDW_reg_t      DDR_PHY_CTRL_1_SHDW;    // (0xE8)
            __R   uint32_t                      RESERVED12[5];
            __   PCSM_reg_t                     PCSM;                   // (0x100)
            __   CIDCS1MAPPING_reg_t            CIDCS1MAPPING;          // (0x104)
            __   CIDCS2MAPPING_reg_t            CIDCS2MAPPING;          // (0x108)
            __R   uint32_t                      RESERVED13[5]; 
            __   RW_EXEC_THRS_reg_t             RW_EXEC_THRS;           // (0x120)        
        };

        struct AM335x_DDR23mPHY_Type
        {     
            __R   uint32_t              RESERVED[7];                                                                                 
            __W   CSR0_reg_t            CMD0_CTRL_SLAVE_RATIO_0;          // (0x01C)  DDR PHY Command 0 Address/Command Slave Ratio Register
            __R   uint32_t              RESERVED1[2];
            __W   DLD0_reg_t            CMD0_DLL_LOCK_DIFF_0;             // (0x028)  DDR PHY Command 0 Address/Command DLL Lock Difference Register
            __W   ICLK0_reg_t           CMD0_INVERT_CLKOUT_0;             // (0x02C)  DDR PHY Command 0 Invert Clockout Selection Register
            __R   uint32_t              RESERVED2[8];
            __W   CSR0_reg_t            CMD1_CTRL_SLAVE_RATIO_0;          // (0x050)  DDR PHY Command 1 Address/Command Slave Ratio Register
            __R   uint32_t              RESERVED3[2];
            __W   DLD0_reg_t            CMD1_DLL_LOCK_DIFF_0;             // (0x05C)  DDR PHY Command 1 Address/Command DLL Lock Difference Register
            __W   ICLK0_reg_t           CMD1_INVERT_CLKOUT_0;             // (0x060)  DDR PHY Command 1 Invert Clockout Selection Register
            __R   uint32_t              RESERVED4[8];
            __W   CSR0_reg_t            CMD2_CTRL_SLAVE_RATIO_0;          // (0x084)  DDR PHY Command 2 Address/Command Slave Ratio Register
            __R   uint32_t              RESERVED5[2];
            __W   DLD0_reg_t            CMD2_DLL_LOCK_DIFF_0;             // (0x090)  DDR PHY Command 2 Address/Command DLL Lock Difference Register
            __W   ICLK0_reg_t           CMD2_INVERT_CLKOUT_0;             // (0x094)  DDR PHY Command 2 Invert Clockout Selection Register
            __R   uint32_t              RESERVED6[12];
            __W   RDQSSR0_reg_t         DATA0_RD_DQS_SLAVE_RATIO_0;       // (0x0C8)  DDR PHY Data Macro 0 Read DQS Slave Ratio Register
            __R   uint32_t              RESERVED7[4];
            __W   WDQSSR0_reg_t         DATA0_WR_DQS_SLAVE_RATIO_0;       // (0x0DC)  DDR PHY Data Macro 0 Write DQS Slave Ratio Register
            __R   uint32_t              RESERVED8[4];
            __W   MWRLVLINI_RATIO_reg_t DATA0_WRLVL_INIT_RATIO_0;         // (0x0F0)  DDR PHY Data Macro 0 Write Leveling Init Ratio Register
            __R   uint32_t              RESERVED9[1];
            __W   MWRLVLINI_MODE_reg_t  DATA0_WRLVL_INIT_MODE_0;          // (0x0F8)  DDR PHY Data Macro 0 Write Leveling Init Mode Ratio Selection Register
            __W   DQSGTI_RATIO_reg_t    DATA0_GATELVL_INIT_RATIO_0;       // (0x0FC)  DDR PHY Data Macro 0 DQS Gate Training Init Ratio Register
            __R   uint32_t              RESERVED10[1];
            __W   DQS_GTI_MODE_reg_t    DATA0_GATELVL_INIT_MODE_0;        // (0x104)  DDR PHY Data Macro 0 DQS Gate Training Init Mode Ratio Selection Register
            __W   DQS_GS_RATIO_reg_t    DATA0_FIFO_WE_SLAVE_RATIO_0;      // (0x108)  DDR PHY Data Macro 0 DQS Gate Slave Ratio Register
            __R   uint32_t              RESERVED11[4];
            __RW  DQS_T_DQ_OFFSET_reg_t DATA0_DQ_OFFSET_0;                // (0x11C)  Offset value from DQS to DQ for Data Macro 0
            __W   WDS_RATIO_reg_t       DATA0_WR_DATA_SLAVE_RATIO_0;      // (0x120)  DDR PHY Data Macro 0 Write Data Slave Ratio Register 
            __R   uint32_t              RESERVED12[4];
            __W   DELAY_SEL_reg_t       DATA0_USE_RANK0_DELAYS;           // (0x134)  DDR PHY Data Macro 0 Delay Selection Register
            __W   DLL_LOCK_DIFF_reg_t   DATA0_DLL_LOCK_DIFF_0;            // (0x138)  DDR PHY Data Macro 0 DLL Lock Difference Register
            __R   uint32_t              RESERVED13[12];
            __W   RDQSSR0_reg_t         DATA1_RD_DQS_SLAVE_RATIO_0;       // (0x16C)  DDR PHY Data Macro 1 Read DQS Slave Ratio Register
            __R   uint32_t              RESERVED14[4];
            __W   WDQSSR0_reg_t         DATA1_WR_DQS_SLAVE_RATIO_0;       // (0x180)  DDR PHY Data Macro 1 Write DQS Slave Ratio Register
            __R   uint32_t              RESERVED15[4];
            __W   MWRLVLINI_RATIO_reg_t DATA1_WRLVL_INIT_RATIO_0;         // (0x194)  DDR PHY Data Macro 1 Write Leveling Init Ratio Register 
            __R   uint32_t              RESERVED16[1];
            __W   MWRLVLINI_MODE_reg_t  DATA1_WRLVL_INIT_MODE_0;          // (0x19C)  DDR PHY Data Macro 1 Write Leveling Init Mode Ratio Selection Register
            __W   DQSGTI_RATIO_reg_t    DATA1_GATELVL_INIT_RATIO_0;       // (0x1A0)  DDR PHY Data Macro 1 DQS Gate Training Init Ratio Register
            __R   uint32_t              RESERVED17[1];
            __W   DQS_GTI_MODE_reg_t    DATA1_GATELVL_INIT_MODE_0;        // (0x1A8)  DDR PHY Data Macro 1 DQS Gate Training Init Mode Ratio Selection Register
            __W   DQS_GS_RATIO_reg_t    DATA1_FIFO_WE_SLAVE_RATIO_0;      // (0x1AC)  DDR PHY Data Macro 1 DQS Gate Slave Ratio Register
            __R   uint32_t              RESERVED18[4];
            __RW  DQS_T_DQ_OFFSET_reg_t DATA1_DQ_OFFSET_0;                // (0x1C0)  Offset value from DQS to DQ for Data Macro 1
            __W   WDS_RATIO_reg_t       DATA1_WR_DATA_SLAVE_RATIO_0;      // (0x1C4)  DDR PHY Data Macro 1 Write Data Slave Ratio Register
            __R   uint32_t              RESERVED19[4];
            __W   DELAY_SEL_reg_t       DATA1_USE_RANK0_DELAYS;           // (0x1D8)  DDR PHY Data Macro 1 Delay Selection Register
            __W   DLL_LOCK_DIFF_reg_t   DATA1_DLL_LOCK_DIFF_0;            // (0x1DC)  DDR PHY Data Macro 1 DLL Lock Difference Register
        };

        constexpr uint32_t AM335x_DDR23mPHY_BASE = 0x44E12000; 
        constexpr uint32_t AM335x_EMIF0_BASE     = 0x4C000000;

        constexpr AM335x_DDR23mPHY_Type  *AM335x_DDR23mPHY = reinterpret_cast<AM335x_DDR23mPHY_Type *>(AM335x_DDR23mPHY_BASE); 
        constexpr AM335x_EMIF4D_Type     *AM335x_EMIF0     = reinterpret_cast<AM335x_EMIF4D_Type *>(AM335x_EMIF0_BASE); 
        

    } // namespace EMIF
} // namespace REGS

#endif //_EMIF_H_
