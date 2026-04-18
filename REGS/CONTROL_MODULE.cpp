#include "CONTROL_MODULE.hpp"

namespace REGS
{  
    namespace CONTROL_MODULE
    {                      
        void  AM335x_CTRL_MODULE_Type::I2C0_pin_mux_setup()
        {    
            conf_i2c0_sda.b.putypesel = PULL_UP;
            conf_i2c0_sda.b.rxactive  = INPUT_ENABLE;
            conf_i2c0_sda.b.slewctrl  = SLOW;
        
            conf_i2c0_scl.b.putypesel = PULL_UP;
            conf_i2c0_scl.b.rxactive  = INPUT_ENABLE;
            conf_i2c0_scl.b.slewctrl  = SLOW;
        }
    
        void  AM335x_CTRL_MODULE_Type::I2C1_pin_mux_setup()
        {
            /** I2C_SCLK **/
            conf_spi0_d1.b.putypesel  = PULL_UP;
            conf_spi0_d1.b.rxactive   = INPUT_ENABLE;
            conf_spi0_d1.b.slewctrl   = SLOW;
            conf_spi0_d1.b.mode       = PINMODE_2;
           
            /** I2C_SDA **/
            conf_spi0_cs0.b.putypesel = PULL_UP;
            conf_spi0_cs0.b.rxactive  = INPUT_ENABLE;
            conf_spi0_cs0.b.slewctrl  = SLOW;
            conf_spi0_cs0.b.mode      = PINMODE_2;
        }
    
        void  AM335x_CTRL_MODULE_Type::I2C2_pin_mux_setup()
        {
            /** I2C_SCLK **/ 
            conf_uart1_rtsn.b.putypesel = PULL_UP;
            conf_uart1_rtsn.b.rxactive  = INPUT_ENABLE;
            conf_uart1_rtsn.b.slewctrl  = SLOW;
            conf_uart1_rtsn.b.mode      = PINMODE_3;
           
            /** I2C_SDA **/ 
            conf_uart1_ctsn.b.putypesel = PULL_UP;
            conf_uart1_ctsn.b.rxactive  = INPUT_ENABLE;
            conf_uart1_ctsn.b.slewctrl  = SLOW;
            conf_uart1_ctsn.b.mode      = PINMODE_3;
        }
    
        void  AM335x_CTRL_MODULE_Type::UART0_pin_mux_setup()
        {
           /** RXD **/
           conf_uart0_rxd.b.putypesel = PULL_UP;
           conf_uart0_rxd.b.rxactive = INPUT_ENABLE;
            
           /** TXD **/
           conf_uart0_txd.b.putypesel = PULL_UP;
        }

    }   //namespace CONTROL_MODULE
    
}   //namespace REGS

