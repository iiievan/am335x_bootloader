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
        
        /* [reset state = 0x40443403] [offset = 0x0]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    MINOR   :6;     // bit: 0..6    (R) Minor Revision.
                uint32_t            :2;     // bit: 7,6     (R) Reserved.
                uint32_t    MAJOR   :3;     // bit: 8..10   (R) Major Revision.
                uint32_t    RTL     :5;     // bit: 11..15  (R) RTL Version.
                uint32_t    ID      :12;    // bit: 16..27  (R) EMIF module ID.
                uint32_t            :2;     // bit: 28,29   (R) Reserved.
                uint32_t    SCHEME  :2;     // bit: 30,31   (R) Used to distinguish between old and current schemes.           
            } b;                            // Structure used for bit access 
            uint32_t  reg;                  // Type used for register access 
        } EMIF_MOD_ID_REV_reg_t;

        /* [reset state = 0x40000000] [offset = 0x4]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t                    :2;     // bit: 0,1     (R) Reserved  
                uint32_t    PHY_DLL_READY   :1;     // bit: 2       (R) DDR PHY Ready.
                                                    //                  Reflects the value on the phy_ready port (active high) that defines
                                                    //                  whether the DDR PHY is ready for normal operation.
                uint32_t                    :26;    // bit: 3..28   (R) Reserved 
                uint32_t    FAST_INIT       :1;     // bit: 29      (R) Fast Init.
                                                    //                  Reflects the value on the config_fast_init port that defines whether
                                                    //                  the EMIF fast initialization mode has been enabled.
                                                    //                  [ 0x0 = Fast init disabled.
                                                    //                    0x1 = Fast init enabled. ]
                uint32_t    DUAL_CLK_MODE   :1;     // bit: 30      (R) Dual Clock mode.
                                                    //                  Reflects the value on the config_dual_clk_mode port that defines
                                                    //                  whether the ocp_clk and m_clk are asynchronous.
                                                    //                  [ 0x0 = ocp_clk = m_clk.
                                                    //                    0x1 = Asynchronous ocp_clk and m_clk. ] 
                uint32_t    BE              :1;     // bit: 31      (R) Big Endian.
                                                    //                  Reflects the value on the config_big_endian port that defines
                                                    //                  whether the EMIF is in big or little endian mode.
                                                    //                  [0x0 = Little endian; 
                                                    //                   0x1 = Big endian]            
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } STATUS_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SDRAM_CONFIG_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t       :2;     // bit: 0,1  (R)  Reserved  
                uint32_t    PHY_DLL_READY   :1;     // bit: 0..3  (W) 
                uint32_t       :26;     // bit: 0..3  (W) 
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SDRAM_CONFIG_2_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SDRAM_REF_CTRL_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SDRAM_REF_CTRL_SHDW_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SDRAM_TIM_1_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SDRAM_TIM_1_SHDW_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SDRAM_TIM_2_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SDRAM_TIM_2_SHDW_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SDRAM_TIM_3_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SDRAM_TIM_3_SHDW_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } PWR_MGMT_CTRL_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } PWR_MGMT_CTRL_SHDW_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } OCP_CONFIG_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } OCP_CFG_VAL_1_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } OCP_CFG_VAL_2_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } PERF_CNT_1_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } PERF_CNT_2_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } PERF_CNT_CFG_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } PERF_CNT_SEL_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } PERF_CNT_TIM_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } READ_IDLE_CTRL_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } READ_IDLE_CTRL_SHDW_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } IRQSTATUS_RAW_SYS_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } IRQSTATUS_SYS_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } IRQENABLE_SET_SYS_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } IRQENABLE_CLR_SYS_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } ZQ_CONFIG_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } RW_LEV_RMP_WINDOW_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } RW_LEV_RMP_CTRL_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } RW_LEV_CTRL_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } DDR_PHY_CTRL_1_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } DDR_PHY_CTRL_1_SHDW_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } PCSM_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } CIDCS1MAPPING_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } CIDCS2MAPPING_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } RW_EXEC_THRS_reg_t;


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
