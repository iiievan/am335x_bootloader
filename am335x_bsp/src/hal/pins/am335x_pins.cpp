
#include "stdint.h"
#include "hal/pins/am3359_pins.hpp"
#include "regs/REGS.hpp"
#include "hal/pins/pin.hpp"


namespace HAL::PINS
{
    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    class pin;


     //MDIO mdio{REGS::GPIO::AM335x_GPIO_0};                              // gpio0_0
     //MDC mdc{REGS::GPIO::AM335x_GPIO_0};                                // gpio0_1
     //SPI0_SCLK spi0_sclk{REGS::GPIO::AM335x_GPIO_0};                    // gpio0_2
     //SPI0_D0 spi0_d0{REGS::GPIO::AM335x_GPIO_0};                        // gpio0_3
     //SPI0_D1 spi0_d1{REGS::GPIO::AM335x_GPIO_0};                        // gpio0_4
     //SPI0_CS0 spi0_cs0{REGS::GPIO::AM335x_GPIO_0};                      // gpio0_5
     //SPI0_CS1 spi0_cs1{REGS::GPIO::AM335x_GPIO_0};                      // gpio0_6
     //ECAP0_IN_PWM0_OUT ecap0_in_pwm0_out{REGS::GPIO::AM335x_GPIO_0};    // gpio0_7
     //LCD_DATA12 lcd_data12{REGS::GPIO::AM335x_GPIO_0};                  // gpio0_8
     //LCD_DATA13 lcd_data13{REGS::GPIO::AM335x_GPIO_0};                  // gpio0_9
     //LCD_DATA14 lcd_data14{REGS::GPIO::AM335x_GPIO_0};                  // gpio0_10
     //LCD_DATA15 lcd_data15{REGS::GPIO::AM335x_GPIO_0};                  // gpio0_11
     //UART1_CTSn uart1_ctsn{REGS::GPIO::AM335x_GPIO_0};                  // gpio0_12
     //UART1_RTSn uart1_rtsn{REGS::GPIO::AM335x_GPIO_0};                  // gpio0_13
     UART1_RXD uart1_rxd{REGS::GPIO::AM335x_GPIO_0};                    // gpio0_14
     UART1_TXD uart1_txd{REGS::GPIO::AM335x_GPIO_0};                    // gpio0_15
     //MII1_TXD3 mii1_txd3{REGS::GPIO::AM335x_GPIO_0};                    // gpio0_16
     //MII1_TXD2 mii1_txd2{REGS::GPIO::AM335x_GPIO_0};                    // gpio0_17
     //USB0_DRVVBUS usb0_drvvbus{REGS::GPIO::AM335x_GPIO_0};              // gpio0_18
     //XDMA_EVENT_INTR0 xdma_event_intr0{REGS::GPIO::AM335x_GPIO_0};      // gpio0_19
     //XDMA_EVENT_INTR1 xdma_event_intr1{REGS::GPIO::AM335x_GPIO_0};      // gpio0_20
     //MII1_TXD1 mii1_txd1{REGS::GPIO::AM335x_GPIO_0};                    // gpio0_21
     GPMC_AD8 gpmc_ad8{REGS::GPIO::AM335x_GPIO_0};                      // gpio0_22
     //GPMC_AD9 gpmc_ad9{REGS::GPIO::AM335x_GPIO_0};                      // gpio0_23
     //GPMC_AD10 gpmc_ad10{REGS::GPIO::AM335x_GPIO_0};                    // gpio0_26
     //GPMC_AD11 gpmc_ad11{REGS::GPIO::AM335x_GPIO_0};                    // gpio0_27
     //MII1_TXD0 mii1_txd0{REGS::GPIO::AM335x_GPIO_0};                    // gpio0_28
     //RMII1_REF_CLK rmii1_ref_clk{REGS::GPIO::AM335x_GPIO_0};            // gpio0_29
     //GPMC_WAIT0 gpmc_wait0{REGS::GPIO::AM335x_GPIO_0};                  // gpio0_30
     //GPMC_WPn gpmc_wpn{REGS::GPIO::AM335x_GPIO_0};                      // gpio0_31


