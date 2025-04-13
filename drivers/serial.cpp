#include "serial.hpp"
#include "uart.h"
#include "interrupt_.h"
#include <prcm_.h>

static void uart_isr(void *p_obj);
static serial_user_callback m_user_callback = NULL;


serial::serial(REGS::UART::AM335x_UART_Type *uart_regs)
: m_UART_module(uart_0),
  m_instance(*uart_regs),
  m_INTC_module(intc),
  m_CM_WKUP_r(*REGS::PRCM::AM335x_CM_WKUP),
  m_CM_r(*REGS::CONTROL_MODULE::AM335x_CONTROL_MODULE),
  m_hexchars{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}
{ 

}

serial::~serial()
{

}

/*
 * @brief  This API performs a module reset of the UART module. It also
 *         waits until the reset process is complete.
 */
void  serial::reset_module()
{
    // Performing Software Reset of the module.
    m_instance.SYSC.b.SOFTRESET = HIGH;

    // Wait until the process of Module Reset is complete.
    while(!m_instance.SYSS.b.RESETDONE);

    switch_operating_mode(REGS::UART::MODE_UART_16x);
}

/*
 * @brief  This API reads the RESUME register which clears the internal flags.
 *  
 * @note   When conditions like TX Underrun/RX Overrun errors occur, the
 *         transmission/reception gets halted and some internal flags are set.
 *         Clearing these flags would resume the halted operation.
 */
void  serial::resume_operation()
{   
    // Dummy read of RESUME register.
    uint8_t resume_read = m_instance.RESUME.b.RESUME;
}

/* @brief initialize UART0 peripheral and set it up for polling I/O
 * @param callback: user defined RX callback function;
 */
void serial::init(serial_user_callback usr_clb) 
{  
    // Enable UART0 functional clock [AM335x TRM 1284] 
    m_CM_WKUP_r.UART0_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_DISABLED; 
    m_CM_WKUP_r.UART0_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_ENABLE;       
    while(m_CM_WKUP_r.UART0_CLKCTRL.b.IDLEST != REGS::PRCM::IDLEST_FUNC);     // waiting for fully enabled
    
    // Enable UART0 interface clock l4_wkup
    m_CM_WKUP_r.L4WKUP_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_DISABLED;
    m_CM_WKUP_r.L4WKUP_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_ENABLE;       
    while(m_CM_WKUP_r.L4WKUP_CLKCTRL.b.IDLEST != REGS::PRCM::IDLEST_FUNC);  // waiting for fully enabled
    
    // Control module pin muxing 
    m_CM_r.conf_uart0_rxd.reg = 0;
    m_CM_r.conf_uart0_txd.reg = 0;    
    m_CM_r.conf_uart0_rxd.b.putypesel = REGS::CONTROL_MODULE::PULL_UP;          // RXD pullup 
    m_CM_r.conf_uart0_rxd.b.rxactive  = REGS::CONTROL_MODULE::INPUT_ENABLE;     // RXD enable input 
    m_CM_r.conf_uart0_txd.b.putypesel = REGS::CONTROL_MODULE::PULL_UP;          // TXD pullup
    
    // UART software reset    
    reset_module();
    idle_mode_configure(REGS::UART::NO_IDLE);
    
    // Disable UART to access protocol, baud rate, interrupt settings 
    switch_operating_mode(REGS::UART::MODE_DISABLE);
    
    // switch to register configuration mode A 
    switch_reg_config_mode(REGS::UART::CONFIG_MODE_A, REGS::UART::ENH_ENABLE);
    
    // disable modem control 
    m_UART_module.modem_control_set(0x00);  
    
    // enable FIFO 
    REGS::UART::FCR_reg_t FCR_reg;
    FCR_reg.reg = 0x07;
    m_UART_module.FIFO_register_write(FCR_reg); 
    
    
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
    
    switch_operating_mode(REGS::UART::MODE_UART_16x);
    
    resume_operation();
    
    m_user_callback = usr_clb; 
    m_INTC_module.register_handler(REGS::INTC::UART0INT, uart_isr);
    m_INTC_module.unmask_interrupt(REGS::INTC::UART0INT);
}

