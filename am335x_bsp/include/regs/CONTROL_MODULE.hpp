#ifndef _CONTROL_MODULE_H_
#define _CONTROL_MODULE_H_

#include <stdint.h>
#include "REGS.hpp"

namespace REGS
{
    //This control module namespace
    namespace CONTROL_MODULE
    { 
    /*******************************************************************************************************************************************************************************/  
    
    /*************************************************************************** AM335x_CTRL_MODULE_Type Registers **********************************************************************/ 
    
    /*******************************************************************************************************************************************************************************/      
        
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                       /*  */
                 
                uint32_t    ip_rev_minor      :6;   // bit: 0..5     (R) Minor Revision (Y).
                uint32_t    ip_rev_custom     :2;   // bit: 6,7      (R) Indicates a special version for a particular device.                      
                uint32_t    ip_rev_major      :3;   // bit: 8..10    (R) Major Revision.   
                uint32_t    ip_rev_rtl        :5;   // bit: 11..15   (R) RTL Version.
                uint32_t    ip_rev_func       :12;  // bit: 16..27   (R) Function indicates a software compatible module family.
                uint32_t                      :2;   // bit: 28,29    Reserved  
                uint32_t    ip_rev_scheme     :2;   // bit: 30,31    (R) 01 - New Scheme 
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } control_revision_reg_t;  
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /*  */
                 
