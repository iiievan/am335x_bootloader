#ifndef _AM3358ZCZ_PINS_H
#define _AM3358ZCZ_PINS_H

#include "stdint.h"
#include "REGS/REGS.hpp"
#include "pins/pin.hpp"

namespace HAL::PINS
{
    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    class pin;

    // ========================================================================
    // MDIO (ZCZ: M17, ZCE: P17) -> gpio0_0
    // ========================================================================
    enum class e_MDIO : uint8_t
    {
        mdio_data                                = 0, // I/O
        timer6                                   = 1, // I/O
        uart5_rxd                                = 2, // I
        uart3_ctsn                               = 3, // I
        mmc0_sdcd                                = 4, // I
        mmc1_cmd                                 = 5, // I/O
        mmc2_cmd                                 = 6, // I/O
        gpio0_0                                  = 7, // I/O (GPIO)
    };

    using MDIO = pin<e_MDIO, 0U, 0x948>;
    inline MDIO mdio{REGS::GPIO::AM335x_GPIO_0}; // gpio0_0


    // ========================================================================
    // MDC (ZCZ: M18, ZCE: R19) -> gpio0_1
    // ========================================================================
    enum class e_MDC : uint8_t
    {
        mdio_clk                                 = 0, // O
        timer5                                   = 1, // I/O
        uart5_txd                                = 2, // O
        uart3_rtsn                               = 3, // O
        mmc0_sdwp                                = 4, // I
        mmc1_clk                                 = 5, // I/O
        mmc2_clk                                 = 6, // I/O
        gpio0_1                                  = 7, // I/O (GPIO)
    };

    using MDC = pin<e_MDC, 1U, 0x94C>;
    inline MDC mdc{REGS::GPIO::AM335x_GPIO_0}; // gpio0_1


    // ========================================================================
    // SPI0_SCLK (ZCZ: A17, ZCE: A18) -> gpio0_2
    // ========================================================================
    enum class e_SPI0_SCLK : uint8_t
    {
        spi0_sclk                                = 0, // I/O
        uart2_rxd                                = 1, // I
        i2c2_sda                                 = 2, // I/OD
        ehrpwm0a                                 = 3, // O
        pr1_uart0_cts_n                          = 4, // I
        pr1_edio_sof                             = 5, // O
        emu2                                     = 6, // I/O
        gpio0_2                                  = 7, // I/O (GPIO)
    };

    using SPI0_SCLK = pin<e_SPI0_SCLK, 2U, 0x950>;
    inline SPI0_SCLK spi0_sclk{REGS::GPIO::AM335x_GPIO_0}; // gpio0_2


    // ========================================================================
    // SPI0_D0 (ZCZ: B17, ZCE: B18) -> gpio0_3
    // ========================================================================
    enum class e_SPI0_D0 : uint8_t
    {
        spi0_d0                                  = 0, // I/O
        uart2_txd                                = 1, // O
        i2c2_scl                                 = 2, // I/OD
        ehrpwm0b                                 = 3, // O
        pr1_uart0_rts_n                          = 4, // O
        pr1_edio_latch_in                        = 5, // I
        emu3                                     = 6, // I/O
        gpio0_3                                  = 7, // I/O (GPIO)
    };

    using SPI0_D0 = pin<e_SPI0_D0, 3U, 0x954>;
    inline SPI0_D0 spi0_d0{REGS::GPIO::AM335x_GPIO_0}; // gpio0_3


    // ========================================================================
    // SPI0_D1 (ZCZ: B16, ZCE: B17) -> gpio0_4
    // ========================================================================
    enum class e_SPI0_D1 : uint8_t
    {
        spi0_d1                                  = 0, // I/O
        mmc1_sdwp                                = 1, // I
        i2c1_sda                                 = 2, // I/OD
        ehrpwm0_tripzone_input                   = 3, // I
        pr1_uart0_rxd                            = 4, // I
        pr1_edio_data_in0                        = 5, // I
        pr1_edio_data_out0                       = 6, // O
        gpio0_4                                  = 7, // I/O (GPIO)
    };

    using SPI0_D1 = pin<e_SPI0_D1, 4U, 0x958>;
    inline SPI0_D1 spi0_d1{REGS::GPIO::AM335x_GPIO_0}; // gpio0_4


    // ========================================================================
    // SPI0_CS0 (ZCZ: A16, ZCE: A17) -> gpio0_5
    // ========================================================================
    enum class e_SPI0_CS0 : uint8_t
    {
        spi0_cs0                                 = 0, // I/O
        mmc2_sdwp                                = 1, // I
        i2c1_scl                                 = 2, // I/OD
        ehrpwm0_synci                            = 3, // I
        pr1_uart0_txd                            = 4, // O
        pr1_edio_data_in1                        = 5, // I
        pr1_edio_data_out1                       = 6, // O
        gpio0_5                                  = 7, // I/O (GPIO)
    };

    using SPI0_CS0 = pin<e_SPI0_CS0, 5U, 0x95C>;
    inline SPI0_CS0 spi0_cs0{REGS::GPIO::AM335x_GPIO_0}; // gpio0_5


    // ========================================================================
    // SPI0_CS1 (ZCZ: C15, ZCE: B16) -> gpio0_6
    // ========================================================================
    enum class e_SPI0_CS1 : uint8_t
    {
        spi0_cs1                                 = 0, // I/O
        uart3_rxd                                = 1, // I
        ecap1_in_pwm1_out                        = 2, // I/O
        mmc0_pow                                 = 3, // O
        xdma_event_intr2                         = 4, // I
        mmc0_sdcd                                = 5, // I
        emu4                                     = 6, // I/O
        gpio0_6                                  = 7, // I/O (GPIO)
    };

    using SPI0_CS1 = pin<e_SPI0_CS1, 6U, 0x960>;
    inline SPI0_CS1 spi0_cs1{REGS::GPIO::AM335x_GPIO_0}; // gpio0_6


    // ========================================================================
    // ECAP0_IN_PWM0_OUT (ZCZ: C18, ZCE: E18) -> gpio0_7
    // ========================================================================
    enum class e_ECAP0_IN_PWM0_OUT : uint8_t
    {
        ecap0_in_pwm0_out                        = 0, // I/O
        uart3_txd                                = 1, // O
        spi1_cs1                                 = 2, // I/O
        pr1_ecap0_ecap_capin_apwm_o              = 3, // I/O
        spi1_sclk                                = 4, // I/O
        mmc0_sdwp                                = 5, // I
        xdma_event_intr2                         = 6, // I
        gpio0_7                                  = 7, // I/O (GPIO)
    };

    using ECAP0_IN_PWM0_OUT = pin<e_ECAP0_IN_PWM0_OUT, 7U, 0x964>;
    inline ECAP0_IN_PWM0_OUT ecap0_in_pwm0_out{REGS::GPIO::AM335x_GPIO_0}; // gpio0_7


    // ========================================================================
    // LCD_DATA12(5) (ZCZ: V2, ZCE: V6) -> gpio0_8
    // ========================================================================
    enum class e_LCD_DATA12 : uint8_t
    {
        lcd_data12                               = 0, // I/O
        gpmc_a16                                 = 1, // O
        eqep1a_in                                = 2, // I
        mcasp0_aclkr                             = 3, // I/O
        mcasp0_axr2                              = 4, // I/O
        pr1_mii0_rxlink                          = 5, // I
        uart4_ctsn                               = 6, // I
        gpio0_8                                  = 7, // I/O (GPIO)
    };

    using LCD_DATA12 = pin<e_LCD_DATA12, 8U, 0x8D0>;
    inline LCD_DATA12 lcd_data12{REGS::GPIO::AM335x_GPIO_0}; // gpio0_8


    // ========================================================================
    // LCD_DATA13(5) (ZCZ: V3, ZCE: U6) -> gpio0_9
    // ========================================================================
    enum class e_LCD_DATA13 : uint8_t
    {
        lcd_data13                               = 0, // I/O
        gpmc_a17                                 = 1, // O
        eqep1b_in                                = 2, // I
        mcasp0_fsr                               = 3, // I/O
        mcasp0_axr3                              = 4, // I/O
        pr1_mii0_rxer                            = 5, // I
        uart4_rtsn                               = 6, // O
        gpio0_9                                  = 7, // I/O (GPIO)
    };

    using LCD_DATA13 = pin<e_LCD_DATA13, 9U, 0x8D4>;
    inline LCD_DATA13 lcd_data13{REGS::GPIO::AM335x_GPIO_0}; // gpio0_9


    // ========================================================================
    // LCD_DATA14(5) (ZCZ: V4, ZCE: W6) -> gpio0_10
    // ========================================================================
    enum class e_LCD_DATA14 : uint8_t
    {
        lcd_data14                               = 0, // I/O
        gpmc_a18                                 = 1, // O
        eqep1_index                              = 2, // I/O
        mcasp0_axr1                              = 3, // I/O
        uart5_rxd                                = 4, // I
        pr1_mii_mr0_clk                          = 5, // I
        uart5_ctsn                               = 6, // I
        gpio0_10                                 = 7, // I/O (GPIO)
    };

    using LCD_DATA14 = pin<e_LCD_DATA14, 10U, 0x8D8>;
    inline LCD_DATA14 lcd_data14{REGS::GPIO::AM335x_GPIO_0}; // gpio0_10


    // ========================================================================
    // LCD_DATA15(5) (ZCZ: T5, ZCE: V7) -> gpio0_11
    // ========================================================================
    enum class e_LCD_DATA15 : uint8_t
    {
        lcd_data15                               = 0, // I/O
        gpmc_a19                                 = 1, // O
        eqep1_strobe                             = 2, // I/O
        mcasp0_ahclkx                            = 3, // I/O
        mcasp0_axr3                              = 4, // I/O
        pr1_mii0_rxdv                            = 5, // I
        uart5_rtsn                               = 6, // O
        gpio0_11                                 = 7, // I/O (GPIO)
    };

    using LCD_DATA15 = pin<e_LCD_DATA15, 11U, 0x8DC>;
    inline LCD_DATA15 lcd_data15{REGS::GPIO::AM335x_GPIO_0}; // gpio0_11


    // ========================================================================
    // UART1_CTSn (ZCZ: D18, ZCE: E17) -> gpio0_12
    // ========================================================================
    enum class e_UART1_CTSn : uint8_t
    {
        uart1_ctsn                               = 0, // I
        timer6                                   = 1, // I/O
        dcan0_tx                                 = 2, // O
        i2c2_sda                                 = 3, // I/OD
        spi1_cs0                                 = 4, // I/O
        pr1_uart0_cts_n                          = 5, // I
        pr1_edc_latch0_in                        = 6, // I
        gpio0_12                                 = 7, // I/O (GPIO)
    };

    using UART1_CTSn = pin<e_UART1_CTSn, 12U, 0x978>;
    inline UART1_CTSn uart1_ctsn{REGS::GPIO::AM335x_GPIO_0}; // gpio0_12


