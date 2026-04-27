#include "hal/UART.hpp"

namespace HAL::UART
{

    template class HAL::UART::uart<HAL::UART::uart0_t,
                               HAL::PINS::UART0_TXD,
                               HAL::PINS::UART0_RXD,
                               REGS::UART::AM335x_UART_0_BASE,
                               REGS::INTC::UART0INT>;

    template class HAL::UART::uart<HAL::UART::uart1_t,
                                   HAL::PINS::UART1_TXD,
                                   HAL::PINS::UART1_RXD,
                                   REGS::UART::AM335x_UART_1_BASE,
                                   REGS::INTC::UART1INT>;
    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::uart(TXPin& tx, RXPin& rx, TXMode tx_mode, RXMode rx_mode)
    : uart_base<Derived>(reinterpret_cast<REGS::UART::AM335x_UART_Type*>(UARTBase))
    , m_tx(tx)
    , m_rx(rx)
    , m_tx_mode(tx_mode)
    , m_rx_mode(rx_mode)
    , m_LCR_before(Base::m_instance.LCR.reg)
    {    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    static void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::uart_isr(void*)
    {
        auto* uart = reinterpret_cast<REGS::UART::AM335x_UART_Type*>(UARTBase);
        char c = uart->RHR.reg;
        if (m_user_callback) m_user_callback(c);
        REGS::INTC::new_IRQ_agree();
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::reset_module()
    {
        using namespace REGS::UART;
        Base::m_instance.SYSC.b.SOFTRESET = 0x1;
        while(!Base::m_instance.SYSS.b.RESETDONE) {}
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::resume_operation() const
    {
        uint8_t resume_read = Base::m_instance.RESUME.b.RESUME;
        (void)resume_read;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::idle_mode_configure(REGS::UART::e_IDLEMODE mode)
    {
        Base::m_instance.SYSC.b.IDLEMODE = 0x0;
        Base::m_instance.SYSC.b.IDLEMODE = mode;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::wakeup_control(bool control)
    {
        Base::m_instance.SYSC.b.ENAWAKEUP = 0x0;
        Base::m_instance.SYSC.b.ENAWAKEUP = control;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::auto_idle_mode_control(bool control)
    {
        Base::m_instance.SYSC.b.AUTOIDLE = 0;
        Base::m_instance.SYSC.b.AUTOIDLE = control;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::switch_operating_mode(REGS::UART::e_MODESELECT mode)
    {
        Base::m_instance.MDR1.b.MODESELECT = 0;
        Base::m_instance.MDR1.b.MODESELECT = mode;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    [[nodiscard]] REGS::UART::e_MODESELECT uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::get_current_operating_mode() const
    { return static_cast<REGS::UART::e_MODESELECT>(Base::m_instance.MDR1.b.MODESELECT); }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::switch_reg_config_mode(REGS::UART::e_CONFIG_MODE mode, REGS::UART::e_ENH enh)
    {
        using namespace REGS::UART;
        LCR_reg_t tLCR;

        switch(mode)
        {
        case CONFIG_MODE_A:
        case CONFIG_MODE_B:
            Base::m_instance.LCR.reg = (static_cast<uint32_t>(mode) & 0xFF);
            break;
        case OPERATIONAL_MODE:
            Base::m_instance.LCR.reg &= 0x7F;
            break;
        default:
            break;
        }

        if (enh != ENH_ENABLE) return;

        tLCR.reg = Base::m_instance.LCR.reg;
        Base::m_instance.LCR.reg = (static_cast<uint32_t>(CONFIG_MODE_B) & 0xFF);
        Base::m_instance.EFR.b.ENHANCEDEN = 0;
        Base::m_instance.EFR.b.ENHANCEDEN = ENH_ENABLE;
        Base::m_instance.LCR.reg = tLCR.reg;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::switch_reg_subconfig_mode(REGS::UART::e_SUBCONFIG_MODE mode)
    {
        using namespace REGS::UART;
        switch(mode)
        {
        case MSR_SPR:
            switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);
            Base::m_instance.MCR.b.TCRTLR = 0x0;
            switch_reg_config_mode(CONFIG_MODE_A, ENH_DISABLE);
            break;
        case TCR_TLR:
            switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);
            Base::m_instance.MCR.b.TCRTLR = 0x1;
            break;
        case XOFF:
            switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);
            Base::m_instance.MCR.b.TCRTLR = 0x0;
            switch_reg_config_mode(CONFIG_MODE_B, ENH_DISABLE);
            break;
        }
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::FIFO_register_write(REGS::UART::FCR_reg_t fcr)
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

        Base::m_instance.FCR.reg = fcr.reg;

        // restore value of divisor latch
        if(divisor_before.raw != 0x0000)
            divisor_latch_set(divisor_before);
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    REGS::UART::divisor_latch uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::divisor_latch_get()
    {
        using namespace REGS::UART;
        volatile  bool  sleep_bit = false;
        divisor_latch  result;

        switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);
        sleep_bit = Base::m_instance.IER_UART.b.SLEEPMODE;

        if(sleep_bit)
            sleep(false);

        switch_reg_config_mode(CONFIG_MODE_A, ENH_DISABLE);

        result.b.DLH = static_cast<uint8_t>(Base::m_instance.DLH.reg);
        result.b.DLL = static_cast<uint8_t>(Base::m_instance.DLL.reg);

        if(sleep_bit)
            sleep(true);

        return result;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void  uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::sleep(bool control)
    {
        using namespace REGS::UART;

        switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);

        Base::m_instance.IER_UART.b.SLEEPMODE = control;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    [[nodiscard]] REGS::UART::e_CONFIG_MODE uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::get_config_mode() const
    {
        using namespace REGS::UART;
        LCR_reg_t tLCR;
        MCR_reg_t tMCR;
        e_CONFIG_MODE result = OPERATIONAL_MODE;

        // get current enhanced function bit state
        tLCR.reg = Base::m_instance.LCR.reg;
        Base::m_instance.LCR.reg = (static_cast<uint32_t>(CONFIG_MODE_B) & 0xFF);
        auto enhanced_sts = static_cast<e_ENH>(Base::m_instance.EFR.b.ENHANCEDEN);
        Base::m_instance.LCR.reg = tLCR.reg;

        if((Base::m_instance.LCR.reg & 0xFF) != 0xBF &&
            enhanced_sts == ENH_ENABLE)
            result = CONFIG_MODE_A;

        if((Base::m_instance.LCR.reg & 0xFF) == 0xBF &&
           enhanced_sts == ENH_ENABLE)
            result = CONFIG_MODE_B;

        if(enhanced_sts == ENH_DISABLE)
            result = OPERATIONAL_MODE;

        return result;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::divisor_latch_set(REGS::UART::divisor_latch divisor)
    {
        using namespace REGS::UART;

        volatile  bool  sleep_bit = false;
        auto  modf = get_current_operating_mode();

        m_save_LCR();

        switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);
        sleep_bit = Base::m_instance.IER_UART.b.SLEEPMODE;
        if(sleep_bit)
            sleep(false);

        switch_reg_config_mode(CONFIG_MODE_B, ENH_ENABLE);
        if(modf != MODE_DISABLE)
            switch_operating_mode(MODE_DISABLE);

        Base::m_instance.DLL.reg = (divisor.b.DLL & 0xFF);
        Base::m_instance.DLH.reg = (divisor.b.DLH & 0x3F);

        if(sleep_bit)
            sleep(true);

        m_restore_LCR();

        //restore the original state of  module
        if(get_current_operating_mode() != modf)
            switch_operating_mode(modf);
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::divisor_latch_enable()
    {
        Base::m_instance.LCR.b.DIV_EN = 0x1;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::divisor_latch_disable()
    {
        Base::m_instance.LCR.b.DIV_EN = 0x0;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::data_format_set(REGS::UART::e_CHAR_LENGHT char_len,
                         REGS::UART::e_STOP_BIT stop_bit,
                         REGS::UART::e_LCR_PARITY parity)
    {
        Base::m_instance.LCR.b.CHAR_LENGTH = 0;
        Base::m_instance.LCR.b.CHAR_LENGTH = char_len;
        Base::m_instance.LCR.b.NB_STOP = 0;
        Base::m_instance.LCR.b.NB_STOP = stop_bit;
        Base::m_instance.LCR.b.PARITY_EN = 0;
        Base::m_instance.LCR.b.PARITY_TYPE1 = 0;
        Base::m_instance.LCR.b.PARITY_TYPE2 = 0;
        Base::m_instance.LCR.reg |= (parity & REGS::UART::LCR_Parity_mask);
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::int_enable(REGS::UART::e_UART_IT_EN int_flag)
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

        Base::m_instance.IER_UART.reg |= (static_cast<uint32_t>(int_flag) & 0xF0);

        switch_reg_config_mode(OPERATIONAL_MODE, ENH_DISABLE);

        m_restore_LCR();

        Base::m_instance.IER_UART.reg |= (int_flag & 0x0F);
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::int_disable(REGS::UART::e_UART_IT_EN int_flag)
    {
        using namespace REGS::UART;

        m_save_LCR();
        switch_reg_config_mode(OPERATIONAL_MODE, ENH_ENABLE);

        Base::m_instance.IER_UART.reg &= ~(((uint32_t)int_flag) & 0xFF);

        switch_reg_config_mode(OPERATIONAL_MODE, ENH_DISABLE);

        m_restore_LCR();
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::modem_control_set(REGS::UART::MCR_reg_t mcr)
    {
        using namespace REGS::UART;
        switch_reg_config_mode(CONFIG_MODE_A, ENH_ENABLE);
        Base::m_instance.MCR.reg |= mcr.reg;
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::init_pins()
    {
        using namespace REGS::CONTROL_MODULE;

        m_rx.gpio_module_init();
        m_rx.sel_pinmode(m_rx_mode);
        m_rx.pullup_enable(true);
        m_rx.sel_pull_type(PULL_UP);
        m_rx.dir_set(REGS::GPIO::GPIO_INPUT);
        m_rx.sel_slewrate(FAST);

        m_tx.sel_pinmode(m_tx_mode);
        m_tx.pullup_enable(true);
        m_tx.sel_pull_type(PULL_UP);
        m_tx.dir_set(REGS::GPIO::GPIO_OUTPUT);
        m_tx.sel_slewrate(FAST);
    }

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::init_baudrate()
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

    template <typename Derived, typename TXPin, typename RXPin, uint32_t UARTBase, uint32_t IRQNum>
    void uart<Derived, TXPin, RXPin, UARTBase, IRQNum>::init_interrupts(serial_user_callback cb)
    {
        using namespace REGS::UART;

        int_enable(RECEIVE_IT);
        switch_reg_config_mode(OPERATIONAL_MODE, ENH_DISABLE);

        switch_operating_mode(MODE_UART_16x);
        resume_operation();

        m_user_callback = cb;
    }

}