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

private:
                                  am335x_uart &m_UART_module;
                 REGS::UART::AM335x_UART_Type &m_instance;
                                  am335x_intc &m_INTC_module;
              REGS::PRCM::AM335x_CM_WKUP_Type &m_CM_WKUP_r;
REGS::CONTROL_MODULE::AM335x_CTRL_MODULE_Type &m_CM_r; 

                        /* FOR CONFIG MODE REGISTERS SWITCHING */
                        REGS::UART::LCR_reg_t  m_LCR_before;
                                         void  m_save_LCR()    { m_LCR_before.reg = m_instance.LCR.reg; } 
                                         void  m_restore_LCR() { m_instance.LCR.reg = m_LCR_before.reg; } 

                     REGS::UART::e_MODESELECT  m_mode_before; 
                                         void  m_save_opmode()    { m_mode_before = (REGS::UART::e_MODESELECT)m_instance.MDR1.b.MODESELECT; } 
                                         void  m_restore_opmode() { m_instance.MDR1.b.MODESELECT = m_mode_before; } 

                   REGS::UART::IER_UART_reg_t  m_IER_before; 
                                         void  m_save_IER()    { m_IER_before.reg = m_instance.IER_UART.reg; } 
                                         void  m_restore_IER() { m_instance.IER_UART.reg = m_IER_before.reg; } 
                                         
                                   const char  m_hexchars[16];                  
public:
          serial(REGS::UART::AM335x_UART_Type *uart_regs);
         ~serial();

    /// <--- Start module init ---> ///
    void  reset_module();
    void  resume_operation();
    void  init(serial_user_callback usr_clb);
    void  initW(serial_user_callback usr_clb);

    /// <--- FIFO management methods TRM 19.3 ---> ///

    /// <--- Mode select methods  TRM 19.3 ---> ///
    void  switch_operating_mode(REGS::UART::e_MODESELECT mode);
    void  switch_reg_config_mode(REGS::UART::e_CONFIG_MODE mode, REGS::UART::e_ENH enh);
    void  switch_reg_subconfig_mode(REGS::UART::e_SUBCONFIG_MODE mode);

    /// <--- Protocol formating methods TRM 19.3 ---> ///
    ///  1. Clock generation setup:
    ///  2. Data formating setup:
    ///  3. Interrupt management: 

    /// <--- Power management methods ---> ///
    void  idle_mode_configure(REGS::UART::e_IDLEMODE mode);
    void  wakeup_control(bool control);
    void  auto_idle_mode_control(bool control);
    void  sleep(bool control);

    /// <--- Other management methods ---> ///
    void  modem_control_set(REGS::UART::MCR_reg_t mcr);

    void  putc(char c);
    void  puts(char* c);
    void  hexdump(uint32_t val); 
    char  getc(void);
};

extern serial serial_uart_0;



#endif //__SERIAL_HPP