    // ========================================================================
    // UART1_RTSn (ZCZ: D17, ZCE: D19) -> gpio0_13
    // ========================================================================
    enum class e_UART1_RTSn : uint8_t
    {
        uart1_rtsn                               = 0, // O
        timer5                                   = 1, // I/O
        dcan0_rx                                 = 2, // I
        i2c2_scl                                 = 3, // I/OD
        spi1_cs1                                 = 4, // I/O
        pr1_uart0_rts_n                          = 5, // O
        pr1_edc_latch1_in                        = 6, // I
        gpio0_13                                 = 7, // I/O (GPIO)
    };

    using UART1_RTSn = pin<e_UART1_RTSn, 13U, 0x97C>;
    inline UART1_RTSn uart1_rtsn{REGS::GPIO::AM335x_GPIO_0}; // gpio0_13


    // ========================================================================
    // UART1_RXD (ZCZ: D16, ZCE: D18) -> gpio0_14
    // ========================================================================
    enum class e_UART1_RXD : uint8_t
    {
        uart1_rxd                                = 0, // I
        mmc1_sdwp                                = 1, // I
        dcan1_tx                                 = 2, // O
        i2c1_sda                                 = 3, // I/OD
        pr1_uart0_rxd                            = 5, // I
        pr1_pru1_pru_r31_16                      = 6, // I
        gpio0_14                                 = 7, // I/O (GPIO)
    };

    using UART1_RXD = pin<e_UART1_RXD, 14U, 0x980>;
    inline UART1_RXD uart1_rxd{REGS::GPIO::AM335x_GPIO_0}; // gpio0_14


    // ========================================================================
    // UART1_TXD (ZCZ: D15, ZCE: C19) -> gpio0_15
    // ========================================================================
    enum class e_UART1_TXD : uint8_t
    {
        uart1_txd                                = 0, // O
        mmc2_sdwp                                = 1, // I
        dcan1_rx                                 = 2, // I
        i2c1_scl                                 = 3, // I/OD
        pr1_uart0_txd                            = 5, // O
        pr1_pru0_pru_r31_16                      = 6, // I
        gpio0_15                                 = 7, // I/O (GPIO)
    };

    using UART1_TXD = pin<e_UART1_TXD, 15U, 0x984>;
    inline UART1_TXD uart1_txd{REGS::GPIO::AM335x_GPIO_0}; // gpio0_15


    // ========================================================================
    // MII1_TXD3 (ZCZ: J18, ZCE: M17) -> gpio0_16
    // ========================================================================
    enum class e_MII1_TXD3 : uint8_t
    {
        gmii1_txd3                               = 0, // O
        dcan0_tx                                 = 1, // O
        rgmii1_td3                               = 2, // O
        uart4_rxd                                = 3, // I
        mcasp1_fsx                               = 4, // I/O
        mmc2_dat1                                = 5, // I/O
        mcasp0_fsr                               = 6, // I/O
        gpio0_16                                 = 7, // I/O (GPIO)
    };

    using MII1_TXD3 = pin<e_MII1_TXD3, 16U, 0x91C>;
    inline MII1_TXD3 mii1_txd3{REGS::GPIO::AM335x_GPIO_0}; // gpio0_16


    // ========================================================================
    // MII1_TXD2 (ZCZ: K15, ZCE: N18) -> gpio0_17
    // ========================================================================
    enum class e_MII1_TXD2 : uint8_t
    {
        gmii1_txd2                               = 0, // O
        dcan0_rx                                 = 1, // I
        rgmii1_td2                               = 2, // O
        uart4_txd                                = 3, // O
        mcasp1_axr0                              = 4, // I/O
        mmc2_dat2                                = 5, // I/O
        mcasp0_ahclkx                            = 6, // I/O
        gpio0_17                                 = 7, // I/O (GPIO)
    };

    using MII1_TXD2 = pin<e_MII1_TXD2, 17U, 0x920>;
    inline MII1_TXD2 mii1_txd2{REGS::GPIO::AM335x_GPIO_0}; // gpio0_17


    // ========================================================================
    // USB0_DRVVBUS (ZCZ: F16, ZCE: G16) -> gpio0_18
    // ========================================================================
    enum class e_USB0_DRVVBUS : uint8_t
    {
        usb0_drvvbus                             = 0, // O
        gpio0_18                                 = 7, // I/O (GPIO)
    };

    using USB0_DRVVBUS = pin<e_USB0_DRVVBUS, 18U, 0xA1C>;
    inline USB0_DRVVBUS usb0_drvvbus{REGS::GPIO::AM335x_GPIO_0}; // gpio0_18


    // ========================================================================
    // XDMA_EVENT_INTR0 (ZCZ: A15, ZCE: C15) -> gpio0_19
    // ========================================================================
    enum class e_XDMA_EVENT_INTR0 : uint8_t
    {
        xdma_event_intr0                         = 0, // I
        timer4                                   = 2, // I/O
        clkout1                                  = 3, // O
        spi1_cs1                                 = 4, // I/O
        pr1_pru1_pru_r31_16                      = 5, // I
        emu2                                     = 6, // I/O
        gpio0_19                                 = 7, // I/O (GPIO)
    };

    using XDMA_EVENT_INTR0 = pin<e_XDMA_EVENT_INTR0, 19U, 0x9B0>;
    inline XDMA_EVENT_INTR0 xdma_event_intr0{REGS::GPIO::AM335x_GPIO_0}; // gpio0_19


    // ========================================================================
    // XDMA_EVENT_INTR1 (ZCZ: D14, ZCE: B15) -> gpio0_20
    // ========================================================================
    enum class e_XDMA_EVENT_INTR1 : uint8_t
    {
        xdma_event_intr1                         = 0, // I
        tclkin                                   = 2, // I
        clkout2                                  = 3, // O
        timer7                                   = 4, // I/O
        pr1_pru0_pru_r31_16                      = 5, // I
        emu3                                     = 6, // I/O
        gpio0_20                                 = 7, // I/O (GPIO)
    };

    using XDMA_EVENT_INTR1 = pin<e_XDMA_EVENT_INTR1, 20U, 0x9B4>;
    inline XDMA_EVENT_INTR1 xdma_event_intr1{REGS::GPIO::AM335x_GPIO_0}; // gpio0_20


    // ========================================================================
    // MII1_TXD1 (ZCZ: K16, ZCE: M18) -> gpio0_21
    // ========================================================================
    enum class e_MII1_TXD1 : uint8_t
    {
        gmii1_txd1                               = 0, // O
        rmii1_txd1                               = 1, // O
        rgmii1_td1                               = 2, // O
        mcasp1_fsr                               = 3, // I/O
        mcasp1_axr1                              = 4, // I/O
        eqep0a_in                                = 5, // I
        mmc1_cmd                                 = 6, // I/O
        gpio0_21                                 = 7, // I/O (GPIO)
    };

    using MII1_TXD1 = pin<e_MII1_TXD1, 21U, 0x924>;
    inline MII1_TXD1 mii1_txd1{REGS::GPIO::AM335x_GPIO_0}; // gpio0_21


    // ========================================================================
    // GPMC_AD8 (ZCZ: U10, ZCE: V15) -> gpio0_22
    // ========================================================================
    enum class e_GPMC_AD8 : uint8_t
    {
        gpmc_ad8                                 = 0, // I/O
        lcd_data23                               = 1, // O
        mmc1_dat0                                = 2, // I/O
        mmc2_dat4                                = 3, // I/O
        ehrpwm2a                                 = 4, // O
        pr1_mii_mt0_clk                          = 5, // I
        gpio0_22                                 = 7, // I/O (GPIO)
    };

    using GPMC_AD8 = pin<e_GPMC_AD8, 22U, 0x820>;
    inline GPMC_AD8 gpmc_ad8{REGS::GPIO::AM335x_GPIO_0}; // gpio0_22


    // ========================================================================
    // GPMC_AD9 (ZCZ: T10, ZCE: W16) -> gpio0_23
    // ========================================================================
    enum class e_GPMC_AD9 : uint8_t
    {
        gpmc_ad9                                 = 0, // I/O
        lcd_data22                               = 1, // O
        mmc1_dat1                                = 2, // I/O
        mmc2_dat5                                = 3, // I/O
        ehrpwm2b                                 = 4, // O
        pr1_mii0_col                             = 5, // I
        gpio0_23                                 = 7, // I/O (GPIO)
    };

    using GPMC_AD9 = pin<e_GPMC_AD9, 23U, 0x824>;
    inline GPMC_AD9 gpmc_ad9{REGS::GPIO::AM335x_GPIO_0}; // gpio0_23


    // ========================================================================
    // GPMC_AD10 (ZCZ: T11, ZCE: T12) -> gpio0_26
    // ========================================================================
    enum class e_GPMC_AD10 : uint8_t
    {
        gpmc_ad10                                = 0, // I/O
        lcd_data21                               = 1, // O
        mmc1_dat2                                = 2, // I/O
        mmc2_dat6                                = 3, // I/O
        ehrpwm2_tripzone_input                   = 4, // I
        pr1_mii0_txen                            = 5, // O
        gpio0_26                                 = 7, // I/O (GPIO)
    };

    using GPMC_AD10 = pin<e_GPMC_AD10, 26U, 0x828>;
    inline GPMC_AD10 gpmc_ad10{REGS::GPIO::AM335x_GPIO_0}; // gpio0_26


    // ========================================================================
    // GPMC_AD11 (ZCZ: U12, ZCE: U12) -> gpio0_27
    // ========================================================================
    enum class e_GPMC_AD11 : uint8_t
    {
        gpmc_ad11                                = 0, // I/O
        lcd_data20                               = 1, // O
        mmc1_dat3                                = 2, // I/O
        mmc2_dat7                                = 3, // I/O
        ehrpwm0_synco                            = 4, // O
        pr1_mii0_txd3                            = 5, // O
        gpio0_27                                 = 7, // I/O (GPIO)
    };

    using GPMC_AD11 = pin<e_GPMC_AD11, 27U, 0x82C>;
    inline GPMC_AD11 gpmc_ad11{REGS::GPIO::AM335x_GPIO_0}; // gpio0_27


    // ========================================================================
    // MII1_TXD0 (ZCZ: K17, ZCE: L18) -> gpio0_28
    // ========================================================================
    enum class e_MII1_TXD0 : uint8_t
    {
        gmii1_txd0                               = 0, // O
        rmii1_txd0                               = 1, // O
        rgmii1_td0                               = 2, // O
        mcasp1_axr2                              = 3, // I/O
        mcasp1_aclkr                             = 4, // I/O
        eqep0b_in                                = 5, // I
        mmc1_clk                                 = 6, // I/O
        gpio0_28                                 = 7, // I/O (GPIO)
    };

    using MII1_TXD0 = pin<e_MII1_TXD0, 28U, 0x928>;
    inline MII1_TXD0 mii1_txd0{REGS::GPIO::AM335x_GPIO_0}; // gpio0_28


    // ========================================================================
    // RMII1_REF_CLK (ZCZ: H18, ZCE: K18) -> gpio0_29
    // ========================================================================
    enum class e_RMII1_REF_CLK : uint8_t
    {
        rmii1_refclk                             = 0, // I/O
        xdma_event_intr2                         = 1, // I
        spi1_cs0                                 = 2, // I/O
        uart5_txd                                = 3, // O
        mcasp1_axr3                              = 4, // I/O
        mmc0_pow                                 = 5, // O
        mcasp1_ahclkx                            = 6, // I/O
        gpio0_29                                 = 7, // I/O (GPIO)
    };