void  serial::initW(serial_user_callback usr_clb)
{
    // Enable UART0 functional clock [AM335x TRM 1284] 
    m_CM_WKUP_r.UART0_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_DISABLED; 
    m_CM_WKUP_r.UART0_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_ENABLE;       
    while(m_CM_WKUP_r.UART0_CLKCTRL.b.IDLEST != REGS::PRCM::IDLEST_FUNC);     // waiting for fully enabled
    
    // Enable UART0 interface clock l4_wkup
    m_CM_WKUP_r.L4WKUP_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_DISABLED;
    m_CM_WKUP_r.L4WKUP_CLKCTRL.b.MODULEMODE = REGS::PRCM::MODULEMODE_ENABLE;       
    while(m_CM_WKUP_r.L4WKUP_CLKCTRL.b.IDLEST != REGS::PRCM::IDLEST_FUNC);  // waiting for fully enabled

    // Control module pin muxing  
    m_CM_r.conf_uart0_rxd.reg = 0;
    m_CM_r.conf_uart0_txd.reg = 0;
    m_CM_r.conf_uart0_rxd.b.putypesel = REGS::CONTROL_MODULE::PULL_UP;          // RXD pullup 
    m_CM_r.conf_uart0_rxd.b.rxactive  = REGS::CONTROL_MODULE::INPUT_ENABLE;     // RXD enable input 
    m_CM_r.conf_uart0_txd.b.putypesel = REGS::CONTROL_MODULE::PULL_UP;          // TXD pullup

  /* UART software reset */
  REG(UART0_SYSC) |= 0x2;               /* initiate software reset */
  while (!(REG(UART0_SYSS) & (0x1))) {} /* wait until end of reset operation */
  REG(UART0_SYSC) = 0x8;

  /* Disable UART to access protocol, baud rate, interrupt settings */
  REG(UART0_MDR1) |= 0x7;

  /* switch to register configuration mode A */
  REG(UART0_LCR) = 0x0080;
  /* disable modem control */
  REG(UART0_MCR) = 0x00;
  /* enable FIFO */
  REG(UART0_FCR) = 0x07;
  /* load divisor values to achieve baud rate of 115200 */
  /* [AM335x TRM table 19-25] for divisor values */
  REG(UART0_DLL) = 0x1A;
  REG(UART0_DLH) = 0x00;

  /* set protocol formatting */
  /* no parity, 1 stop bit, 8 bit chars */
  REG(UART0_LCR) = 0x000B;
  /* enable RHR interrupt */
  REG(UART0_IER_UART) = 0x1;
  /* mode select */
  REG(UART0_MDR1) = 0x0; /* clear all, UART 16x mode */

  REG(UART0_RESUME);

  m_user_callback = usr_clb;
  
  /* register UART ISR */
  irq_register(72, uart_isr);

  /* unmask UART0 interrupt */
  /* 72 UART0INT */
  /* each MIR register has 32 bits, so we are in MIR2. #72-(2*32) = 8 */
  REG(INTC_MIR_CLEAR2) = (0x1 << 8);
}

/*
 * @brief  This API configures the operating mode for the UART instance.
 *         The different operating modes are:
 *         - UART(16x, 13x, 16x Auto-Baud)
 *         - IrDA(SIR, MIR, FIR)
 *         - CIR
 *         - Disabled state(default state)
 *
 * @param   'mode' -  A value which holds the mode number. This mode  
 *                number is referred from the MODESELECT field in MDR1.
 *
 * 'mode' can take one of the following values:
 * 'REGS::UART::MODE_UART_16x'          - switch to UART 16x operating mode
 * 'REGS::UART::MODE_SIR'               - switch to IrDA SIR operating mode
 * 'REGS::UART::MODE_UART_16x_AUTOBAUD' - switch to UART 16x Auto Baud operating mode
 * 'REGS::UART::MODE_UART_13x'          - switch to UART 13x operating mode
 * 'REGS::UART::MODE_MIR'               - switch to IrDA MIR operating mode
 * 'REGS::UART::MODE_FIR'               - switch to IrDA FIR operating mode
 * 'REGS::UART::MODE_CIR'               - switch to CIR operating mode
 * 'REGS::UART::MODE_DISABLE'           - switch to Disabled state
 *
 */
void  serial::switch_operating_mode(REGS::UART::e_MODESELECT mode)
{    
    m_save_opmode();  
    m_instance.MDR1.b.MODESELECT = 0;              // Clearing the MODESELECT field in MDR1.
    m_instance.MDR1.b.MODESELECT = mode;           // Programming the MODESELECT field in MDR1.    
}