     //GPMC_AD0 gpmc_ad0{REGS::GPIO::AM335x_GPIO_1};      // gpio1_0
     //GPMC_AD1 gpmc_ad1{REGS::GPIO::AM335x_GPIO_1};      // gpio1_1
     //GPMC_AD2 gpmc_ad2{REGS::GPIO::AM335x_GPIO_1};      // gpio1_2
     //GPMC_AD3 gpmc_ad3{REGS::GPIO::AM335x_GPIO_1};      // gpio1_3
     //GPMC_AD4 gpmc_ad4{REGS::GPIO::AM335x_GPIO_1};      // gpio1_4
     //GPMC_AD5 gpmc_ad5{REGS::GPIO::AM335x_GPIO_1};      // gpio1_5
     //GPMC_AD6 gpmc_ad6{REGS::GPIO::AM335x_GPIO_1};      // gpio1_6
     //GPMC_AD7 gpmc_ad7{REGS::GPIO::AM335x_GPIO_1};      // gpio1_7
     //UART0_CTSn uart0_ctsn{REGS::GPIO::AM335x_GPIO_1};  // gpio1_8
     //UART0_RTSn uart0_rtsn{REGS::GPIO::AM335x_GPIO_1};  // gpio1_9
     UART0_RXD uart0_rxd{REGS::GPIO::AM335x_GPIO_1};    // gpio1_10
     UART0_TXD uart0_txd{REGS::GPIO::AM335x_GPIO_1};    // gpio1_11
     //GPMC_AD12 gpmc_ad12{REGS::GPIO::AM335x_GPIO_1};    // gpio1_12
     //GPMC_AD13 gpmc_ad13{REGS::GPIO::AM335x_GPIO_1};    // gpio1_13
     //GPMC_AD14 gpmc_ad14{REGS::GPIO::AM335x_GPIO_1};    // gpio1_14
     //GPMC_AD15 gpmc_ad15{REGS::GPIO::AM335x_GPIO_1};    // gpio1_15
     //GPMC_A0 gpmc_a0{REGS::GPIO::AM335x_GPIO_1};        // gpio1_16
     //GPMC_A1 gpmc_a1{REGS::GPIO::AM335x_GPIO_1};        // gpio1_17
     //GPMC_A2 gpmc_a2{REGS::GPIO::AM335x_GPIO_1};        // gpio1_18
     //GPMC_A3 gpmc_a3{REGS::GPIO::AM335x_GPIO_1};        // gpio1_19
     //GPMC_A4 gpmc_a4{REGS::GPIO::AM335x_GPIO_1};        // gpio1_20
     GPMC_A5 gpmc_a5{REGS::GPIO::AM335x_GPIO_1};        // gpio1_21
     GPMC_A6 gpmc_a6{REGS::GPIO::AM335x_GPIO_1};        // gpio1_22
     GPMC_A7 gpmc_a7{REGS::GPIO::AM335x_GPIO_1};        // gpio1_23
     GPMC_A8 gpmc_a8{REGS::GPIO::AM335x_GPIO_1};        // gpio1_24
     //GPMC_A9 gpmc_a9{REGS::GPIO::AM335x_GPIO_1};        // gpio1_25
     //GPMC_A10 gpmc_a10{REGS::GPIO::AM335x_GPIO_1};      // gpio1_26
     //GPMC_A11 gpmc_a11{REGS::GPIO::AM335x_GPIO_1};      // gpio1_27
     //GPMC_BEn1 gpmc_ben1{REGS::GPIO::AM335x_GPIO_1};    // gpio1_28
     //GPMC_CSn0 gpmc_csn0{REGS::GPIO::AM335x_GPIO_1};    // gpio1_29
     //GPMC_CSn1 gpmc_csn1{REGS::GPIO::AM335x_GPIO_1};    // gpio1_30
     //GPMC_CSn2 gpmc_csn2{REGS::GPIO::AM335x_GPIO_1};    // gpio1_31