                uint32_t    ip_hwinfo     :1;         // bit: 0      (R) IP Module dependent [0x0 =  0x1 = ]
                uint32_t                  :31;        // bit: 1..31  Reserved  
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } control_hwinfo_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /*  */
                 
                uint32_t                  :1;         // bit: 0      (R) 
                uint32_t    freeemu       :1;         // bit: 1      (R)  Sensitivity to Emulation suspend input.    [0x0 = sensitive to EMU suspend; 0x1 = not sensitive to EMU suspend ]                      
                uint32_t    idlemode      :2;         // bit: 2,3    (RW) Configure local target state management.   [see e_CTRLSYSCFG_idlemode]     
                uint32_t    standby       :2;         // bit: 4,5    (R)  Configure local initiator state management. [see e_CTRLSYSCFG_standby]
                uint32_t                  :26;        // bit: 6..31  Reserved  
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } control_sysconfig_reg_t; 
    
        enum e_CTRLSYSCFG_idlemode : uint32_t
        {
            CTRLSYSCFG_Force_idle          = 0x0,
            CTRLSYSCFG_No_idle             = 0x1, 
            CTRLSYSCFG_Smart_idle          = 0x2,
            CTRLSYSCFG_Smart_idle_wkupcap   = 0x3      
        };
    
        enum e_CTRLSYSCFG_standby : uint32_t
        {
            CTRLSYSCFG_Force_standby          = 0x0,
            CTRLSYSCFG_No_standby             = 0x1, 
            CTRLSYSCFG_Smart_standby          = 0x2,
            CTRLSYSCFG_Smart_standby_wkupcap  = 0x3      
        };
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                     /*  */
                 
                uint32_t    sysboot0  :8;         // bit: 0..7       (R) Selected boot mode. 
                uint32_t    devtype   :3;         // bit: 8..10      (R) [0x000,0x001,0x010,0x111 = Reserved; 0x011 = General Purpose (GP) Device ] 
                uint32_t              :5;         // bit: 11..15     Reserved                    
                uint32_t    bw        :1;         // bit: 16         (R) GPMC CS0 Default Bus Width [0x0 = 8-itb data bus; 0x1 = 16-bit data bus]     
                uint32_t    waiten    :1;         // bit: 17         (R) GPMC CS0 Default Wait Enable [0x0 = Ignore WAIT input 0x1 = Use WAIT input ]
                uint32_t    admux     :2;         // bit: 18,19      (R) GPMC CS0 Default Address Muxing [see e_CTRLSTS_admux]
                uint32_t    testmd    :2;         // bit: 20,21      (R) Set to 00b.See SYSBOOT Configuration Pins for more information.
                uint32_t    sysboot1  :2;         // bit: 22,23      (R) Used to select crystal clock frequency.See SYSBOOT Configuration Pins. 
                uint32_t              :8;         // bit: 24..31     Reserved  
            } b;                                  // Structure used for bit access 
            uint32_t  reg;                        // Type used for register access 
        } control_status_reg_t;
    
        enum e_CTRLSTS_admux : uint32_t
        {
            NO_ADDR_DATA_MUXING       = 0x0,
            ADDR_ADDR_DATA_MUXING     = 0x1, 
            ADDR_DATA_MUXING          = 0x2,
            ADMUX_RESERVED            = 0x3      
        };

        /* [reset state = 0x0] */
        typedef union
        {
            struct
            {
                uint32_t    bc            :1;         // bit: 0      (R) Boot Complete
                uint32_t                  :15;        // bit: 1..15  Reserved
                uint32_t    booterr       :4;         // bit: 16..19 (R) Boot Error code
                uint32_t    rsvd2         :12;        // bit: 20..31 Reserved
            } b;
            uint32_t  reg;
        } control_bootstat_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                          /* The CONTROL_EMIF_SDRAM_CONFIG register exports SDRAM configuration information to the EMIF
                                                          after resuming from low power scenarios.
                                                          This register should be loaded with the same value as SDRAM_CONFIG during DDR initialization.  */
                 
                uint32_t    PAGESIZE       :3;         // bit: 0..2   (RW) Page Size. Defines the internal page size of connected SDRAMdevices [see e_SDRAM_PAGESIZE ]
                uint32_t    EBANK          :1;         // bit: 3      (RW) External chip select setup [0x0 = use pad_cs_o_n[0] only; 0x1 = use pad_cs_o_n[1:0] ]                       
                uint32_t    IBANK          :3;         // bit: 4..6   (RW) Internal Bank setup. Defines number of banks inside connected SDRAM devices [see e_SDRAM_IBANK]     
                uint32_t    ROWSIZE        :3;         // bit: 7..9   (RW) Defines the number of row address bits of connected SDRAM devices[see e_SDRAM_ROWSIZE]
                uint32_t    CL             :4;         // bit: 10..13 (RW) CAS Latency. The value of this field defines the CAS latency to be used when accessing connected SDRAM devices.[ see e_SDRAM_CAS_LATENCY ]
                uint32_t    NARROW_MODE    :2;         // bit: 14..15 (RW) SDRAM data bus width.[0x0 = for 32-bit ; 0x1 = for 16-bit]
                uint32_t    CWL            :2;         // bit: 16,17  (RW) DDR3 CAS Write latency.[see e_DDR3_CAS_LATENCY ]
                uint32_t    SDRAM_DRIVE    :2;         // bit: 18,19  (RW) SDRAM drive strength. [ see e_SDRAM_DRIVE_STRENGTH ]
                uint32_t                   :1;         // bit: 20     Reserved
                uint32_t    DYN_ODT        :2;         // bit: 21,22  (RW) DDR3 Dynamic ODT.[ see e_SDRAM_DYNAMIC_ODT ]
                uint32_t    DDR2_DDQS      :1;         // bit: 23     (R)  Defaults to 0 for single ended DQS. For differential operation, SDRAM_CONFIG register in the EMIF module must be written
                uint32_t    DDR_TERM       :3;         // bit: 24..26 (RW) DDR2 and DDR3 termination resistor value. [see e_DDR2_TERMINATION_RESISTOR and e_DDR3_TERMINATION_RESISTOR]
                uint32_t    IBANK_POS      :2;         // bit: 27,28  (RW) Internal bank position.[ see e_IBANK_POS ]
                uint32_t    SDRAM_TYPE     :3;         // bit: 29,31  (RW) SDRAM Type selection [see e_SDRAM_TYPE]  
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } control_emif_sdram_config_reg_t;
        
        enum e_SDRAM_PAGESIZE : uint32_t
        {
            WORD_256     = 0x0,     // Set to 0 for 256-word page (8 column bits)
            WORD_512     = 0x1,     // set to 1 for 512-word page (9 column bits) 
            WORD_1024    = 0x2,     // set to 2 for 1024-word page (10 column bits)
            WORD_2048    = 0x3      // set to 3 for 2048-word page (11 column bits)    
        };
    
        enum e_SDRAM_IBANK : uint32_t
        {
            IBANK_BANK_1    = 0x0,    // Set to 0 for 1 bank
            IBANK_BANK_2    = 0x1,    // set to 1 for 2 banks 
            IBANK_BANK_3    = 0x2,     // set to 2 for 4 banks
            IBANK_BANK_4    = 0x3      // set to 3 for 8 banks  
        };
    
        /** This field is only used when ibank_pos field in SDRAM Config register is set to 1, 2, or 3. **/
        enum e_SDRAM_ROWSIZE : uint32_t
        {
            ROWSIZE_9_BITS_ROW     = 0x0,     // Set to 0 for 9 row bits
            ROWSIZE_10_BITS_ROW    = 0x1,     // set to 1 for 9 row bits 
            ROWSIZE_11_BITS_ROW    = 0x2,     // set to 2 for 9 row bits
            ROWSIZE_12_BITS_ROW    = 0x3,     // set to 3 for 9 row bits
            ROWSIZE_13_BITS_ROW    = 0x4,     // set to 4 for 9 row bits 
            ROWSIZE_14_BITS_ROW    = 0x5,     // set to 5 for 9 row bits 
            ROWSIZE_15_BITS_ROW    = 0x6,     // set to 6 for 9 row bits 
            ROWSIZE_16_BITS_ROW    = 0x7      // set to 7 for 9 row bits
        };
    
        /** Value of 2, 3, 4,
        and 5 (CAS latency of 2, 3, 4, and 5) are supported for DDR2. Value
        of 2, 4, 6, 8, 10, 12, and 14 (CAS latency of 5, 6, 7, 8, 9, 10, and 11)
        are supported for DDR3. All other values are reserved.**/
        enum e_SDRAM_CAS_LATENCY : uint32_t
        {
            SDRAM_CAS_5    = 0x2,     // For DDR3
            SDRAM_CAS_6    = 0x5,     // For DDR3 
            SDRAM_CAS_7    = 0x6,     // For DDR3 
            SDRAM_CAS_8    = 0x8,     // For DDR3 
            SDRAM_CAS_9    = 0x10,    // For DDR3
            SDRAM_CAS_10   = 0x12,    // For DDR3
            SDRAM_CAS_11   = 0x14,    // For DDR3
        };
    
        /** Use the lowest value supported for best performance. **/
        enum e_DDR3_CAS_LATENCY : uint32_t
        {
            DDR3_CAS_5    = 0x0,    
            DDR3_CAS_6    = 0x1,    
            DDR3_CAS_7    = 0x2,    
            DDR3_CAS_8    = 0x3,    
        };
    
        /** For DDR2, set to 0 for normal, and set to 1 for weak drive strength.
            For DDR3, set to 0 for RZQ/6 and set to 1 for RZQ/7.
            For LPDDR1, set to 0 for full, set to 1 for 1/2, set to 2 for 1/4, and set
            to 3 for 1/8 drive strength. **/
        enum e_SDRAM_DRIVE_STRENGTH : uint32_t
        {
            STRENGTH_0    = 0x0,    
            STRENGTH_1    = 0x1,    
            STRENGTH_2    = 0x2,
            STRENGTH_3    = 0x3,       
        };
    
        enum e_SDRAM_DYNAMIC_ODT : uint32_t
        {
            DYN_ODT_TURN_OFF    = 0x0,    
            DYN_ODT_RZQ4        = 0x1,    
            DYN_ODT_RZQ2        = 0x2,      
        };
    
        enum e_DDR2_TERMINATION_RESISTOR : uint32_t
        {
            DDR2_TERMINATION_DISABLE    = 0x0,    
            DDR2_TERMINATION_75_Ohm     = 0x1,    
            DDR2_TERMINATION_150_Ohm    = 0x2,
            DDR2_TERMINATION_50_Ohm     = 0x3      
        };
    
        enum e_DDR3_TERMINATION_RESISTOR : uint32_t
        {
            DDR3_TERMINATION_DISABLE  = 0x0,    
            DDR3_TERMINATION_RZQ4     = 0x1,    
            DDR3_TERMINATION_RZQ2     = 0x2,
            DDR3_TERMINATION_RZQ6     = 0x3, 
            DDR3_TERMINATION_RZQ12    = 0x4,
            DDR3_TERMINATION_RZQ8     = 0x5,    
        };
    
        enum e_IBANK_POS : uint32_t
        {
            IBANK_POS_0     = 0x0,   // All Bank Address bits assigned from OCP address above column address bits. 
            IBANK_POS_1     = 0x1,   // Bank Address bits [1:0] assigned from OCP address above column address bits and bit [2] from OCP address bits above row address bits.    
            IBANK_POS_2     = 0x2,   // Bank Address bit [0] assigned from OCP address above column address bits and bit [2:1] from OCP address bits above row address bits.
            IBANK_POS_3     = 0x3,   // All Bank Address bits assigned from OCP address bits above row address bits.     
        };
    
        /** All other reserved**/
        enum e_SDRAM_TYPE : uint32_t
        {    
            SDRAM_TYPE_LPDDR1   = 0x1,    
            SDRAM_TYPE_DDR2     = 0x2,
            SDRAM_TYPE_DDR3     = 0x3   
        };

        /* [reset state = 0x0] */
        typedef union
        {
            struct
            {
                uint32_t    novbgbyr      :1;         // bit: 0      (RW)
                uint32_t    nocap         :1;         // bit: 1      (RW)
                uint32_t    bbsel         :1;         // bit: 2      (RW)
                uint32_t    hz            :1;         // bit: 3      (RW)
                uint32_t    lowpwr        :1;         // bit: 4      (RW)
                uint32_t    ldobypassz    :1;         // bit: 5      (RW)
                uint32_t                  :10;        // bit: 6..15  Reserved
                uint32_t    vsetrbb       :5;         // bit: 16..20 (RW) VSET for RBB
                uint32_t    vsetfbb       :5;         // bit: 21..25 (RW) VSET for FBB
                uint32_t    rsvd2         :6;         // bit: 26..31 Reserved
            } b;
            uint32_t  reg;
        } cortex_vbbldo_ctrl_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                   /*  */
                 
                uint32_t            :16;        // bit: 0..15      Reserved
                uint32_t    vset    :10;        // bit: 16..25     (RW) Trims VDDAR                       
                uint32_t            :6;         // bit: 26..31     Reserved
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } core_sldo_ctrl_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                   /*  */
                 
                uint32_t            :16;        // bit: 0..15      Reserved
                uint32_t    vset    :10;        // bit: 16..25     (RW) Trims VDDAR                       
                uint32_t            :6;         // bit: 26..31     Reserved
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } mpu_sldo_ctrl_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                            /*  */             
    
                uint32_t    clkdivopp50_en    :1;        // bit: 1        (RW) [see e_CLK32DIVRATIO]                       
                uint32_t                      :31;       // bit: 2..31    Reserved
            } b;                                         // Structure used for bit access 
            uint32_t  reg;                               // Type used for register access 
        } clk32kdivratio_ctrl_reg_t;
    
        enum e_CLK32DIVRATIO : uint32_t
        {    
            CLK32_OPP100   = 0x0,   // OPP100 operation, use ratio for 24MHz to 32KHz division   
            CLK32_OPP50    = 0x1    // OPP50 operation, use ratio for 12MHz to 32KHz division
        };
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                      /*  */
                 
                uint32_t    tshut       :1;        // bit: 0      (R) [0x0 = Normal operation; 0x1 = Thermal shutdown event (greater than 147C)]
                uint32_t    ecoz        :1;        // bit: 1      (R) ADC end of conversion [0x0 =  End of conversion; 0x1 = Conversion in progress]                      
                uint32_t    contconv    :1;        // bit: 2      (RW) [0x0 = ADC single conversion mode; 0x1 = ADC continuous conversion mode]     
                uint32_t    clrz        :1;        // bit: 3      (RW) Resets the digital outputs [0x0 =  ; 0x1 = ]
                uint32_t    soc         :1;        // bit: 4      (RW) ADC start of conversion.[0x0 = NOP ; 0x1 = Transition to high starts a new ADC conversion cycle.]
                uint32_t    tmpsoff     :1;        // bit: 5      (RW) [0x0 = Normal operation ; 0x1 = Temperature sensor is off and thermal shutdown in OFF mode]                      
                uint32_t    bgroff      :1;        // bit: 6      (RW) [0x0 =  Normal operation; 0x1 = Bandgap is OFF (OFF Mode)]     
                uint32_t    cbiassel    :1;        // bit: 7      (RW) [0x0 =  Select bandgap voltage as reference; 0x1 = Select resistor divider as reference]
                uint32_t    dtemp       :8;        // bit: 8..15  (R)  Temperature data from ADC.To be used when end of conversion (EOCZ) is 0.
                uint32_t                :16;       // bit: 16..31  Reserved  
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } bandgap_ctrl_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                           /*  */
                 
                uint32_t    dtrtempsc       :8;         // bit: 0..7      (RW) trim the output voltage of bandgap 
                uint32_t    dtrtemps        :8;         // bit: 8..15     (RW) trim the output voltage of bandgap                      
                uint32_t    dtrbgapv        :8;         // bit: 16..23    (RW) trim the temperature sensor    
                uint32_t    dtrbgapc        :8;         // bit: 24..31    (RW) trim the temperature sensor
            } b;                                        // Structure used for bit access 
            uint32_t  reg;                              // Type used for register access 
        } bandgap_trim_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                           /*  */
                 
                uint32_t    mpu_dpll_clkinpulow_sel       :1;         // bit: 0        (RW) [0x0 = Select CORE_CLKOUT_M6 clock as CLKINPULOW ; 0x1 = Select PER_CLKOUT_M2 clock as CLKINPULOW] 
                uint32_t    disp_pll_clkinpulow_sel       :1;         // bit: 1        (RW) [0x0 = Select CORE_CLKOUT_M6 clock as CLKINPULOW ; 0x1 = Select PER_CLKOUT_M2 clock as CLKINPULOW]                      
                uint32_t    ddr_pll_clkinpulow_sel        :1;         // bit: 2        (RW) [0x0 = Select CORE_CLKOUT_M6 clock as CLKINPULOW ; 0x1 = Select PER_CLKOUT_M2 clock as CLKINPULOW]    
                uint32_t                                  :29;        // bit: 3..31    Reserved
            } b;                                                      // Structure used for bit access 
            uint32_t  reg;                                            // Type used for register access 
        } pll_clkinpulow_ctrl_reg_t;
    
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                           /*  */
                 
                uint32_t    resselect       :1;         // bit: 0        (RW) [0x0 = Enable 1M ohm internal resistor (connected between XTALIN andXTALOUT). ; 
                                                        //                     0x1 = Disable 1M ohm internal resistor (bias resistor needs to beprovided externally to device).]    
                uint32_t                    :31;        // bit: 1..31    Reserved
            } b;                                        // Structure used for bit access 
            uint32_t  reg;                              // Type used for register access 
        } mosc_ctrl_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /*  */
                 
                uint32_t    dscount       :16;        // bit: 0..15      (RW) Programmable count of how many CLK_M_OSC clocks needs to be
                                                      //                      seen before exiting deep sleep mode  
                uint32_t                  :1;         // bit: 16         Reserved                      
                uint32_t    dsenable      :1;         // bit: 17         (RW) Deep sleep enable [0x0 = Normal operation; 0x1 = Master oscillator output is gated]    
                uint32_t                  :14;        // bit: 18..31     Reserved
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } deepsleep_ctrl_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /*  */
                 
                uint32_t                  :8;         // bit: 0..7    Reserved
                uint32_t    ponout_per    :1;         // bit: 8       (R) Power Enable status for PER DPLL [0x0 = Disabled; 0x1 = Enabled]
                uint32_t    pgoodout_per  :1;         // bit: 9       (R) Power Good status for PER DPLL [0x0 = Power Fault; 0x1 = Power Good]                  
                uint32_t                  :6;         // bit: 10..15  Reserved    
                uint32_t    ponout_disp   :1;         // bit: 16      (R) Power Enable status for DISP DPLL [0x0 = Disabled; 0x1 = Enabled ]
                uint32_t    pgoodout_disp :1;         // bit: 17      (R) Power Good status for DISP DPLL [0x0 = Power Fault; 0x1 = Power Good] 
                uint32_t                  :6;         // bit: 18..23  Reserved
                uint32_t    ponout_ddr    :1;         // bit: 24      (R) Power Enable status for DDR DPLL [0x0 = Disabled; 0x1 = Enabled ]
                uint32_t    pgoodout_ddr  :1;         // bit: 25      (R) Power Good status for DDR DPLL [0x0 = Power Fault; 0x1 = Power Good]
                uint32_t                  :6;         // bit: 26..31  Reserved
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } dpll_pwr_sw_status_reg_t;
    
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* See device errata for detailed information on functionality in each device revision. */
                 
                uint32_t                  :1;         // bit: 0       Reserved
                uint32_t    mfgr          :11;        // bit: 1..11   (R) Manufacturer's JTAG ID [0000b = Silicon Revision 1.0; 0001b = Silicon Revision 2.0; 0010b = Silicon Revision 2.1]
                uint32_t    partnum       :16;        // bit: 12..27  (R) Device part number (unique JTAG ID)                  
                uint32_t    devrev        :4;         // bit: 28..31  (R) Device revision.
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } device_id_reg_t;
    
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /*  */
                 
                uint32_t    dev_feature_bits  :32;    // bit: 0..31   (R) Device-dependent, See Device Feature Comparison table in devicedata manual
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } dev_feature_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /*  */
                 
                uint32_t    host_arm      :2;         // bit: 0,1      (RW) Host Cortex A8 initiator priority
                uint32_t                  :2;         // bit: 2,3      Reserved                     
                uint32_t    pru_icss      :2;         // bit: 4,5      (RW) PRU-ICSS initiator priority     
                uint32_t    mmu           :2;         // bit: 6,7      (RW) System MMU initiator priority
                uint32_t                  :6;         // bit: 8..13    Reserved
                uint32_t    p1500         :2;         // bit: 14,15    (RW) P1500 Port Initiator priority                      
                uint32_t    tcrd0         :2;         // bit: 16,17    (RW) TPTC 0 Read Port initiator priority     
                uint32_t    tcwr0         :2;         // bit: 18,19    (RW) TPTC 0 Write Port initiator priority
                uint32_t    tcrd1         :2;         // bit: 20,21    (RW) TPTC 1 Read Port initiator priority
                uint32_t    tcwr1         :2;         // bit: 22,23    (RW) TPTC 1 Write Port initiator priority                     
                uint32_t    tcrd2         :2;         // bit: 24,25    (RW) TPTC 2 Read Port initiator priority     
                uint32_t    tcwr2         :2;         // bit: 26,27    (RW) TPTC 2 Write Port initiator priority
                uint32_t                  :4;         // bit: 28,31    Reserved  
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } init_priority_0_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                       /*  */
                 
                uint32_t    cpsw        :2;         // bit: 0,1      (RW) CPSW initiator priority
                uint32_t                :2;         // bit: 2,3      Reserved                     
                uint32_t    usb_dma     :2;         // bit: 4,5      (RW) USB DMA port initiator priority     
                uint32_t    usb_qmgr    :2;         // bit: 6,7      (RW) USB Queue Manager initiator priority
                uint32_t                :12;        // bit: 8..13    Reserved
                uint32_t    sgx         :2;         // bit: 20,21    (RW) SGX initiator priorityy                      
                uint32_t    lcd         :2;         // bit: 22,23    (RW) LCD initiator priority     
                uint32_t    debug       :2;         // bit: 24,25    (RW) Debug Subsystem initiator priority
                uint32_t                :6;         // bit: 26..31   Reserved  
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } init_priority_1_reg_t;

        /* [reset state = 0x0] */
        typedef union
        {
            struct
            {
                uint32_t                  :7;         // bit: 0..6   Reserved
                uint32_t    mmu_disable   :1;         // bit: 7      (RW) MMU disable
                uint32_t    rsvd2         :7;         // bit: 8..14  Reserved
                uint32_t    mmu_abort     :1;         // bit: 15     (RW) MMU abort enable
                uint32_t    rsvd3         :16;        // bit: 16..31 Reserved
            } b;
            uint32_t  reg;
        } control_mmu_cfg_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                      /*  */
                 
                uint32_t    tc0dbs        :1;         // bit: 0,1      (RW) TPTC0 Default Burst Size[see e_TPTC_BURST_SIZE]
                uint32_t    tc1dbs        :1;         // bit: 2,3      (RW) TPTC1 Default Burst Size[see e_TPTC_BURST_SIZE]                      
                uint32_t    tc2dbs        :1;         // bit: 4,5      (RW) TPTC2 Default Burst Size[see e_TPTC_BURST_SIZE]     
                uint32_t                  :26;        // bit: 6..31  Reserved  
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } tptc_cfg_reg_t;
    
        enum e_TPTC_BURST_SIZE : uint32_t
        {
            TPTC_16_BYTE  = 0x0,
            TPTC_32_BYTE  = 0x1,
            TPTC_64_BYTE  = 0x2,
            TPTC_128_BYTE = 0x3,
        };

        /* [reset state = 0x0] */
        typedef union
        {
            struct
            {
                uint32_t    par_en        :1;         // bit: 0      (RW) Parity enable
                uint32_t    par_resp_en   :1;         // bit: 1      (RW) Parity response enable
                uint32_t                  :2;         // bit: 2..3   Reserved
                uint32_t    par_int_clr   :1;         // bit: 4      (RW) Parity interrupt clear
                uint32_t                  :27;        // bit: 5..31  Reserved
            } b;
            uint32_t  reg;
        } control_ocmc_cfg_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                             /*  */
                 
                uint32_t    cm_pwrdn          :1;         // bit: 0      (RW) Power down the USB CM PHY [0x0 = normal mode; 0x1 = Powered down ]
                uint32_t    otg_pwrdn         :1;         // bit: 1      (RW) Power down the USB OTG PHY [0x0 = normal mode; 0x1 = Powered down ]                      
                uint32_t    chgdet_dis        :1;         // bit: 2      (RW) Charger Detect Disable [0x0 = Enable; 0x1 = Disable ]  
                uint32_t    chgdet_rstrt      :1;         // bit: 3      (RW) Restart Charger Detect.[ �� �� �������� ]
                uint32_t    srcondm           :1;         // bit: 4      (RW) Source on DM [0x0 = Source on DP; 0x1 = Source on DM ]                      
                uint32_t    sinkondp          :1;         // bit: 5      (RW) Sink on DP [0x0 = Sink on DM; 0x1 = Sink on DP ]
                uint32_t    chgisink_en       :1;         // bit: 6      (RW) Enable ISINK on DM line (Host Charger case)[ �� ]
                uint32_t    chgvsrc_en        :1;         // bit: 7      (RW) Enable VSRC on DP line (Host Charger case) [ �� ]                      
                uint32_t    dmpulldn          :1;         // bit: 8      (RW) Pull-down on DM line [0x0 = No effect; 0x1 = Enable pull-down on DM line ]
                uint32_t    dppullup          :1;         // bit: 9      (RW) Pull-up on DP line [0x0 = No effect; 0x1 = Enable pull-up on DP line ]
                uint32_t    cdet_extctl       :1;         // bit: 10     (RW) Bypass the charger detection state machine [0x0 = Charger detection on; 0x1 = Charger detection is bypassed ]                      
                uint32_t                      :1;         // bit: 11     Reserved
                uint32_t    gpiomode          :1;         // bit: 12     (RW) GPIO Mode [0x0 = USB Mode; 0x1 = GPIO Mode (UART Mode) ]
                uint32_t    gpio_sig_inv      :1;         // bit: 13     (RW) UART TX -> Invert -> DP ; UART RX -> Invert -> DM                   
                uint32_t    gpio_sig_cross    :1;         // bit: 14     (RW) UART TX -> DM; UART RX -> DP 
                uint32_t                      :2;         // bit: 15,16   Reserved
                uint32_t    dpgpio_pd         :1;         // bit: 17     (RW) Pulldown on DP in GPIO Mode [0x0 = Enables pulldown; 0x1 = Disables pulldown ]                      
                uint32_t    dmgpio_pd         :1;         // bit: 18     (RW) Pulldown on DM in GPIO Mode [0x0 = Enables pulldown; 0x1 = Disables pulldown ]
                uint32_t    otgvdet_en        :1;         // bit: 19     (RW) VBUS Detect Enable [0x0 = Disable VBUS Detect Enable; 0x1 = Turns on all comparators except Session End comparator ]
                uint32_t    otgsessenden      :1;         // bit: 20     (RW) Session End Detect Enable [0x0 = Disable Session End Comparator; 0x1 = Turns on Session End Comparator ]                      
                uint32_t                      :2;         // bit: 21,22   Reserved
                uint32_t    datapolarity_inv  :1;         // bit: 23     (RW) Data Polarity Invert: [0x0 = DP/DM (normal polarity matching port definition); 0x1 = DM/DP (inverted polarity of port definition) ]   
                uint32_t                      :8;         // bit: 24..31  Reserved.Any writes to this register must keep these bits set to 0x3C.
            } b;                                          // Structure used for bit access 
            uint32_t  reg;                                // Type used for register access 
        } usb_ctrl0_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                             /*  */
                 
                uint32_t    chgdetdone        :1;         // bit: 0      (R) Charger Detection Protocol Done
                uint32_t    chgdetect         :1;         // bit: 1      (R) Charger Detection Status [0x0 = Charger was no detected; 0x1 = Charger was detected ]                      
                uint32_t    cdet_datadet      :1;         // bit: 2      (R) Charger Comparator Output 
                uint32_t    cdet_dpdet        :1;         // bit: 3      (R) DP Comparator Output
                uint32_t    cdet_dmdet        :1;         // bit: 4      (R) DM Comparator Output                    
                uint32_t    chgdetsts         :3;         // bit: 5      (R) Charge Detection Status [ see e_USB_CDET_STS ]  
                uint32_t                      :24;         // bit: 24..31  Reserved.Any writes to this register must keep these bits set to 0x3C.
            } b;                                          // Structure used for bit access 
            uint32_t  reg;                                // Type used for register access 
        } usb_sts0_reg_t;
    
        enum e_USB_CDET_STS : uint32_t
        {
            USB_CDET_WAITSTATE         = 0x0,
            USB_CDET_NO_CONTACT        = 0x1,
            USB_CDET_PS2               = 0x2,
            USB_CDET_UNKNOWN_ERR       = 0x3,
            USB_CDET_DIDICATED_CHARGER = 0x4,
            USB_CDET_HOST_CHARGER      = 0x5,
            USB_CDET_PC                = 0x6,
            USB_CDET_INTERRUPT         = 0x7  // if any of the pullup is enabled, charger detect routine gets interrupted and will restart from the beginning if the same is disabled
        };
    
        /* (offset = 0x628)[reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                             /*  */
                 
                uint32_t    cm_pwrdn          :1;         // bit: 0      (RW) Power down the USB CM PHY [0x0 = normal mode; 0x1 = Powered down ]
                uint32_t    otg_pwrdn         :1;         // bit: 1      (RW) Power down the USB OTG PHY [0x0 = normal mode; 0x1 = Powered down ]                      
                uint32_t    chgdet_dis        :1;         // bit: 2      (RW) Charger Detect Disable [0x0 = Enable; 0x1 = Disable ]  
                uint32_t    chgdet_rstrt      :1;         // bit: 3      (RW) Restart Charger Detect.[ �� �� �������� ]
                uint32_t    srcondm           :1;         // bit: 4      (RW) Source on DM [0x0 = Source on DP; 0x1 = Source on DM ]                      
                uint32_t    sinkondp          :1;         // bit: 5      (RW) Sink on DP [0x0 = Sink on DM; 0x1 = Sink on DP ]
                uint32_t    chgisink_en       :1;         // bit: 6      (RW) Enable ISINK on DM line (Host Charger case)[ �� ]
                uint32_t    chgvsrc_en        :1;         // bit: 7      (RW) Enable VSRC on DP line (Host Charger case) [ �� ]                      
                uint32_t    dmpulldn          :1;         // bit: 8      (RW) Pull-down on DM line [0x0 = No effect; 0x1 = Enable pull-down on DM line ]
                uint32_t    dppullup          :1;         // bit: 9      (RW) Pull-up on DP line [0x0 = No effect; 0x1 = Enable pull-up on DP line ]
                uint32_t    cdet_extctl       :1;         // bit: 10     (RW) Bypass the charger detection state machine [0x0 = Charger detection on; 0x1 = Charger detection is bypassed ]                      
                uint32_t                      :1;         // bit: 11     Reserved
                uint32_t    gpiomode          :1;         // bit: 12     (RW) GPIO Mode [0x0 = USB Mode; 0x1 = GPIO Mode (UART Mode) ]
                uint32_t    gpio_sig_inv      :1;         // bit: 13     (RW) UART TX -> Invert -> DP ; UART RX -> Invert -> DM                   
                uint32_t    gpio_sig_cross    :1;         // bit: 14     (RW) UART TX -> DM; UART RX -> DP 
                uint32_t                      :2;         // bit: 15,16   Reserved
                uint32_t    dpgpio_pd         :1;         // bit: 17     (RW) Pulldown on DP in GPIO Mode [0x0 = Enables pulldown; 0x1 = Disables pulldown ]                      
                uint32_t    dmgpio_pd         :1;         // bit: 18     (RW) Pulldown on DM in GPIO Mode [0x0 = Enables pulldown; 0x1 = Disables pulldown ]
                uint32_t    otgvdet_en        :1;         // bit: 19     (RW) VBUS Detect Enable [0x0 = Disable VBUS Detect Enable; 0x1 = Turns on all comparators except Session End comparator ]
                uint32_t    otgsessenden      :1;         // bit: 20     (RW) Session End Detect Enable [0x0 = Disable Session End Comparator; 0x1 = Turns on Session End Comparator ]                      
                uint32_t                      :2;         // bit: 21,22   Reserved
                uint32_t    datapolarity_inv  :1;         // bit: 23     (RW) Data Polarity Invert: [0x0 = DP/DM (normal polarity matching port definition); 0x1 = DM/DP (inverted polarity of port definition) ]   
                uint32_t                      :8;         // bit: 24..31  Reserved.Any writes to this register must keep these bits set to 0x3C.
            } b;                                          // Structure used for bit access 
            uint32_t  reg;                                // Type used for register access 
        } usb_ctrl1_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                             /*  */
                 
                uint32_t    chgdetdone        :1;         // bit: 0      (R) Charger Detection Protocol Done
                uint32_t    chgdetect         :1;         // bit: 1      (R) Charger Detection Status [0x0 = Charger was no detected; 0x1 = Charger was detected ]                      
                uint32_t    cdet_datadet      :1;         // bit: 2      (R) Charger Comparator Output 
                uint32_t    cdet_dpdet        :1;         // bit: 3      (R) DP Comparator Output
                uint32_t    cdet_dmdet        :1;         // bit: 4      (R) DM Comparator Output                    
                uint32_t    chgdetsts         :3;         // bit: 5      (R) Charge Detection Status [ see e_USB_CDET_STS ]  
                uint32_t                      :24;         // bit: 24..31  Reserved.Any writes to this register must keep these bits set to 0x3C.
            } b;                                          // Structure used for bit access 
            uint32_t  reg;                                // Type used for register access 
        } usb_sts1_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                             /*  */
                 
                uint32_t    macaddr_39_32     :8;         // bit: 0..7      (R) MAC0 Address - Byte 4.Reset value is device-dependent.
                uint32_t    macaddr_47_40     :8;         // bit: 8..15     (R) MAC0 Address - Byte 5.Reset value is device-dependent.                     
                uint32_t                      :16;        // bit: 24..31    Reserved.
            } b;                                          // Structure used for bit access 
            uint32_t  reg;                                // Type used for register access 
        } mac_id0_lo_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                             /*  */
                 
                uint32_t    macaddr_7_0       :8;         // bit: 0..7      (R) MAC0 Address - Byte 0.Reset value is device-dependent.
                uint32_t    macaddr_15_8      :8;         // bit: 8..15     (R) MAC0 Address - Byte 1.Reset value is device-dependent.  
                uint32_t    macaddr_23_16     :8;         // bit: 16..23    (R) MAC0 Address - Byte 2.Reset value is device-dependent.
                uint32_t    macaddr_31_24     :8;         // bit: 24..31    (R) MAC0 Address - Byte 3.Reset value is device-dependent.                   
            } b;                                          // Structure used for bit access 
            uint32_t  reg;                                // Type used for register access 
        } mac_id0_hi_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                             /*  */
                 
                uint32_t    macaddr_39_32     :8;         // bit: 0..7      (R) MAC1 Address - Byte 4.Reset value is device-dependent.
                uint32_t    macaddr_47_40     :8;         // bit: 8..15     (R) MAC1 Address - Byte 5.Reset value is device-dependent.                     
                uint32_t                      :16;        // bit: 24..31    Reserved.
            } b;                                          // Structure used for bit access 
            uint32_t  reg;                                // Type used for register access 
        } mac_id1_lo_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                             /*  */
                 
                uint32_t    macaddr_7_0       :8;         // bit: 0..7      (R) MAC1 Address - Byte 0.Reset value is device-dependent.
                uint32_t    macaddr_15_8      :8;         // bit: 8..15     (R) MAC1 Address - Byte 1.Reset value is device-dependent.  
                uint32_t    macaddr_23_16     :8;         // bit: 16..23    (R) MAC1 Address - Byte 2.Reset value is device-dependent.
                uint32_t    macaddr_31_24     :8;         // bit: 24..31    (R) MAC1 Address - Byte 3.Reset value is device-dependent.                   
            } b;                                          // Structure used for bit access 
            uint32_t  reg;                                // Type used for register access 
        } mac_id1_hi_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                                   /*  */
                 
                uint32_t    dcan0_raminit_start     :1;         // bit: 0        (RW) A transition from 0 to 1 will start DCAN0 RAM initialization sequence.
                uint32_t    dcan1_raminit_start     :1;         // bit: 1        (RW) A transition from 0 to 1 will start DCAN1 RAM initialization sequence.
                uint32_t                            :6;         // bit: 2..7     Reserved.
                uint32_t    dcan0_raminit_done      :1;         // bit: 8        (RW) [0x0 = DCAN0 RAM Initialization NOT complete; 0x1 = DCAN0 RAM Initialization complete ] 
                uint32_t    dcan1_raminit_done      :1;         // bit: 9        (RW) [0x0 = DCAN1 RAM Initialization NOT complete; 0x1 = DCAN1 RAM Initialization complete ]  
                uint32_t                            :22;         // bit: 10..31   Reserved.         
            } b;                                                // Structure used for bit access 
            uint32_t  reg;                                      // Type used for register access 
        } dcan_raminit_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /*  */
                 
                uint32_t    phy0_wuen     :1;         // bit: 0        (RW) PHY0 Wakeup Enable.Write to 1 enables WKUP from USB PHY0
                uint32_t                  :7;         // bit: 1..7     Reserved.
                uint32_t    phy1_wuen     :1;         // bit: 8        (RW) PHY1 Wakeup Enable. Write to 1 enables WKUP from USB PHY1.  
                uint32_t                  :23;        // bit: 10..31   Reserved.         
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } usb_wkup_ctrl_reg_t;

        /* (offset = 0x650) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                                 /* Register gmii_sel */

                uint32_t    gmii1_sel       : 2; // bits:0..1  (R/W) 00: Port1 GMII/MII Mode 01: Port1 RMII Mode 10: Port1 RGMII Mode 11: Not Used
                uint32_t    gmii2_sel       : 2; // bits:2..3  (R/W) 00: Port2 GMII/MII Mode 01: Port2 RMII Mode 10: Port2 RGMII Mode 11: Not Used
                uint32_t    rgmii1_idmode   : 1; // bit:4      (R/W) RGMII1 Internal Delay Mode 0: Reserved 1: No Internal Delay See &quot;Silicon Revision
                                                 //                 Functional Differences and Enhancements&quot; for differences in operation based on
                                                 //                 AM335x silicon revision.
                uint32_t    rgmii2_idmode   : 1; // bit:5      (R/W) RGMII2 Internal Delay Mode 0: Reserved 1: No Internal Delay See &quot;Silicon Revision
                                                 //                 Functional Differences and Enhancements&quot; for differences in operation based on
                                                 //                 AM335x silicon revision.
                uint32_t    rmii1_io_clk_en : 1; // bit:6      (R/W) 0: RMII Reference Clock Output mode. Enable RMII clock to be sourced from PLL 1: RMII
                                                 //                 Reference Clock Input mode. Enable RMII clock to be sourced from chip pin See
                                                 //                 &quot;Silicon Revision Functional Differences and Enhancements&quot; for differences in
                                                 //                 operation based on AM335x silicon revision.
                uint32_t    rmii2_io_clk_en : 1; // bit:7      (R/W) 0: RMII Reference Clock Output mode. Enable RMII clock to be sourced from PLL. 1: RMII
                                                 //                 Reference Clock Input mode. Enable RMII clock to be sourced from chip pin. See
                                                 //                 &quot;Silicon Revision Functional Differences and Enhancements&quot; for differences in
                                                 //                 operation based on AM335x silicon revision.
                uint32_t                    :24; // bits:8..31 (R)   Reserved
            } b;
            uint32_t reg;
        } gmii_sel_reg_t;

        /* (offset = 0x664) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                /* Register pwmss_ctrl */

                uint32_t    pwmss0_tbclken : 1; // bit:0      (R/W) Timebase clock enable for PWMSS0
                uint32_t    pwmss1_tbclken : 1; // bit:1      (R/W) Timebase clock enable for PWMSS1
                uint32_t    pwmss2_tbclken : 1; // bit:2      (R/W) Timebase clock enable for PWMSS2
                uint32_t                   :29; // bits:3..31 (R)   Reserved
            } b;
            uint32_t reg;
        } pwmss_ctrl_reg_t;
    
        /* (offset = 0x670) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                               /* Register mreqprio_0 */

                uint32_t    sab_init0     : 3; // bits:0..2   (R/W) MReqPriority for MPU Initiator 0 OCP Interface
                uint32_t                  : 1; // bit:3       (R)   Reserved
                uint32_t    sab_init1     : 3; // bits:4..6   (R/W) MReqPriority for MPU Initiator 1 OCP Interface
                uint32_t                  : 1; // bit:7       (R)   Reserved
                uint32_t    pru_icss_pru0 : 3; // bits:8..10  (R/W) MReqPriority for PRU-ICSS PRU0 Initiator OCP Interface
                uint32_t                  : 5; // bits:11..15 (R)   Reserved
                uint32_t    cpsw          : 3; // bits:16..18 (R/W) MReqPriority for CPSW Initiator OCP Interface
                uint32_t                  : 1; // bit:19      (R)   Reserved
                uint32_t    usb0          : 3; // bits:20..22 (R/W) MReqPriority for USB0 Initiator OCP Interface
                uint32_t                  : 1; // bit:23      (R)   Reserved
                uint32_t    usb1          : 3; // bits:24..26 (R/W) MReqPriority for USB1 Initiator OCP Interface
                uint32_t                  : 1; // bit:27      (R)   Reserved
                uint32_t    sgx           : 3; // bits:28..30 (R/W) MReqPriority for SGX Initiator OCP Interface
                uint32_t                  : 1; // bit:31      (R)   Reserved
            } b;
            uint32_t reg;
        } mreqprio_0_reg_t;


        /* (offset = 0x674) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                                      /* Register mreqprio_1 */

                uint32_t                         :32; // bits:0..31 (R) Reserved
            } b;
            uint32_t reg;
        } mreqprio_1_reg_t;


        /* (offset = 0x690) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                        /* Register hw_event_sel_grp1 */

                uint32_t    event1 : 8; // bits:0..7   (R/W) Select 1st trace event from group 1
                uint32_t    event2 : 8; // bits:8..15  (R/W) Select 2nd trace event from group 1
                uint32_t    event3 : 8; // bits:16..23 (R/W) Select 3rd trace event from group 1
                uint32_t    event4 : 8; // bits:24..31 (R/W) Select 4th trace event from group 1
            } b;
            uint32_t reg;
        } hw_event_sel_grp1_reg_t;


        /* (offset = 0x694) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                        /* Register hw_event_sel_grp2 */

                uint32_t    event5 : 8; // bits:0..7   (R/W) Select 5th trace event from group 2
                uint32_t    event6 : 8; // bits:8..15  (R/W) Select 6th trace event from group 2
                uint32_t    event7 : 8; // bits:16..23 (R/W) Select 7th trace event from group 2
                uint32_t    event8 : 8; // bits:24..31 (R/W) Select 8th trace event from group 2
            } b;
            uint32_t reg;
        } hw_event_sel_grp2_reg_t;


        /* (offset = 0x698) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                         /* Register hw_event_sel_grp3 */

                uint32_t    event9  : 8; // bits:0..7   (R/W) Select 9th trace event from group 3
                uint32_t    event10 : 8; // bits:8..15  (R/W) Select 10th trace event from group 3
                uint32_t    event11 : 8; // bits:16..23 (R/W) Select 11th trace event from group 3
                uint32_t    event12 : 8; // bits:24..31 (R/W) Select 12th trace event from group 3
            } b;
            uint32_t reg;
        } hw_event_sel_grp3_reg_t;


        /* (offset = 0x69C) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                         /* Register hw_event_sel_grp4 */

                uint32_t    event13 : 8; // bits:0..7   (R/W) Select 13th trace event from group 4
                uint32_t    event14 : 8; // bits:8..15  (R/W) Select 14th trace event from group 4
                uint32_t    event15 : 8; // bits:16..23 (R/W) Select 15th trace event from group 4
                uint32_t    event16 : 8; // bits:24..31 (R/W) Select 16th trace event from group 4
            } b;
            uint32_t reg;
        } hw_event_sel_grp4_reg_t;


        /* (offset = 0x6A0) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                           /* Register smrt_ctrl */

                uint32_t    sr0_sleep : 1; // bit:0      (R/W) 0: Disable sensor (SRSLEEP on sensor driven to 1) 1: Enable sensor (SRSLEEP on sensor
                                           //                 driven to 0).
                uint32_t    sr1_sleep : 1; // bit:1      (R/W) 0: Disable sensor (SRSLEEP on sensor driven to 1) 1: Enable sensor (SRSLEEP on sensor
                                           //                 driven to 0).
                uint32_t              :30; // bits:2..31 (R)   Reserved
            } b;
            uint32_t reg;
        } smrt_ctrl_reg_t;
    
        /* (offset = 0x6A4)[reset state = 0x0] */
        typedef union
        {
            struct
            {
                uint32_t    hw_dbg_sel               : 4;   // bit:  0..3  (R/W) Selects which Group of signals are sent out to the
                                                            //                   MODENA_HW_DBG_INFO register. Please see MPU functional spec for more details.
                                                            //                   [see e_HW_DBG_SEL]
                uint32_t                             : 5;   // bit:  4..8  (R) Reserved
                uint32_t    hw_dbg_gate_en           : 1;   // bit:  9     (R/W) To save power input to MPUSS_HW_DBG_INFO is gated off to all
                                                            //                   zeros when HW_DBG_GATE_EN bit is low.
                                                            //                   [0x0: Debug info gated off;
                                                            //                    0x1: Debug info not gated off]
                uint32_t                             :22;   // bit: 10..31 (R) Reserved
            } b;
            uint32_t  reg;
        } mpuss_hw_debug_sel_reg_t;

        enum e_HW_DBG_SEL : uint32_t
        {
            GROUP_0         = 0x0,
            GROUP_1         = 0x1,
            GROUP_2         = 0x2,
            GROUP_3         = 0x3,
            GROUP_4         = 0x4,
            GROUP_5         = 0x5,
            GROUP_6         = 0x6,
            GROUP_7         = 0x7,
            GROUP_RESERVED  = 0x8
        };

        /* (offset = 0x6A8)[reset state = 0x0] */
        typedef union
        {
            struct
            {
                uint32_t    hw_dbg_info   :32; // bit:  0..31 (R) Hardware Debug Info from MPU.
            } b;
            uint32_t  reg;
        } mpuss_hw_dbg_info_reg_t;

        /* [reset state = 0x0] */
        typedef union
        {
            struct
            {
                uint32_t    mmode0        :2;         // bit: 0..1
                uint32_t    mmode1        :2;         // bit: 2..3
                uint32_t    mmode2        :2;         // bit: 4..5
                uint32_t    mmode3        :2;         // bit: 6..7
                uint32_t    mmode4        :2;         // bit: 8..9
                uint32_t    mmode5        :2;         // bit: 10..11
                uint32_t    mmode6        :2;         // bit: 12..13
                uint32_t    mmode7        :2;         // bit: 14..15
                uint32_t    mmode8        :2;         // bit: 16..17
                uint32_t    mmode9        :2;         // bit: 18..19
                uint32_t    mmode10       :2;         // bit: 20..21
                uint32_t    mmode11       :2;         // bit: 22..23
                uint32_t    mmode12       :2;         // bit: 24..25
                uint32_t    mmode13       :2;         // bit: 26..27
                uint32_t    mmode14       :2;         // bit: 28..29
                uint32_t    mmode15       :2;         // bit: 30..31
            } b;
            uint32_t  reg;
        } mrgn_mode0_reg_t;

        /* [reset state = 0x0] */
        typedef union
        {
            struct
            {
                uint32_t    mmode16       :2;         // bit: 0..1
                uint32_t    mmode17       :2;         // bit: 2..3
                uint32_t    mmode18       :2;         // bit: 4..5
                uint32_t    mmode19       :2;         // bit: 6..7
                uint32_t                  :24;        // bit: 8..31  Reserved
            } b;
            uint32_t  reg;
        } mrgn_mode1_reg_t;
    
        /* (offset = 0x770) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                         /* Register vdd_mpu_opp_050 */

                uint32_t    ntarget :24; // bits:0..23  (R) Ntarget value for MPU Voltage domain OPP50 Reset value is device-dependent.
                uint32_t            : 8; // bits:24..31 (R) Reserved
            } b;
            uint32_t reg;
        } vdd_mpu_opp_050_reg_t;


        /* (offset = 0x774) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                         /* Register vdd_mpu_opp_100 */

                uint32_t    ntarget :24; // bits:0..23  (R) Ntarget value for MPU Voltage domain OPP100 Reset value is device-dependent.
                uint32_t            : 8; // bits:24..31 (R) Reserved
            } b;
            uint32_t reg;
        } vdd_mpu_opp_100_reg_t;


        /* (offset = 0x778) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                         /* Register vdd_mpu_opp_120 */

                uint32_t    ntarget :24; // bits:0..23  (R) Ntarget value for MPU Voltage domain OPP120 Reset value is device-dependent.
                uint32_t            : 8; // bits:24..31 (R) Reserved
            } b;
            uint32_t reg;
        } vdd_mpu_opp_120_reg_t;


        /* (offset = 0x77C) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                         /* Register vdd_mpu_opp_turbo */

                uint32_t    ntarget :24; // bits:0..23  (R) Ntarget value for MPU Voltage domain OPPTURBO Reset value is device-dependent.
                uint32_t            : 8; // bits:24..31 (R) Reserved
            } b;
            uint32_t reg;
        } vdd_mpu_opp_turbo_reg_t;


        /* (offset = 0x7B8) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                         /* Register vdd_core_opp_050 */

                uint32_t    ntarget :24; // bits:0..23  (R) Ntarget value for CORE Voltage domain OPP50 Reset value is device-dependent.
                uint32_t            : 8; // bits:24..31 (R) Reserved
            } b;
            uint32_t reg;
        } vdd_core_opp_050_reg_t;


        /* (offset = 0x7BC) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                         /* Register vdd_core_opp_100 */

                uint32_t    ntarget :24; // bits:0..23  (R) Ntarget value for CORE Voltage domain OPP100 Reset value is device-dependent.
                uint32_t            : 8; // bits:24..31 (R) Reserved
            } b;
            uint32_t reg;
        } vdd_core_opp_100_reg_t;


        /* (offset = 0x7D0) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                       /* Register bb_scale */

                uint32_t    bbias : 2; // bits:0..1   (R) BBIAS value from Efuse
                uint32_t          : 6; // bits:2..7   (R) Reserved
                uint32_t    scale : 4; // bits:8..11  (R) Dynamic core voltage scaling for class 0
                uint32_t          :20; // bits:12..31 (R) Reserved
            } b;
            uint32_t reg;
        } bb_scale_reg_t;


        /* (offset = 0x7F4) [reset state = 0x4516141] */
        typedef union
        {
            struct
            {
                                         /* Register usb_vid_pid */

                uint32_t    usb_pid :16; // bits:0..15  (R) USB Product ID
                uint32_t    usb_vid :16; // bits:16..31 (R) USB Vendor ID
            } b;
            uint32_t reg;
        } usb_vid_pid_reg_t;


        /* (offset = 0x7FC) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                                  /* Register efuse_sma */

                uint32_t    arm_mpu_max_freq :32; // bits:0..31 (R/W) Designates the ARM MPU Maximum Frequency supported by the device (PG2.x only). There are
                                                  //                 also voltag
            } b;
            uint32_t reg;
        } efuse_sma_reg_t;
    
        /* [reset state = 0xX]*/
        typedef union 
        { 
            struct 
            {                                         /**  See the device datasheet for information on default pin mux configurations. Note that the device ROM
                                                           may change the default pin mux for certain pins based on the SYSBOOT mode settings. **/
                 
                uint32_t    mode          :3;         // bit: 0..2     (RW) Pad functional signal mux select. Reset value is pad-dependent. [see e_PINMODE]
                uint32_t    puden         :1;         // bit: 3        (RW) Pad pullup/pulldown enable. Reset value is pad-dependent. [see e_PUDEN]
                uint32_t    putypesel     :1;         // bit: 4        (RW) Pad pullup/pulldown type selection.Reset value is pad-dependent. [see e_PUTYPESEL]
                uint32_t    rxactive      :1;         // bit: 5        (RW) Input enable value for the PAD. [see e_RXACTIVE]
                uint32_t    slewctrl      :1;         // bit: 6        (RW) Select between faster or slower slew rate.Reset value is pad-dependent. [see e_SLEWCTRL]
                uint32_t                  :25;        // bit: 7..31   Reserved.         
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } conf_module_pin_reg_t;
    
        /** Mode 0 is the primary mode. When mode 0 is set, the function mapped to the pin corresponds to the
            name of the pin. Mode 1 to mode 7 are possible modes for alternate functions. On each pin, some modes
            are used effectively for alternate functions, while other modes are unused and correspond to no functional
            configuration. !!! For most pads, the reset value for the MUXMODE field in the registers is 0b111 = 0x7 !!! **/
        enum e_PINMODE : uint32_t
        {
            PINMODE_0 = 0x0,    // Primary Mode = Mode 0
            PINMODE_1 = 0x1,    // Mode 1
            PINMODE_2 = 0x2,    // Mode 2
            PINMODE_3 = 0x3,    // Mode 3
            PINMODE_4 = 0x4,    // Mode 4
            PINMODE_5 = 0x5,    // Mode 5
            PINMODE_6 = 0x6,    // Mode 6
            PINMODE_7 = 0x7     // Mode 7
        };
    
        enum e_PUDEN : uint32_t
        {
            PULL_ENABLED  = 0x0,    // Pull Up or Down enabled
            PULL_DISABLED = 0x1    // Pull Up or Down disabled
        };
    
        enum e_PUTYPESEL : uint32_t
        {
            PULL_DOWN  = 0x0,    
            PULL_UP    = 0x1     
        };
    
        enum e_RXACTIVE : uint32_t
        {
            INPUT_DISABLE  = 0x0,    
            INPUT_ENABLE   = 0x1     
        };
    
        enum e_SLEWCTRL : uint32_t
        {
            FAST   = 0x0,    
            SLOW   = 0x1     
        };
    
        /* (offset = 0xE00) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                                /* Register cqdetect_status */

                uint32_t    cqstat_gpmc    : 1; // bit:0       (R) 1: IOs are 3.3V mode 0: IOs are 1.8V mode
                uint32_t    cqstat_mmcsd_a : 1; // bit:1       (R) 1: IOs are 3.3V mode 0: IOs are 1.8V mode
                uint32_t    cqstat_mmcsd_b : 1; // bit:2       (R) 1: IOs are 3.3V mode 0: IOs are 1.8V mode
                uint32_t    cqstat_gemac_a : 1; // bit:3       (R) 1: IOs are 3.3V mode 0: IOs are 1.8V mode
                uint32_t    cqstat_gemac_b : 1; // bit:4       (R) 1: IOs are 3.3V mode 0: IOs are 1.8V mode
                uint32_t    cqstat_general : 1; // bit:5       (R) 1: IOs are 3.3V mode 0: IOs are 1.8V mode
                uint32_t                   : 2; // bits:6..7   (R) Reserved
                uint32_t    cqerr_gpmc     : 1; // bit:8       (R) CQDetect Mode Error Status
                uint32_t    cqerr_mmcsd_a  : 1; // bit:9       (R) CQDetect Mode Error Status
                uint32_t    cqerr_mmcsd_b  : 1; // bit:10      (R) CQDetect Mode Error Status
                uint32_t    cqerr_gemac_a  : 1; // bit:11      (R) CQDetect Mode Error Status
                uint32_t    cqerr_gemac_b  : 1; // bit:12      (R) CQDetect Mode Error Status
                uint32_t    cqerr_general  : 1; // bit:13      (R) CQDetect Mode Error Status
                uint32_t                   :18; // bits:14..31 (R) Reserved
            } b;
            uint32_t reg;
        } cqdetect_status_reg_t;


        /* (offset = 0xE04) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                                   /* Register ddr_io_ctrl */

                uint32_t                      :28; // bits:0..27 (R)   Reserved
                uint32_t    mddr_sel          : 1; // bit:28     (R/W) 0: IOs set for DDR2/DDR3 (STL mode) 1: IOs set for mDDR (CMOS mode)
                uint32_t                      : 1; // bit:29     (R)   Reserved
                uint32_t    ddr_wuclk_disable : 1; // bit:30     (R/W) Disables the slow clock to WUCLKIN and ISOCLKIN of DDR emif SS and IOs (required for
                                                   //                 proper initialization, after which clock could be shut off). 0 = free running SLOW (32k)
                                                   //                 clock 1 = clock is synchronously gated
                uint32_t    ddr3_rst_def_val  : 1; // bit:31     (R/W) DDR3 reset default value
            } b;
            uint32_t reg;
        } ddr_io_ctrl_reg_t;
    
        /* (offset = 0xE0C) [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                         /**  Register virtual temperature process compensation **/
                 
                uint32_t    clrz      :1;        // bit: 0        (RW) clears flops, start count again, after low going pulse.
                uint32_t    filter    :3;        // bit: 1..3     (RW) Digital filter bits to prevent the controller from making excessive
                                                 //                    number of changes. [see e_DFILTER_UPD_REQ]
                uint32_t    lock      :1;        // bit: 4        (RW) [0x0 = Normal operation dynamic update;
                                                 //                     0x1= freeze dynamic update, pwrdn controller]
                uint32_t    ready     :1;        // bit: 5        (RW) [0x0 = Training sequence is not complete;
                                                 //                     0x1= Training sequence is complete]
                uint32_t    enable    :1;        // bit: 6        (RW) [0x0 = VTP macro in bypass mode. P and N are driven from PCIN and NCIN.;
                                                 //                     0x1= Dynamic VTP compensation mode]
                uint32_t              :1;        // bit: 7        (R) Reserved.
                uint32_t    ncin      :7;        // bit: 8..14    (R) Default/reset values of 'N' for the VTP controller.
                                                 //                   See "Silicon Revision Functional Differences and Enhancements" for
                                                 //                   differences in operation based on AM335x silicon revision.
                uint32_t              :1;        // bit: 15       (R) Reserved.
                uint32_t    pcin      :7;        // bit: 16..22   (R) Default/reset values of 'N' for the VTP controller.
                                                 //                   See "Silicon Revision Functional Differences and Enhancements" for
                                                 //                   differences in operation based on AM335x silicon revision.
                uint32_t              :9;        // bit: 23..31   (R) Reserved.
            } b;                                 // Structure used for bit access
            uint32_t  reg;                       // Type used for register access
        } vtp_ctrl_reg_t;

        enum e_DFILTER_UPD_REQ : uint32_t
        {
            DFILTER_OFF             = 0x0,       // 0x000: Filter off
            DFILTER_TWO_REQUESTS    = 0x1,       // 0x001: Update on two consecutive update requests
            DFILTER_THREE_REQUESTS  = 0x2,       // 0x010: Update on three consecutive update requests
            DFILTER_FOUR_REQUESTS   = 0x3,       // 0x011: Update on four consecutive update requests
            DFILTER_FIVE_REQUESTS   = 0x4,       // 0x100: Update on five consecutive update requests
            DFILTER_SIX_REQUESTS    = 0x5,       // 0x101: Update on six consecutive update requests
            DFILTER_SEVEN_REQUESTS  = 0x6,       // 0x110: Update on seven consecutive update requests
            DFILTER_EIGHT_REQUESTS  = 0x7,       // 0x111: Update on eight consecutive update requests
        };
    
        /* (offset = 0xE14) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                               /* Register vref_ctrl */

                uint32_t    ddr_vref_en   : 1; // bit:0      (R/W) active high internal reference enable for DDR
                uint32_t    ddr_vref_tap  : 2; // bits:1..2  (R/W) select for int ref for DDR 00 : Pad/Bias2 connected to internal reference VDDS/2 for 2uA
                                               //                 current load 01 : Pad/Bias2 connected to internal reference VDDS/2 for 4uA current load
                                               //                 10 : Pad/Bias2 connected to internal reference VDDS/2 for 6uA current load 11 :
                                               //                 Pad/Bias2 connected to internal reference VDDS/2 for 8uA current load
                uint32_t    ddr_vref_ccap : 2; // bits:3..4  (R/W) select for coupling cap for DDR 00 : No capacitor connected 01 : Capacitor between BIAS2
                                               //                 and VSS 10 : Capacitor between BIAS2 and VDDS 11: Capacitor between BIAS2 and VSS andamp
                                               //                 Capacitor between BIAS2 and VDDS
                uint32_t                  :27; // bits:5..31 (R)   Reserved
            } b;
            uint32_t reg;
        } vref_ctrl_reg_t;

        /* [reset state = 0x0] */
        typedef union
        {
            struct
            {
                uint32_t    pwrdn         :1;         // bit: 0      (RW) Power down
                uint32_t    pwrdn_se      :1;         // bit: 1      (RW) Power down single-ended
                uint32_t                  :30;        // bit: 2..31  Reserved
            } b;
            uint32_t  reg;
        } serdes_refclk_ctl_reg_t;
    
        /* (offset = 0xF90) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                           /* Register tpcc_evt_mux_0_3 */

                uint32_t    evt_mux_0 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 0
                uint32_t              : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_1 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 1
                uint32_t              : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_2 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 2
                uint32_t              : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_3 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 3
                uint32_t              : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_0_3_reg_t;


        /* (offset = 0xF94) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                           /* Register tpcc_evt_mux_4_7 */

                uint32_t    evt_mux_4 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 4
                uint32_t              : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_5 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 5
                uint32_t              : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_6 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 6
                uint32_t              : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_7 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 7
                uint32_t              : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_4_7_reg_t;


        /* (offset = 0xF98) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_8_11 */

                uint32_t    evt_mux_8  : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 8
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_9  : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 9
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_10 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 10
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_11 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 11
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_8_11_reg_t;


        /* (offset = 0xF9C) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_12_15 */

                uint32_t    evt_mux_12 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 12
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_13 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 13
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_14 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 14
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_15 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 15
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_12_15_reg_t;


        /* (offset = 0xFA0) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_16_19 */

                uint32_t    evt_mux_16 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 16
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_17 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 17
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_18 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 18
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_19 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 19
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_16_19_reg_t;


        /* (offset = 0xFA4) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_20_23 */

                uint32_t    evt_mux_20 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 20
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_21 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 21
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_22 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 22
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_23 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 23
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_20_23_reg_t;


        /* (offset = 0xFA8) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_24_27 */

                uint32_t    evt_mux_24 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 24
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_25 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 25
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_26 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 26
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_27 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 27
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_24_27_reg_t;


        /* (offset = 0xFAC) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_28_31 */

                uint32_t    evt_mux_28 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 28
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_29 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 29
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_30 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 30
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_31 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 31
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_28_31_reg_t;


        /* (offset = 0xFB0) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_32_35 */

                uint32_t    evt_mux_32 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 32
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_33 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 33
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_34 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 34
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_35 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 35
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_32_35_reg_t;


        /* (offset = 0xFB4) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_36_39 */

                uint32_t    evt_mux_36 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 36
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_37 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 37
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_38 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 38
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_39 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 39
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_36_39_reg_t;


        /* (offset = 0xFB8) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_40_43 */

                uint32_t    evt_mux_40 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 40
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_41 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 41
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_42 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 42
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_43 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 43
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_40_43_reg_t;


        /* (offset = 0xFBC) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_44_47 */

                uint32_t    evt_mux_44 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 44
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_45 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 45
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_46 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 46
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_47 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 47
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_44_47_reg_t;


        /* (offset = 0xFC0) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_48_51 */

                uint32_t    evt_mux_48 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 48
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_49 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 49
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_50 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 50
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_51 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 51
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_48_51_reg_t;


        /* (offset = 0xFC4) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_52_55 */

                uint32_t    evt_mux_52 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 52
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_53 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 53
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_54 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 54
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_55 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 55
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_52_55_reg_t;


        /* (offset = 0xFC8) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_56_59 */

                uint32_t    evt_mux_56 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 56
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_57 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 57
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_58 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 58
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_59 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 59
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_56_59_reg_t;


        /* (offset = 0xFCC) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                            /* Register tpcc_evt_mux_60_63 */

                uint32_t    evt_mux_60 : 6; // bits:0..5   (R/W) Selects 1 of 64 inputs for DMA event 60
                uint32_t               : 2; // bits:6..7   (R)   Reserved
                uint32_t    evt_mux_61 : 6; // bits:8..13  (R/W) Selects 1 of 64 inputs for DMA event 61
                uint32_t               : 2; // bits:14..15 (R)   Reserved
                uint32_t    evt_mux_62 : 6; // bits:16..21 (R/W) Selects 1 of 64 inputs for DMA event 62
                uint32_t               : 2; // bits:22..23 (R)   Reserved
                uint32_t    evt_mux_63 : 6; // bits:24..29 (R/W) Selects 1 of 64 inputs for DMA event 63
                uint32_t               : 2; // bits:30..31 (R)   Reserved
            } b;
            uint32_t reg;
        } tpcc_evt_mux_60_63_reg_t;


        /* (offset = 0xFD0) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                                /* Register timer_evt_capt */

                uint32_t    timer5_evtcapt : 5; // bits:0..4   (R/W) Timer 5 event capture mux
                uint32_t                   : 3; // bits:5..7   (R)   Reserved
                uint32_t    timer6_evtcapt : 5; // bits:8..12  (R/W) Timer 6 event capture mux
                uint32_t                   : 3; // bits:13..15 (R)   Reserved
                uint32_t    timer7_evtcapt : 5; // bits:16..20 (R/W) Timer 7 event capture mux
                uint32_t                   :11; // bits:21..31 (R)   Reserved
            } b;
            uint32_t reg;
        } timer_evt_capt_reg_t;


        /* (offset = 0xFD4) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                               /* Register ecap_evt_capt */

                uint32_t    ecap0_evtcapt : 5; // bits:0..4   (R/W) ECAP0 event capture mux
                uint32_t                  : 3; // bits:5..7   (R)   Reserved
                uint32_t    ecap1_evtcapt : 5; // bits:8..12  (R/W) ECAP1 event capture mux
                uint32_t                  : 3; // bits:13..15 (R)   Reserved
                uint32_t    ecap2_evtcapt : 5; // bits:16..20 (R/W) ECAP2 event capture mux
                uint32_t                  :11; // bits:21..31 (R)   Reserved
            } b;
            uint32_t reg;
        } ecap_evt_capt_reg_t;


        /* (offset = 0xFD8) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                             /* Register adc_evt_capt */

                uint32_t    adc_evtcapt : 4; // bits:0..3  (R/W) ECAP0 event capture mux
                uint32_t                :28; // bits:4..31 (R)   Reserved
            } b;
            uint32_t reg;
        } adc_evt_capt_reg_t;


        /* (offset = 0x1000) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                             /* Register reset_iso */

                uint32_t    iso_control : 1; // bit:0      (R/W) 0 : Ethernet Switch is not isolated 1 : Ethernet Switch is isolated
                uint32_t                :31; // bits:1..31 (R)   Reserved
            } b;
            uint32_t reg;
        } reset_iso_reg_t;


        /* (offset = 0x1318) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                                  /* Register dpll_pwr_sw_ctrl */

                uint32_t                     : 8; // bits:0..7 (R)   Reserved
                uint32_t    ponin_per        : 1; // bit:8     (R/W) Drives PONIN signal of PER DPLL.
                uint32_t    pgoodin_per      : 1; // bit:9     (R/W) Drives PGOODIN signal of PER DPLL.
                uint32_t    iso_per          : 1; // bit:10    (R/W) Drives ISO signal of PER DPLL.
                uint32_t    reset_per        : 1; // bit:11    (R/W) Drives RESET signal of PER DPLL.
                uint32_t    ret_per          : 1; // bit:12    (R/W) Drives RET of PER DPLL.
                uint32_t    isoscan_per      : 1; // bit:13    (R/W) Drives ISOSCAN of PER PLL.
                uint32_t                     : 1; // bit:14    (R)   Reserved
                uint32_t    sw_ctrl_per_dpll : 1; // bit:15    (R/W) Enable software control over PER DPLL RET, RESET, ISO, PGOODIN, PONIN for power savings.
                                                  //                0: PRCM controls the DPLL reset, RET = 0, ISO = 0, PGOODIN = 1, PONIN = 1. 1: Controlled
                                                  //                by corresponding bits in this register.
                uint32_t    ponin_disp       : 1; // bit:16    (R/W) Drives PONIN of DISP DPLL.
                uint32_t    pgoodin_disp     : 1; // bit:17    (R/W) Drives PGOODIN of DISP DPLL.
                uint32_t    iso_disp         : 1; // bit:18    (R/W) Drives ISO of DISP DPLL.
                uint32_t    reset_disp       : 1; // bit:19    (R/W) Drives RESET of DISP DPLL.
                uint32_t    ret_disp         : 1; // bit:20    (R/W) Drives RET of DISP DPLL.
                uint32_t    isoscan_disp     : 1; // bit:21    (R/W) Drives ISOSCAN of DISP PLL.
                uint32_t                     : 1; // bit:22    (R)   Reserved
                uint32_t    sw_ctrl_disp_pll : 1; // bit:23    (R/W) Enable software control over DISP DPLL RET, RESET, ISO, PGOODIN, PONIN for power
                                                  //                savings. 0: PRCM controls the DPLL reset, RET = 0, ISO = 0, PGOODIN = 1, PONIN = 1. 1:
                                                  //                Controlled by corresponding bits in this register.
                uint32_t    ponin_ddr        : 1; // bit:24    (R/W) Drives PONIN of DDR DPLL.
                uint32_t    pgoodin_ddr      : 1; // bit:25    (R/W) Drives PGOODIN of DDR DPLL.
                uint32_t    iso_ddr          : 1; // bit:26    (R/W) Drives ISO of DDR DPLL.
                uint32_t    reset_ddr        : 1; // bit:27    (R/W) Drives RESET of DDR DPLL.
                uint32_t    ret_ddr          : 1; // bit:28    (R/W) Drives RET signal of DDR PLL.
                uint32_t    isoscan_ddr      : 1; // bit:29    (R/W) Drives ISOSCAN of DDR PLL.
                uint32_t                     : 1; // bit:30    (R)   Reserved
                uint32_t    sw_ctrl_ddr_pll  : 1; // bit:31    (R/W) Enable software control over DDR DPLL RET, RESET, ISO, PGOODIN, PONIN for power savings.
                                                  //                0: PRCM controls the DPLL reset, RET = 0, ISO = 0, PGOODIN = 1, PONIN = 1. 1: Controlled
                                                  //                by corresponding bits in this register.
            } b;
            uint32_t reg;
        } dpll_pwr_sw_ctrl_reg_t;


        /* (offset = 0x131C) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                              /* Register ddr_cke_ctrl */

                uint32_t    ddr_cke_ctrl : 1; // bit:0      (R/W) CKE from EMIF/DDRPHY is ANDed with this bit. 0: CKE to memories gated off to zero.
                                              //                 External DRAM memories will not able to register DDR commands from device 1: Normal
                                              //                 operation. CKE is now controlled by EMIF/DDR PHY.
                uint32_t                 :31; // bits:1..31 (R)   Reserved
            } b;
            uint32_t reg;
        } ddr_cke_ctrl_reg_t;


        /* (offset = 0x1320) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                                       /* Register sma2 */

                uint32_t    rmii2_crs_dv_mode_sel : 1; // bit:0      (R/W) 0: Select MMC2_DAT7 on GPMC_A9 pin in MODE3. 1: Select RMII2_CRS_DV on GPMC_A9 pin in
                                                       //                 MODE3.
                uint32_t                          : 1; // bit:1      (R)   Reserved
                uint32_t                          :30; // bits:2..31 (R)   Reserved
            } b;
            uint32_t reg;
        } sma2_reg_t;


        /* (offset = 0x1324) [reset state = 0x0] */
        typedef union
        {
            struct
            {
                                             /* Register m3_txev_eoi */

                uint32_t    m3_txev_eoi : 1; // bit:0      (R/W) TXEV (Event) from M3 processor is a pulse signal connected as intertupt to MPU IRQ(78)
                                             //                 Since MPU expects level signals. The TXEV pulse from M3 is converted to a level in glue
                                             //                 logic. The logic works as follows: -On a 0-1 transition on TXEV, the IRQ[78] is set.
                                             //                 -For clearing the interrupt, S/W must do the following: S/W must clear the IRQ[78] by
                                             //                 writing a 1 to M3_TXEV_EOI bit in this registe This bit is sticky and for re-arming the
                                             //                 IRQ[78], S/W must write a 0 to this field in the ISR
                uint32_t                :31; // bits:1..31 (R)   Reserved
            } b;
            uint32_t reg;
        } m3_txev_eoi_reg_t;

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
            __RW  conf_module_pin_reg_t               onf_gpmc_a10;              // (0x868)
            __RW  conf_module_pin_reg_t               onf_gpmc_a11;              // (0x86C)
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