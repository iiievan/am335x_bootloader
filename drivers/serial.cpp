#include "serial.hpp"

static void uart_isr(void *p_obj);
static serial_user_callback m_user_callback = NULL;

serial::serial(REGS::UART::AM335x_UART_Type *uart_regs)
: m_UART_module(uart_0),
  m_instance(*uart_regs),
  m_INTC_module(intc),
  m_CM_WKUP_r(*REGS::PRCM::AM335x_CM_WKUP),
  m_CM_r(*REGS::CONTROL_MODULE::AM335x_CONTROL_MODULE),
  m_state(uart_regs),
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
    using namespace REGS::UART;

    // Performing Software Reset of the module.
    m_instance.SYSC.b.SOFTRESET = HIGH;

    // Wait until the process of Module Reset is complete.
    while(!m_instance.SYSS.b.RESETDONE);

    m_state.update();
}

void  serial::module_state_t::update()
{
    using namespace REGS::UART;
    LCR_reg_t tLCR;
    MCR_reg_t tMCR;

    // get current operating module function UART, IrDA, CIR etc.
    module_function = (e_MODESELECT)m_instance.MDR1.b.MODESELECT;

    // get current enhanced function bit state
    tLCR.reg = m_instance.LCR.reg;
    m_instance.LCR.reg = (((uint32_t)CONFIG_MODE_B) & 0xFF);
    enhanced_sts = (e_ENH)m_instance.EFR.b.ENHANCEDEN;
    m_instance.LCR.reg = tLCR.reg;

    // get configuration mode registers status
    if((m_instance.LCR.reg & 0xFF) != 0xBF && 
        enhanced_sts == ENH_ENABLE) 
        config_mode = CONFIG_MODE_A;

    if((m_instance.LCR.reg & 0xFF) == 0xBF && 
       enhanced_sts == ENH_ENABLE) 
        config_mode = CONFIG_MODE_B;

    if(enhanced_sts == ENH_DISABLE) 
        config_mode = OPERATIONAL_MODE;

    tLCR.reg = m_instance.LCR.reg;
    m_instance.LCR.reg = (((uint32_t)CONFIG_MODE_A) & 0xFF);
    tMCR.reg = m_instance.MCR.reg;
    m_instance.LCR.reg = tLCR.reg;

    // get subconfiguration mode registers status
    switch(config_mode)
    {
        case OPERATIONAL_MODE:
        case CONFIG_MODE_A:
            if(enhanced_sts == ENH_ENABLE && 
               tMCR.b.TCRTLR == HIGH)
                subconfig_mode = TCR_TLR;

            if(enhanced_sts == ENH_DISABLE || 
               tMCR.b.TCRTLR == LOW)
                subconfig_mode = MSR_SPR;
            break;
        case CONFIG_MODE_B:
            if(enhanced_sts == ENH_ENABLE && 
               tMCR.b.TCRTLR == HIGH)
                subconfig_mode = TCR_TLR;

            if(enhanced_sts == ENH_DISABLE ||
               tMCR.b.TCRTLR == LOW) 
                subconfig_mode = XOFF;
            break;
    }
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
    using namespace REGS::UART;

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
    idle_mode_configure(NO_IDLE);
    wakeup_control(false);
    auto_idle_mode_control(false);
    
    // Disable UART to access protocol, baud rate, interrupt settings 
    switch_operating_mode(MODE_DISABLE);
    
    // disable modem control 
    MCR_reg_t tMCR;
    tMCR.reg = 0;
    modem_control_set(tMCR);  
    
    FCR_reg_t tFCR;
    tFCR.reg = 0;
    tFCR.b.FIFO_EN = 0x1;
    tFCR.b.RX_FIFO_CLEAR = 0x1;
    tFCR.b.TX_FIFO_CLEAR = 0x1;
    FIFO_register_write(tFCR);
    
    divisor_latch divisor;
    divisor.set_baud(KBPS_115_2);
    divisor_latch_set(divisor);  
    divisor_latch_disable();
    
    // set protocol formatting 
    // no parity, 1 stop bit, 8 bit chars 
    data_format_set(CHL_8_BITS,STOP_1,PARITY_NONE);
    
    // enable RHR interrupt 
    m_UART_module.int_enable(RECEIVE_IT);
    switch_reg_config_mode(OPERATIONAL_MODE,ENH_DISABLE);
    
    switch_operating_mode(MODE_UART_16x);    
    resume_operation();
    
    
    m_user_callback = usr_clb; 
    
    m_INTC_module.register_handler(REGS::INTC::UART0INT, uart_isr);
    m_INTC_module.unmask_interrupt(REGS::INTC::UART0INT);
}

