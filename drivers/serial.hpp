#ifndef __SERIAL_HPP
#define __SERIAL_HPP

#include <stdint.h>
#include "am335x_uart.hpp"
#include "am335x_intc.h"
#include "UART.hpp"
#include "CONTROL_MODULE.h"
#include "PRCM.h"



extern am335x_uart uart_0;
extern am335x_intc intc;

typedef void (*serial_user_callback)(char);

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

                                      module_state_t(REGS::UART::AM335x_UART_Type *uart_regs)
                                      : m_instance(*uart_regs),
                                        module_function(REGS::UART::MODE_DISABLE),
                                        config_mode(REGS::UART::OPERATIONAL_MODE),
                                        subconfig_mode(REGS::UART::MSR_SPR),
                                        enhanced_sts(REGS::UART::ENH_DISABLE) 
                                       {}

                                void  update();
    };

private:
                 REGS::UART::AM335x_UART_Type &m_instance;
                                  am335x_intc &m_INTC_module;
              REGS::PRCM::AM335x_CM_WKUP_Type &m_CM_WKUP_r;
REGS::CONTROL_MODULE::AM335x_CTRL_MODULE_Type &m_CM_r;
                               module_state_t  m_state; 

                        /* FOR CONFIG MODE REGISTERS SWITCHING */
                        REGS::UART::LCR_reg_t  m_LCR_before;
                                         void  m_save_LCR()    { m_LCR_before.reg = m_instance.LCR.reg; } 
                                         void  m_restore_LCR() { m_instance.LCR.reg = m_LCR_before.reg; } 

                   REGS::UART::IER_UART_reg_t  m_IER_before; 
                                         void  m_save_IER()    { m_IER_before.reg = m_instance.IER_UART.reg; } 
                                         void  m_restore_IER() { m_instance.IER_UART.reg = m_IER_before.reg; } 
                                         
                                   const char  m_hexchars[16];                  
public:
          serial(REGS::UART::AM335x_UART_Type *uart_regs);
          template<REGS::UART::AM335x_UART_Type *uart_regs>
          serial() {
            
          }
          template<typename UART_Type>
          serial() {
            
          }
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


serial new_serial = serial<AM335x_UART_0_BASE_t>();

extern serial serial_uart_0;



#endif //__SERIAL_HPP