    using RMII1_REF_CLK = pin<e_RMII1_REF_CLK, 29U, 0x944>;
    inline RMII1_REF_CLK rmii1_ref_clk{REGS::GPIO::AM335x_GPIO_0}; // gpio0_29


    // ========================================================================
    // GPMC_WAIT0 (ZCZ: T17, ZCE: R15) -> gpio0_30
    // ========================================================================
    enum class e_GPMC_WAIT0 : uint8_t
    {
        gpmc_wait0                               = 0, // I
        gmii2_crs                                = 1, // I
        gpmc_csn4                                = 2, // O
        rmii2_crs_dv                             = 3, // I
        mmc1_sdcd                                = 4, // I
        pr1_mii1_col                             = 5, // I
        uart4_rxd                                = 6, // I
        gpio0_30                                 = 7, // I/O (GPIO)
    };

    using GPMC_WAIT0 = pin<e_GPMC_WAIT0, 30U, 0x870>;
    inline GPMC_WAIT0 gpmc_wait0{REGS::GPIO::AM335x_GPIO_0}; // gpio0_30


    // ========================================================================
    // GPMC_WPn (ZCZ: U17, ZCE: W18) -> gpio0_31
    // ========================================================================
    enum class e_GPMC_WPn : uint8_t
    {
        gpmc_wpn                                 = 0, // O
        gmii2_rxerr                              = 1, // I
        gpmc_csn5                                = 2, // O
        rmii2_rxerr                              = 3, // I
        mmc2_sdcd                                = 4, // I
        pr1_mii1_txen                            = 5, // O
        uart4_txd                                = 6, // O
        gpio0_31                                 = 7, // I/O (GPIO)
    };

    using GPMC_WPn = pin<e_GPMC_WPn, 31U, 0x874>;
    inline GPMC_WPn gpmc_wpn{REGS::GPIO::AM335x_GPIO_0}; // gpio0_31


    // ========================================================================
    // GPMC_AD0 (ZCZ: U7, ZCE: W10) -> gpio1_0
    // ========================================================================
    enum class e_GPMC_AD0 : uint8_t
    {
        gpmc_ad0                                 = 0, // I/O
        mmc1_dat0                                = 1, // I/O
        gpio1_0                                  = 7, // I/O (GPIO)
    };

    using GPMC_AD0 = pin<e_GPMC_AD0, 0U, 0x800>;
    inline GPMC_AD0 gpmc_ad0{REGS::GPIO::AM335x_GPIO_1}; // gpio1_0


    // ========================================================================
    // GPMC_AD1 (ZCZ: V7, ZCE: V9) -> gpio1_1
    // ========================================================================
    enum class e_GPMC_AD1 : uint8_t
    {
        gpmc_ad1                                 = 0, // I/O
        mmc1_dat1                                = 1, // I/O
        gpio1_1                                  = 7, // I/O (GPIO)
    };

    using GPMC_AD1 = pin<e_GPMC_AD1, 1U, 0x804>;
    inline GPMC_AD1 gpmc_ad1{REGS::GPIO::AM335x_GPIO_1}; // gpio1_1


    // ========================================================================
    // GPMC_AD2 (ZCZ: R8, ZCE: V12) -> gpio1_2
    // ========================================================================
    enum class e_GPMC_AD2 : uint8_t
    {
        gpmc_ad2                                 = 0, // I/O
        mmc1_dat2                                = 1, // I/O
        gpio1_2                                  = 7, // I/O (GPIO)
    };

    using GPMC_AD2 = pin<e_GPMC_AD2, 2U, 0x808>;
    inline GPMC_AD2 gpmc_ad2{REGS::GPIO::AM335x_GPIO_1}; // gpio1_2


    // ========================================================================
    // GPMC_AD3 (ZCZ: T8, ZCE: W13) -> gpio1_3
    // ========================================================================
    enum class e_GPMC_AD3 : uint8_t
    {
        gpmc_ad3                                 = 0, // I/O
        mmc1_dat3                                = 1, // I/O
        gpio1_3                                  = 7, // I/O (GPIO)
    };

    using GPMC_AD3 = pin<e_GPMC_AD3, 3U, 0x80C>;
    inline GPMC_AD3 gpmc_ad3{REGS::GPIO::AM335x_GPIO_1}; // gpio1_3


    // ========================================================================
    // GPMC_AD4 (ZCZ: U8, ZCE: V13) -> gpio1_4
    // ========================================================================
    enum class e_GPMC_AD4 : uint8_t
    {
        gpmc_ad4                                 = 0, // I/O
        mmc1_dat4                                = 1, // I/O
        gpio1_4                                  = 7, // I/O (GPIO)
    };

    using GPMC_AD4 = pin<e_GPMC_AD4, 4U, 0x810>;
    inline GPMC_AD4 gpmc_ad4{REGS::GPIO::AM335x_GPIO_1}; // gpio1_4


    // ========================================================================
    // GPMC_AD5 (ZCZ: V8, ZCE: W14) -> gpio1_5
    // ========================================================================
    enum class e_GPMC_AD5 : uint8_t
    {
        gpmc_ad5                                 = 0, // I/O
        mmc1_dat5                                = 1, // I/O
        gpio1_5                                  = 7, // I/O (GPIO)
    };

    using GPMC_AD5 = pin<e_GPMC_AD5, 5U, 0x814>;
    inline GPMC_AD5 gpmc_ad5{REGS::GPIO::AM335x_GPIO_1}; // gpio1_5


    // ========================================================================
    // GPMC_AD6 (ZCZ: R9, ZCE: U14) -> gpio1_6
    // ========================================================================
    enum class e_GPMC_AD6 : uint8_t
    {
        gpmc_ad6                                 = 0, // I/O
        mmc1_dat6                                = 1, // I/O
        gpio1_6                                  = 7, // I/O (GPIO)
    };

    using GPMC_AD6 = pin<e_GPMC_AD6, 6U, 0x818>;
    inline GPMC_AD6 gpmc_ad6{REGS::GPIO::AM335x_GPIO_1}; // gpio1_6


    // ========================================================================
    // GPMC_AD7 (ZCZ: T9, ZCE: W15) -> gpio1_7
    // ========================================================================
    enum class e_GPMC_AD7 : uint8_t
    {
        gpmc_ad7                                 = 0, // I/O
        mmc1_dat7                                = 1, // I/O
        gpio1_7                                  = 7, // I/O (GPIO)
    };

    using GPMC_AD7 = pin<e_GPMC_AD7, 7U, 0x81C>;
    inline GPMC_AD7 gpmc_ad7{REGS::GPIO::AM335x_GPIO_1}; // gpio1_7


    // ========================================================================
    // UART0_CTSn (ZCZ: E18, ZCE: F19) -> gpio1_8
    // ========================================================================
    enum class e_UART0_CTSn : uint8_t
    {
        uart0_ctsn                               = 0, // I
        uart4_rxd                                = 1, // I
        dcan1_tx                                 = 2, // O
        i2c1_sda                                 = 3, // I/OD
        spi1_d0                                  = 4, // I/O
        timer7                                   = 5, // I/O
        pr1_edc_sync0_out                        = 6, // O
        gpio1_8                                  = 7, // I/O (GPIO)
    };

    using UART0_CTSn = pin<e_UART0_CTSn, 8U, 0x968>;
    inline UART0_CTSn uart0_ctsn{REGS::GPIO::AM335x_GPIO_1}; // gpio1_8


    // ========================================================================
    // UART0_RTSn (ZCZ: E17, ZCE: F18) -> gpio1_9
    // ========================================================================
    enum class e_UART0_RTSn : uint8_t
    {
        uart0_rtsn                               = 0, // O
        uart4_txd                                = 1, // O
        dcan1_rx                                 = 2, // I
        i2c1_scl                                 = 3, // I/OD
        spi1_d1                                  = 4, // I/O
        spi1_cs0                                 = 5, // I/O
        pr1_edc_sync1_out                        = 6, // O
        gpio1_9                                  = 7, // I/O (GPIO)
    };

    using UART0_RTSn = pin<e_UART0_RTSn, 9U, 0x96C>;
    inline UART0_RTSn uart0_rtsn{REGS::GPIO::AM335x_GPIO_1}; // gpio1_9


    // ========================================================================
    // UART0_RXD (ZCZ: E15, ZCE: E19) -> gpio1_10
    // ========================================================================
    enum class e_UART0_RXD : uint8_t
    {
        uart0_rxd                                = 0, // I
        spi1_cs0                                 = 1, // I/O
        dcan0_tx                                 = 2, // O
        i2c2_sda                                 = 3, // I/OD
        ecap2_in_pwm2_out                        = 4, // I/O
        pr1_pru1_pru_r30_14                      = 5, // O
        pr1_pru1_pru_r31_14                      = 6, // I
        gpio1_10                                 = 7, // I/O (GPIO)
    };

    using UART0_RXD = pin<e_UART0_RXD, 10U, 0x970>;
    inline UART0_RXD uart0_rxd{REGS::GPIO::AM335x_GPIO_1}; // gpio1_10


    // ========================================================================
    // UART0_TXD (ZCZ: E16, ZCE: F17) -> gpio1_11
    // ========================================================================
    enum class e_UART0_TXD : uint8_t
    {
        uart0_txd                                = 0, // O
        spi1_cs1                                 = 1, // I/O
        dcan0_rx                                 = 2, // I
        i2c2_scl                                 = 3, // I/OD
        ecap1_in_pwm1_out                        = 4, // I/O
        pr1_pru1_pru_r30_15                      = 5, // O
        pr1_pru1_pru_r31_15                      = 6, // I
        gpio1_11                                 = 7, // I/O (GPIO)
    };

    using UART0_TXD = pin<e_UART0_TXD, 11U, 0x974>;
    inline UART0_TXD uart0_txd{REGS::GPIO::AM335x_GPIO_1}; // gpio1_11


    // ========================================================================
    // GPMC_AD12 (ZCZ: T12, ZCE: U13) -> gpio1_12
    // ========================================================================
    enum class e_GPMC_AD12 : uint8_t
    {
        gpmc_ad12                                = 0, // I/O
        lcd_data19                               = 1, // O
        mmc1_dat4                                = 2, // I/O
        mmc2_dat0                                = 3, // I/O
        eqep2a_in                                = 4, // I
        pr1_mii0_txd2                            = 5, // O
        pr1_pru0_pru_r30_14                      = 6, // O
        gpio1_12                                 = 7, // I/O (GPIO)
    };

    using GPMC_AD12 = pin<e_GPMC_AD12, 12U, 0x830>;
    inline GPMC_AD12 gpmc_ad12{REGS::GPIO::AM335x_GPIO_1}; // gpio1_12


    // ========================================================================
    // GPMC_AD13 (ZCZ: R12, ZCE: T13) -> gpio1_13
    // ========================================================================
    enum class e_GPMC_AD13 : uint8_t
    {
        gpmc_ad13                                = 0, // I/O
        lcd_data18                               = 1, // O
        mmc1_dat5                                = 2, // I/O
        mmc2_dat1                                = 3, // I/O
        eqep2b_in                                = 4, // I
        pr1_mii0_txd1                            = 5, // O
        pr1_pru0_pru_r30_15                      = 6, // O
        gpio1_13                                 = 7, // I/O (GPIO)
    };

