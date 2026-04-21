#ifndef __BOARD_HPP
#define __BOARD_HPP

#include "pins/am3358zcz_pins.hpp"

namespace Board
{
    /************** All pins from beagleboard black revision C. **************/

    // ========================================================================
    // USER LEDs (BeagleBone Black)
    // ========================================================================
    extern HAL::PINS::GPMC_A5& USR0;   // GPIO1_21, P9.25
    extern HAL::PINS::GPMC_A6& USR1;   // GPIO1_22, P9.27
    extern HAL::PINS::GPMC_A7& USR2;   // GPIO1_23, P9.28
    extern HAL::PINS::GPMC_A8& USR3;   // GPIO1_24, P9.30

    // ========================================================================
    // BOOT BUTTON (BeagleBone Black)
    // ========================================================================
    extern HAL::PINS::GPMC_AD8& BOOT_BUTTON;  // GPIO0_22, P8.19 (active low, pull-up)

    // ========================================================================
    // UART0 (Debug Console - FTDI header J1)
    // ========================================================================
    extern HAL::PINS::UART0_TXD& UART0_TX;    // GPIO1_11, J1.4
    extern HAL::PINS::UART0_RXD& UART0_RX;    // GPIO1_10, J1.5

    /*
    // ========================================================================
    // UART1 (Available on P9.24, P9.26)
    // ========================================================================
    extern HAL::PINS::UART1_TXD& UART1_TX;    // GPIO0_15, P9.24
    extern HAL::PINS::UART1_RXD& UART1_RX;    // GPIO0_14, P9.26

    // ========================================================================
    // UART2 (Available on P8.37, P8.38)
    // ========================================================================
    extern HAL::PINS::LCD_DATA9& UART2_TX;    // GPIO2_15, P8.38 (Mode 6)
    extern HAL::PINS::LCD_DATA8& UART2_RX;    // GPIO2_14, P8.37 (Mode 6)

    // ========================================================================
    // UART4 (Available on P9.11, P9.13)
    // ========================================================================
    extern HAL::PINS::GPMC_WAIT0& UART4_TX;   // GPIO0_30, P9.11 (Mode 6)
    extern HAL::PINS::GPMC_WPn& UART4_RX;     // GPIO0_31, P9.13 (Mode 6)

    // ========================================================================
    // UART5 (Available on P8.31, P8.32)
    // ========================================================================
    extern HAL::PINS::LCD_DATA13& UART5_TX;   // GPIO0_9, P8.32 (Mode 4)
    extern HAL::PINS::LCD_DATA12& UART5_RX;   // GPIO0_8, P8.31 (Mode 4)

    // ========================================================================
    // I2C0 (Internal - PMIC, Cape EEPROM)
    // ========================================================================
    extern HAL::PINS::I2C0_SDA& I2C0_SDA;     // GPIO3_5, P9.18 (Mode 0)
    extern HAL::PINS::I2C0_SCL& I2C0_SCL;     // GPIO3_6, P9.17 (Mode 0)

    // ========================================================================
    // I2C1 (Available on P9.20, P9.19)
    // ========================================================================
    extern HAL::PINS::SPI0_D1& I2C1_SDA;      // GPIO0_4, P9.20 (Mode 2)
    extern HAL::PINS::SPI0_CS0& I2C1_SCL;     // GPIO0_5, P9.19 (Mode 2)

    // ========================================================================
    // I2C2 (Available on P9.21, P9.22)
    // ========================================================================
    extern HAL::PINS::SPI0_D0& I2C2_SDA;      // GPIO0_3, P9.21 (Mode 2)
    extern HAL::PINS::SPI0_SCLK& I2C2_SCL;    // GPIO0_2, P9.22 (Mode 2)

    // ========================================================================
    // SPI0 (Available on P9.17, P9.18, P9.21, P9.22)
    // ========================================================================
    extern HAL::PINS::SPI0_SCLK& SPI0_SCLK;   // GPIO0_2, P9.22
    extern HAL::PINS::SPI0_D0& SPI0_D0;       // GPIO0_3, P9.21 (MISO)
    extern HAL::PINS::SPI0_D1& SPI0_D1;       // GPIO0_4, P9.18 (MOSI)
    extern HAL::PINS::SPI0_CS0& SPI0_CS0;     // GPIO0_5, P9.17

    // ========================================================================
    // SPI1 (Available on P9.28, P9.29, P9.30, P9.31)
    // ========================================================================
    extern HAL::PINS::MCASP0_AHCLKR& SPI1_SCLK;  // GPIO3_17, P9.31 (Mode 3)
    extern HAL::PINS::MCASP0_ACLKR& SPI1_D0;     // GPIO3_18, P9.29 (Mode 3)
    extern HAL::PINS::MCASP0_FSR& SPI1_D1;       // GPIO3_19, P9.28 (Mode 3)
    extern HAL::PINS::MCASP0_AHCLKX& SPI1_CS0;   // GPIO3_21, P9.25 (Mode 3)

    // ========================================================================
    // PWM / EHRPWM
    // ========================================================================
    extern HAL::PINS::SPI0_SCLK& EHRPWM0A;    // GPIO0_2, P9.22 (Mode 3)
    extern HAL::PINS::SPI0_D0& EHRPWM0B;      // GPIO0_3, P9.21 (Mode 3)
    extern HAL::PINS::GPMC_A2& EHRPWM1A;      // GPIO1_18, P9.14 (Mode 6)
    extern HAL::PINS::GPMC_A3& EHRPWM1B;      // GPIO1_19, P9.16 (Mode 6)
    extern HAL::PINS::GPMC_AD8& EHRPWM2A;     // GPIO0_22, P8.19 (Mode 4)
    extern HAL::PINS::GPMC_AD9& EHRPWM2B;     // GPIO0_23, P8.13 (Mode 4)

    extern HAL::PINS::ECAP0_IN_PWM0_OUT& ECAP0_IN_PWM0_OUT;  // GPIO0_7, P9.42
    extern HAL::PINS::UART0_TXD& ECAP1_IN_PWM1_OUT;          // GPIO1_11, P9.24? (Mode 4)
    extern HAL::PINS::UART0_RXD& ECAP2_IN_PWM2_OUT;          // GPIO1_10, P9.26? (Mode 4)

    // ========================================================================
    // CAN Bus (DCAN0, DCAN1)
    // ========================================================================
    extern HAL::PINS::UART0_RXD& DCAN0_TX;    // GPIO1_10, P9.26 (Mode 2)
    extern HAL::PINS::UART0_TXD& DCAN0_RX;    // GPIO1_11, P9.24 (Mode 2)
    extern HAL::PINS::UART0_CTSn& DCAN1_TX;   // GPIO1_8, P9.11? (Mode 2)
    extern HAL::PINS::UART0_RTSn& DCAN1_RX;   // GPIO1_9, P9.13? (Mode 2)

    // ========================================================================
    // FREE GPIO PINS (Safe to use as general purpose I/O)
    // ========================================================================

    // P8 Header - Free GPIOs
    extern HAL::PINS::GPMC_ADVn_ALE& P8_07;  // GPIO2_2
    extern HAL::PINS::GPMC_OEn_REn& P8_08;   // GPIO2_3
    extern HAL::PINS::GPMC_WEn& P8_09;       // GPIO2_4
    extern HAL::PINS::GPMC_BEn0_CLE& P8_10;  // GPIO2_5
    extern HAL::PINS::GPMC_AD13& P8_11;      // GPIO1_13
    extern HAL::PINS::GPMC_AD12& P8_12;      // GPIO1_12
    extern HAL::PINS::GPMC_BEn1& P8_13;      // GPIO1_28
    extern HAL::PINS::GPMC_AD10& P8_14;      // GPIO0_26
    extern HAL::PINS::GPMC_AD15& P8_15;      // GPIO1_15
    extern HAL::PINS::GPMC_AD14& P8_16;      // GPIO1_14
    extern HAL::PINS::GPMC_AD11& P8_17;      // GPIO0_27
    extern HAL::PINS::GPMC_WAIT0& P8_18;     // GPIO0_30
    extern HAL::PINS::GPMC_WPn& P8_19;       // GPIO0_31
    extern HAL::PINS::GPMC_CSn0& P8_26;      // GPIO1_29

    // P9 Header - Free GPIOs
    extern HAL::PINS::GPMC_WAIT0& P9_11;     // GPIO0_30
    extern HAL::PINS::GPMC_BEn1& P9_12;      // GPIO1_28
    extern HAL::PINS::GPMC_WPn& P9_13;       // GPIO0_31
    extern HAL::PINS::GPMC_A2& P9_14;        // GPIO1_18
    extern HAL::PINS::GPMC_A0& P9_15;        // GPIO1_16
    extern HAL::PINS::GPMC_A3& P9_16;        // GPIO1_19
    extern HAL::PINS::GPMC_A1& P9_23;        // GPIO1_17
    extern HAL::PINS::GPMC_A5& P9_25;        // GPIO1_21 (USR0 LED)
    extern HAL::PINS::GPMC_A6& P9_27;        // GPIO1_22 (USR1 LED)
    extern HAL::PINS::GPMC_A7& P9_28;        // GPIO1_23 (USR2 LED)
    extern HAL::PINS::GPMC_A8& P9_30;        // GPIO1_24 (USR3 LED)
    extern HAL::PINS::XDMA_EVENT_INTR0& P9_41; // GPIO0_19
    extern HAL::PINS::ECAP0_IN_PWM0_OUT& P9_42; // GPIO0_7

    // ========================================================================
    // eQEP (Quadrature Encoder Pulse)
    // ========================================================================
    extern HAL::PINS::MII1_TXD1& EQEP0A_IN;      // GPIO0_21, P8.13? (Mode 5)
    extern HAL::PINS::MII1_TXD0& EQEP0B_IN;      // GPIO0_28, P8.12? (Mode 5)
    extern HAL::PINS::GPMC_A4& EQEP1A_IN;        // GPIO1_20, P9.15? (Mode 6)
    extern HAL::PINS::GPMC_A5& EQEP1B_IN;        // GPIO1_21, P9.25 (Mode 6)
    extern HAL::PINS::GPMC_AD12& EQEP2A_IN;      // GPIO1_12, P8.12 (Mode 4)
    extern HAL::PINS::GPMC_AD13& EQEP2B_IN;      // GPIO1_13, P8.11 (Mode 4)

    // ========================================================================
    // XDMA Event Intr
    // ========================================================================
    extern HAL::PINS::XDMA_EVENT_INTR0& XDMA_EVENT_INTR0; // GPIO0_19, P9.41
    extern HAL::PINS::XDMA_EVENT_INTR1& XDMA_EVENT_INTR1; // GPIO0_20

    // ========================================================================
    // USB
    // ========================================================================
    extern HAL::PINS::USB0_DRVVBUS& USB0_DRVVBUS; // GPIO0_18
    extern HAL::PINS::USB1_DRVVBUS& USB1_DRVVBUS; // GPIO3_13

    // ========================================================================
    // EMU (JTAG Debug)
    // ========================================================================
    extern HAL::PINS::EMU0& EMU0; // GPIO3_7
    extern HAL::PINS::EMU1& EMU1; // GPIO3_8
*/
    // ========================================================================
    // INITIALIZATION FUNCTIONS
    // ========================================================================

    void init_user_leds();
    void init_boot_button();
    void init_uart0();
    void init_i2c0();
    void init_all();

} // namespace Board

#endif //__BOARD_HPP