/*
 * @brief  This API configures the specified Register Configuration mode for
 *         the UART. And sets a certain bit in Enhanced Feature Register(EFR) which
 *         shall avail the UART to use some Enhanced Features.
 *
 * @param  'mode'  This specifies the register configuration mode to be
 *                 enabled.
* 'mode' can take one of the following values:
 *  'REGS::UART::CONFIG_MODE_A'    - to enable Register Configuration Mode A\n
 *  'REGS::UART::CONFIG_MODE_B'    - to enable Register Configuration Mode B\n
 *  'REGS::UART::OPERATIONAL_MODE' - to enable Register Operational Mode\n
 *
 * @param 'enh'   This specifies the register enhanced feature access mode to be
 *                enabled.
 * 'enh' can take one of the following two values:
 *  'ENH_DISABLE' - disable enhanced function
 *  'ENH_ENABLE'  - enable enhanced function
 *
 * @note   Since the UART module registers that can be accessed at any time
 *         depends on the value in the Line Control Register(LCR), three
 *         register configuration modes have been defined, each corresponding
 *         to a specific state of the LCR. The three register configuration
 *         modes are:\n
 *         - Configuration Mode A: LCR[7] = 1 and LCR[7:0] != 0xBF.\n
 *         - Configuration Mode B: LCR[7:0] = 0xBF.\n
 *         - Operational Mode    : LCR[7] = 0.\n
 *
 */

void  serial::switch_reg_config_mode(REGS::UART::e_CONFIG_MODE mode, REGS::UART::e_ENH enh)
{ 
    REGS::UART::LCR_reg_t LCR;

     // if LCR[7] is 0x0 uart in opertioanl mode, save register to restore later 
     // when resume operational
     if(m_instance.LCR.b.DIV_EN == LOW)
        m_save_LCR();  

    switch(mode)  
    {
        case REGS::UART::CONFIG_MODE_A:
        case REGS::UART::CONFIG_MODE_B:
            m_instance.LCR.reg = ((uint32_t)mode & 0xFF);
            break;
        case REGS::UART::OPERATIONAL_MODE:
            // if LCR[7] is 0x1 restore register saved later
            if(m_instance.LCR.b.DIV_EN == HIGH)
                m_restore_LCR();
            m_instance.LCR.reg &= 0x7F;
            break;
        default:
            break;
    }

    LCR.reg = m_instance.LCR.reg;
    m_instance.LCR.reg = (((uint32_t)REGS::UART::CONFIG_MODE_B) & 0xFF);

    if(enh) 
    {
        m_instance.EFR.b.ENHANCEDEN = 0;
        m_instance.EFR.b.ENHANCEDEN = REGS::UART::ENH_ENABLE; 
    } 
    else
        m_instance.EFR.b.ENHANCEDEN = REGS::UART::ENH_DISABLE;

    m_instance.LCR.reg = LCR.reg; 
}

/*
 * @brief  This API enables the MSR_SPR, TCR_TLR, XOFF sub-sonfiguration modes of operation.
 *
 * @param 'mode'   This specifies the register sub-configuration mode access.
 *
 * 'mode' can take one of the following two values:
 *  'MSR_SPR'  - Access to Modem Status Register(MSR) and scratch pad Register(SPR). This is applicable for 
 *               configuration mode A and operational mode of operation.
 *  'TCR_TLR'  - Access to Transmission Control Register(TCR) and Trigger Level Register(TLR). 
 *               This is applicable for all the three register configuration modes.
 *  'XOFF'     - Acces to XOFF registers can be realized in ñonfiguration mode B of operation.
 * 
 */
void  serial::switch_reg_subconfig_mode(REGS::UART::e_SUBCONFIG_MODE mode)
{
    switch(mode)
    {
        case REGS::UART::MSR_SPR:
            switch_reg_config_mode(REGS::UART::CONFIG_MODE_A, REGS::UART::ENH_ENABLE);
            m_instance.MCR.b.TCRTLR = LOW;
            switch_reg_config_mode(REGS::UART::CONFIG_MODE_A, REGS::UART::ENH_DISABLE);
            break;
        case REGS::UART::TCR_TLR:
            switch_reg_config_mode(REGS::UART::CONFIG_MODE_A, REGS::UART::ENH_ENABLE);
            m_instance.MCR.b.TCRTLR = HIGH;
            break;
        case REGS::UART::XOFF:
            switch_reg_config_mode(REGS::UART::CONFIG_MODE_A, REGS::UART::ENH_ENABLE);
            m_instance.MCR.b.TCRTLR = LOW;
            switch_reg_config_mode(REGS::UART::CONFIG_MODE_B, REGS::UART::ENH_DISABLE);
            break;
    }
}