    using GPMC_AD13 = pin<e_GPMC_AD13, 13U, 0x834>;
    inline GPMC_AD13 gpmc_ad13{REGS::GPIO::AM335x_GPIO_1}; // gpio1_13


    // ========================================================================
    // GPMC_AD14 (ZCZ: V13, ZCE: W17) -> gpio1_14
    // ========================================================================
    enum class e_GPMC_AD14 : uint8_t
    {
        gpmc_ad14                                = 0, // I/O
        lcd_data17                               = 1, // O
        mmc1_dat6                                = 2, // I/O
        mmc2_dat2                                = 3, // I/O
        eqep2_index                              = 4, // I/O
        pr1_mii0_txd0                            = 5, // O
        pr1_pru0_pru_r31_14                      = 6, // I
        gpio1_14                                 = 7, // I/O (GPIO)
    };

    using GPMC_AD14 = pin<e_GPMC_AD14, 14U, 0x838>;
    inline GPMC_AD14 gpmc_ad14{REGS::GPIO::AM335x_GPIO_1}; // gpio1_14


    // ========================================================================
    // GPMC_AD15 (ZCZ: U13, ZCE: V17) -> gpio1_15
    // ========================================================================
    enum class e_GPMC_AD15 : uint8_t
    {
        gpmc_ad15                                = 0, // I/O
        lcd_data16                               = 1, // O
        mmc1_dat7                                = 2, // I/O
        mmc2_dat3                                = 3, // I/O
        eqep2_strobe                             = 4, // I/O
        pr1_ecap0_ecap_capin_apwm_o              = 5, // I/O
        pr1_pru0_pru_r31_15                      = 6, // I
        gpio1_15                                 = 7, // I/O (GPIO)
    };

    using GPMC_AD15 = pin<e_GPMC_AD15, 15U, 0x83C>;
    inline GPMC_AD15 gpmc_ad15{REGS::GPIO::AM335x_GPIO_1}; // gpio1_15


    // ========================================================================
    // GPMC_A0 (ZCZ: R13, ZCE: NA) -> gpio1_16
    // ========================================================================
    enum class e_GPMC_A0 : uint8_t
    {
        gpmc_a0                                  = 0, // O
        gmii2_txen                               = 1, // O
        rgmii2_tctl                              = 2, // O
        rmii2_txen                               = 3, // O
        gpmc_a16                                 = 4, // O
        pr1_mii_mt1_clk                          = 5, // I
        ehrpwm1_tripzone_input                   = 6, // I
        gpio1_16                                 = 7, // I/O (GPIO)
    };

    using GPMC_A0 = pin<e_GPMC_A0, 16U, 0x840>;
    inline GPMC_A0 gpmc_a0{REGS::GPIO::AM335x_GPIO_1}; // gpio1_16


    // ========================================================================
    // GPMC_A1 (ZCZ: V14, ZCE: NA) -> gpio1_17
    // ========================================================================
    enum class e_GPMC_A1 : uint8_t
    {
        gpmc_a1                                  = 0, // O
        gmii2_rxdv                               = 1, // I
        rgmii2_rctl                              = 2, // I
        mmc2_dat0                                = 3, // I/O
        gpmc_a17                                 = 4, // O
        pr1_mii1_txd3                            = 5, // O
        ehrpwm0_synco                            = 6, // O
        gpio1_17                                 = 7, // I/O (GPIO)
    };

    using GPMC_A1 = pin<e_GPMC_A1, 17U, 0x844>;
    inline GPMC_A1 gpmc_a1{REGS::GPIO::AM335x_GPIO_1}; // gpio1_17


    // ========================================================================
    // GPMC_A2 (ZCZ: U14, ZCE: NA) -> gpio1_18
    // ========================================================================
    enum class e_GPMC_A2 : uint8_t
    {
        gpmc_a2                                  = 0, // O
        gmii2_txd3                               = 1, // O
        rgmii2_td3                               = 2, // O
        mmc2_dat1                                = 3, // I/O
        gpmc_a18                                 = 4, // O
        pr1_mii1_txd2                            = 5, // O
        ehrpwm1a                                 = 6, // O
        gpio1_18                                 = 7, // I/O (GPIO)
    };

    using GPMC_A2 = pin<e_GPMC_A2, 18U, 0x848>;
    inline GPMC_A2 gpmc_a2{REGS::GPIO::AM335x_GPIO_1}; // gpio1_18


    // ========================================================================
    // GPMC_A3 (ZCZ: T14, ZCE: NA) -> gpio1_19
    // ========================================================================
    enum class e_GPMC_A3 : uint8_t
    {
        gpmc_a3                                  = 0, // O
        gmii2_txd2                               = 1, // O
        rgmii2_td2                               = 2, // O
        mmc2_dat2                                = 3, // I/O
        gpmc_a19                                 = 4, // O
        pr1_mii1_txd1                            = 5, // O
        ehrpwm1b                                 = 6, // O
        gpio1_19                                 = 7, // I/O (GPIO)
    };

    using GPMC_A3 = pin<e_GPMC_A3, 19U, 0x84C>;
    inline GPMC_A3 gpmc_a3{REGS::GPIO::AM335x_GPIO_1}; // gpio1_19


    // ========================================================================
    // GPMC_A4 (ZCZ: R14, ZCE: NA) -> gpio1_20
    // ========================================================================
    enum class e_GPMC_A4 : uint8_t
    {
        gpmc_a4                                  = 0, // O
        gmii2_txd1                               = 1, // O
        rgmii2_td1                               = 2, // O
        rmii2_txd1                               = 3, // O
        gpmc_a20                                 = 4, // O
        pr1_mii1_txd0                            = 5, // O
        eqep1a_in                                = 6, // I
        gpio1_20                                 = 7, // I/O (GPIO)
    };

    using GPMC_A4 = pin<e_GPMC_A4, 20U, 0x850>;
    inline GPMC_A4 gpmc_a4{REGS::GPIO::AM335x_GPIO_1}; // gpio1_20


    // ========================================================================
    // GPMC_A5 (ZCZ: V15, ZCE: NA) -> gpio1_21
    // ========================================================================
    enum class e_GPMC_A5 : uint8_t
    {
        gpmc_a5                                  = 0, // O
        gmii2_txd0                               = 1, // O
        rgmii2_td0                               = 2, // O
        rmii2_txd0                               = 3, // O
        gpmc_a21                                 = 4, // O
        pr1_mii1_rxd3                            = 5, // I
        eqep1b_in                                = 6, // I
        gpio1_21                                 = 7, // I/O (GPIO)
    };

    using GPMC_A5 = pin<e_GPMC_A5, 21U, 0x854>;
    inline GPMC_A5 gpmc_a5{REGS::GPIO::AM335x_GPIO_1}; // gpio1_21


    // ========================================================================
    // GPMC_A6 (ZCZ: U15, ZCE: NA) -> gpio1_22
    // ========================================================================
    enum class e_GPMC_A6 : uint8_t
    {
        gpmc_a6                                  = 0, // O
        gmii2_txclk                              = 1, // I
        rgmii2_tclk                              = 2, // O
        mmc2_dat4                                = 3, // I/O
        gpmc_a22                                 = 4, // O
        pr1_mii1_rxd2                            = 5, // I
        eqep1_index                              = 6, // I/O
        gpio1_22                                 = 7, // I/O (GPIO)
    };

    using GPMC_A6 = pin<e_GPMC_A6, 22U, 0x858>;
    inline GPMC_A6 gpmc_a6{REGS::GPIO::AM335x_GPIO_1}; // gpio1_22


    // ========================================================================
    // GPMC_A7 (ZCZ: T15, ZCE: NA) -> gpio1_23
    // ========================================================================
    enum class e_GPMC_A7 : uint8_t
    {
        gpmc_a7                                  = 0, // O
        gmii2_rxclk                              = 1, // I
        rgmii2_rclk                              = 2, // I
        mmc2_dat5                                = 3, // I/O
        gpmc_a23                                 = 4, // O
        pr1_mii1_rxd1                            = 5, // I
        eqep1_strobe                             = 6, // I/O
        gpio1_23                                 = 7, // I/O (GPIO)
    };

    using GPMC_A7 = pin<e_GPMC_A7, 23U, 0x85C>;
    inline GPMC_A7 gpmc_a7{REGS::GPIO::AM335x_GPIO_1}; // gpio1_23


    // ========================================================================
    // GPMC_A8 (ZCZ: V16, ZCE: NA) -> gpio1_24
    // ========================================================================
    enum class e_GPMC_A8 : uint8_t
    {
        gpmc_a8                                  = 0, // O
        gmii2_rxd3                               = 1, // I
        rgmii2_rd3                               = 2, // I
        mmc2_dat6                                = 3, // I/O
        gpmc_a24                                 = 4, // O
        pr1_mii1_rxd0                            = 5, // I
        mcasp0_aclkx                             = 6, // I/O
        gpio1_24                                 = 7, // I/O (GPIO)
    };

    using GPMC_A8 = pin<e_GPMC_A8, 24U, 0x860>;
    inline GPMC_A8 gpmc_a8{REGS::GPIO::AM335x_GPIO_1}; // gpio1_24


    // ========================================================================
    // GPMC_A9(10) (ZCZ: U16, ZCE: NA) -> gpio1_25
    // ========================================================================
    enum class e_GPMC_A9 : uint8_t
    {
        gpmc_a9                                  = 0, // O
        gmii2_rxd2                               = 1, // I
        rgmii2_rd2                               = 2, // I
        mmc2_dat7_rmii2_crs_dv                   = 3, // I/O
        gpmc_a25                                 = 4, // O
        pr1_mii_mr1_clk                          = 5, // I
        mcasp0_fsx                               = 6, // I/O
        gpio1_25                                 = 7, // I/O (GPIO)
    };

    using GPMC_A9 = pin<e_GPMC_A9, 25U, 0x864>;
    inline GPMC_A9 gpmc_a9{REGS::GPIO::AM335x_GPIO_1}; // gpio1_25

    // ========================================================================
    // GPMC_A10 (ZCZ: T16, ZCE: NA) -> gpio1_26
    // ========================================================================
    enum class e_GPMC_A10 : uint8_t
    {
        gpmc_a10                                 = 0, // O
        gmii2_rxd1                               = 1, // I
        rgmii2_rd1                               = 2, // I
        rmii2_rxd1                               = 3, // I
        gpmc_a26                                 = 4, // O
        pr1_mii1_rxdv                            = 5, // I
        mcasp0_axr0                              = 6, // I/O
        gpio1_26                                 = 7, // I/O (GPIO)
    };

    using GPMC_A10 = pin<e_GPMC_A10, 26U, 0x868>;
    inline GPMC_A10 gpmc_a10{REGS::GPIO::AM335x_GPIO_1}; // gpio1_26


    // ========================================================================
    // GPMC_A11 (ZCZ: V17, ZCE: NA) -> gpio1_27
    // ========================================================================
    enum class e_GPMC_A11 : uint8_t
    {
        gpmc_a11                                 = 0, // O
        gmii2_rxd0                               = 1, // I
        rgmii2_rd0                               = 2, // I
        rmii2_rxd0                               = 3, // I
        gpmc_a27                                 = 4, // O
        pr1_mii1_rxer                            = 5, // I
        mcasp0_axr1                              = 6, // I/O
        gpio1_27                                 = 7, // I/O (GPIO)
    };

