#include "serial.hpp"

static void uart_isr(void *p_obj);
static serial_user_callback m_user_callback = NULL;

serial::serial(am335x_uart& uart_module)
: m_UART_module(uart_module),
  m_INTC_module(intc),
  m_CM_WKUP_r(*REGS::PRCM::AM335x_CM_WKUP),
  m_CM_r(*REGS::CONTROL_MODULE::AM335x_CONTROL_MODULE)
{ 

}

serial::~serial()
{

}

/* @brief initialize UART0 peripheral and set it up for polling I/O
 * @param callback: user defined RX callback function;
 */
void serial::init(serial_user_callback usr_clb) 
{  
    // Enable UART0 functional clock [AM335x TRM 1284] 
    m_CM_WKUP_r.UART0_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_DISABLED; // clear MODULEMODE
    m_CM_WKUP_r.UART0_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_ENABLE;   // enable MODULEMODE
     // poll idle status waiting for fully enabled
    while(m_CM_WKUP_r.UART0_CLKCTRL.b.IDLEST != REGS::PRCM::IDLEST_FUNC);  
    
    // Enable UART0 interface clock l4_wkup
    m_CM_WKUP_r.L4WKUP_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_DISABLED;
    m_CM_WKUP_r.L4WKUP_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_ENABLE;
    // poll idle status waiting for fully enabled   
    while(m_CM_WKUP_r.L4WKUP_CLKCTRL.b.IDLEST != REGS::PRCM::IDLEST_FUNC);
    
    // Control module pin muxing 
    // RXD 
    m_CM_r.conf_uart0_rxd.b.putypesel = REGS::CONTROL_MODULE::PULL_UP;
    m_CM_r.conf_uart0_rxd.b.rxactive = REGS::CONTROL_MODULE::INPUT_ENABLE;
              
     // TXD
     m_CM_r.conf_uart0_txd.b.putypesel = REGS::CONTROL_MODULE::PULL_UP;
    
     // UART software reset    
     m_UART_module.module_reset();
     m_UART_module.idle_mode_configure(REGS::UART::NO_IDLE);
    
    // Disable UART to access protocol, baud rate, interrupt settings 
     m_UART_module.operating_mode_select(REGS::UART::MODE_DISABLE);
    
    // switch to register configuration mode A 
    m_UART_module.reg_config_mode_enable(REGS::UART::CONFIG_MODE_A);
    
    // disable modem control 
    m_UART_module.modem_control_set(0x00);  // TODO: take break here!!!!
    
    // enable FIFO 
    REGS::UART::FCR_reg_t FCR_reg;
    FCR_reg.reg = 0x07;
    m_UART_module.FIFO_register_write(FCR_reg);   // TODO: take break here!!!!*/
    
    
    // set protocol formatting 
    // no parity, 1 stop bit, 8 bit chars 
    m_UART_module.char_len_config(REGS::UART::CHL_8_BITS);
    m_UART_module.stop_bit_config(REGS::UART::STOP_1);
    m_UART_module.parity_config(REGS::UART::PARITY_NONE);
    
    // load divisor values to achieve baud rate of 115200 
    // [AM335x TRM table 19-25] for divisor values
    m_UART_module.divisor_latch_write(0x001A);  
    m_UART_module.divisor_latch_disable();
    
    // enable RHR interrupt 
    m_UART_module.int_enable(REGS::UART::RECEIVE_IT);
    
    // mode select 
    m_UART_module.operating_mode_select(REGS::UART::MODE_UART_16x);
    
    m_UART_module.resume_operation();
    
    m_user_callback = usr_clb;
    
    // register UART ISR
    m_INTC_module.register_handler(REGS::INTC::UART0INT, uart_isr);
    
    // unmask UART0 interrupt
    m_INTC_module.unmask_interrupt(REGS::INTC::UART0INT);
}

/* @brief write char out to UART. blocks if Tx FIFO is full
 * @param 'c': input ascii symbol;
 */
void serial::putc(char c) 
{
    m_UART_module.char_put((uint8_t)c);
}

/* @brief print out null terminated string
 * @param 'c': input pointer on ascii symbol array;
 */
void serial::puts(char* c) 
{
    uint32_t i = 0;
    
    while (c[i] != '\0') 
    {
        putc(c[i]);
        i++;
    }
}

static const char hexchars[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
 
/* @brief utility to print out a 32 bit value
 * @param 'val': value to format to hex - not more 4 bytes lenght;
 */
void serial::hexdump(uint32_t val) 
{
    int32_t i;
    putc('0');
    putc('x');
    
    // print out all eight hex digits
    for (i = 7; i >= 0; i--) 
    {
        putc(hexchars[(val >> (i * 4)) & 0xF]);
    }
}

/* @brief poll for new character from UART, returns 0 if Rx FIFO is empty 
 * @return: received ascii symbol;
 */
char serial::getc(void) 
{
    //// check if there is at least one character in Rx FIFO 
    //if (!(REG(UART0_LSR_UART) & 0x1)) 
    //{
    //    //TODO is 0 a valid char? return empty result in some other way? */
    //    return 0;
    //} 
    //else 
    //{
    //    return REG(UART0_RHR) & 0xFF;
    //}
    return m_UART_module.char_get();
}

static void uart_isr(void *p_obj) 
{
    char received;

    received = REGS::UART::AM335X_UART_0_regs->RHR.reg;
  
    if (m_user_callback != nullptr) 
    {
        m_user_callback(received);
    }  

    REGS::INTC::AM335x_INTC->CONTROL.b.NewIRQAgr = HIGH;
}
