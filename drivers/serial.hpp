#ifndef __SERIAL_HPP
#define __SERIAL_HPP

#include <stdint.h>
#include "am335x_uart.hpp"
#include "am335x_intc.h"
#include "UART.hpp"
#include "PRCM.h"
#include "am3358zcz_pins.hpp"
#include "pin.h"

extern am335x_intc intc;

typedef void (*serial_user_callback)(char);

template <REGS::UART::e_UART_modules uart_module>
struct uart_pins;

template <>
struct uart_pins<REGS::UART::UART_0>
{
    using rx_pin = PINS::pin<PINS::e_UART0_RXD,  10U, 0x970>;
    using tx_pin = PINS::pin<PINS::e_UART0_TXD,  11U, 0x974>;
    using pinmode_rx_t = PINS::e_UART0_RXD;
    using pinmode_tx_t = PINS::e_UART0_TXD;
    static constexpr auto pinmode_rx = PINS::e_UART0_RXD::uart0_rxd;
    static constexpr auto pinmode_tx = PINS::e_UART0_TXD::uart0_txd;
    static constexpr auto gpio_regs = REGS::GPIO::AM335x_GPIO_1;
    static constexpr auto uart_regs = REGS::UART::AM335X_UART_0;
};

template <>
struct uart_pins<REGS::UART::UART_1>
{
    using rx_pin = PINS::pin<PINS::e_UART1_RXD, 14U, 0x980>;
    using tx_pin = PINS::pin<PINS::e_UART1_TXD, 15U, 0x984>;
    using pinmode_rx_t = PINS::e_UART1_RXD;
    using pinmode_tx_t = PINS::e_UART1_TXD;
    static constexpr auto pinmode_rx = PINS::e_UART1_RXD::uart1_rxd;
    static constexpr auto pinmode_tx = PINS::e_UART1_TXD::uart1_txd;
    static constexpr auto gpio_regs = REGS::GPIO::AM335x_GPIO_0;
    static constexpr auto uart_regs = REGS::UART::AM335X_UART_1;
    
};

template <REGS::UART::e_UART_modules uart_module>
class serial
{
    class module_state_t
    {
    private:
        REGS::UART::AM335x_UART_Type &m_instance;
    public:
        
            REGS::UART::e_MODESELECT  module_function;
           REGS::UART::e_CONFIG_MODE  config_mode;
        REGS::UART::e_SUBCONFIG_MODE  subconfig_mode;
                   REGS::UART::e_ENH  enhanced_sts;
    
                                      module_state_t(REGS::UART::AM335x_UART_Type * p_regs);
                                void  update();
    };

private:
                 REGS::UART::AM335x_UART_Type &m_instance;
                                  am335x_intc &m_INTC_module;
              REGS::PRCM::AM335x_CM_WKUP_Type &m_CM_WKUP_r;
                               module_state_t  m_state;

            typename uart_pins<uart_module>::rx_pin  m_rx_pin;
const typename uart_pins<uart_module>::pinmode_rx_t  m_rx_pinmode {uart_pins<uart_module>::pinmode_rx};
            typename uart_pins<uart_module>::tx_pin  m_tx_pin;
const typename uart_pins<uart_module>::pinmode_tx_t  m_tx_pinmode {uart_pins<uart_module>::pinmode_tx};

                        /* FOR CONFIG MODE REGISTERS SWITCHING */
                        REGS::UART::LCR_reg_t  m_LCR_before;
                                         void  m_save_LCR()    { m_LCR_before.reg = m_instance.LCR.reg; } 
                                         void  m_restore_LCR() { m_instance.LCR.reg = m_LCR_before.reg; } 

                   REGS::UART::IER_UART_reg_t  m_IER_before; 
                                         void  m_save_IER()    { m_IER_before.reg = m_instance.IER_UART.reg; } 
                                         void  m_restore_IER() { m_instance.IER_UART.reg = m_IER_before.reg; } 
                                         
                                   const char  m_hexchars[16];                  
public:
          serial();
         ~serial();

    /// <--- Start module init ---> ///
    void  reset_module(void);
    void  resume_operation(void);
    void  init(serial_user_callback usr_clb);

    /// <--- FIFO management methods TRM 19.3 ---> ///
    void  FIFO_register_write(REGS::UART::FCR_reg_t  fcr);

    /// <--- Mode select methods  TRM 19.3 ---> ///
    void  switch_operating_mode(REGS::UART::e_MODESELECT mode);
    void  switch_reg_config_mode(REGS::UART::e_CONFIG_MODE mode, REGS::UART::e_ENH enh);
    void  switch_reg_subconfig_mode(REGS::UART::e_SUBCONFIG_MODE mode);

    /// <--- Protocol formating methods TRM 19.3 ---> ///
    ///  1. Clock generation setup:
    REGS::UART::divisor_latch  divisor_latch_get(void);
    void  divisor_latch_set(REGS::UART::divisor_latch divisor);
    void  divisor_latch_enable();
    void  divisor_latch_disable();

    ///  2. Data formating setup:
    void  data_format_set(REGS::UART::e_CHAR_LENGHT  char_len,
                             REGS::UART::e_STOP_BIT  stop_bit,
                           REGS::UART::e_LCR_PARITY  parity);

    ///  3. Interrupt management: 
    void  int_enable(REGS::UART::e_UART_IT_EN int_flag);
    void  int_disable(REGS::UART::e_UART_IT_EN int_flag);

    /// <--- Power management methods ---> ///
    void  idle_mode_configure(REGS::UART::e_IDLEMODE mode);
    void  wakeup_control(bool control);
    void  auto_idle_mode_control(bool control);
    void  sleep(bool control);

    /// <--- Other features---> ///
    void  modem_control_set(REGS::UART::MCR_reg_t mcr);

    void  putc(char c);
    void  puts(char* c);
    void  hexdump(uint32_t val); 
    char  getc(void);
};

template class  serial<REGS::UART::UART_0>;
template class  serial<REGS::UART::UART_1>;


#endif //__SERIAL_HPP