    using GPMC_A11 = pin<e_GPMC_A11, 27U, 0x86C>;
    inline GPMC_A11 gpmc_a11{REGS::GPIO::AM335x_GPIO_1}; // gpio1_27

    // ========================================================================
    // GPMC_BEn1 (ZCZ: U18, ZCE: V18) -> gpio1_28
    // ========================================================================
    enum class e_GPMC_BEn1 : uint8_t
    {
        gpmc_be1n                                = 0, // O
        gmii2_col                                = 1, // I
        gpmc_csn6                                = 2, // O
        mmc2_dat3                                = 3, // I/O
        gpmc_dir                                 = 4, // O
        pr1_mii1_rxlink                          = 5, // I
        mcasp0_aclkr                             = 6, // I/O
        gpio1_28                                 = 7, // I/O (GPIO)
    };

    using GPMC_BEn1 = pin<e_GPMC_BEn1, 28U, 0x878>;
    inline GPMC_BEn1 gpmc_ben1{REGS::GPIO::AM335x_GPIO_1}; // gpio1_28


    // ========================================================================
    // GPMC_CSn0 (ZCZ: V6, ZCE: W8) -> gpio1_29
    // ========================================================================
    enum class e_GPMC_CSn0 : uint8_t
    {
        gpmc_csn0                                = 0, // O
        gpio1_29                                 = 7, // I/O (GPIO)
    };

    using GPMC_CSn0 = pin<e_GPMC_CSn0, 29U, 0x87C>;
    inline GPMC_CSn0 gpmc_csn0{REGS::GPIO::AM335x_GPIO_1}; // gpio1_29


    // ========================================================================
    // GPMC_CSn1 (ZCZ: U9, ZCE: V14) -> gpio1_30
    // ========================================================================
    enum class e_GPMC_CSn1 : uint8_t
    {
        gpmc_csn1                                = 0, // O
        gpmc_clk                                 = 1, // I/O
        mmc1_clk                                 = 2, // I/O
        pr1_edio_data_in6                        = 3, // I
        pr1_edio_data_out6                       = 4, // O
        pr1_pru1_pru_r30_12                      = 5, // O
        pr1_pru1_pru_r31_12                      = 6, // I
        gpio1_30                                 = 7, // I/O (GPIO)
    };

    using GPMC_CSn1 = pin<e_GPMC_CSn1, 30U, 0x880>;
    inline GPMC_CSn1 gpmc_csn1{REGS::GPIO::AM335x_GPIO_1}; // gpio1_30


    // ========================================================================
    // GPMC_CSn2 (ZCZ: V9, ZCE: U15) -> gpio1_31
    // ========================================================================
    enum class e_GPMC_CSn2 : uint8_t
    {
        gpmc_csn2                                = 0, // O
        gpmc_be1n                                = 1, // O
        mmc1_cmd                                 = 2, // I/O
        pr1_edio_data_in7                        = 3, // I
        pr1_edio_data_out7                       = 4, // O
        pr1_pru1_pru_r30_13                      = 5, // O
        pr1_pru1_pru_r31_13                      = 6, // I
        gpio1_31                                 = 7, // I/O (GPIO)
    };

    using GPMC_CSn2 = pin<e_GPMC_CSn2, 31U, 0x884>;
    inline GPMC_CSn2 gpmc_csn2{REGS::GPIO::AM335x_GPIO_1}; // gpio1_31


    // ========================================================================
    // GPMC_CSn3(6) (ZCZ: T13, ZCE: U17) -> gpio2_0
    // ========================================================================
    enum class e_GPMC_CSn3 : uint8_t
    {
        gpmc_csn3                                = 0, // O
        gpmc_a3                                  = 1, // O
        rmii2_crs_dv                             = 2, // I
        mmc2_cmd                                 = 3, // I/O
        pr1_mii0_crs                             = 4, // I
        pr1_mdio_data                            = 5, // I/O
        emu4                                     = 6, // I/O
        gpio2_0                                  = 7, // I/O (GPIO)
    };

    using GPMC_CSn3 = pin<e_GPMC_CSn3, 0U, 0x888>;
    inline GPMC_CSn3 gpmc_csn3{REGS::GPIO::AM335x_GPIO_2}; // gpio2_0


    // ========================================================================
    // GPMC_CLK (ZCZ: V12, ZCE: V16) -> gpio2_1
    // ========================================================================
    enum class e_GPMC_CLK : uint8_t
    {
        gpmc_clk                                 = 0, // I/O
        lcd_memory_clk                           = 1, // O
        gpmc_wait1                               = 2, // I
        mmc2_clk                                 = 3, // I/O
        pr1_mii1_crs                             = 4, // I
        pr1_mdio_mdclk                           = 5, // O
        mcasp0_fsr                               = 6, // I/O
        gpio2_1                                  = 7, // I/O (GPIO)
    };

    using GPMC_CLK = pin<e_GPMC_CLK, 1U, 0x88C>;
    inline GPMC_CLK gpmc_clk{REGS::GPIO::AM335x_GPIO_2}; // gpio2_1


    // ========================================================================
    // GPMC_ADVn_ALE (ZCZ: R7, ZCE: V10) -> gpio2_2
    // ========================================================================
    enum class e_GPMC_ADVn_ALE : uint8_t
    {
        gpmc_advn_ale                            = 0, // O
        timer4                                   = 2, // I/O
        gpio2_2                                  = 7, // I/O (GPIO)
    };

    using GPMC_ADVn_ALE = pin<e_GPMC_ADVn_ALE, 2U, 0x890>;
    inline GPMC_ADVn_ALE gpmc_advn_ale{REGS::GPIO::AM335x_GPIO_2}; // gpio2_2


    // ========================================================================
    // GPMC_OEn_REn (ZCZ: T7, ZCE: W9) -> gpio2_3
    // ========================================================================
    enum class e_GPMC_OEn_REn : uint8_t
    {
        gpmc_oen_ren                             = 0, // O
        timer7                                   = 2, // I/O
        gpio2_3                                  = 7, // I/O (GPIO)
    };

    using GPMC_OEn_REn = pin<e_GPMC_OEn_REn, 3U, 0x894>;
    inline GPMC_OEn_REn gpmc_oen_ren{REGS::GPIO::AM335x_GPIO_2}; // gpio2_3


    // ========================================================================
    // GPMC_WEn (ZCZ: U6, ZCE: U8) -> gpio2_4
    // ========================================================================
    enum class e_GPMC_WEn : uint8_t
    {
        gpmc_wen                                 = 0, // O
        timer6                                   = 2, // I/O
        gpio2_4                                  = 7, // I/O (GPIO)
    };

    using GPMC_WEn = pin<e_GPMC_WEn, 4U, 0x898>;
    inline GPMC_WEn gpmc_wen{REGS::GPIO::AM335x_GPIO_2}; // gpio2_4


    // ========================================================================
    // GPMC_BEn0_CLE (ZCZ: T6, ZCE: V8) -> gpio2_5
    // ========================================================================
    enum class e_GPMC_BEn0_CLE : uint8_t
    {
        gpmc_be0n_cle                            = 0, // O
        timer5                                   = 2, // I/O
        gpio2_5                                  = 7, // I/O (GPIO)
    };

    using GPMC_BEn0_CLE = pin<e_GPMC_BEn0_CLE, 5U, 0x89C>;
    inline GPMC_BEn0_CLE gpmc_ben0_cle{REGS::GPIO::AM335x_GPIO_2}; // gpio2_5


    // ========================================================================
    // LCD_DATA0(5) (ZCZ: R1, ZCE: U1) -> gpio2_6
    // ========================================================================
    enum class e_LCD_DATA0 : uint8_t
    {
        lcd_data0                                = 0, // I/O
        gpmc_a0                                  = 1, // O
        pr1_mii_mt0_clk                          = 2, // I
        ehrpwm2a                                 = 3, // O
        pr1_pru1_pru_r30_0                       = 5, // O
        pr1_pru1_pru_r31_0                       = 6, // I
        gpio2_6                                  = 7, // I/O (GPIO)
    };

    using LCD_DATA0 = pin<e_LCD_DATA0, 6U, 0x8A0>;
    inline LCD_DATA0 lcd_data0{REGS::GPIO::AM335x_GPIO_2}; // gpio2_6


    // ========================================================================
    // LCD_DATA1(5) (ZCZ: R2, ZCE: U2) -> gpio2_7
    // ========================================================================
    enum class e_LCD_DATA1 : uint8_t
    {
        lcd_data1                                = 0, // I/O
        gpmc_a1                                  = 1, // O
        pr1_mii0_txen                            = 2, // O
        ehrpwm2b                                 = 3, // O
        pr1_pru1_pru_r30_1                       = 5, // O
        pr1_pru1_pru_r31_1                       = 6, // I
        gpio2_7                                  = 7, // I/O (GPIO)
    };

    using LCD_DATA1 = pin<e_LCD_DATA1, 7U, 0x8A4>;
    inline LCD_DATA1 lcd_data1{REGS::GPIO::AM335x_GPIO_2}; // gpio2_7


    // ========================================================================
    // LCD_DATA2(5) (ZCZ: R3, ZCE: V1) -> gpio2_8
    // ========================================================================
    enum class e_LCD_DATA2 : uint8_t
    {
        lcd_data2                                = 0, // I/O
        gpmc_a2                                  = 1, // O
        pr1_mii0_txd3                            = 2, // O
        ehrpwm2_tripzone_input                   = 3, // I
        pr1_pru1_pru_r30_2                       = 5, // O
        pr1_pru1_pru_r31_2                       = 6, // I
        gpio2_8                                  = 7, // I/O (GPIO)
    };

    using LCD_DATA2 = pin<e_LCD_DATA2, 8U, 0x8A8>;
    inline LCD_DATA2 lcd_data2{REGS::GPIO::AM335x_GPIO_2}; // gpio2_8


    // ========================================================================
    // LCD_DATA3(5) (ZCZ: R4, ZCE: V2) -> gpio2_9
    // ========================================================================
    enum class e_LCD_DATA3 : uint8_t
    {
        lcd_data3                                = 0, // I/O
        gpmc_a3                                  = 1, // O
        pr1_mii0_txd2                            = 2, // O
        ehrpwm0_synco                            = 3, // O
        pr1_pru1_pru_r30_3                       = 5, // O
        pr1_pru1_pru_r31_3                       = 6, // I
        gpio2_9                                  = 7, // I/O (GPIO)
    };

    using LCD_DATA3 = pin<e_LCD_DATA3, 9U, 0x8AC>;
    inline LCD_DATA3 lcd_data3{REGS::GPIO::AM335x_GPIO_2}; // gpio2_9


    // ========================================================================
    // LCD_DATA4(5) (ZCZ: T1, ZCE: W2) -> gpio2_10
    // ========================================================================
    enum class e_LCD_DATA4 : uint8_t
    {
        lcd_data4                                = 0, // I/O
        gpmc_a4                                  = 1, // O
        pr1_mii0_txd1                            = 2, // O
        eqep2a_in                                = 3, // I
        pr1_pru1_pru_r30_4                       = 5, // O
        pr1_pru1_pru_r31_4                       = 6, // I
        gpio2_10                                 = 7, // I/O (GPIO)
    };

