#include "serial.hpp"

static void uart_isr(void *p_obj);
static serial_user_callback m_user_callback = NULL;

template <REGS::UART::e_UART_modules uart_module>
serial<uart_module>::module_state_t::module_state_t(REGS::UART::AM335x_UART_Type *p_regs)
: m_instance(*p_regs),
  module_function(REGS::UART::MODE_DISABLE),
  config_mode(REGS::UART::OPERATIONAL_MODE),
  subconfig_mode(REGS::UART::MSR_SPR),
  enhanced_sts(REGS::UART::ENH_DISABLE) 
{

}

template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::module_state_t::update()
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

template <REGS::UART::e_UART_modules uart_module>
serial<uart_module>::serial()
: m_instance(*uart_pins<uart_module>::uart_regs),
  m_rx_pin(uart_pins<uart_module>::gpio_regs),
  m_tx_pin(uart_pins<uart_module>::gpio_regs),
  m_INTC_module(intc),
  m_CM_WKUP_r(*REGS::PRCM::AM335x_CM_WKUP),
  m_state(uart_pins<uart_module>::uart_regs),
  m_hexchars{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}
{ 

}

template <REGS::UART::e_UART_modules uart_module>
serial<uart_module>::~serial()
{

}

/*
 * @brief  This API performs a module reset of the UART module. It also
 *         waits until the reset process is complete.
 */
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::reset_module()
{
    using namespace REGS::UART;

    // Performing Software Reset of the module.
    m_instance.SYSC.b.SOFTRESET = HIGH;

    // Wait until the process of Module Reset is complete.
    while(!m_instance.SYSS.b.RESETDONE);

    m_state.update();
}


/*
 * @brief  This API reads the RESUME register which clears the internal flags.
 *  
 * @note   When conditions like TX Underrun/RX Overrun errors occur, the
 *         transmission/reception gets halted and some internal flags are set.
 *         Clearing these flags would resume the halted operation.
 */
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::resume_operation()
{   
    // Dummy read of RESUME register.
    uint8_t resume_read = m_instance.RESUME.b.RESUME;
}

/* @brief initialize UART0 peripheral and set it up for polling I/O
 * @param callback: user defined RX callback function;
 */
template <REGS::UART::e_UART_modules uart_module>
void serial<uart_module>::init(serial_user_callback usr_clb) 
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
    
    m_rx_pin.sel_pinmode(m_rx_pinmode);
    m_rx_pin.pullup_enable(true);
    m_rx_pin.sel_pull_type(REGS::CONTROL_MODULE::PULL_UP);
    m_rx_pin.dir_set(REGS::GPIO::GPIO_INPUT);
    m_rx_pin.sel_slewrate(REGS::CONTROL_MODULE::FAST);

    m_tx_pin.sel_pinmode(m_tx_pinmode);
    m_tx_pin.pullup_enable(true);
    m_tx_pin.sel_pull_type(REGS::CONTROL_MODULE::PULL_UP);
    m_tx_pin.dir_set(REGS::GPIO::GPIO_OUTPUT);
    m_tx_pin.sel_slewrate(REGS::CONTROL_MODULE::FAST); 
    
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
    int_enable(RECEIVE_IT);
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
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::FIFO_register_write(REGS::UART::FCR_reg_t  fcr)
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
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::switch_operating_mode(REGS::UART::e_MODESELECT mode)
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
 *         - Configuration Mode A: LCR[7] = 1 and LCR[7:0] != 0xBF.
 *         - Configuration Mode B: LCR[7:0] = 0xBF
 *         - Operational Mode    : LCR[7] = 0
 *
 */
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::switch_reg_config_mode(REGS::UART::e_CONFIG_MODE mode, REGS::UART::e_ENH enh)
{ 
    using namespace REGS::UART;
    LCR_reg_t tLCR;

    switch(mode)  
    {
        case CONFIG_MODE_A:
        case CONFIG_MODE_B:
            m_instance.LCR.reg = ((uint32_t)mode & 0xFF);
            break;
        case OPERATIONAL_MODE:
            m_instance.LCR.reg &= 0x7F;
            break;
        default:
            break;
    }

    m_state.config_mode = mode;

    if(m_state.enhanced_sts != enh)
    {
        tLCR.reg = m_instance.LCR.reg;
        m_instance.LCR.reg = (((uint32_t)CONFIG_MODE_B) & 0xFF);
    
        m_instance.EFR.b.ENHANCEDEN = 0;
        m_instance.EFR.b.ENHANCEDEN = enh; 
        m_state.enhanced_sts        = enh;
    
        m_instance.LCR.reg = tLCR.reg;
    } 
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
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::switch_reg_subconfig_mode(REGS::UART::e_SUBCONFIG_MODE mode)
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
template <REGS::UART::e_UART_modules uart_module>
REGS::UART::divisor_latch  serial<uart_module>::divisor_latch_get(void)
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
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::divisor_latch_set(REGS::UART::divisor_latch divisor)
{
    using namespace REGS::UART;

    volatile  bool  sleep_bit = false;
      e_MODESELECT  modf = m_state.module_function;

    m_save_LCR();

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
    
    m_restore_LCR();
       
    //restore the original state of  module
    if(m_state.module_function != modf)
        switch_operating_mode(modf);        
}

/*
 * @brief  This API enables write access to Divisor Latch registers DLL and
 *         DLH.
 */
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::divisor_latch_enable()
{
    m_instance.LCR.b.DIV_EN = HIGH;
    m_state.update();
}

/*
 * @brief  This API disables write access to Divisor Latch registers DLL and
 *         DLH.
 */
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::divisor_latch_disable()
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
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::data_format_set(REGS::UART::e_CHAR_LENGHT  char_len,
                                 REGS::UART::e_STOP_BIT  stop_bit,
                               REGS::UART::e_LCR_PARITY  parity)
{   

    m_instance.LCR.b.CHAR_LENGTH = 0;  
    m_instance.LCR.b.CHAR_LENGTH = char_len;

    m_instance.LCR.b.NB_STOP = 0;
    m_instance.LCR.b.NB_STOP = stop_bit;

    m_instance.LCR.b.PARITY_EN = 0;
    m_instance.LCR.b.PARITY_TYPE1 = 0;
    m_instance.LCR.b.PARITY_TYPE2 = 0;
    
    m_instance.LCR.reg |= (parity & REGS::UART::LCR_Parity_mask);
} 

/*
 * @brief   This API enables the specified interrupts in the UART mode of
 *          operation.
 *
 * @param   int_flag   Bit mask value of the bits corresponding to Interrupt
 *                     Enable Register(IER). This specifies the UART interrupts
 *                     to be enabled.
 *
 * @note    This API modifies the contents of UART Interrupt Enable Register
 *          (IER). Modifying the bits IER[7:4] requires that EFR[4] be set.
 *          This API does the needful before it accesses IER.
 *          Moreover, this API should be called when UART is operating in
 *          UART 16x Mode, UART 13x Mode or UART 16x Auto-baud mode.\n
 */
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::int_enable(REGS::UART::e_UART_IT_EN int_flag)
{
    using namespace REGS::UART;

    m_save_LCR();
    switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);

    // It is suggested that the System Interrupts for UART in the
    // Interrupt Controller are enabled after enabling the peripheral
    // interrupts of the UART using this API. If done otherwise, there
    // is a risk of LCR value not getting restored and illicit characters
    // transmitted or received from/to the UART. The situation is explained
    // below.
    // The scene is that the system interrupt for UART is already enabled and
    // the current API is invoked. On enabling the interrupts corresponding
    // to IER[7:4] bits below, if any of those interrupt conditions
    // already existed, there is a possibility that the control goes to
    // Interrupt Service Routine (ISR) without executing the remaining
    // statements in this API. Executing the remaining statements is
    // critical in that the LCR value is restored in them.
    // However, there seems to be no risk in this API for enabling interrupts
    // corresponding to IER[3:0] because it is done at the end and no
    // statements follow that.

    m_instance.IER_UART.reg |= (((uint32_t)int_flag) & 0xF0);

    switch_reg_config_mode(OPERATIONAL_MODE, ENH_DISABLE);

    m_restore_LCR();  

    m_instance.IER_UART.reg |= (int_flag & 0x0F);
}

