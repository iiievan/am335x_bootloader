#include "hal/UART.hpp"

#if defined(__GNUC__)
#pragma GCC push_options
#pragma GCC optimize ("-O0")
#endif

namespace HAL::UART
{
    /**
     * @brief  This API performs a module reset of the UART module. It also
     *         waits until the reset process is complete.
     */
    void uart_base::reset_module() const noexcept
    {
        using namespace REGS::UART;
        m_instance.SYSC.b.SOFTRESET = 0x1;
        while(!m_instance.SYSS.b.RESETDONE) {}
    }

    /**
     * @brief  This API reads the RESUME register which clears the internal flags.
     *
     * @note   When conditions like TX Underrun/RX Overrun errors occur, the
     *         transmission/reception gets halted and some internal flags are set.
     *         Clearing these flags would resume the halted operation.
     */
    void uart_base::resume_operation() const noexcept
    {
        uint8_t resume_read = m_instance.RESUME.b.RESUME;
        (void)resume_read;
    }

    void uart_base::put_char(char c) const noexcept
    {
        while (!m_instance.LSR_UART.b.TXSRE) {}
        m_instance.THR.reg = c;
    }

    char uart_base::get_char() const noexcept
    {
        uint32_t LCR_reg_value = m_instance.LCR.reg;
        char ret_val = 0;

        switch_reg_config_mode(REGS::UART::OPERATIONAL_MODE, REGS::UART::ENH_DISABLE);

        while (m_instance.LSR_UART.b.RXFIFOE == 0) {}
        ret_val = static_cast<char>(m_instance.RHR.b.RHR);

        m_instance.LCR.reg = LCR_reg_value;
        return ret_val;
    }

    void uart_base::put_string(const char* str) const noexcept
    {
        while (*str)
        {
            if (*str == '\n') put_char('\r');
            put_char(*str++);
        }
    }