/*
 * @brief  This API is used to write a specified value to the FIFO Control
 *         Register(FCR).
 *
 * @param  fcr     This specifies the value to be written to the FCR.
 *
 * @note  1> The FIFO_EN and DMA_MODE bits of FCR can be written to only when
 *           the Baud Clock is not running(DLL and DLH register are cleared
 *           to 0). Modifying DLL and DLH registers in turn requires that the
 *           UART be operated in Disabled Mode(MDR1[2:0] = 0x7).
 *        2> Writing to 'TX_FIFO_TRIG' field in FCR requires that the
 *           ENHANCEDEN bit in EFR(EFR[4]) be set to 1.
 *        Prior to writing to the FCR, this API does the above two operations.
 *        It also restores the respective bit values after FCR has been
 *        written to.
 */
void  serial::FIFO_register_write(REGS::UART::FCR_reg_t  fcr)
{ 
    using namespace REGS::UART;

    divisor_latch  divisor_before = divisor_latch_get();
    divisor_latch  divisor_zero;

    // The FIFO_EN and DMA_MODE bits of FCR can be written to only when
    // the Baud Clock is not running(DLL and DLH register are cleared  to 0).
    if(divisor_before.raw != 0x0000)
    {
        divisor_zero.raw = 0x0000;
        divisor_latch_set(divisor_zero);    
    }
    switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE); 
                                                                     
    m_instance.FCR.reg = fcr.reg;                                 
       
    // restore value of divisor latch
    if(divisor_before.raw != 0x0000)
        divisor_latch_set(divisor_before); 
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
    m_instance.MDR1.b.MODESELECT = 0;              // Clearing the MODESELECT field in MDR1.
    m_instance.MDR1.b.MODESELECT = mode;           // Programming the MODESELECT field in MDR1.
    m_state.module_function = mode;    
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
    using namespace REGS::UART;
    LCR_reg_t tLCR;

     // if uart in opertioanl mode, save register to restore later 
     // when resume operational mode
     if(m_state.config_mode == OPERATIONAL_MODE)
        m_save_LCR();  

    switch(mode)  
    {
        case CONFIG_MODE_A:
        case CONFIG_MODE_B:
            m_instance.LCR.reg = ((uint32_t)mode & 0xFF);
            break;
        case OPERATIONAL_MODE:
            // if LCR[7] is 0x1 restore register saved later
            if(m_state.config_mode == CONFIG_MODE_A || 
               m_state.config_mode == CONFIG_MODE_B)
                m_restore_LCR();
            m_instance.LCR.reg &= 0x7F;
            break;
        default:
            break;
    }

    m_state.config_mode = mode;

    tLCR.reg = m_instance.LCR.reg;
    m_instance.LCR.reg = (((uint32_t)CONFIG_MODE_B) & 0xFF);


    m_instance.EFR.b.ENHANCEDEN = 0;
    m_instance.EFR.b.ENHANCEDEN = enh; 
    m_state.enhanced_sts        = enh;

    m_instance.LCR.reg = tLCR.reg; 
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
    using namespace REGS::UART;

    switch(mode)
    {
        case REGS::UART::MSR_SPR:
            switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);
            m_instance.MCR.b.TCRTLR = LOW;
            switch_reg_config_mode(CONFIG_MODE_A, ENH_DISABLE);
            break;
        case REGS::UART::TCR_TLR:
            switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);
            m_instance.MCR.b.TCRTLR = HIGH;
            break;
        case REGS::UART::XOFF:
            switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);
            m_instance.MCR.b.TCRTLR = LOW;
            switch_reg_config_mode(CONFIG_MODE_B, ENH_DISABLE);
            break;
    }

    m_state.subconfig_mode = mode;
}

/*
 * @brief  This API is used to read the specified divisor value to Divisor
 *         Latch registers DLL and DLH.
 *
 * @return  divisor  latch values of registers DLL and DLH.
 */
