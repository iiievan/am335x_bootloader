#ifndef _CONTROL_MODULE_H_
#define _CONTROL_MODULE_H_

#include <stdint.h>
#include "REGS.hpp"

namespace REGS
{
    //This control module namespace
    namespace CONTROL_MODULE
    { 
    /

        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* ipc_msg_reg0 is shown in Figure 9-81 and described in Table 9-90. This register is typically used for
                                                         messaging between Cortex A8 and CortexM3 (WKUP).       */
                 
                uint32_t    ipc_msg_reg0      :32;    // bit: 0..32        (RW) Inter Processor Messaging Register          
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } ipc_msg_reg0_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* ipc_msg_reg1 is shown in Figure 9-81 and described in Table 9-90. This register is typically used for
                                                         messaging between Cortex A8 and CortexM3 (WKUP).       */
                 
                uint32_t    ipc_msg_reg2      :32;    // bit: 0..32        (RW) Inter Processor Messaging Register          
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } ipc_msg_reg1_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* ipc_msg_reg2 is shown in Figure 9-81 and described in Table 9-90. This register is typically used for
                                                         messaging between Cortex A8 and CortexM3 (WKUP).       */
                 
                uint32_t    ipc_msg_reg2      :32;    // bit: 0..32        (RW) Inter Processor Messaging Register          
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } ipc_msg_reg2_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* ipc_msg_reg3 is shown in Figure 9-81 and described in Table 9-90. This register is typically used for
                                                         messaging between Cortex A8 and CortexM3 (WKUP).       */
                 
                uint32_t    ipc_msg_reg3      :32;    // bit: 0..32        (RW) Inter Processor Messaging Register          
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } ipc_msg_reg3_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* ipc_msg_reg4 is shown in Figure 9-81 and described in Table 9-90. This register is typically used for
                                                         messaging between Cortex A8 and CortexM3 (WKUP).       */
                 
                uint32_t    ipc_msg_reg4      :32;    // bit: 0..32        (RW) Inter Processor Messaging Register          
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } ipc_msg_reg4_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* ipc_msg_reg5 is shown in Figure 9-81 and described in Table 9-90. This register is typically used for
                                                         messaging between Cortex A8 and CortexM3 (WKUP).       */
                 
                uint32_t    ipc_msg_reg5      :32;    // bit: 0..32        (RW) Inter Processor Messaging Register          
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } ipc_msg_reg5_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* ipc_msg_reg6 is shown in Figure 9-81 and described in Table 9-90. This register is typically used for
                                                         messaging between Cortex A8 and CortexM3 (WKUP).       */
                 
                uint32_t    ipc_msg_reg6      :32;    // bit: 0..32        (RW) Inter Processor Messaging Register          
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } ipc_msg_reg6_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* ipc_msg_reg7 is shown in Figure 9-81 and described in Table 9-90. This register is typically used for
                                                         messaging between Cortex A8 and CortexM3 (WKUP).       */
                 
                uint32_t    ipc_msg_reg7      :32;    // bit: 0..32        (RW) Inter Processor Messaging Register          
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } ipc_msg_reg7_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /**   **/
                 
                uint32_t    io_config_i           :3;         // bit: 0..2          (RW) 3-bit configuration input to program addr/cmd IO output impedance.
                                                              //                         These connect as I2, I1, I0 to the corresponding DDR IO buffer.
                                                              //                         See the DDR Impedance Control Settings table in the Control
                                                              //                         Module Functional Description section for a definition of these bits.
                uint32_t    io_config_sr          :2;         // bit: 3,4           (RW) 2 bit to program addr/cmd IO Pads output slew rate.
                                                              //                         These connect as SR1, SR0 to the corresponding DDR IO buffer.
                                                              //                         See the DDR Slew Rate Control Settings table in the Control Module
                                                              //                         Functional Description section for a definition of these bits.
                uint32_t    io_config_i_clk       :3;         // bit: 5..7          (RW) 3-bit configuration input to program clock IO pads
                                                              //                         (DDR_CK/DDR_CKN) output impedance.
                                                              //                         These connect as I2, I1, I0 to the corresponding DDR IO buffer.
                                                              //                         See the DDR Impedance Control Settings table in the Control
                                                              //                         Module Functional Description section for a definition of these bits.
                uint32_t    io_config_sr_clk      :2;         // bit: 8,9           (RW) 2 bit to program clock IO Pads (DDR_CK/DDR_CKN) output slew rate.
                                                              //                         These connect as SR1, SR0 to the corresponding DDR IO buffer.
                                                              //                         See the DDR Slew Rate Control Settings table in the Control Module
                                                              //                         Functional Description section for a definition of these bits.
                uint32_t    io_config_gp_wd0      :11;        // bit: 10..20        (RW) There are 2 bits per IO: io_config_gp_wd1 and io_config_gp_wd0.
                                                              //                         For example:
                                                              //                         macro pin 0: WD1 is bit 21, WD0 is bit 10
                                                              //                         macro pin 1: WD1 is bit 22, WD0 is bit 11
                                                              //                         ...
                                                              //                         macro pin 10: WD1 is bit 31, WD0 is bit 20
                                                              //                         See the DDR PHY to IO Pin Mapping table in the Control Module
                                                              //                         Functional Description section for a mapping of macro bits to I/Os.
                                                              //                         WD1:WD0 [see e_WD0_WD1_PULL]
                uint32_t    io_config_gp_wd1      :11;        // bit: 21..31        (RW) There are 2 bits per IO: io_config_gp_wd1 and io_config_gp_wd0.
                                                              //                         For example:
                                                              //                         macro pin 0: WD1 is bit 21, WD0 is bit 10
                                                              //                         macro pin 1: WD1 is bit 22, WD0 is bit 11
                                                              //                         ...
                                                              //                         macro pin 10: WD1 is bit 31, WD0 is bit 20
                                                              //                         See the DDR PHY to IO Pin Mapping table in the Control Module
                                                              //                         Functional Description section for a mapping of macro bits to I/Os.
                                                              //                         WD1:WD0 [see e_WD0_WD1_PULL]
            } b;                                              // Structure used for bit access
            uint32_t  reg;                                    // Type used for register access
        } ddr_cmd_ioctrl_reg_t;

        /* [reset state = 0x0]*/
        typedef union
        {
            struct
            {                                                 /**   **/

                uint32_t    io_config_i           :3;         // bit: 0..2          (RW) 3-bit configuration input to program data IO output impedance.
                                                              //                         These connect as I2, I1, I0 of the corresponding IO buffer.
                                                              //                         See the DDR Impedance Control Settings table in the Control
                                                              //                         Module Functional Description section for a definition of these bits.
                uint32_t    io_config_sr          :2;         // bit: 3,4           (RW) 2 bit to program data IO Pads output slew rate.
                                                              //                         These connect as SR1, SR0 of the corresponding IO buffer.
                                                              //                         See the DDR Slew Rate Control Settings table in the Control Module
                                                              //                         Functional Description section for a definition of these bits.
                uint32_t    io_config_i_clk       :3;         // bit: 5..7          (RW) 3-bit configuration input to program clock IO pads
                                                              //                         (DDR_DQS/DDR_DQSn) output impedance.
                                                              //                         These connect as I2, I1, I0 of the corresponding buffer.
                                                              //                         See the DDR Impedance Control Settings table in the Control
                                                              //                         Module Functional Description section for a definition of these bits.
                uint32_t    io_config_sr_clk      :2;         // bit: 8,9           (RW) 2 bit to program clock IO Pads (DDR_DQS/DDR_DQSn) output slew rate.
                                                              //                         These connect as SR1, SR0 of the corresponding IO buffer.
                                                              //                         See the DDR Slew Rate Control Settings table in the Control Module
                                                              //                         Functional Description section for a definition of these bits.
                uint32_t    io_config_gp_wd0_dq   :8;         // bit: 10..17        (RW) Input that selects pullup or pulldown for DQ.
                                                              //                         There are 2 bits per IO: io_config_wd1_dq and io_config_wd0_dq.
                                                              //                         For example:
                                                              //                         macro pin 0: WD1 is bit 20, WD0 is bit 10
                                                              //                         macro pin 1: WD1 is bit 21, WD0 is bit 11
                                                              //                         ...
                                                              //                         macro pin 7: WD1 is bit 27, WD0 is bit 17
                                                              //                         See the DDR PHY to IO Pin Mapping table in the Control Module
                                                              //                         Functional Description section for a mapping of macro bits to I/Os.
                                                              //                         [see e_WD0_WD1_PULL]
                uint32_t    io_config_wd0_dm      :1;         // bit: 18            (RW) Input that selects pullup or pulldown for DM.
                                                              //                         Used with io_config_wd1_dm to define pullup/pulldown according to
                                                              //                         the following: WD1:WD0 [see e_WD0_WD1_PULL]
                uint32_t    io_config_wd0_dqs     :1;         // bit: 19            (RW) Input that selects pullup or pulldown for DDR_DQS0 and DDR_DQSn0.
                                                              //                         Used with io_config_wd1_dqs to define pullup/pulldown according to
                                                              //                         the following:WD1:WD0  [see e_WD0_WD1_PULL]
                uint32_t    io_config_gp_wd1_dq   :8;         // bit: 20..27        (RW) Input that selects pullup or pulldown for DQ.
                                                              //                         There are 2 bits per IO: io_config_wd1_dq and io_config_wd0_dq.
                                                              //                         For example:
                                                              //                         macro pin 0: WD1 is bit 20, WD0 is bit 10
                                                              //                         macro pin 1: WD1 is bit 21, WD0 is bit 11
                                                              //                         ...
                                                              //                         macro pin 7: WD1 is bit 27, WD0 is bit 17
                                                              //                         See the DDR PHY to IO Pin Mapping table in the Control Module
                                                              //                         Functional Description section for a mapping of macro bits to I/Os.
                                                              //                         [see e_WD0_WD1_PULL]
                uint32_t    io_config_wd1_dm      :1;         // bit: 28            (RW) Input that selects pullup or pulldown for DM.
                                                              //                         Used with io_config_wd1_dm to define pullup/pulldown according to
                                                              //                         the following: WD1:WD0 [see e_WD0_WD1_PULL]
                uint32_t    io_config_wd1_dqs     :1;         // bit: 29            (RW) Input that selects pullup or pulldown for DDR_DQS0 and DDR_DQSn0.
                                                              //                         Used with io_config_wd1_dqs to define pullup/pulldown according to
                                                              //                         the following:WD1:WD0  [see e_WD0_WD1_PULL]
                uint32_t                          :2;         // bit: 30,31         (R) Reserved
            } b;                                              // Structure used for bit access
            uint32_t  reg;                                    // Type used for register access
        } ddr_data_ioctrl_reg_t;

        enum e_WD0_WD1_PULL : uint32_t
        {
            WD0_WD1_PUPD_DISABLED = 0x0,  // Pullup/Pulldown disabled
            WD0_WD1_PU_ENABLED    = 0x1,  // Weak pullup enabled
            WD0_WD1_PD_DISABLED   = 0x2,  // Weak pulldown enabled
            WD0_WD1_KEEP_ENABLED  = 0x3   // Weak keeper enabled
        };

        struct AM335x_CTRL_MODULE_Type
        {
            __R   control_revision_reg_t              control_revision;          // (0x00)
            __R   control_hwinfo_reg_t                control_hwinfo;            // (0x04)
            __R   uint32_t                            RESERVED[2];               //

            __RW  control_sysconfig_reg_t             control_sysconfig;         // (0x10)
            __R   uint32_t                            RESERVED1[11];             //

            __R   control_status_reg_t                control_status;            // (0x40)
            __R   control_bootstat_reg_t              control_bootstat;          // (0x44)
            __R   uint32_t                            RESERVED2[50];             // уменьшено на 1

            __RW  control_emif_sdram_config_reg_t     control_emif_sdram_config; // (0x110)
            __R   uint32_t                            RESERVED3[194];            // secure-регистры и прочее до 0x428
            __RW  cortex_vbbldo_ctrl_reg_t            cortex_vbbldo_ctrl;        // (0x41C)
            __R   uint32_t                            RESERVED4[2];
            __RW  core_sldo_ctrl_reg_t                core_sldo_ctrl;            // (0x428)
            __RW  mpu_sldo_ctrl_reg_t                 mpu_sldo_ctrl;             // (0x42C)

            __R   uint32_t                            RESERVED5[5];
            __RW  clk32kdivratio_ctrl_reg_t           clk32kdivratio_ctrl;       // (0x444)
            __RW  bandgap_ctrl_reg_t                  bandgap_ctrl;              // (0x448)
            __RW  bandgap_trim_reg_t                  bandgap_trim;              // (0x44C)
            __R   uint32_t                            RESERVED6[2];
            __RW  pll_clkinpulow_ctrl_reg_t           pll_clkinpulow_ctrl;       // (0x458)
            __R   uint32_t                            RESERVED7[3];
            __RW  mosc_ctrl_reg_t                     mosc_ctrl;                 // (0x468)
            __R   uint32_t                            RESERVED8[1];
            __RW  deepsleep_ctrl_reg_t                deepsleep_ctrl;            // (0x470)
            __R   uint32_t                            RESERVED9[38];
            __R   dpll_pwr_sw_status_reg_t            dpll_pwr_sw_status;        // (0x50C)
            __R   uint32_t                            RESERVED10[60];
            __R   device_id_reg_t                     device_id;                 // (0x600)
            __R   dev_feature_reg_t                   dev_feature;               // (0x604)
            __RW  init_priority_0_reg_t               init_priority_0;           // (0x608)
            __RW  init_priority_1_reg_t               init_priority_1;           // (0x60C)
            __RW  control_mmu_cfg_reg_t               control_mmu_cfg;           // (0x610)
            __RW  tptc_cfg_reg_t                      tptc_cfg;                  // (0x614)
            __RW  control_ocmc_cfg_reg_t              control_ocmc_cfg;          // (0x618)
            __R   uint32_t                            RESERVED11[1];             //
            __RW  usb_ctrl0_reg_t                     usb_ctrl0;                 // (0x620)
            __R   usb_sts0_reg_t                      usb_sts0;                  // (0x624)
            __RW  usb_ctrl1_reg_t                     usb_ctrl1;                 // (0x628)
            __R   usb_sts1_reg_t                      usb_sts1;                  // (0x62C)
            __R   mac_id0_lo_reg_t                    mac_id0_lo;                // (0x630)
            __R   mac_id0_hi_reg_t                    mac_id0_hi;                // (0x634)
            __R   mac_id1_lo_reg_t                    mac_id1_lo;                // (0x638)
            __R   mac_id1_hi_reg_t                    mac_id1_hi;                // (0x63C)
            __R   uint32_t                            RESERVED12[1];
            __RW  dcan_raminit_reg_t                  dcan_raminit;              // (0x644)
            __RW  usb_wkup_ctrl_reg_t                 usb_wkup_ctrl;             // (0x648)
            __R   uint32_t                            RESERVED13[1];
            __RW  gmii_sel_reg_t                      gmii_sel;                  // (0x650)
            __R   uint32_t                            RESERVED14[4];
            __RW  pwmss_ctrl_reg_t                    pwmss_ctrl;                // (0x664)
            __R   uint32_t                            RESERVED15[2];
            __RW  mreqprio_0_reg_t                    mreqprio_0;                // (0x670)
            __R   mreqprio_1_reg_t                    mreqprio_1;                // (0x674)
            __R   uint32_t                            RESERVED16[6];
            __RW  hw_event_sel_grp1_reg_t             hw_event_sel_grp1;         // (0x690)
            __RW  hw_event_sel_grp2_reg_t             hw_event_sel_grp2;         // (0x694)
            __RW  hw_event_sel_grp3_reg_t             hw_event_sel_grp3;         // (0x698)
            __RW  hw_event_sel_grp4_reg_t             hw_event_sel_grp4;         // (0x69C)
            __RW  smrt_ctrl_reg_t                     smrt_ctrl;                 // (0x6A0)
            __RW  mpuss_hw_debug_sel_reg_t            mpuss_hw_debug_sel;        // (0x6A4)
            __R   mpuss_hw_dbg_info_reg_t             mpuss_hw_dbg_info;         // (0x6A8)
            __R   uint32_t                            RESERVED17[5];            //
            __RW  mrgn_mode0_reg_t                    mrgn_mode0;                // (0x6C0)
            __RW  mrgn_mode1_reg_t                    mrgn_mode1;                // (0x6C4)
            __R   uint32_t                            RESERVED18[42];           //
            __R   vdd_mpu_opp_050_reg_t               vdd_mpu_opp_050;           // (0x770)
            __R   vdd_mpu_opp_100_reg_t               vdd_mpu_opp_100;           // (0x774)
            __R   vdd_mpu_opp_120_reg_t               vdd_mpu_opp_120;           // (0x778)
            __R   vdd_mpu_opp_turbo_reg_t             vdd_mpu_opp_turbo;         // (0x77C)
            __R   uint32_t                            RESERVED19[14];
            __R   vdd_core_opp_050_reg_t              vdd_core_opp_050;          // (0x7B8)
            __R   vdd_core_opp_100_reg_t              vdd_core_opp_100;          // (0x7BC)
            __R   uint32_t                            RESERVED20[4];
            __R   bb_scale_reg_t                      bb_scale;                  // (0x7D0)
            __R   uint32_t                            RESERVED21[8];
            __R   usb_vid_pid_reg_t                   usb_vid_pid;               // (0x7F4)
            __R   uint32_t                            RESERVED22[1];
            __R   efuse_sma_reg_t                     efuse_sma;                 // (0x7FC)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad0;             // (0x800)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad1;             // (0x804)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad2;             // (0x808)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad3;             // (0x80C)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad4;             // (0x810)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad5;             // (0x814)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad6;             // (0x818)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad7;             // (0x81C)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad8;             // (0x820)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad9;             // (0x824)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad10;            // (0x828)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad11;            // (0x82C)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad12;            // (0x830)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad13;            // (0x834)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad14;            // (0x838)
            __RW  conf_module_pin_reg_t               conf_gpmc_ad15;            // (0x83C)
            __RW  conf_module_pin_reg_t               conf_gpmc_a0;              // (0x840)
            __RW  conf_module_pin_reg_t               conf_gpmc_a1;              // (0x844)
            __RW  conf_module_pin_reg_t               conf_gpmc_a2;              // (0x848)
            __RW  conf_module_pin_reg_t               conf_gpmc_a3;              // (0x84C)
            __RW  conf_module_pin_reg_t               conf_gpmc_a4;              // (0x850)
            __RW  conf_module_pin_reg_t               conf_gpmc_a5;              // (0x854)
            __RW  conf_module_pin_reg_t               conf_gpmc_a6;              // (0x858)
            __RW  conf_module_pin_reg_t               conf_gpmc_a7;              // (0x85C)
            __RW  conf_module_pin_reg_t               conf_gpmc_a8;              // (0x860)
            __RW  conf_module_pin_reg_t               conf_gpmc_a9;              // (0x864)
            __RW  conf_module_pin_reg_t               conf_gpmc_a10;             // (0x868)
            __RW  conf_module_pin_reg_t               conf_gpmc_a11;             // (0x86C)
            __RW  conf_module_pin_reg_t               conf_gpmc_wait0;           // (0x870)
            __RW  conf_module_pin_reg_t               conf_gpmc_wpn;             // (0x874)
            __RW  conf_module_pin_reg_t               conf_gpmc_ben1;            // (0x878)
            __RW  conf_module_pin_reg_t               conf_gpmc_csn0;            // (0x87C)
            __RW  conf_module_pin_reg_t               conf_gpmc_csn1;            // (0x880)
            __RW  conf_module_pin_reg_t               conf_gpmc_csn2;            // (0x884)
            __RW  conf_module_pin_reg_t               conf_gpmc_csn3;            // (0x888)
            __RW  conf_module_pin_reg_t               conf_gpmc_clk;             // (0x88C)
            __RW  conf_module_pin_reg_t               conf_gpmc_advn_ale;        // (0x890)
            __RW  conf_module_pin_reg_t               conf_gpmc_oen_ren;         // (0x894)
            __RW  conf_module_pin_reg_t               conf_gpmc_wen;             // (0x898)
            __RW  conf_module_pin_reg_t               conf_gpmc_ben0_cle;        // (0x89C)
            __RW  conf_module_pin_reg_t               conf_lcd_data0;            // (0x8A0)
            __RW  conf_module_pin_reg_t               conf_lcd_data1;            // (0x8A4)
            __RW  conf_module_pin_reg_t               conf_lcd_data2;            // (0x8A8)
            __RW  conf_module_pin_reg_t               conf_lcd_data3;            // (0x8AC)
            __RW  conf_module_pin_reg_t               conf_lcd_data4;            // (0x8B0)
            __RW  conf_module_pin_reg_t               conf_lcd_data5;            // (0x8B4)
            __RW  conf_module_pin_reg_t               conf_lcd_data6;            // (0x8B8)
            __RW  conf_module_pin_reg_t               conf_lcd_data7;            // (0x8BC)
            __RW  conf_module_pin_reg_t               conf_lcd_data8;            // (0x8C0)
            __RW  conf_module_pin_reg_t               conf_lcd_data9;            // (0x8C4)
            __RW  conf_module_pin_reg_t               conf_lcd_data10;           // (0x8C8)
            __RW  conf_module_pin_reg_t               conf_lcd_data11;           // (0x8CC)
            __RW  conf_module_pin_reg_t               conf_lcd_data12;           // (0x8D0)
            __RW  conf_module_pin_reg_t               conf_lcd_data13;           // (0x8D4)
            __RW  conf_module_pin_reg_t               conf_lcd_data14;           // (0x8D8)
            __RW  conf_module_pin_reg_t               conf_lcd_data15;           // (0x8DC)
            __RW  conf_module_pin_reg_t               conf_lcd_vsync;            // (0x8E0)
            __RW  conf_module_pin_reg_t               conf_lcd_hsync;            // (0x8E4)
            __RW  conf_module_pin_reg_t               conf_lcd_pclk;             // (0x8E8)
            __RW  conf_module_pin_reg_t               conf_lcd_ac_bias_en;       // (0x8EC)
            __RW  conf_module_pin_reg_t               conf_mmc0_dat3;            // (0x8F0)
            __RW  conf_module_pin_reg_t               conf_mmc0_dat2;            // (0x8F4)
            __RW  conf_module_pin_reg_t               conf_mmc0_dat1;            // (0x8F8)
            __RW  conf_module_pin_reg_t               conf_mmc0_dat0;            // (0x8FC)
            __RW  conf_module_pin_reg_t               conf_mmc0_clk;             // (0x900)
            __RW  conf_module_pin_reg_t               conf_mmc0_cmd;             // (0x904)
            __RW  conf_module_pin_reg_t               conf_mii1_col;             // (0x908)
            __RW  conf_module_pin_reg_t               conf_mii1_crs;             // (0x90C)
            __RW  conf_module_pin_reg_t               conf_mii1_rx_er;           // (0x910)
            __RW  conf_module_pin_reg_t               conf_mii1_tx_en;           // (0x914)
            __RW  conf_module_pin_reg_t               conf_mii1_rx_dv;           // (0x918)
            __RW  conf_module_pin_reg_t               conf_mii1_txd3;            // (0x91C)
            __RW  conf_module_pin_reg_t               conf_mii1_txd2;            // (0x920)
            __RW  conf_module_pin_reg_t               conf_mii1_txd1;            // (0x924)
            __RW  conf_module_pin_reg_t               conf_mii1_txd0;            // (0x928)
            __RW  conf_module_pin_reg_t               conf_mii1_tx_clk;          // (0x92C)
            __RW  conf_module_pin_reg_t               conf_mii1_rx_clk;          // (0x930)
            __RW  conf_module_pin_reg_t               conf_mii1_rxd3;            // (0x934)
            __RW  conf_module_pin_reg_t               conf_mii1_rxd2;            // (0x938)
            __RW  conf_module_pin_reg_t               conf_mii1_rxd1;            // (0x93C)
            __RW  conf_module_pin_reg_t               conf_mii1_rxd0;            // (0x940)
            __RW  conf_module_pin_reg_t               conf_rmii1_ref_clk;        // (0x944)
            __RW  conf_module_pin_reg_t               conf_mdio;                 // (0x948)
            __RW  conf_module_pin_reg_t               conf_mdc;                  // (0x94C)
            __RW  conf_module_pin_reg_t               conf_spi0_sclk;            // (0x950)
            __RW  conf_module_pin_reg_t               conf_spi0_d0;              // (0x954)
            __RW  conf_module_pin_reg_t               conf_spi0_d1;              // (0x958)
            __RW  conf_module_pin_reg_t               conf_spi0_cs0;             // (0x95C)
            __RW  conf_module_pin_reg_t               conf_spi0_cs1;             // (0x960)
            __RW  conf_module_pin_reg_t               conf_ecap0_in_pwm0_out;    // (0x964)
            __RW  conf_module_pin_reg_t               conf_uart0_ctsn;           // (0x968)
            __RW  conf_module_pin_reg_t               conf_uart0_rtsn;           // (0x96C)
            __RW  conf_module_pin_reg_t               conf_uart0_rxd;            // (0x970)
            __RW  conf_module_pin_reg_t               conf_uart0_txd;            // (0x974)
            __RW  conf_module_pin_reg_t               conf_uart1_ctsn;           // (0x978)
            __RW  conf_module_pin_reg_t               conf_uart1_rtsn;           // (0x97C)
            __RW  conf_module_pin_reg_t               conf_uart1_rxd;            // (0x980)
            __RW  conf_module_pin_reg_t               conf_uart1_txd;            // (0x984)
            __RW  conf_module_pin_reg_t               conf_i2c0_sda;             // (0x988)
            __RW  conf_module_pin_reg_t               conf_i2c0_scl;             // (0x98C)
            __RW  conf_module_pin_reg_t               conf_mcasp0_aclkx;         // (0x990)
            __RW  conf_module_pin_reg_t               conf_mcasp0_fsx;           // (0x994)
            __RW  conf_module_pin_reg_t               conf_mcasp0_axr0;          // (0x998)
            __RW  conf_module_pin_reg_t               conf_mcasp0_ahclkr;        // (0x99C)
            __RW  conf_module_pin_reg_t               conf_mcasp0_aclkr;         // (0x9A0)
            __RW  conf_module_pin_reg_t               conf_mcasp0_fsr;           // (0x9A4)
            __RW  conf_module_pin_reg_t               conf_mcasp0_axr1;          // (0x9A8)
            __RW  conf_module_pin_reg_t               conf_mcasp0_ahclkx;        // (0x9AC)
            __RW  conf_module_pin_reg_t               conf_xdma_event_intr0;     // (0x9B0)
            __RW  conf_module_pin_reg_t               conf_xdma_event_intr1;     // (0x9B4)
            __RW  conf_module_pin_reg_t               conf_warmrstn;             // (0x9B8)
            __R   uint32_t                            RESERVED23[1];
            __RW  conf_module_pin_reg_t               conf_nnmi;                 // (0x9C0)
            __R   uint32_t                            RESERVED24[3];
            __RW  conf_module_pin_reg_t               conf_tms;                  // (0x9D0)
            __RW  conf_module_pin_reg_t               conf_tdi;                  // (0x9D4)
            __RW  conf_module_pin_reg_t               conf_tdo;                  // (0x9D8)
            __RW  conf_module_pin_reg_t               conf_tck;                  // (0x9DC)
            __RW  conf_module_pin_reg_t               conf_trstn;                // (0x9E0)
            __RW  conf_module_pin_reg_t               conf_emu0;                 // (0x9E4)
            __RW  conf_module_pin_reg_t               conf_emu1;                 // (0x9E8)
            __R   uint32_t                            RESERVED25[3];
            __RW  conf_module_pin_reg_t               conf_rtc_pwronrstn;        // (0x9F8)
            __RW  conf_module_pin_reg_t               conf_pmic_power_en;        // (0x9FC)
            __RW  conf_module_pin_reg_t               conf_ext_wakeup;           // (0xA00)
            __RW  conf_module_pin_reg_t               conf_enz_kaldo_1p8v;       // (0xA04)
            __RW  conf_module_pin_reg_t               conf_usb0_dm;              // (0xA08)
            __RW  conf_module_pin_reg_t               conf_usb0_dp;              // (0xA0C)
            __RW  conf_module_pin_reg_t               conf_usb0_ce;              // (0xA10)
            __RW  conf_module_pin_reg_t               conf_usb0_id;              // (0xA14)
            __RW  conf_module_pin_reg_t               conf_usb0_vbus;            // (0xA18)
            __RW  conf_module_pin_reg_t               conf_usb0_drvvbus;         // (0xA1C)

            __RW  conf_module_pin_reg_t               conf_usb1_dm;              // (0xA20)
            __RW  conf_module_pin_reg_t               conf_usb1_dp;              // (0xA24)
            __RW  conf_module_pin_reg_t               conf_usb1_ce;              // (0xA28)
            __RW  conf_module_pin_reg_t               conf_usb1_id;              // (0xA2C)
            __RW  conf_module_pin_reg_t               conf_usb1_vbus;            // (0xA30)
            __RW  conf_module_pin_reg_t               conf_usb1_drvvbus;         // (0xA34)

            /* ==================== DDR PIN CONF (BeagleBone Black) ==================== */
            __RW  conf_module_pin_reg_t               conf_ddr_resetn;           // (0xA38)
            __RW  conf_module_pin_reg_t               conf_ddr_csn0;             // (0xA3C)
            __RW  conf_module_pin_reg_t               conf_ddr_cke;              // (0xA40)
            __RW  conf_module_pin_reg_t               conf_ddr_ck;               // (0xA44)
            __RW  conf_module_pin_reg_t               conf_ddr_nck;              // (0xA48)
            __RW  conf_module_pin_reg_t               conf_ddr_casn;             // (0xA4C)
            __RW  conf_module_pin_reg_t               conf_ddr_rasn;             // (0xA50)
            __RW  conf_module_pin_reg_t               conf_ddr_wen;              // (0xA54)
            __RW  conf_module_pin_reg_t               conf_ddr_ba0;              // (0xA58)
            __RW  conf_module_pin_reg_t               conf_ddr_ba1;              // (0xA5C)
            __RW  conf_module_pin_reg_t               conf_ddr_ba2;              // (0xA60)
            __RW  conf_module_pin_reg_t               conf_ddr_a0;               // (0xA64)
            __RW  conf_module_pin_reg_t               conf_ddr_a1;               // (0xA68)
            __RW  conf_module_pin_reg_t               conf_ddr_a2;               // (0xA6C)
            __RW  conf_module_pin_reg_t               conf_ddr_a3;               // (0xA70)
            __RW  conf_module_pin_reg_t               conf_ddr_a4;               // (0xA74)
            __RW  conf_module_pin_reg_t               conf_ddr_a5;               // (0xA78)
            __RW  conf_module_pin_reg_t               conf_ddr_a6;               // (0xA7C)
            __RW  conf_module_pin_reg_t               conf_ddr_a7;               // (0xA80)
            __RW  conf_module_pin_reg_t               conf_ddr_a8;               // (0xA84)
            __RW  conf_module_pin_reg_t               conf_ddr_a9;               // (0xA88)
            __RW  conf_module_pin_reg_t               conf_ddr_a10;              // (0xA8C)
            __RW  conf_module_pin_reg_t               conf_ddr_a11;              // (0xA90)
            __RW  conf_module_pin_reg_t               conf_ddr_a12;              // (0xA94)
            __RW  conf_module_pin_reg_t               conf_ddr_a13;              // (0xA98)
            __RW  conf_module_pin_reg_t               conf_ddr_a14;              // (0xA9C)
            __RW  conf_module_pin_reg_t               conf_ddr_a15;              // (0xAA0)
            __RW  conf_module_pin_reg_t               conf_ddr_odt;              // (0xAA4)
            __RW  conf_module_pin_reg_t               conf_ddr_d0;               // (0xAA8)
            __RW  conf_module_pin_reg_t               conf_ddr_d1;               // (0xAAC)
            __RW  conf_module_pin_reg_t               conf_ddr_d2;               // (0xAB0)
            __RW  conf_module_pin_reg_t               conf_ddr_d3;               // (0xAB4)
            __RW  conf_module_pin_reg_t               conf_ddr_d4;               // (0xAB8)
            __RW  conf_module_pin_reg_t               conf_ddr_d5;               // (0xABC)
            __RW  conf_module_pin_reg_t               conf_ddr_d6;               // (0xAC0)
            __RW  conf_module_pin_reg_t               conf_ddr_d7;               // (0xAC4)
            __RW  conf_module_pin_reg_t               conf_ddr_d8;               // (0xAC8)
            __RW  conf_module_pin_reg_t               conf_ddr_d9;               // (0xACC)
            __RW  conf_module_pin_reg_t               conf_ddr_d10;              // (0xAD0)
            __RW  conf_module_pin_reg_t               conf_ddr_d11;              // (0xAD4)
            __RW  conf_module_pin_reg_t               conf_ddr_d12;              // (0xAD8)
            __RW  conf_module_pin_reg_t               conf_ddr_d13;              // (0xADC)
            __RW  conf_module_pin_reg_t               conf_ddr_d14;              // (0xAE0)
            __RW  conf_module_pin_reg_t               conf_ddr_d15;              // (0xAE4)
            __RW  conf_module_pin_reg_t               conf_ddr_dqm0;             // (0xAE8)
            __RW  conf_module_pin_reg_t               conf_ddr_dqm1;             // (0xAEC)
            __RW  conf_module_pin_reg_t               conf_ddr_dqs0;             // (0xAF0)
            __RW  conf_module_pin_reg_t               conf_ddr_dqsn0;            // (0xAF4)
            __RW  conf_module_pin_reg_t               conf_ddr_dqs1;             // (0xAF8)
            __RW  conf_module_pin_reg_t               conf_ddr_dqsn1;            // (0xAFC)
            __RW  conf_module_pin_reg_t               conf_ddr_vref;             // (0xB00)
            __RW  conf_module_pin_reg_t               conf_ddr_vtp;              // (0xB04)
            __RW  conf_module_pin_reg_t               conf_ddr_strben0;          // (0xB08)
            __R   uint32_t                            RESERVED26[1];

            /* ==================== ADC / TEST PINS ==================== */
            __RW  conf_module_pin_reg_t               conf_ain7;                 // (0xB10)
            __RW  conf_module_pin_reg_t               conf_ain6;                 // (0xB14)
            __RW  conf_module_pin_reg_t               conf_ain5;                 // (0xB18)
            __RW  conf_module_pin_reg_t               conf_ain4;                 // (0xB1C)
            __RW  conf_module_pin_reg_t               conf_ain3;                 // (0xB20)
            __RW  conf_module_pin_reg_t               conf_ain2;                 // (0xB24)
            __RW  conf_module_pin_reg_t               conf_ain1;                 // (0xB28)
            __RW  conf_module_pin_reg_t               conf_ain0;                 // (0xB2C)
            __RW  conf_module_pin_reg_t               conf_vrefp;                // (0xB30)
            __RW  conf_module_pin_reg_t               conf_vrefn;                // (0xB34)
            __RW  conf_module_pin_reg_t               conf_avdd;                 // (0xB38)
            __RW  conf_module_pin_reg_t               conf_avss;                 // (0xB3C)
            __RW  conf_module_pin_reg_t               conf_iforce;               // (0xB40)
            __RW  conf_module_pin_reg_t               conf_vsense;               // (0xB44)
            __RW  conf_module_pin_reg_t               conf_testout;              // (0xB48)
            __R   uint32_t                            RESERVED27[173];
            __R   cqdetect_status_reg_t               cqdetect_status;           // (0xE00)
            __RW  ddr_io_ctrl_reg_t                   ddr_io_ctrl;               // (0xE04)
            __R   uint32_t                            RESERVED28[1];
            __RW  vtp_ctrl_reg_t                      vtp_ctrl;                  // (0xE0C)
            __R   uint32_t                            RESERVED29[1];
            __R   vref_ctrl_reg_t                     vref_ctrl;                 // (0xE14)
            __R   uint32_t                            RESERVED30[3];
            __R   serdes_refclk_ctl_reg_t             serdes_refclk_ctl;         // (0xE24)
            __R   uint32_t                            RESERVED31[90];
            __RW  tpcc_evt_mux_0_3_reg_t              tpcc_evt_mux_0_3;          // (0xF90)
            __RW  tpcc_evt_mux_4_7_reg_t              tpcc_evt_mux_4_7;          // (0xF94)
            __RW  tpcc_evt_mux_8_11_reg_t             tpcc_evt_mux_8_11;         // (0xF98)
            __RW  tpcc_evt_mux_12_15_reg_t            tpcc_evt_mux_12_15;        // (0xF9C)
            __RW  tpcc_evt_mux_16_19_reg_t            tpcc_evt_mux_16_19;        // (0xFA0)
            __RW  tpcc_evt_mux_20_23_reg_t            tpcc_evt_mux_20_23;        // (0xFA4)
            __RW  tpcc_evt_mux_24_27_reg_t            tpcc_evt_mux_24_27;        // (0xFA8)
            __RW  tpcc_evt_mux_28_31_reg_t            tpcc_evt_mux_28_31;        // (0xFAC)
            __RW  tpcc_evt_mux_32_35_reg_t            tpcc_evt_mux_32_35;        // (0xFB0)
            __RW  tpcc_evt_mux_36_39_reg_t            tpcc_evt_mux_36_39;        // (0xFB4)
            __RW  tpcc_evt_mux_40_43_reg_t            tpcc_evt_mux_40_43;        // (0xFB8)
            __RW  tpcc_evt_mux_44_47_reg_t            tpcc_evt_mux_44_47;        // (0xFBC)
            __RW  tpcc_evt_mux_48_51_reg_t            tpcc_evt_mux_48_51;        // (0xFC0)
            __RW  tpcc_evt_mux_52_55_reg_t            tpcc_evt_mux_52_55;        // (0xFC4)
            __RW  tpcc_evt_mux_56_59_reg_t            tpcc_evt_mux_56_59;        // (0xFC8)
            __RW  tpcc_evt_mux_60_63_reg_t            tpcc_evt_mux_60_63;        // (0xFCC)
            __RW  timer_evt_capt_reg_t                timer_evt_capt;            // (0xFD0)
            __RW  ecap_evt_capt_reg_t                 ecap_evt_capt;             // (0xFD4)
            __RW  adc_evt_capt_reg_t                  adc_evt_capt;              // (0xFD8)
            __R   uint32_t                            RESERVED32[9];
            __RW  reset_iso_reg_t                     reset_iso;                 // (0x1000)
            __R   uint32_t                            RESERVED33[197];
            __RW  dpll_pwr_sw_ctrl_reg_t              dpll_pwr_sw_ctrl;          // (0x1318)
            __RW  ddr_cke_ctrl_reg_t                  ddr_cke_ctrl;              // (0x131C)
            __RW  sma2_reg_t                          sma2;                      // (0x1320)
            __RW  m3_txev_eoi_reg_t                   m3_txev_eoi;               // (0x1324)
            __RW  ipc_msg_reg0_reg_t                  ipc_msg_reg0;              // (0x1328)
            __RW  ipc_msg_reg1_reg_t                  ipc_msg_reg1;              // (0x132C)
            __RW  ipc_msg_reg2_reg_t                  ipc_msg_reg2;              // (0x1330)
            __RW  ipc_msg_reg3_reg_t                  ipc_msg_reg3;              // (0x1334)
            __RW  ipc_msg_reg4_reg_t                  ipc_msg_reg4;              // (0x1338)
            __RW  ipc_msg_reg5_reg_t                  ipc_msg_reg5;              // (0x133C)
            __RW  ipc_msg_reg6_reg_t                  ipc_msg_reg6;              // (0x1340)
            __RW  ipc_msg_reg7_reg_t                  ipc_msg_reg7;              // (0x1344)
            __R   uint32_t                            RESERVED34[47];
            __RW  ddr_cmd_ioctrl_reg_t                ddr_cmd0_ioctrl;           // (0x1404)
            __RW  ddr_cmd_ioctrl_reg_t                ddr_cmd1_ioctrl;           // (0x1408)
            __RW  ddr_cmd_ioctrl_reg_t                ddr_cmd2_ioctrl;           // (0x140C)
            __R   uint32_t                            RESERVED35[12];
            __RW  ddr_data_ioctrl_reg_t               ddr_data0_ioctrl;          // (0x1440)
            __RW  ddr_data_ioctrl_reg_t               ddr_data1_ioctrl;          // (0x1444)

            void  I2C0_pin_mux_setup();
            void  I2C1_pin_mux_setup();
            void  I2C2_pin_mux_setup();
            void  UART0_pin_mux_setup();
        };

        constexpr uint32_t AM335x_CONTROL_MODULE_BASE = 0x44E10000; 

        /************************************************************************ ALL POINTERS ON CONTROL MODULE BLOCKS ***********************************************************************************************/

        inline AM335x_CTRL_MODULE_Type  *AM335x_CONTROL_MODULE = reinterpret_cast<AM335x_CTRL_MODULE_Type*> (AM335x_CONTROL_MODULE_BASE);


    } // namespace CONTROL_MODULE
} // namespace REGS

#endif //_CONTROL_MODULE_H_
