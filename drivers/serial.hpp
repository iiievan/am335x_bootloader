#ifndef __SERIAL_HPP
#define __SERIAL_HPP

#include <stdint.h>
#include "am335x_uart.hpp"
#include "am335x_intc.h"
#include "CONTROL_MODULE.h"
#include "PRCM.h"


extern am335x_uart uart_0;
extern am335x_intc intc;

typedef void (*serial_user_callback)(char);

class serial
{

private:
                                  am335x_uart &m_UART_module;
                                  am335x_intc &m_INTC_module;
              REGS::PRCM::AM335x_CM_WKUP_Type &m_CM_WKUP_r;
REGS::CONTROL_MODULE::AM335x_CTRL_MODULE_Type &m_CM_r;                         
public:
          serial(am335x_uart& uart_module);
         ~serial();

    void  init(serial_user_callback usr_clb);
    void  putc(char c);
    void  puts(char* c);
    void  hexdump(uint32_t val); 
    char  getc(void);
};

extern serial serial_uart_0;



#endif //__SERIAL_HPP