    using LCD_DATA4 = pin<e_LCD_DATA4, 10U, 0x8B0>;
    inline LCD_DATA4 lcd_data4{REGS::GPIO::AM335x_GPIO_2}; // gpio2_10


    // ========================================================================
    // LCD_DATA5(5) (ZCZ: T2, ZCE: W3) -> gpio2_11
    // ========================================================================
    enum class e_LCD_DATA5 : uint8_t
    {
        lcd_data5                                = 0, // I/O
        gpmc_a5                                  = 1, // O
        pr1_mii0_txd0                            = 2, // O
        eqep2b_in                                = 3, // I
        pr1_pru1_pru_r30_5                       = 5, // O
        pr1_pru1_pru_r31_5                       = 6, // I
        gpio2_11                                 = 7, // I/O (GPIO)
    };

    using LCD_DATA5 = pin<e_LCD_DATA5, 11U, 0x8B4>;
    inline LCD_DATA5 lcd_data5{REGS::GPIO::AM335x_GPIO_2}; // gpio2_11


    // ========================================================================
    // LCD_DATA6(5) (ZCZ: T3, ZCE: V3) -> gpio2_12
    // ========================================================================
    enum class e_LCD_DATA6 : uint8_t
    {
        lcd_data6                                = 0, // I/O
        gpmc_a6                                  = 1, // O
        pr1_edio_data_in6                        = 2, // I
        eqep2_index                              = 3, // I/O
        pr1_edio_data_out6                       = 4, // O
        pr1_pru1_pru_r30_6                       = 5, // O
        pr1_pru1_pru_r31_6                       = 6, // I
        gpio2_12                                 = 7, // I/O (GPIO)
    };

    using LCD_DATA6 = pin<e_LCD_DATA6, 12U, 0x8B8>;
    inline LCD_DATA6 lcd_data6{REGS::GPIO::AM335x_GPIO_2}; // gpio2_12


    // ========================================================================
    // LCD_DATA7(5) (ZCZ: T4, ZCE: U3) -> gpio2_13
    // ========================================================================
    enum class e_LCD_DATA7 : uint8_t
    {
        lcd_data7                                = 0, // I/O
        gpmc_a7                                  = 1, // O
        pr1_edio_data_in7                        = 2, // I
        eqep2_strobe                             = 3, // I/O
        pr1_edio_data_out7                       = 4, // O
        pr1_pru1_pru_r30_7                       = 5, // O
        pr1_pru1_pru_r31_7                       = 6, // I
        gpio2_13                                 = 7, // I/O (GPIO)
    };

    using LCD_DATA7 = pin<e_LCD_DATA7, 13U, 0x8BC>;
    inline LCD_DATA7 lcd_data7{REGS::GPIO::AM335x_GPIO_2}; // gpio2_13


    // ========================================================================
    // LCD_DATA8(5) (ZCZ: U1, ZCE: V4) -> gpio2_14
    // ========================================================================
    enum class e_LCD_DATA8 : uint8_t
    {
        lcd_data8                                = 0, // I/O
        gpmc_a12                                 = 1, // O
        ehrpwm1_tripzone_input                   = 2, // I
        mcasp0_aclkx                             = 3, // I/O
        uart5_txd                                = 4, // O
        pr1_mii0_rxd3                            = 5, // I
        uart2_ctsn                               = 6, // I
        gpio2_14                                 = 7, // I/O (GPIO)
    };

    using LCD_DATA8 = pin<e_LCD_DATA8, 14U, 0x8C0>;
    inline LCD_DATA8 lcd_data8{REGS::GPIO::AM335x_GPIO_2}; // gpio2_14


    // ========================================================================
    // LCD_DATA9(5) (ZCZ: U2, ZCE: W4) -> gpio2_15
    // ========================================================================
    enum class e_LCD_DATA9 : uint8_t
    {
        lcd_data9                                = 0, // I/O
        gpmc_a13                                 = 1, // O
        ehrpwm0_synco                            = 2, // O
        mcasp0_fsx                               = 3, // I/O
        uart5_rxd                                = 4, // I
        pr1_mii0_rxd2                            = 5, // I
        uart2_rtsn                               = 6, // O
        gpio2_15                                 = 7, // I/O (GPIO)
    };

    using LCD_DATA9 = pin<e_LCD_DATA9, 15U, 0x8C4>;
    inline LCD_DATA9 lcd_data9{REGS::GPIO::AM335x_GPIO_2}; // gpio2_15


    // ========================================================================
    // LCD_DATA10(5) (ZCZ: U3, ZCE: U5) -> gpio2_16
    // ========================================================================
    enum class e_LCD_DATA10 : uint8_t
    {
        lcd_data10                               = 0, // I/O
        gpmc_a14                                 = 1, // O
        ehrpwm1a                                 = 2, // O
        mcasp0_axr0                              = 3, // I/O
        pr1_mii0_rxd1                            = 5, // I
        uart3_ctsn                               = 6, // I
        gpio2_16                                 = 7, // I/O (GPIO)
    };

    using LCD_DATA10 = pin<e_LCD_DATA10, 16U, 0x8C8>;
    inline LCD_DATA10 lcd_data10{REGS::GPIO::AM335x_GPIO_2}; // gpio2_16


    // ========================================================================
    // LCD_DATA11(5) (ZCZ: U4, ZCE: V5) -> gpio2_17
    // ========================================================================
    enum class e_LCD_DATA11 : uint8_t
    {
        lcd_data11                               = 0, // I/O
        gpmc_a15                                 = 1, // O
        ehrpwm1b                                 = 2, // O
        mcasp0_ahclkr                            = 3, // I/O
        mcasp0_axr2                              = 4, // I/O
        pr1_mii0_rxd0                            = 5, // I
        uart3_rtsn                               = 6, // O
        gpio2_17                                 = 7, // I/O (GPIO)
    };

    using LCD_DATA11 = pin<e_LCD_DATA11, 17U, 0x8CC>;
    inline LCD_DATA11 lcd_data11{REGS::GPIO::AM335x_GPIO_2}; // gpio2_17


    // ========================================================================
    // MII1_RXD3 (ZCZ: L17, ZCE: N17) -> gpio2_18
    // ========================================================================
    enum class e_MII1_RXD3 : uint8_t
    {
        gmii1_rxd3                               = 0, // I
        uart3_rxd                                = 1, // I
        rgmii1_rd3                               = 2, // I
        mmc0_dat5                                = 3, // I/O
        mmc1_dat2                                = 4, // I/O
        uart1_dtrn                               = 5, // O
        mcasp0_axr0                              = 6, // I/O
        gpio2_18                                 = 7, // I/O (GPIO)
    };

    using MII1_RXD3 = pin<e_MII1_RXD3, 18U, 0x934>;
    inline MII1_RXD3 mii1_rxd3{REGS::GPIO::AM335x_GPIO_2}; // gpio2_18


    // ========================================================================
    // MII1_RXD2 (ZCZ: L16, ZCE: N16) -> gpio2_19
    // ========================================================================
    enum class e_MII1_RXD2 : uint8_t
    {
        gmii1_rxd2                               = 0, // I
        uart3_txd                                = 1, // O
        rgmii1_rd2                               = 2, // I
        mmc0_dat4                                = 3, // I/O
        mmc1_dat3                                = 4, // I/O
        uart1_rin                                = 5, // I
        mcasp0_axr1                              = 6, // I/O
        gpio2_19                                 = 7, // I/O (GPIO)
    };

    using MII1_RXD2 = pin<e_MII1_RXD2, 19U, 0x938>;
    inline MII1_RXD2 mii1_rxd2{REGS::GPIO::AM335x_GPIO_2}; // gpio2_19


    // ========================================================================
    // MII1_RXD1 (ZCZ: L15, ZCE: P19) -> gpio2_20
    // ========================================================================
    enum class e_MII1_RXD1 : uint8_t
    {
        gmii1_rxd1                               = 0, // I
        rmii1_rxd1                               = 1, // I
        rgmii1_rd1                               = 2, // I
        mcasp1_axr3                              = 3, // I/O
        mcasp1_fsr                               = 4, // I/O
        eqep0_strobe                             = 5, // I/O
        mmc2_clk                                 = 6, // I/O
        gpio2_20                                 = 7, // I/O (GPIO)
    };

    using MII1_RXD1 = pin<e_MII1_RXD1, 20U, 0x93C>;
    inline MII1_RXD1 mii1_rxd1{REGS::GPIO::AM335x_GPIO_2}; // gpio2_20


    // ========================================================================
    // MII1_RXD0 (ZCZ: M16, ZCE: P18) -> gpio2_21
    // ========================================================================
    enum class e_MII1_RXD0 : uint8_t
    {
        gmii1_rxd0                               = 0, // I
        rmii1_rxd0                               = 1, // I
        rgmii1_rd0                               = 2, // I
        mcasp1_ahclkx                            = 3, // I/O
        mcasp1_ahclkr                            = 4, // I/O
        mcasp1_aclkr                             = 5, // I/O
        mcasp0_axr3                              = 6, // I/O
        gpio2_21                                 = 7, // I/O (GPIO)
    };

    using MII1_RXD0 = pin<e_MII1_RXD0, 21U, 0x940>;
    inline MII1_RXD0 mii1_rxd0{REGS::GPIO::AM335x_GPIO_2}; // gpio2_21


    // ========================================================================
    // LCD_VSYNC(7) (ZCZ: U5, ZCE: U7) -> gpio2_22
    // ========================================================================
    enum class e_LCD_VSYNC : uint8_t
    {
        lcd_vsync                                = 0, // O
        gpmc_a8                                  = 1, // O
        gpmc_a1                                  = 2, // O
        pr1_edio_data_in2                        = 3, // I
        pr1_edio_data_out2                       = 4, // O
        pr1_pru1_pru_r30_8                       = 5, // O
        pr1_pru1_pru_r31_8                       = 6, // I
        gpio2_22                                 = 7, // I/O (GPIO)
    };

    using LCD_VSYNC = pin<e_LCD_VSYNC, 22U, 0x8E0>;
    inline LCD_VSYNC lcd_vsync{REGS::GPIO::AM335x_GPIO_2}; // gpio2_22


    // ========================================================================
    // LCD_HSYNC(7) (ZCZ: R5, ZCE: T7) -> gpio2_23
    // ========================================================================
    enum class e_LCD_HSYNC : uint8_t
    {
        lcd_hsync                                = 0, // O
        gpmc_a9                                  = 1, // O
        gpmc_a2                                  = 2, // O
        pr1_edio_data_in3                        = 3, // I
        pr1_edio_data_out3                       = 4, // O
        pr1_pru1_pru_r30_9                       = 5, // O
        pr1_pru1_pru_r31_9                       = 6, // I
        gpio2_23                                 = 7, // I/O (GPIO)
    };

    using LCD_HSYNC = pin<e_LCD_HSYNC, 23U, 0x8E4>;
    inline LCD_HSYNC lcd_hsync{REGS::GPIO::AM335x_GPIO_2}; // gpio2_23


