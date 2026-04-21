#include "board.hpp"

namespace Board
{
    // ========================================================================
    // USER LEDs
    // ========================================================================
    HAL::PINS::GPMC_A5& USR0 = HAL::PINS::gpmc_a5;
    HAL::PINS::GPMC_A6& USR1 = HAL::PINS::gpmc_a6;
    HAL::PINS::GPMC_A7& USR2 = HAL::PINS::gpmc_a7;
    HAL::PINS::GPMC_A8& USR3 = HAL::PINS::gpmc_a8;

    // ========================================================================
    // BOOT BUTTON
    // ========================================================================
    HAL::PINS::GPMC_AD8& BOOT_BUTTON = HAL::PINS::gpmc_ad8;

    // ========================================================================
    // UART0
    // ========================================================================
    HAL::PINS::UART0_TXD& UART0_TX = HAL::PINS::uart0_txd;
    HAL::PINS::UART0_RXD& UART0_RX = HAL::PINS::uart0_rxd;

/*
    // ========================================================================
    // UART1
    // ========================================================================
    HAL::PINS::UART1_TXD& UART1_TX = HAL::PINS::uart1_txd;
    HAL::PINS::UART1_RXD& UART1_RX = HAL::PINS::uart1_rxd;

    // ========================================================================
    // UART2
    // ========================================================================
    HAL::PINS::LCD_DATA9& UART2_TX = HAL::PINS::lcd_data9;
    HAL::PINS::LCD_DATA8& UART2_RX = HAL::PINS::lcd_data8;

    // ========================================================================
    // UART4
    // ========================================================================
    HAL::PINS::GPMC_WAIT0& UART4_TX = HAL::PINS::gpmc_wait0;
    HAL::PINS::GPMC_WPn& UART4_RX = HAL::PINS::gpmc_wpn;

    // ========================================================================
    // UART5
    // ========================================================================
    HAL::PINS::LCD_DATA13& UART5_TX = HAL::PINS::lcd_data13;
    HAL::PINS::LCD_DATA12& UART5_RX = HAL::PINS::lcd_data12;

    // ========================================================================
    // I2C0
    // ========================================================================
    HAL::PINS::I2C0_SDA& I2C0_SDA = HAL::PINS::i2c0_sda;
    HAL::PINS::I2C0_SCL& I2C0_SCL = HAL::PINS::i2c0_scl;

    // ========================================================================
    // I2C1
    // ========================================================================
    HAL::PINS::SPI0_D1& I2C1_SDA = HAL::PINS::spi0_d1;
    HAL::PINS::SPI0_CS0& I2C1_SCL = HAL::PINS::spi0_cs0;

    // ========================================================================
    // I2C2
    // ========================================================================
    HAL::PINS::SPI0_D0& I2C2_SDA = HAL::PINS::spi0_d0;
    HAL::PINS::SPI0_SCLK& I2C2_SCL = HAL::PINS::spi0_sclk;

    // ========================================================================
    // SPI0
    // ========================================================================
    HAL::PINS::SPI0_SCLK& SPI0_SCLK = HAL::PINS::spi0_sclk;
    HAL::PINS::SPI0_D0& SPI0_D0 = HAL::PINS::spi0_d0;
    HAL::PINS::SPI0_D1& SPI0_D1 = HAL::PINS::spi0_d1;
    HAL::PINS::SPI0_CS0& SPI0_CS0 = HAL::PINS::spi0_cs0;

    // ========================================================================
    // SPI1
    // ========================================================================
    HAL::PINS::MCASP0_AHCLKR& SPI1_SCLK = HAL::PINS::mcasp0_ahclkr;
    HAL::PINS::MCASP0_ACLKR& SPI1_D0 = HAL::PINS::mcasp0_aclkr;
    HAL::PINS::MCASP0_FSR& SPI1_D1 = HAL::PINS::mcasp0_fsr;
    HAL::PINS::MCASP0_AHCLKX& SPI1_CS0 = HAL::PINS::mcasp0_ahclkx;

    // ========================================================================
    // PWM
    // ========================================================================
    HAL::PINS::SPI0_SCLK& EHRPWM0A = HAL::PINS::spi0_sclk;
    HAL::PINS::SPI0_D0& EHRPWM0B = HAL::PINS::spi0_d0;
    HAL::PINS::GPMC_A2& EHRPWM1A = HAL::PINS::gpmc_a2;
    HAL::PINS::GPMC_A3& EHRPWM1B = HAL::PINS::gpmc_a3;
    HAL::PINS::GPMC_AD8& EHRPWM2A = HAL::PINS::gpmc_ad8;
    HAL::PINS::GPMC_AD9& EHRPWM2B = HAL::PINS::gpmc_ad9;

    HAL::PINS::ECAP0_IN_PWM0_OUT& ECAP0_IN_PWM0_OUT = HAL::PINS::ecap0_in_pwm0_out;
    HAL::PINS::UART0_TXD& ECAP1_IN_PWM1_OUT = HAL::PINS::uart0_txd;
    HAL::PINS::UART0_RXD& ECAP2_IN_PWM2_OUT = HAL::PINS::uart0_rxd;

    // ========================================================================
    // CAN
    // ========================================================================
    HAL::PINS::UART0_RXD& DCAN0_TX = HAL::PINS::uart0_rxd;
    HAL::PINS::UART0_TXD& DCAN0_RX = HAL::PINS::uart0_txd;
    HAL::PINS::UART0_CTSn& DCAN1_TX = HAL::PINS::uart0_ctsn;
    HAL::PINS::UART0_RTSn& DCAN1_RX = HAL::PINS::uart0_rtsn;

    // ========================================================================
    // FREE GPIOs - P8
    // ========================================================================
    HAL::PINS::GPMC_ADVn_ALE& P8_07 = HAL::PINS::gpmc_advn_ale;
    HAL::PINS::GPMC_OEn_REn& P8_08 = HAL::PINS::gpmc_oen_ren;
    HAL::PINS::GPMC_WEn& P8_09 = HAL::PINS::gpmc_wen;
    HAL::PINS::GPMC_BEn0_CLE& P8_10 = HAL::PINS::gpmc_ben0_cle;
    HAL::PINS::GPMC_AD13& P8_11 = HAL::PINS::gpmc_ad13;
    HAL::PINS::GPMC_AD12& P8_12 = HAL::PINS::gpmc_ad12;
    HAL::PINS::GPMC_BEn1& P8_13 = HAL::PINS::gpmc_ben1;
    HAL::PINS::GPMC_AD10& P8_14 = HAL::PINS::gpmc_ad10;
    HAL::PINS::GPMC_AD15& P8_15 = HAL::PINS::gpmc_ad15;
    HAL::PINS::GPMC_AD14& P8_16 = HAL::PINS::gpmc_ad14;
    HAL::PINS::GPMC_AD11& P8_17 = HAL::PINS::gpmc_ad11;
    HAL::PINS::GPMC_WAIT0& P8_18 = HAL::PINS::gpmc_wait0;
    HAL::PINS::GPMC_WPn& P8_19 = HAL::PINS::gpmc_wpn;
    HAL::PINS::GPMC_CSn0& P8_26 = HAL::PINS::gpmc_csn0;

    // ========================================================================
    // FREE GPIOs - P9
    // ========================================================================
    HAL::PINS::GPMC_WAIT0& P9_11 = HAL::PINS::gpmc_wait0;
    HAL::PINS::GPMC_BEn1& P9_12 = HAL::PINS::gpmc_ben1;
    HAL::PINS::GPMC_WPn& P9_13 = HAL::PINS::gpmc_wpn;
    HAL::PINS::GPMC_A2& P9_14 = HAL::PINS::gpmc_a2;
    HAL::PINS::GPMC_A0& P9_15 = HAL::PINS::gpmc_a0;
    HAL::PINS::GPMC_A3& P9_16 = HAL::PINS::gpmc_a3;
    HAL::PINS::GPMC_A1& P9_23 = HAL::PINS::gpmc_a1;
    HAL::PINS::GPMC_A5& P9_25 = HAL::PINS::gpmc_a5;
    HAL::PINS::GPMC_A6& P9_27 = HAL::PINS::gpmc_a6;
    HAL::PINS::GPMC_A7& P9_28 = HAL::PINS::gpmc_a7;
    HAL::PINS::GPMC_A8& P9_30 = HAL::PINS::gpmc_a8;
    HAL::PINS::XDMA_EVENT_INTR0& P9_41 = HAL::PINS::xdma_event_intr0;
    HAL::PINS::ECAP0_IN_PWM0_OUT& P9_42 = HAL::PINS::ecap0_in_pwm0_out;

    // ========================================================================
    // eQEP
    // ========================================================================
    HAL::PINS::MII1_TXD1& EQEP0A_IN = HAL::PINS::mii1_txd1;
    HAL::PINS::MII1_TXD0& EQEP0B_IN = HAL::PINS::mii1_txd0;
    HAL::PINS::GPMC_A4& EQEP1A_IN = HAL::PINS::gpmc_a4;
    HAL::PINS::GPMC_A5& EQEP1B_IN = HAL::PINS::gpmc_a5;
    HAL::PINS::GPMC_AD12& EQEP2A_IN = HAL::PINS::gpmc_ad12;
    HAL::PINS::GPMC_AD13& EQEP2B_IN = HAL::PINS::gpmc_ad13;

    // ========================================================================
    // XDMA
    // ========================================================================
    HAL::PINS::XDMA_EVENT_INTR0& XDMA_EVENT_INTR0 = HAL::PINS::xdma_event_intr0;
    HAL::PINS::XDMA_EVENT_INTR1& XDMA_EVENT_INTR1 = HAL::PINS::xdma_event_intr1;

    // ========================================================================
    // USB
    // ========================================================================
    HAL::PINS::USB0_DRVVBUS& USB0_DRVVBUS = HAL::PINS::usb0_drvvbus;
    HAL::PINS::USB1_DRVVBUS& USB1_DRVVBUS = HAL::PINS::usb1_drvvbus;

    // ========================================================================
    // EMU
    // ========================================================================
    HAL::PINS::EMU0& EMU0 = HAL::PINS::emu0;
    HAL::PINS::EMU1& EMU1 = HAL::PINS::emu1;
*/
    // ========================================================================
    // INITIALIZATION FUNCTIONS
    // ========================================================================