REGS::UART::divisor_latch  serial::divisor_latch_get(void)
{
    using namespace REGS::UART;
    volatile  bool  sleep_bit = false;
     divisor_latch  result;

    switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);

    sleep_bit = m_instance.IER_UART.b.SLEEPMODE;

    if(sleep_bit)
        sleep(false);  

    switch_reg_config_mode(CONFIG_MODE_A, ENH_DISABLE);

    result.b.DLH = (uint8_t)m_instance.DLH.reg;
    result.b.DLL = (uint8_t)m_instance.DLL.reg;

    if(sleep_bit)
       sleep(true);

   return result;
}

/*
 * @brief  This API is used to write the specified divisor value to Divisor
 *         Latch registers DLL and DLH.
 *
 * @param  divisor  The 14-bit value whose least 8 bits go to DLL
 *                  and highest 6 bits go to DLH.
 */
void  serial::divisor_latch_set(REGS::UART::divisor_latch divisor)
{
    using namespace REGS::UART;
    LCR_reg_t tLCR;

    volatile  bool  sleep_bit = false;
     e_MODESELECT  modf = m_state.module_function;

    tLCR.reg = m_instance.LCR.reg;
    switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);

    sleep_bit = m_instance.IER_UART.b.SLEEPMODE;

    if(sleep_bit)
        sleep(false);  

    switch_reg_config_mode(CONFIG_MODE_B, ENH_ENABLE); 

    if(modf != MODE_DISABLE)
        switch_operating_mode(MODE_DISABLE);  
    
    m_instance.DLL.reg = (divisor.b.DLL & 0xFF);                
    m_instance.DLH.reg = (divisor.b.DLH & 0x3F);  

    if(sleep_bit)
       sleep(true); 
    
    m_instance.LCR.reg = tLCR.reg;
       
    //restore the original state of  module
    if(m_state.module_function != modf)
        switch_operating_mode(modf);        
}

/*
 * @brief  This API enables write access to Divisor Latch registers DLL and
 *         DLH.
 */
void  serial::divisor_latch_enable()
{
    m_instance.LCR.b.DIV_EN = HIGH;
    m_state.update();
}

/*
 * @brief  This API disables write access to Divisor Latch registers DLL and
 *         DLH.
 */
void  serial::divisor_latch_disable()
{
    m_instance.LCR.b.DIV_EN = LOW;
    m_state.update();
}

/*
 * @brief  This API spicify data format of uart transmission and reception
 *         such as character length, parity bit, and stop bit
 * 
 * @param  'char_len' - word length to be transmitted or received;
 * @param  'stop_bit' - number of stop bits;
 * @param  'parity'   -  parity bit;
 */
void  serial::data_format_set(REGS::UART::e_CHAR_LENGHT  char_len,
                                 REGS::UART::e_STOP_BIT  stop_bit,
                               REGS::UART::e_LCR_PARITY  parity)
{   

    m_instance.LCR.b.CHAR_LENGTH = 0;  
    m_instance.LCR.b.CHAR_LENGTH = char_len;    // then write

    m_instance.LCR.b.NB_STOP = 0;
    m_instance.LCR.b.NB_STOP = stop_bit;  // then write

    m_instance.LCR.b.PARITY_EN = 0;
    m_instance.LCR.b.PARITY_TYPE1 = 0;
    m_instance.LCR.b.PARITY_TYPE2 = 0;
    
    m_instance.LCR.reg |= (parity & REGS::UART::LCR_Parity_mask);
    
    m_save_LCR();
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
  
    if(m_state.config_mode != OPERATIONAL_MODE && 
        m_state.enhanced_sts != ENH_ENABLE)
        switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);

    m_instance.IER_UART.b.SLEEPMODE = control;
}

/*
 * @brief  This API switches the specified Modem Control register to desired values
 * 
 * @param  'mcr' - desired MCR value;
 */
void  serial::modem_control_set(REGS::UART::MCR_reg_t mcr)
{
    using namespace REGS::UART;    

    switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);

    m_instance.MCR.reg |= mcr.reg; 

    m_state.update();  // because TCRTLR may be changed, and subonfig mode with him
}

/* @brief write char out to UART. blocks if Tx FIFO is full
 * @param 'c': input ascii symbol;
 */
void serial::putc(char c) 
{
    while (!m_instance.LSR_UART.b.TXSRE) {}
    
    //m_instance.THR.b.THR = c;  - dont do that in interrupts, sends every 1st character. 2-nd char dissapeared.
    m_instance.THR.reg = c;
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