/*
 * @brief   This API disables the specified interrupts in the UART mode of
 *          operation.
 *
 * @param   int_flag   Bit mask value of the bits corresponding to Interrupt
 *                     Enable Register(IER). This specifies the UART interrupts
 *                     to be disabled.
 *
 * @note  The note motod of int_enable() also applies to this API.
 */
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::int_disable(REGS::UART::e_UART_IT_EN int_flag)
{
    using namespace REGS::UART;
    
    m_save_LCR();
    switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);

    m_instance.IER_UART.reg &= ~(((uint32_t)int_flag) & 0xFF);

    switch_reg_config_mode(OPERATIONAL_MODE, ENH_DISABLE);

    m_restore_LCR();
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
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::idle_mode_configure(REGS::UART::e_IDLEMODE mode)
{
    m_instance.SYSC.b.IDLEMODE = 0x0;
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
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::wakeup_control(bool control)
{
    m_instance.SYSC.b.ENAWAKEUP = 0;
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
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::auto_idle_mode_control(bool control)
{
    m_instance.SYSC.b.AUTOIDLE = 0;
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
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::sleep(bool control)
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
template <REGS::UART::e_UART_modules uart_module>
void  serial<uart_module>::modem_control_set(REGS::UART::MCR_reg_t mcr)
{
    using namespace REGS::UART;    

    switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);

    m_instance.MCR.reg |= mcr.reg; 

    m_state.update();  // because TCRTLR may be changed, and subonfig mode with him
}

/* @brief write char out to UART. blocks if Tx FIFO is full
 * @param 'c': input ascii symbol;
 */
template <REGS::UART::e_UART_modules uart_module>
void serial<uart_module>::putc(char c) 
{
    while (!m_instance.LSR_UART.b.TXSRE);
    
    //m_instance.THR.b.THR = c;  - dont do that in interrupts, sends every 1st character. 2-nd char dissapeared.
    m_instance.THR.reg = c;
}

/* @brief print out null terminated string
 * @param 'c': input pointer on ascii symbol array;
 */
template <REGS::UART::e_UART_modules uart_module>
void serial<uart_module>::puts(char* c) 
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
template <REGS::UART::e_UART_modules uart_module>
void serial<uart_module>::hexdump(uint32_t val) 
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
template <REGS::UART::e_UART_modules uart_module>
char serial<uart_module>::getc(void) 
{
    return 0; // FIXME
}

static void uart_isr(void *p_obj) 
{
    char received;

    received = REGS::UART::AM335X_UART_0->RHR.reg;
  
    if (m_user_callback != nullptr) 
    {
        m_user_callback(received);
    }  

    REGS::INTC::new_IRQ_agree();
}