     //GPMC_CSn3 gpmc_csn3{REGS::GPIO::AM335x_GPIO_2};            // gpio2_0
     //GPMC_CLK gpmc_clk{REGS::GPIO::AM335x_GPIO_2};              // gpio2_1
     //GPMC_ADVn_ALE gpmc_advn_ale{REGS::GPIO::AM335x_GPIO_2};    // gpio2_2
     //GPMC_OEn_REn gpmc_oen_ren{REGS::GPIO::AM335x_GPIO_2};      // gpio2_3
     //GPMC_WEn gpmc_wen{REGS::GPIO::AM335x_GPIO_2};              // gpio2_4
     //GPMC_BEn0_CLE gpmc_ben0_cle{REGS::GPIO::AM335x_GPIO_2};    // gpio2_5
     //LCD_DATA0 lcd_data0{REGS::GPIO::AM335x_GPIO_2};            // gpio2_6
     //LCD_DATA1 lcd_data1{REGS::GPIO::AM335x_GPIO_2};            // gpio2_7
     //LCD_DATA2 lcd_data2{REGS::GPIO::AM335x_GPIO_2};            // gpio2_8
     //LCD_DATA3 lcd_data3{REGS::GPIO::AM335x_GPIO_2};            // gpio2_9
     //LCD_DATA4 lcd_data4{REGS::GPIO::AM335x_GPIO_2};            // gpio2_10
     //LCD_DATA5 lcd_data5{REGS::GPIO::AM335x_GPIO_2};            // gpio2_11
     //LCD_DATA6 lcd_data6{REGS::GPIO::AM335x_GPIO_2};            // gpio2_12
     //LCD_DATA7 lcd_data7{REGS::GPIO::AM335x_GPIO_2};            // gpio2_13
     //LCD_DATA8 lcd_data8{REGS::GPIO::AM335x_GPIO_2};            // gpio2_14
     //LCD_DATA9 lcd_data9{REGS::GPIO::AM335x_GPIO_2};            // gpio2_15
     //LCD_DATA10 lcd_data10{REGS::GPIO::AM335x_GPIO_2};          // gpio2_16
     //LCD_DATA11 lcd_data11{REGS::GPIO::AM335x_GPIO_2};          // gpio2_17
     //MII1_RXD3 mii1_rxd3{REGS::GPIO::AM335x_GPIO_2};            // gpio2_18
     //MII1_RXD2 mii1_rxd2{REGS::GPIO::AM335x_GPIO_2};            // gpio2_19
     //MII1_RXD1 mii1_rxd1{REGS::GPIO::AM335x_GPIO_2};            // gpio2_20
     //MII1_RXD0 mii1_rxd0{REGS::GPIO::AM335x_GPIO_2};            // gpio2_21
     //LCD_VSYNC lcd_vsync{REGS::GPIO::AM335x_GPIO_2};            // gpio2_22
     //LCD_HSYNC lcd_hsync{REGS::GPIO::AM335x_GPIO_2};            // gpio2_23
     //LCD_PCLK lcd_pclk{REGS::GPIO::AM335x_GPIO_2};              // gpio2_24
     //LCD_AC_BIAS_EN lcd_ac_bias_en{REGS::GPIO::AM335x_GPIO_2};  // gpio2_25
     //MMC0_DAT3 mmc0_dat3{REGS::GPIO::AM335x_GPIO_2};            // gpio2_26
     //MMC0_DAT2 mmc0_dat2{REGS::GPIO::AM335x_GPIO_2};            // gpio2_27
     //MMC0_DAT1 mmc0_dat1{REGS::GPIO::AM335x_GPIO_2};            // gpio2_28
     //MMC0_DAT0 mmc0_dat0{REGS::GPIO::AM335x_GPIO_2};            // gpio2_29
     //MMC0_CLK mmc0_clk{REGS::GPIO::AM335x_GPIO_2};              // gpio2_30
     //MMC0_CMD mmc0_cmd{REGS::GPIO::AM335x_GPIO_2};              // gpio2_31


     //MII1_COL mii1_col{REGS::GPIO::AM335x_GPIO_3};              // gpio3_0
     //MII1_CRS mii1_crs{REGS::GPIO::AM335x_GPIO_3};              // gpio3_1
     //MII1_RX_ER mii1_rx_er{REGS::GPIO::AM335x_GPIO_3};          // gpio3_2
     //MII1_TX_EN mii1_tx_en{REGS::GPIO::AM335x_GPIO_3};          // gpio3_3
     //MII1_RX_DV mii1_rx_dv{REGS::GPIO::AM335x_GPIO_3};          // gpio3_4
     //I2C0_SDA i2c0_sda{REGS::GPIO::AM335x_GPIO_3};              // gpio3_5
     //I2C0_SCL i2c0_scl{REGS::GPIO::AM335x_GPIO_3};              // gpio3_6
     //EMU0 emu0{REGS::GPIO::AM335x_GPIO_3};                      // gpio3_7
     //EMU1 emu1{REGS::GPIO::AM335x_GPIO_3};                      // gpio3_8
     //MII1_TX_CLK mii1_tx_clk{REGS::GPIO::AM335x_GPIO_3};        // gpio3_9
     //MII1_RX_CLK mii1_rx_clk{REGS::GPIO::AM335x_GPIO_3};        // gpio3_10
     //USB1_DRVVBUS usb1_drvvbus{REGS::GPIO::AM335x_GPIO_3};      // gpio3_13
     //MCASP0_ACLKX mcasp0_aclkx{REGS::GPIO::AM335x_GPIO_3};      // gpio3_14
     //MCASP0_FSX mcasp0_fsx{REGS::GPIO::AM335x_GPIO_3};          // gpio3_15
     //MCASP0_AXR0 mcasp0_axr0{REGS::GPIO::AM335x_GPIO_3};        // gpio3_16
     //MCASP0_AHCLKR mcasp0_ahclkr{REGS::GPIO::AM335x_GPIO_3};    // gpio3_17
     //MCASP0_ACLKR mcasp0_aclkr{REGS::GPIO::AM335x_GPIO_3};      // gpio3_18
     //MCASP0_FSR mcasp0_fsr{REGS::GPIO::AM335x_GPIO_3};          // gpio3_19
     //MCASP0_AXR1 mcasp0_axr1{REGS::GPIO::AM335x_GPIO_3};        // gpio3_20
     //MCASP0_AHCLKX mcasp0_ahclkx{REGS::GPIO::AM335x_GPIO_3};    // gpio3_21

} // namespace HAL::PINS