    /**
     * @brief  This API configures the operating mode for the UART instance.
     *         The different operating modes are:
     *         - UART(16x, 13x, 16x Auto-Baud)
     *         - IrDA(SIR, MIR, FIR)
     *         - CIR
     *         - Disabled state(default state)
     *
     * @param   mode -  A value which holds the mode number. This mode
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
    void uart_base::switch_operating_mode(REGS::UART::e_MODESELECT mode) const noexcept
    {
        m_instance.MDR1.b.MODESELECT = 0;
        m_instance.MDR1.b.MODESELECT = mode;
    }

    REGS::UART::e_MODESELECT uart_base::get_current_operating_mode() const noexcept
    {
        return static_cast<REGS::UART::e_MODESELECT>(m_instance.MDR1.b.MODESELECT);
    }

    /**
     * @brief  This API configures the specified Register Configuration mode for
     *         the UART. And sets a certain bit in Enhanced Feature Register(EFR) which
     *         shall avail the UART to use some Enhanced Features.
     *
     * @param  mode  This specifies the register configuration mode to be
     *                 enabled.
    * 'mode' can take one of the following values:
     *  'REGS::UART::CONFIG_MODE_A'    - to enable Register Configuration Mode A\n
     *  'REGS::UART::CONFIG_MODE_B'    - to enable Register Configuration Mode B\n
     *  'REGS::UART::OPERATIONAL_MODE' - to enable Register Operational Mode\n
     *
     * @param enh   This specifies the register enhanced feature access mode to be
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
    void uart_base::switch_reg_config_mode(REGS::UART::e_CONFIG_MODE mode, REGS::UART::e_ENH enh) const noexcept
    {
        using namespace REGS::UART;
        LCR_reg_t tLCR;

        switch(mode)
        {
        case CONFIG_MODE_A:
        case CONFIG_MODE_B:
            m_instance.LCR.reg = (static_cast<uint32_t>(mode) & 0xFF);
            break;
        case OPERATIONAL_MODE:
            m_instance.LCR.reg &= 0x7F;
            break;
        default:
            break;
        }

        if (enh != ENH_ENABLE) return;

        tLCR.reg = m_instance.LCR.reg;
        m_instance.LCR.reg = (static_cast<uint32_t>(CONFIG_MODE_B) & 0xFF);
        m_instance.EFR.b.ENHANCEDEN = 0;
        m_instance.EFR.b.ENHANCEDEN = ENH_ENABLE;
        m_instance.LCR.reg = tLCR.reg;
    }

    REGS::UART::e_CONFIG_MODE uart_base::get_config_mode() const noexcept
    {
        using namespace REGS::UART;
        LCR_reg_t tLCR;
        e_CONFIG_MODE result = OPERATIONAL_MODE;

        tLCR.reg = m_instance.LCR.reg;
        m_instance.LCR.reg = (static_cast<uint32_t>(CONFIG_MODE_B) & 0xFF);
        auto enhanced_sts = static_cast<e_ENH>(m_instance.EFR.b.ENHANCEDEN);
        m_instance.LCR.reg = tLCR.reg;

        if((m_instance.LCR.reg & 0xFF) != 0xBF && enhanced_sts == ENH_ENABLE)
            result = CONFIG_MODE_A;
        else if((m_instance.LCR.reg & 0xFF) == 0xBF && enhanced_sts == ENH_ENABLE)
            result = CONFIG_MODE_B;

        return result;
    }

    /**
     * @brief  This API enables the MSR_SPR, TCR_TLR, XOFF sub-sonfiguration modes of operation.
     *
     * @param mode   This specifies the register sub-configuration mode access.
     *
     * 'mode' can take one of the following two values:
     *  'MSR_SPR'  - Access to Modem Status Register(MSR) and scratch pad Register(SPR). This is applicable for
     *               configuration mode A and operational mode of operation.
     *  'TCR_TLR'  - Access to Transmission Control Register(TCR) and Trigger Level Register(TLR).
     *               This is applicable for all the three register configuration modes.
     *  'XOFF'     - Acces to XOFF registers can be realized in �onfiguration mode B of operation.
     *
     */
    void uart_base::switch_reg_subconfig_mode(REGS::UART::e_SUBCONFIG_MODE mode) noexcept
    {
        using namespace REGS::UART;
        switch(mode)
        {
        case MSR_SPR:
            switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);
            m_instance.MCR.b.TCRTLR = 0x0;
            switch_reg_config_mode(CONFIG_MODE_A, ENH_DISABLE);
            break;
        case TCR_TLR:
            switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);
            m_instance.MCR.b.TCRTLR = 0x1;
            break;
        case XOFF:
            switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);
            m_instance.MCR.b.TCRTLR = 0x0;
            switch_reg_config_mode(CONFIG_MODE_B, ENH_DISABLE);
            break;
        }
    }

    /**
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
    void uart_base::FIFO_register_write(REGS::UART::FCR_reg_t fcr) noexcept
    {
        using namespace REGS::UART;

        divisor_latch divisor_before = divisor_latch_get();
        divisor_latch divisor_zero;

        if(divisor_before.raw != 0x0000)
        {
            divisor_zero.raw = 0x0000;
            divisor_latch_set(divisor_zero);
        }
        switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);

        m_instance.FCR.reg = fcr.reg;

        if(divisor_before.raw != 0x0000)
            divisor_latch_set(divisor_before);
    }

    /**
     * @brief  This API is used to read the specified divisor value to Divisor
     *         Latch registers DLL and DLH.
     *
     * @return  divisor - latch values of registers DLL and DLH.
     */
    REGS::UART::divisor_latch uart_base::divisor_latch_get() noexcept
    {
        using namespace REGS::UART;
        volatile bool sleep_bit = false;
        divisor_latch result;

        switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);
        sleep_bit = m_instance.IER_UART.b.SLEEPMODE;

        if(sleep_bit)
            sleep(false);

        switch_reg_config_mode(CONFIG_MODE_A, ENH_DISABLE);

        result.b.DLH = static_cast<uint8_t>(m_instance.DLH.reg);
        result.b.DLL = static_cast<uint8_t>(m_instance.DLL.reg);

        if(sleep_bit)
            sleep(true);

        return result;
    }

    /**
     * @brief  This API is used to write the specified divisor value to Divisor
     *         Latch registers DLL and DLH.
     *
     * @param  divisor  The 14-bit value whose least 8 bits go to DLL
     *                  and highest 6 bits go to DLH.
     */
    void uart_base::divisor_latch_set(REGS::UART::divisor_latch divisor) noexcept
    {
        using namespace REGS::UART;

        volatile bool sleep_bit = false;
        auto modf = get_current_operating_mode();

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

        if(get_current_operating_mode() != modf)
            switch_operating_mode(modf);
    }

    /**
     * @brief  This API enables write access to Divisor Latch registers DLL and
     *         DLH.
     */
    void uart_base::divisor_latch_enable() noexcept
    {
        m_instance.LCR.b.DIV_EN = 0x1;
    }

    /**
     * @brief  This API disables write access to Divisor Latch registers DLL and
     *         DLH.
     */
    void uart_base::divisor_latch_disable() noexcept
    {
        m_instance.LCR.b.DIV_EN = 0x0;
    }

    void uart_base::config_baudrate() noexcept
    {
        using namespace REGS::UART;

        reset_module();
        idle_mode_configure(NO_IDLE);
        wakeup_control(false);
        auto_idle_mode_control(false);

        switch_operating_mode(MODE_DISABLE);

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

        data_format_set(CHL_8_BITS, STOP_1, PARITY_NONE);
    }

    /**
     * @brief  This API spicify data format of uart transmission and reception
     *         such as character length, parity bit, and stop bit
     *
     * @param  char_len - word length to be transmitted or received;
     * @param  stop_bit - number of stop bits;
     * @param  parity   -  parity bit;
     */
    void uart_base::data_format_set(REGS::UART::e_CHAR_LENGHT char_len,
                                     REGS::UART::e_STOP_BIT stop_bit,
                                     REGS::UART::e_LCR_PARITY parity) noexcept
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

    /**
     * @brief   This API enables the specified interrupts in the UART mode of
     *          operation.
     *
     * @param   int_flag   Bit mask value of the bits corresponding to Interrupt
     *                    Enable Register(IER). This specifies the UART interrupts
     *                    to be enabled.
     *
     *  'int_flag' can take one or a combination of the following macros:
     *  - CTS_IT - to enable Clear-To-Send interrupt,
     *  - RTS_IT - to enable Request-To-Send interrupt,
     *  - XOFF_IT - to enable XOFF interrupt,
     *  - SLEEPMODE_IT - to enable Sleep Mode,
     *  - MODEMSTS_IT - to enable Modem Status interrupt,
     *  - LINESTS_IT - to enable Line Status interrupt,
     *  - TRANSMIT_IT - to enable Transmitter Holding Register Empty interrupt,
     *  - RECEIVE_IT - to enable Receiver Data available interrupt and
     *                       Character timeout indication interrupt.
     *
     * @note    This API modifies the contents of UART Interrupt Enable Register
     *          (IER). Modifying the bits IER[7:4] requires that EFR[4] be set.
     *          This API does the needful before it accesses IER.
     *          Moreover, this API should be called when UART is operating in
     *          UART 16x Mode, UART 13x Mode or UART 16x Auto-baud mode.\n
     *
     */
    void uart_base::int_enable(REGS::UART::e_UART_IT_EN int_flag) noexcept
    {
        using namespace REGS::UART;

        m_save_LCR();
        switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);

         //
         //  It is suggested that the System Interrupts for UART in the
         //  Interrupt Controller are enabled after enabling the peripheral
         //  interrupts of the UART using this API. If done otherwise, there
         //  is a risk of LCR value not getting restored and illicit characters
         //  transmitted or received from/to the UART. The situation is explained
         //  below.
         //  The scene is that the system interrupt for UART is already enabled and
         //  the current API is invoked. On enabling the interrupts corresponding
         //  to IER[7:4] bits below, if any of those interrupt conditions
         //  already existed, there is a possibility that the control goes to
         //  Interrupt Service Routine (ISR) without executing the remaining
         //  statements in this API. Executing the remaining statements is
         //  critical in that the LCR value is restored in them.
         //  However, there seems to be no risk in this API for enabling interrupts
         //  corresponding to IER[3:0] because it is done at the end and no
         //  statements follow that.

        m_instance.IER_UART.reg |= (static_cast<uint32_t>(int_flag) & 0xF0);

        switch_reg_config_mode(OPERATIONAL_MODE, ENH_DISABLE);
        m_restore_LCR();

        m_instance.IER_UART.reg |= (int_flag & 0x0F);
    }

    /**
     * @brief   This API disables the specified interrupts in the UART mode of
     *          operation.
     *
     * @param   int_flag   Bit mask value of the bits corresponding to Interrupt
     *                    Enable Register(IER). This specifies the UART interrupts
     *                    to be disabled.
     *
     *  'int_flag' can take one or a combination of the following macros:
     *  - CTS_IT - to disable Clear-To-Send interrupt,
     *  - RTS_IT - to disable Request-To-Send interrupt,
     *  - XOFF_IT - to disable XOFF interrupt,
     *  - SLEEPMODE_IT - to disable Sleep Mode,
     *  - MODEMSTS_IT - to disable Modem Status interrupt,
     *  - LINESTS_IT - to disable Line Status interrupt,
     *  - TRANSMIT_IT - to disable Transmitter Holding Register Empty interrupt,
     *  - RECEIVE_IT - to disable Receiver Data available interrupt and
     *                       Character timeout indication interrupt.
     *
     * @note  The note section of int_enable() also applies to this API.
     */
    void uart_base::int_disable(REGS::UART::e_UART_IT_EN int_flag) noexcept
    {
        using namespace REGS::UART;

        m_save_LCR();
        switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);

        m_instance.IER_UART.reg &= ~(((uint32_t)int_flag) & 0xFF);

        switch_reg_config_mode(OPERATIONAL_MODE, ENH_DISABLE);
        m_restore_LCR();
    }

    /**
     * @brief  This API can be used to control the Power Management
     *         request/acknowledgement process.
     *
     * @param  mode -  This specifies the Power Management
     *                   request/acknowledgement process to be followed
     *
     * 'mode' can take one of the following values:
     * 'REGS::UART::FORCE_IDLE' - to enable Force Idle mode\n
     * 'REGS::UART::NO_IDLE'    - to enable No-Idle mode\n
     * 'REGS::UART::ENAWAKEUP'  - to enable Smart Idle Wakeup mode\n
     * 'REGS::UART::IDLEMODE'   - to enable Smart Idle mode\n
     */
    void uart_base::idle_mode_configure(REGS::UART::e_IDLEMODE mode) noexcept
    {
        m_instance.SYSC.b.IDLEMODE = 0x0;
        m_instance.SYSC.b.IDLEMODE = mode;
    }

    /**
     * @brief  This API is used to control(enable/disable) the Wake-Up feature
     *         of the UART.
     *
     * @param  control -  this specifies whether the Wake Up feature should
     *                      be enabled or disabled for the UART instance
     *
     * 'control' can take one of the following two values:
     * 'true'  - enable Wake-Up feature
     * 'false' - disable Wake-Up feature
     */
    void uart_base::wakeup_control(bool control) noexcept
    {
        m_instance.SYSC.b.ENAWAKEUP = 0x0;
        m_instance.SYSC.b.ENAWAKEUP = control;
    }

    /**
     * @brief  This API is used to control(enable/disable) the Auto-Idle mode
     *         of operation of the UART.
     *
     * @param  control -  this specifies whether to enable or disable the
     *                      Auto-Idle mode of the UART
     *
     * 'control' can take one of the following two values:
     * 'false' - disable Auto-Idle mode
     * 'true'  - enable Auto-Idle mode
     */
    void uart_base::auto_idle_mode_control(bool control) noexcept
    {
        m_instance.SYSC.b.AUTOIDLE = 0;
        m_instance.SYSC.b.AUTOIDLE = control;
    }

    /**
     * @brief  This API is used to control(enable/disable) the sleep mode
     *         of UART.
     *
     * @param  control -  this specifies whether to enable or disable the
     *                      Sleep mode of the UART
     *
     * 'control' can take one of the following two values:
     * 'false' - disable Sleep mode
     * 'true'  - enable Sleep mode
     */
    void uart_base::sleep(bool control) noexcept
    {
        using namespace REGS::UART;
        switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);
        m_instance.IER_UART.b.SLEEPMODE = control;
    }

    /**
     * @brief  This API switches the specified Modem Control register to desired values
     *
     * @param  mcr - desired MCR value;
     */
    void uart_base::modem_control_set(REGS::UART::MCR_reg_t mcr) noexcept
    {
        using namespace REGS::UART;
        switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);
        m_instance.MCR.reg |= mcr.reg;
    }

} // namespace HAL::UART

#if defined(__GNUC__)
#pragma GCC pop_options
#endif