/*
 * @brief  This API switches the specified Modem Control register to desired values
 * 
 * @param  'mcr' - desired MCR value;
 */
void  serial::modem_control_set(REGS::UART::MCR_reg_t mcr)
{
    // Programming the specified bits of MCR.  
    m_instance.MCR.reg |= mcr.reg;
}

/*
 * @brief  This API can be used to control the Power Management
 *         request/acknowledgement process.
 *
 * @param  'mode' -  This specifies the Power Management
 *                   request/acknowledgement process to be followed
 *
 * 'mode' can take one of the following values:
 * 'REGS::UART::FORCE_IDLE' - to enable Force Idle mode\n
 * 'REGS::UART::NO_IDLE'    - to enable No-Idle mode\n
 * 'REGS::UART::ENAWAKEUP'  - to enable Smart Idle Wakeup mode\n
 * 'REGS::UART::IDLEMODE'   - to enable Smart Idle mode\n
 */
void  serial::idle_mode_configure(REGS::UART::e_IDLEMODE mode)
{
    // Clearing the IDLEMODE field in SYSC.
    m_instance.SYSC.b.IDLEMODE = 0x0;

    // Programming the IDLEMODE field in SYSC.
    m_instance.SYSC.b.IDLEMODE = mode;
}

/*
 * @brief  This API is used to control(enable/disable) the Wake-Up feature
 *         of the UART.
 *
 * @param  'control' -  this specifies whether the Wake Up feature should
 *                      be enabled or disabled for the UART instance
 *
 * 'control' can take one of the following two values:
 * 'true'  - enable Wake-Up feature
 * 'false' - disable Wake-Up feature
 */
void  serial::wakeup_control(bool control)
{
    // Clearing the ENAWAKEUP bit in SYSC register.
    m_instance.SYSC.b.ENAWAKEUP = 0;

    // Programming the ENAWAKEUP feature in SYSC register.
    m_instance.SYSC.b.ENAWAKEUP = control;
}

/*
 * @brief  This API is used to control(enable/disable) the Auto-Idle mode
 *         of operation of the UART.
 *
 * @param  'control' -  this specifies whether to enable or disable the
 *                      Auto-Idle mode of the UART
 *
 * 'control' can take one of the following two values:
 * 'false' - disable Auto-Idle mode
 * 'true'  - enable Auto-Idle mode
 */
void  serial::auto_idle_mode_control(bool control)
{
    // Clearing the AUTOIDLE bit in SYSC register.
    m_instance.SYSC.b.AUTOIDLE = 0;

    // Programming the AUTOIDLE bit in SYSC register.
    m_instance.SYSC.b.AUTOIDLE = control;
}

/*
 * @brief  This API is used to control(enable/disable) the sleep mode
 *         of UART.
 *
 * @param  'control' -  this specifies whether to enable or disable the
 *                      Sleep mode of the UART
 *
 * 'control' can take one of the following two values:
 * 'false' - disable Sleep mode
 * 'true'  - enable Sleep mode
 */
void  serial::sleep(bool control)
{
    using namespace REGS::UART;
  
    switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);

    m_instance.IER_UART.b.SLEEPMODE = control;
}

/* @brief write char out to UART. blocks if Tx FIFO is full
 * @param 'c': input ascii symbol;
 */
void serial::putc(char c) 
{
    while (!m_instance.LSR_UART.b.TXSRE) {}
    m_instance.THR.b.THR = c;
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
        putc(m_hexchars[(val >> (i * 4)) & 0xF]);
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

    received = REGS::UART::AM335X_UART_0->RHR.reg;
  
    if (m_user_callback != nullptr) 
    {
        m_user_callback(received);
    }  

    REGS::INTC::AM335x_INTC->CONTROL.b.NewIRQAgr = HIGH;
}