    // ========================================================================
    // LCD_PCLK (ZCZ: V5, ZCE: W5) -> gpio2_24
    // ========================================================================
    enum class e_LCD_PCLK : uint8_t
    {
        lcd_pclk                                 = 0, // O
        gpmc_a10                                 = 1, // O
        pr1_mii0_crs                             = 2, // I
        pr1_edio_data_in4                        = 3, // I
        pr1_edio_data_out4                       = 4, // O
        pr1_pru1_pru_r30_10                      = 5, // O
        pr1_pru1_pru_r31_10                      = 6, // I
        gpio2_24                                 = 7, // I/O (GPIO)
    };

    using LCD_PCLK = pin<e_LCD_PCLK, 24U, 0x8E8>;
    inline LCD_PCLK lcd_pclk{REGS::GPIO::AM335x_GPIO_2}; // gpio2_24


    // ========================================================================
    // LCD_AC_BIAS_EN (ZCZ: R6, ZCE: W7) -> gpio2_25
    // ========================================================================
    enum class e_LCD_AC_BIAS_EN : uint8_t
    {
        lcd_ac_bias_en                           = 0, // O
        gpmc_a11                                 = 1, // O
        pr1_mii1_crs                             = 2, // I
        pr1_edio_data_in5                        = 3, // I
        pr1_edio_data_out5                       = 4, // O
        pr1_pru1_pru_r30_11                      = 5, // O
        pr1_pru1_pru_r31_11                      = 6, // I
        gpio2_25                                 = 7, // I/O (GPIO)
    };

    using LCD_AC_BIAS_EN = pin<e_LCD_AC_BIAS_EN, 25U, 0x8EC>;
    inline LCD_AC_BIAS_EN lcd_ac_bias_en{REGS::GPIO::AM335x_GPIO_2}; // gpio2_25


    // ========================================================================
    // MMC0_DAT3 (ZCZ: F17, ZCE: H19) -> gpio2_26
    // ========================================================================
    enum class e_MMC0_DAT3 : uint8_t
    {
        mmc0_dat3                                = 0, // I/O
        gpmc_a20                                 = 1, // O
        uart4_ctsn                               = 2, // I
        timer5                                   = 3, // I/O
        uart1_dcdn                               = 4, // I
        pr1_pru0_pru_r30_8                       = 5, // O
        pr1_pru0_pru_r31_8                       = 6, // I
        gpio2_26                                 = 7, // I/O (GPIO)
    };

    using MMC0_DAT3 = pin<e_MMC0_DAT3, 26U, 0x8F0>;
    inline MMC0_DAT3 mmc0_dat3{REGS::GPIO::AM335x_GPIO_2}; // gpio2_26


    // ========================================================================
    // MMC0_DAT2 (ZCZ: F18, ZCE: H18) -> gpio2_27
    // ========================================================================
    enum class e_MMC0_DAT2 : uint8_t
    {
        mmc0_dat2                                = 0, // I/O
        gpmc_a21                                 = 1, // O
        uart4_rtsn                               = 2, // O
        timer6                                   = 3, // I/O
        uart1_dsrn                               = 4, // I
        pr1_pru0_pru_r30_9                       = 5, // O
        pr1_pru0_pru_r31_9                       = 6, // I
        gpio2_27                                 = 7, // I/O (GPIO)
    };

    using MMC0_DAT2 = pin<e_MMC0_DAT2, 27U, 0x8F4>;
    inline MMC0_DAT2 mmc0_dat2{REGS::GPIO::AM335x_GPIO_2}; // gpio2_27


    // ========================================================================
    // MMC0_DAT1 (ZCZ: G15, ZCE: H17) -> gpio2_28
    // ========================================================================
    enum class e_MMC0_DAT1 : uint8_t
    {
        mmc0_dat1                                = 0, // I/O
        gpmc_a22                                 = 1, // O
        uart5_ctsn                               = 2, // I
        uart3_rxd                                = 3, // I
        uart1_dtrn                               = 4, // O
        pr1_pru0_pru_r30_10                      = 5, // O
        pr1_pru0_pru_r31_10                      = 6, // I
        gpio2_28                                 = 7, // I/O (GPIO)
    };

    using MMC0_DAT1 = pin<e_MMC0_DAT1, 28U, 0x8F8>;
    inline MMC0_DAT1 mmc0_dat1{REGS::GPIO::AM335x_GPIO_2}; // gpio2_28


    // ========================================================================
    // MMC0_DAT0 (ZCZ: G16, ZCE: G18) -> gpio2_29
    // ========================================================================
    enum class e_MMC0_DAT0 : uint8_t
    {
        mmc0_dat0                                = 0, // I/O
        gpmc_a23                                 = 1, // O
        uart5_rtsn                               = 2, // O
        uart3_txd                                = 3, // O
        uart1_rin                                = 4, // I
        pr1_pru0_pru_r30_11                      = 5, // O
        pr1_pru0_pru_r31_11                      = 6, // I
        gpio2_29                                 = 7, // I/O (GPIO)
    };

    using MMC0_DAT0 = pin<e_MMC0_DAT0, 29U, 0x8FC>;
    inline MMC0_DAT0 mmc0_dat0{REGS::GPIO::AM335x_GPIO_2}; // gpio2_29


    // ========================================================================
    // MMC0_CLK (ZCZ: G17, ZCE: G19) -> gpio2_30
    // ========================================================================
    enum class e_MMC0_CLK : uint8_t
    {
        mmc0_clk                                 = 0, // I/O
        gpmc_a24                                 = 1, // O
        uart3_ctsn                               = 2, // I
        uart2_rxd                                = 3, // I
        dcan1_tx                                 = 4, // O
        pr1_pru0_pru_r30_12                      = 5, // O
        pr1_pru0_pru_r31_12                      = 6, // I
        gpio2_30                                 = 7, // I/O (GPIO)
    };

    using MMC0_CLK = pin<e_MMC0_CLK, 30U, 0x900>;
    inline MMC0_CLK mmc0_clk{REGS::GPIO::AM335x_GPIO_2}; // gpio2_30


    // ========================================================================
    // MMC0_CMD (ZCZ: G18, ZCE: G17) -> gpio2_31
    // ========================================================================
    enum class e_MMC0_CMD : uint8_t
    {
        mmc0_cmd                                 = 0, // I/O
        gpmc_a25                                 = 1, // O
        uart3_rtsn                               = 2, // O
        uart2_txd                                = 3, // O
        dcan1_rx                                 = 4, // I
        pr1_pru0_pru_r30_13                      = 5, // O
        pr1_pru0_pru_r31_13                      = 6, // I
        gpio2_31                                 = 7, // I/O (GPIO)
    };

    using MMC0_CMD = pin<e_MMC0_CMD, 31U, 0x904>;
    inline MMC0_CMD mmc0_cmd{REGS::GPIO::AM335x_GPIO_2}; // gpio2_31


    // ========================================================================
    // MII1_COL (ZCZ: H16, ZCE: J19) -> gpio3_0
    // ========================================================================
    enum class e_MII1_COL : uint8_t
    {
        gmii1_col                                = 0, // I
        rmii2_refclk                             = 1, // I/O
        spi1_sclk                                = 2, // I/O
        uart5_rxd                                = 3, // I
        mcasp1_axr2                              = 4, // I/O
        mmc2_dat3                                = 5, // I/O
        mcasp0_axr2                              = 6, // I/O
        gpio3_0                                  = 7, // I/O (GPIO)
    };

    using MII1_COL = pin<e_MII1_COL, 0U, 0x908>;
    inline MII1_COL mii1_col{REGS::GPIO::AM335x_GPIO_3}; // gpio3_0


    // ========================================================================
    // MII1_CRS (ZCZ: H17, ZCE: J18) -> gpio3_1
    // ========================================================================
    enum class e_MII1_CRS : uint8_t
    {
        gmii1_crs                                = 0, // I
        rmii1_crs_dv                             = 1, // I
        spi1_d0                                  = 2, // I/O
        i2c1_sda                                 = 3, // I/OD
        mcasp1_aclkx                             = 4, // I/O
        uart5_ctsn                               = 5, // I
        uart2_rxd                                = 6, // I
        gpio3_1                                  = 7, // I/O (GPIO)
    };

    using MII1_CRS = pin<e_MII1_CRS, 1U, 0x90C>;
    inline MII1_CRS mii1_crs{REGS::GPIO::AM335x_GPIO_3}; // gpio3_1


    // ========================================================================
    // MII1_RX_ER (ZCZ: J15, ZCE: K19) -> gpio3_2
    // ========================================================================
    enum class e_MII1_RX_ER : uint8_t
    {
        gmii1_rxerr                              = 0, // I
        rmii1_rxerr                              = 1, // I
        spi1_d1                                  = 2, // I/O
        i2c1_scl                                 = 3, // I/OD
        mcasp1_fsx                               = 4, // I/O
        uart5_rtsn                               = 5, // O
        uart2_txd                                = 6, // O
        gpio3_2                                  = 7, // I/O (GPIO)
    };

    using MII1_RX_ER = pin<e_MII1_RX_ER, 2U, 0x910>;
    inline MII1_RX_ER mii1_rx_er{REGS::GPIO::AM335x_GPIO_3}; // gpio3_2


    // ========================================================================
    // MII1_TX_EN (ZCZ: J16, ZCE: K17) -> gpio3_3
    // ========================================================================
    enum class e_MII1_TX_EN : uint8_t
    {
        gmii1_txen                               = 0, // O
        rmii1_txen                               = 1, // O
        rgmii1_tctl                              = 2, // O
        timer4                                   = 3, // I/O
        mcasp1_axr0                              = 4, // I/O
        eqep0_index                              = 5, // I/O
        mmc2_cmd                                 = 6, // I/O
        gpio3_3                                  = 7, // I/O (GPIO)
    };

    using MII1_TX_EN = pin<e_MII1_TX_EN, 3U, 0x914>;
    inline MII1_TX_EN mii1_tx_en{REGS::GPIO::AM335x_GPIO_3}; // gpio3_3


    // ========================================================================
    // MII1_RX_DV (ZCZ: J17, ZCE: L19) -> gpio3_4
    // ========================================================================
    enum class e_MII1_RX_DV : uint8_t
    {
        gmii1_rxdv                               = 0, // I
        lcd_memory_clk                           = 1, // O
        rgmii1_rctl                              = 2, // I
        uart5_txd                                = 3, // O
        mcasp1_aclkx                             = 4, // I/O
        mmc2_dat0                                = 5, // I/O
        mcasp0_aclkr                             = 6, // I/O
        gpio3_4                                  = 7, // I/O (GPIO)
    };

    using MII1_RX_DV = pin<e_MII1_RX_DV, 4U, 0x918>;
    inline MII1_RX_DV mii1_rx_dv{REGS::GPIO::AM335x_GPIO_3}; // gpio3_4


    // ========================================================================
    // I2C0_SDA (ZCZ: C17, ZCE: C18) -> gpio3_5
    // ========================================================================
    enum class e_I2C0_SDA : uint8_t
    {
        i2c0_sda                                 = 0, // I/OD
        timer4                                   = 1, // I/O
        uart2_ctsn                               = 2, // I
        ecap2_in_pwm2_out                        = 3, // I/O
        gpio3_5                                  = 7, // I/O (GPIO)
    };