    void init_user_leds()
    {
        USR0.configure_as_gpio_output(HAL::PINS::e_GPMC_A5::gpio1_21);
        USR1.configure_as_gpio_output(HAL::PINS::e_GPMC_A6::gpio1_22);
        USR2.configure_as_gpio_output(HAL::PINS::e_GPMC_A7::gpio1_23);
        USR3.configure_as_gpio_output(HAL::PINS::e_GPMC_A8::gpio1_24);

        USR0.clear();
        USR1.clear();
        USR2.clear();
        USR3.clear();
    }

    void init_boot_button()
    {
        BOOT_BUTTON.configure_as_gpio_input(HAL::PINS::e_GPMC_AD8::gpio0_22);
    }

    void init_uart0()
    {
        //UART0_TX.configure_pinmux(HAL::PINS::e_UART0_TXD::uart0_txd);
        //UART0_RX.configure_pinmux(HAL::PINS::e_UART0_RXD::uart0_rxd);
    }

    void init_i2c0()
    {
        //I2C0_SDA.configure_pinmux(HAL::PINS::e_I2C0_SDA::i2c0_sda);
        //I2C0_SCL.configure_pinmux(HAL::PINS::e_I2C0_SCL::i2c0_scl);
    }

    void init_all()
    {
        init_user_leds();
        init_boot_button();
        init_uart0();
        init_i2c0();
    }

} // namespace Board