    using I2C0_SDA = pin<e_I2C0_SDA, 5U, 0x988>;
    inline I2C0_SDA i2c0_sda{REGS::GPIO::AM335x_GPIO_3}; // gpio3_5


    // ========================================================================
    // I2C0_SCL (ZCZ: C16, ZCE: B19) -> gpio3_6
    // ========================================================================
    enum class e_I2C0_SCL : uint8_t
    {
        i2c0_scl                                 = 0, // I/OD
        timer7                                   = 1, // I/O
        uart2_rtsn                               = 2, // O
        ecap1_in_pwm1_out                        = 3, // I/O
        gpio3_6                                  = 7, // I/O (GPIO)
    };

    using I2C0_SCL = pin<e_I2C0_SCL, 6U, 0x98C>;
    inline I2C0_SCL i2c0_scl{REGS::GPIO::AM335x_GPIO_3}; // gpio3_6


    // ========================================================================
    // EMU0 (ZCZ: C14, ZCE: A15) -> gpio3_7
    // ========================================================================
    enum class e_EMU0 : uint8_t
    {
        emu0                                     = 0, // I/O
        gpio3_7                                  = 7, // I/O (GPIO)
    };

    using EMU0 = pin<e_EMU0, 7U, 0x9E4>;
    inline EMU0 emu0{REGS::GPIO::AM335x_GPIO_3}; // gpio3_7


    // ========================================================================
    // EMU1 (ZCZ: B14, ZCE: D14) -> gpio3_8
    // ========================================================================
    enum class e_EMU1 : uint8_t
    {
        emu1                                     = 0, // I/O
        gpio3_8                                  = 7, // I/O (GPIO)
    };

    using EMU1 = pin<e_EMU1, 8U, 0x9E8>;
    inline EMU1 emu1{REGS::GPIO::AM335x_GPIO_3}; // gpio3_8


    // ========================================================================
    // MII1_TX_CLK (ZCZ: K18, ZCE: N19) -> gpio3_9
    // ========================================================================
    enum class e_MII1_TX_CLK : uint8_t
    {
        gmii1_txclk                              = 0, // I
        uart2_rxd                                = 1, // I
        rgmii1_tclk                              = 2, // O
        mmc0_dat7                                = 3, // I/O
        mmc1_dat0                                = 4, // I/O
        uart1_dcdn                               = 5, // I
        mcasp0_aclkx                             = 6, // I/O
        gpio3_9                                  = 7, // I/O (GPIO)
    };

    using MII1_TX_CLK = pin<e_MII1_TX_CLK, 9U, 0x92C>;
    inline MII1_TX_CLK mii1_tx_clk{REGS::GPIO::AM335x_GPIO_3}; // gpio3_9


    // ========================================================================
    // MII1_RX_CLK (ZCZ: L18, ZCE: M19) -> gpio3_10
    // ========================================================================
    enum class e_MII1_RX_CLK : uint8_t
    {
        gmii1_rxclk                              = 0, // I
        uart2_txd                                = 1, // O
        rgmii1_rclk                              = 2, // I
        mmc0_dat6                                = 3, // I/O
        mmc1_dat1                                = 4, // I/O
        uart1_dsrn                               = 5, // I
        mcasp0_fsx                               = 6, // I/O
        gpio3_10                                 = 7, // I/O (GPIO)
    };

    using MII1_RX_CLK = pin<e_MII1_RX_CLK, 10U, 0x930>;
    inline MII1_RX_CLK mii1_rx_clk{REGS::GPIO::AM335x_GPIO_3}; // gpio3_10


    // ========================================================================
    // USB1_DRVVBUS (ZCZ: F15, ZCE: NA) -> gpio3_13
    // ========================================================================
    enum class e_USB1_DRVVBUS : uint8_t
    {
        usb1_drvvbus                             = 0, // O
        gpio3_13                                 = 7, // I/O (GPIO)
    };

    using USB1_DRVVBUS = pin<e_USB1_DRVVBUS, 13U, 0xA34>;
    inline USB1_DRVVBUS usb1_drvvbus{REGS::GPIO::AM335x_GPIO_3}; // gpio3_13


    // ========================================================================
    // MCASP0_ACLKX (ZCZ: A13, ZCE: NA) -> gpio3_14
    // ========================================================================
    enum class e_MCASP0_ACLKX : uint8_t
    {
        mcasp0_aclkx                             = 0, // I/O
        ehrpwm0a                                 = 1, // O
        spi1_sclk                                = 3, // I/O
        mmc0_sdcd                                = 4, // I
        pr1_pru0_pru_r30_0                       = 5, // O
        pr1_pru0_pru_r31_0                       = 6, // I
        gpio3_14                                 = 7, // I/O (GPIO)
    };

    using MCASP0_ACLKX = pin<e_MCASP0_ACLKX, 14U, 0x990>;
    inline MCASP0_ACLKX mcasp0_aclkx{REGS::GPIO::AM335x_GPIO_3}; // gpio3_14


    // ========================================================================
    // MCASP0_FSX (ZCZ: B13, ZCE: NA) -> gpio3_15
    // ========================================================================
    enum class e_MCASP0_FSX : uint8_t
    {
        mcasp0_fsx                               = 0, // I/O
        ehrpwm0b                                 = 1, // O
        spi1_d0                                  = 3, // I/O
        mmc1_sdcd                                = 4, // I
        pr1_pru0_pru_r30_1                       = 5, // O
        pr1_pru0_pru_r31_1                       = 6, // I
        gpio3_15                                 = 7, // I/O (GPIO)
    };

    using MCASP0_FSX = pin<e_MCASP0_FSX, 15U, 0x994>;
    inline MCASP0_FSX mcasp0_fsx{REGS::GPIO::AM335x_GPIO_3}; // gpio3_15


    // ========================================================================
    // MCASP0_AXR0 (ZCZ: D12, ZCE: NA) -> gpio3_16
    // ========================================================================
    enum class e_MCASP0_AXR0 : uint8_t
    {
        mcasp0_axr0                              = 0, // I/O
        ehrpwm0_tripzone_input                   = 1, // I
        spi1_d1                                  = 3, // I/O
        mmc2_sdcd                                = 4, // I
        pr1_pru0_pru_r30_2                       = 5, // O
        pr1_pru0_pru_r31_2                       = 6, // I
        gpio3_16                                 = 7, // I/O (GPIO)
    };

    using MCASP0_AXR0 = pin<e_MCASP0_AXR0, 16U, 0x998>;
    inline MCASP0_AXR0 mcasp0_axr0{REGS::GPIO::AM335x_GPIO_3}; // gpio3_16


    // ========================================================================
    // MCASP0_AHCLKR (ZCZ: C12, ZCE: NA) -> gpio3_17
    // ========================================================================
    enum class e_MCASP0_AHCLKR : uint8_t
    {
        mcasp0_ahclkr                            = 0, // I/O
        ehrpwm0_synci                            = 1, // I
        mcasp0_axr2                              = 2, // I/O
        spi1_cs0                                 = 3, // I/O
        ecap2_in_pwm2_out                        = 4, // I/O
        pr1_pru0_pru_r30_3                       = 5, // O
        pr1_pru0_pru_r31_3                       = 6, // I
        gpio3_17                                 = 7, // I/O (GPIO)
    };

    using MCASP0_AHCLKR = pin<e_MCASP0_AHCLKR, 17U, 0x99C>;
    inline MCASP0_AHCLKR mcasp0_ahclkr{REGS::GPIO::AM335x_GPIO_3}; // gpio3_17


    // ========================================================================
    // MCASP0_ACLKR (ZCZ: B12, ZCE: NA) -> gpio3_18
    // ========================================================================
    enum class e_MCASP0_ACLKR : uint8_t
    {
        mcasp0_aclkr                             = 0, // I/O
        eqep0a_in                                = 1, // I
        mcasp0_axr2                              = 2, // I/O
        mcasp1_aclkx                             = 3, // I/O
        mmc0_sdwp                                = 4, // I
        pr1_pru0_pru_r30_4                       = 5, // O
        pr1_pru0_pru_r31_4                       = 6, // I
        gpio3_18                                 = 7, // I/O (GPIO)
    };

    using MCASP0_ACLKR = pin<e_MCASP0_ACLKR, 18U, 0x9A0>;
    inline MCASP0_ACLKR mcasp0_aclkr{REGS::GPIO::AM335x_GPIO_3}; // gpio3_18


    // ========================================================================
    // MCASP0_FSR (ZCZ: C13, ZCE: NA) -> gpio3_19
    // ========================================================================
    enum class e_MCASP0_FSR : uint8_t
    {
        mcasp0_fsr                               = 0, // I/O
        eqep0b_in                                = 1, // I
        mcasp0_axr3                              = 2, // I/O
        mcasp1_fsx                               = 3, // I/O
        emu2                                     = 4, // I/O
        pr1_pru0_pru_r30_5                       = 5, // O
        pr1_pru0_pru_r31_5                       = 6, // I
        gpio3_19                                 = 7, // I/O (GPIO)
    };

    using MCASP0_FSR = pin<e_MCASP0_FSR, 19U, 0x9A4>;
    inline MCASP0_FSR mcasp0_fsr{REGS::GPIO::AM335x_GPIO_3}; // gpio3_19


    // ========================================================================
    // MCASP0_AXR1 (ZCZ: D13, ZCE: NA) -> gpio3_20
    // ========================================================================
    enum class e_MCASP0_AXR1 : uint8_t
    {
        mcasp0_axr1                              = 0, // I/O
        eqep0_index                              = 1, // I/O
        mcasp1_axr0                              = 3, // I/O
        emu3                                     = 4, // I/O
        pr1_pru0_pru_r30_6                       = 5, // O
        pr1_pru0_pru_r31_6                       = 6, // I
        gpio3_20                                 = 7, // I/O (GPIO)
    };

    using MCASP0_AXR1 = pin<e_MCASP0_AXR1, 20U, 0x9A8>;
    inline MCASP0_AXR1 mcasp0_axr1{REGS::GPIO::AM335x_GPIO_3}; // gpio3_20


    // ========================================================================
    // MCASP0_AHCLKX (ZCZ: A14, ZCE: NA) -> gpio3_21
    // ========================================================================
    enum class e_MCASP0_AHCLKX : uint8_t
    {
        mcasp0_ahclkx                            = 0, // I/O
        eqep0_strobe                             = 1, // I/O
        mcasp0_axr3                              = 2, // I/O
        mcasp1_axr1                              = 3, // I/O
        emu4                                     = 4, // I/O
        pr1_pru0_pru_r30_7                       = 5, // O
        pr1_pru0_pru_r31_7                       = 6, // I
        gpio3_21                                 = 7, // I/O (GPIO)
    };

    using MCASP0_AHCLKX = pin<e_MCASP0_AHCLKX, 21U, 0x9AC>;
    inline MCASP0_AHCLKX mcasp0_ahclkx{REGS::GPIO::AM335x_GPIO_3}; // gpio3_21




} // namespace HAL::PINS

#endif // _AM3358ZCZ_PINS_H