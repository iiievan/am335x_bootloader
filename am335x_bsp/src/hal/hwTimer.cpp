#include "hal/hwTimer.hpp"

namespace HAL::TIMERS
{
    using namespace REGS::DMTIMER;

    template <typename DMT>
    hwTimer<DMT>::hwTimer(DMT *p_tmr_regs) noexcept
        : m_regs(*p_tmr_regs), m_time(0)
    {
    }

    template <typename DMT>
    void  hwTimer<DMT>::m_wait_for_write(e_TWPS_flags twps_mask) noexcept
    {
        // Wait for previous write to complete if posted mode enabled
        if(m_regs.TSICR.b.POSTED)
            while(m_regs.TWPS.reg & twps_mask){}
    }

    /**
     * @brief   This API will start the timer.
     * @note    The timer must be configured before it is started/enabled.
     **/
    template <typename DMT>
    void  hwTimer<DMT>::enable()  noexcept
    {
        m_wait_for_write(F_PEND_TCLR); // wait in posted mode
        m_regs.TCLR.b.ST = 0x1; // Start the timer

        m_is_paused = false;

        m_time = 0UL;
    }

    /**
     * @brief   This API will stop the timer.
     **/
    template <typename DMT>
    void  hwTimer<DMT>::disable()  noexcept
    {
        m_wait_for_write(F_PEND_TCLR); // wait in posted mode
        m_regs.TCLR.b.ST = 0x0; // Stop the timer

        m_is_paused = true;
    }

    /**
     * @brief   This API will configure the timer in combinations of
     *          'One Shot timer' and 'Compare' Mode or 'Auto-reload timer'
     *          and 'Compare' Mode.
     * @param   mode    Mode for enabling the timer.
     *
     *    'mode' can take the following values \n
     *    MODE_ONESHOT_CMP_ENABLE   - One shot and compare mode enabled \n
     *    MODE_ONESHOT_NOCMP_ENABLE - One shot enabled, compare mode disabled \n
     *    MODE_AUTORLD_CMP_ENABLE   - Auto-reload and compare mode enabled \n
     *    MODE_AUTORLD_NOCMP_ENABLE - Auto-reload enabled, compare mode
     *                                disabled \n
    **/
    template <typename DMT>
    void  hwTimer<DMT>::mode_configure(e_DMTIMER_mode mode) noexcept
    {
        m_wait_for_write(F_PEND_TCLR); // wait in posted mode

        m_regs.TCLR.b.AR = 0x0;  // clear autoreload mode
        m_regs.TCLR.b.CE = 0x0;  // clear compare mode

        m_wait_for_write(F_PEND_TCLR); // wait in posted mode

        // Set the timer mode in TCLR register
        m_regs.TCLR.reg |= mode;
    }

    /**
     * @brief   This API will configure and enable the pre-scaler clock.
     * @param   ptv          Pre-scale clock Timer value.
     *    'ptv' can take the following values \n
     *    REGS::DMTIMER::CLK_DIV_BY_2 - Timer clock divide by 2 \n
     *    REGS::DMTIMER::CLK_DIV_BY_4 - Timer clock divide by 4 \n
     *    REGS::DMTIMER::CLK_DIV_BY_8 - Timer clock divide by 8 \n
     *    REGS::DMTIMER::CLK_DIV_BY_16 - Timer clock divide by 16 \n
     *    REGS::DMTIMER::CLK_DIV_BY_32 - Timer clock divide by 32 \n
     *    REGS::DMTIMER::CLK_DIV_BY_64 - Timer clock divide by 64 \n
     *    REGS::DMTIMER::CLK_DIV_BY_128 - Timer clock divide by 128 \n
     *    REGS::DMTIMER::CLK_DIV_BY_256 - Timer clock divide by 256 \n
     **/
    template <typename DMT>
    void  hwTimer<DMT>::prescaler_clk_enable(e_PRSC ptv) noexcept
    {
        m_wait_for_write(F_PEND_TCLR); // wait in posted mode

        m_regs.TCLR.b.PTV = 0x0;  // Clear the PTV field of TCLR

        m_wait_for_write(F_PEND_TCLR); // wait in posted mode

        // Set the PTV field and enable the pre-scaler clock
        m_regs.TCLR.b.PTV = ptv;
        m_regs.TCLR.b.PRE = 0x1;
    }

    /**
     * @brief   This API will disable the pre-scaler clock.
     **/
    template <typename DMT>
    void  hwTimer<DMT>::prescaler_clk_disable() noexcept
    {
        m_wait_for_write(F_PEND_TCLR); // wait in posted mode

        // Disable Pre-scaler clock
        m_regs.TCLR.b.PRE = 0x0;
    }

    /**
     * @brief   This API will set 1ms block values for precision 1ms only for DMTIMER_1MS
     **/
    template<>
    void  hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::set_1ms_block(int32_t pos, int32_t neg) noexcept
    {
        m_wait_for_write(F_PEND_TCLR); // wait in posted mode

        m_regs.TPIR.b.POSITIVE_INC_VALUE = pos;

        m_regs.TNIR.b.NEGATIVE_INC_VALUE = neg;
    }

    /**
     * @brief   Set/Write the Counter register with the counter value.
     * @param   counter       Count value for the timer.
     * @note    Value can be loaded into the counter register when the counter is
     *          stopped or when it is running.
     **/
    template <typename DMT>
    void  hwTimer<DMT>::counter_set(uint32_t counter) noexcept
    {
        m_wait_for_write(F_PEND_TCRR); // wait in posted mode

        // Set the counter value
        m_regs.TCRR.reg = counter;
    }

    /**
     * @brief   Get/Read the counter value from the counter register.
     * @return  This API returns the count value present in the DMTimer Counter
     *          register.
     * @note:   Value can be read from the counter register when the counter is
     *          stopped or when it is running.
     **/
    template <typename DMT>
    uint32_t  hwTimer<DMT>::counter_get() noexcept
    {
        m_wait_for_write(F_PEND_TCRR); // wait in posted mode
        return  m_regs.TCRR.reg;
    }

    /**
     * @brief   Set the reload count value in the timer load register.
     * @param   reload        The reload count value of the timer.
     * @note:   It is recommended to not use reload value as 0xFFFFFFFF as it can
     *          lead to undesired results.
     **/
    template <typename DMT>
    void  hwTimer<DMT>::reload_set(uint32_t reload) noexcept
    {
        m_wait_for_write(F_PEND_TLDR); // wait in posted mode

        // Load the register with the re-load value
        m_regs.TLDR.reg = reload;
    }

    /**
     * @brief   Get the reload count value from the timer load register.
     * @return  This API returns the value present in DMTimer Load Register.
     **/
    template <typename DMT>
    uint32_t  hwTimer<DMT>::reload_get() noexcept
    {
        return   m_regs.TLDR.reg;
    }

    /**
     * @brief   Configure general purpose output pin.
     * @param   gpo_cfg        General purpose output.
     *
     *    'gpo_cfg' can take the following values \n
     *    true  - PORGPOCFG drives 0 \n
     *    false - PORGPOCFG drives 1 \n
     **/
    template <typename DMT>
    void  hwTimer<DMT>::GPO_configure(bool gpo_cfg) noexcept
    {
        m_wait_for_write(F_PEND_TCLR); // wait in posted mode

        m_regs.TCLR.b.GPO_CFG = 0x0; // Clear the GPO_CFG field of TCLR

        m_wait_for_write(F_PEND_TCLR); // wait in posted mode

        // Write to the GPO_CFG field of TCLR
        m_regs.TCLR.b.GPO_CFG = gpo_cfg;
    }

    /**
    * @brief   Set the match register with the compare value.
    * @param   compare_val    Compare value.
    **/
    template <typename DMT>
    void  hwTimer<DMT>::compare_set(uint32_t compare_val) noexcept
    {
        m_wait_for_write(F_PEND_TMAR); // wait in posted mode

        // Write the compare value to TMAR
        m_regs.TMAR.reg = compare_val;
    }

    /**
    * @brief   Get the match register contents.
    * @return  This API returns the match register contents.
    **/
    template <typename DMT>
    uint32_t  hwTimer<DMT>::compare_get() noexcept
    {
        return  m_regs.TMAR.reg;
    }

    /**
    * @brief   Trigger IRQ event by software.
    * @param   int_flags      Variable used to trigger the events.
    *
    *    'int_flags' can take the following values \n
    *    IRQ_NONE = Trigger IRQ none \n,
    *    IRQ_TCAR - Trigger IRQ status for capture \n
    *    IRQ_OVF  - Trigger IRQ status for overflow \n
    *    IRQ_MAT  - Trigger IRQ status for match \n
    * @note !this function is not in the registers AM335x_DMTIMER1MS_Type!
    **/
    template <>
    void  hwTimer<AM335x_DMTIMER_Type>::IRQ_raw_set(e_IRQ_flags int_flags) noexcept
    {
        // Trigger the events in IRQSTATUS_RAW register
        m_regs.IRQSTATUS_RAW.reg = int_flags;
    }

    /**
     * @brief   Read the status of IRQSTATUS_RAW register.
     * @return  This API returns the contents of IRQSTATUS_RAW register.
     * @note    !this function is not in the registers AM335x_DMTIMER1MS_Type!
     **/
    template <>
    uint32_t  hwTimer<AM335x_DMTIMER_Type>::IRQ_raw_get() noexcept
    {
        // Return the status of IRQSTATUS_RAW register
        return  m_regs.IRQSTATUS_RAW.reg;
    }

    /**
     * @brief   Read the status of IRQ_STATUS register.
     * @return  This API returns the status of IRQSTATUS register.
     **/
    template <>
    uint32_t  hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::IRQ_get() noexcept
    {
        // Return the status of IRQSTATUS register
        return  m_regs.TISR.reg;
    }

    template <typename DMT>
    uint32_t  hwTimer<DMT>::IRQ_get() noexcept
    {
        // Return the status of IRQSTATUS register
        return  m_regs.IRQSTATUS.reg;
    }

    /**
     * @brief   Clear the status of interrupt events.
     * @param   int_flags      Variable used to clear the events.
     *
     *   'int_flags' can take the following values \n
     *    IRQ_TCAR - Clear IRQ status for capture \n
     *    IRQ_OVF  - Clear IRQ status for overflow \n
     *    IRQ_MAT  - Clear IRQ status for match \n
     **/
    template <>
    void  hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::IRQ_clear(e_IRQ_flags int_flags) noexcept
    {
        // Clear the interrupt status from TISR register
        m_regs.TISR.reg = int_flags;
    }

    template <typename DMT>
    void  hwTimer<DMT>::IRQ_clear(e_IRQ_flags int_flags) noexcept
    {
        // Clear the interrupt status from IRQSTATUS register
        m_regs.IRQSTATUS.reg = int_flags;
    }

    /**
    * @brief   Enable the DMTimer interrupts.
    * @param   int_flags      Variable used to enable the interrupts.
    *
    *    'int_flags' can take the following values \n
    *    IRQ_TCAR - IRQ enable for capture \n
    *    IRQ_OVF - IRQ enable for overflow \n
    *    IRQ_MAT - IRQ enable for match \n
    **/
    template <>
    void  hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::IRQ_enable(e_IRQ_flags int_flags) noexcept
    {
        // Enable the DMTimer interrupts represented by int_flags
        m_regs.TIER.reg |= int_flags;
    }

    template <typename DMT>
    void  hwTimer<DMT>::IRQ_enable(e_IRQ_flags int_flags) noexcept
    {
        // Enable the DMTimer interrupts represented by int_flags
        m_regs.IRQENABLE_SET.reg = int_flags;
    }

    /**
    * @brief   Disable the DMTimer interrupts.
    * @param   int_flags      Variable used to disable the interrupts.
    *
    *    'int_flags' can take the following values \n
    *    IRQ_TCAR - IRQ disable for capture \n
    *    IRQ_OVF - IRQ disable for overflow \n
    *    IRQ_MAT - IRQ disable for match \n
    **/
    template <>
    void  hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::IRQ_disable(e_IRQ_flags int_flags) noexcept
    {
        // Disable the DMTimer interrupts represented by int_flags
        m_regs.TIER.reg &= ~int_flags;
    }

    template <typename DMT>
    void  hwTimer<DMT>::IRQ_disable(e_IRQ_flags int_flags) noexcept
    {
        // Disable the DMTimer interrupts represented by int_flags
        m_regs.IRQENABLE_CLR.reg = int_flags;
    }

    /**
     * @brief   Set/enable the trigger write access.
     * @note    When we have enabled the timer in Auto-reload mode, the value from
     *          TLDR is reloaded into TCRR when a overflow condition occurs. But if
     *          we want to load the contents from TLDR to TCRR before overflow
     *          occurs then call this API.
     **/
    template <typename DMT>
    void  hwTimer<DMT>::trigger_set() noexcept
    {
        m_wait_for_write(F_PEND_TTGR); // wait in posted mode

        m_regs.TTGR.reg = TTGR_DEF_VALUE;
    }

    /**
     * @brief   Read the status of IRQENABLE_SET register.
     * @return  This API returns the status of IRQENABLE_SET register.
     **/
    template <>
    uint32_t  hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::IRQ_enable_get() noexcept
    {
        // Return the status of register TIER
        return  m_regs.TIER.reg;
    }

    template <typename DMT>
    uint32_t  hwTimer<DMT>::IRQ_enable_get() noexcept
    {
        // Return the status of register IRQENABLE_SET
        return  m_regs.IRQENABLE_SET.reg;
    }

    /**
     * @brief   Enable/Disable software reset for DMTimer module.
     * @param   rst_option     Enable/Disable reset option for DMTimer.
     *
     *    'rst_option' can take the following values \n
     *    false  - Software reset is enabled \n
     *    ture - Software reset is disabled \n
     **/
    template <typename DMT>
    void  hwTimer<DMT>::reset_configure(bool rst_option) noexcept
    {
        // Clear the SFT field of TSICR
        m_regs.TSICR.b.SFT = 0x0;

        // Write the option sent by user to SFT field of TSICR
        m_regs.TSICR.b.SFT = rst_option;
    }

    /**
     * @brief   Reset the DMTimer module.
     **/
    template <>
    void  hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::reset() noexcept
    {
        // Reset the DMTimer module
        m_regs.TIOCP_CFG.b.SoftReset = 0x1;

        while( m_regs.TIOCP_CFG.b.SoftReset);
    }

    template <typename DMT>
    void  hwTimer<DMT>::reset() noexcept
    {
        // Reset the DMTimer module
        m_regs.TIOCP_CFG.b.SOFTRESET = 0x1;

        while( m_regs.TIOCP_CFG.b.SOFTRESET);
    }

    /**
     * @brief   Configure the posted mode of DMTimer.
     * @param   post_mode      Posted mode configuration.
     *
     *    'post_mode' can take the following values \n
     *    false - Posted mode not used \n
     *    true - Posted mode used \n
     **/
    template <typename DMT>
    void  hwTimer<DMT>::posted_mode_config(bool post_mode) noexcept
    {
        m_regs.TSICR.b.POSTED = 0x0;

        m_regs.TSICR.b.POSTED = post_mode;
    }

    /**
     * @brief   Check posted mode  is enbled
     * @return  true -  Posted mode active
     *          false -  Posted mode inactive
     **/
    template <typename DMT>
    bool  hwTimer<DMT>::posted_status_get() noexcept
    {
        return (bool)m_regs.TSICR.b.POSTED;
    }

    /**
     * @brief   This API stores the context of the DMTimer
     **/
    template <>
    void  hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::context_save() noexcept
    {
        m_context.tldr =  m_regs.TLDR.reg;
        m_context.tmar =  m_regs.TMAR.reg;
        m_context.irqenableset =  m_regs.TIER.reg;

        m_wait_for_write(F_PEND_TCRR); // wait in posted mode
        m_context.tcrr =  m_regs.TCRR.reg;

        m_wait_for_write(F_PEND_TCLR); // wait in posted mode
        m_context.tclr =  m_regs.TCLR.reg;
    }

    template <typename DMT>
    void  hwTimer<DMT>::context_save() noexcept
    {
        m_context.tldr =  m_regs.TLDR.reg;
        m_context.tmar =  m_regs.TMAR.reg;
        m_context.irqenableset =  m_regs.IRQENABLE_SET.reg;

        m_wait_for_write(F_PEND_TCRR); // wait in posted mode
        m_context.tcrr =  m_regs.TCRR.reg;

        m_wait_for_write(F_PEND_TCLR); // wait in posted mode
        m_context.tclr =  m_regs.TCLR.reg;
    }

    /**
     * @brief   This API restores the context of the DMTimer
     **/
    template <>
    void  hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::context_restore() noexcept
    {
        m_wait_for_write(F_PEND_TLDR); // wait in posted mode
        m_regs.TLDR.reg = m_context.tldr;

        m_wait_for_write(F_PEND_TMAR); // wait in posted mode
        m_regs.TMAR.reg = m_context.tmar;
        m_regs.TIER.reg = m_context.irqenableset;

        m_wait_for_write(F_PEND_TCRR); // wait in posted mode
        m_regs.TCRR.reg = m_context.tcrr;

        m_wait_for_write(F_PEND_TCLR); // wait in posted mode
        m_regs.TCLR.reg = m_context.tclr;
    }

    template <typename DMT>
    void  hwTimer<DMT>::context_restore() noexcept
    {
        m_wait_for_write(F_PEND_TLDR); // wait in posted mode
        m_regs.TLDR.reg = m_context.tldr;

        m_wait_for_write(F_PEND_TMAR); // wait in posted mode
        m_regs.TMAR.reg = m_context.tmar;
        m_regs.IRQENABLE_SET.reg = m_context.irqenableset;

        m_wait_for_write(F_PEND_TCRR); // wait in posted mode
        m_regs.TCRR.reg = m_context.tcrr;

        m_wait_for_write(F_PEND_TCLR); // wait in posted mode
        m_regs.TCLR.reg = m_context.tclr;
    }

    /**
     * @brief   Get hardware timer number
     * @return  sequence number of the timer involved
     **/
    template <typename DMT>
    e_TIMER_NUM hwTimer<DMT>::get_DMTIMER_number() noexcept
    {
        auto timer_num = reinterpret_cast<uint32_t>(&m_regs);

        switch(timer_num)
        {
        case AM335x_DMTIMER_0_BASE:     // only 32KHz RC Clock
            return TIMER_0;
        case REGS::DMTIMER1MS::AM335x_DMTIMER_1MS_BASE:
            return TIMER_1ms;
        case AM335x_DMTIMER_2_BASE:
            return TIMER_2;
        case AM335x_DMTIMER_3_BASE:
            return TIMER_3;
        case AM335x_DMTIMER_4_BASE:
            return TIMER_4;
        case AM335x_DMTIMER_5_BASE:
            return TIMER_5;
        case AM335x_DMTIMER_6_BASE:
            return TIMER_6;
        case AM335x_DMTIMER_7_BASE:
            return TIMER_7;
        default:
            break;
        }

        return TIMER_NA;
    }

    /**
     * @brief   Get hardware timer number interrupt
     * @return  sequence number of timer interrupt
     **/
    template <typename DMT>
    REGS::INTC::e_INT_ID hwTimer<DMT>::get_DMTIMER_sys_interrupt() noexcept
    {
        using namespace REGS::INTC;
        auto timer_num = reinterpret_cast<uint32_t>(&m_regs);

        switch(timer_num)
        {
        case AM335x_DMTIMER_0_BASE:     // only 32KHz RC Clock
            return TINT0;
        case REGS::DMTIMER1MS::AM335x_DMTIMER_1MS_BASE:
            return TINT1_1MS;
        case AM335x_DMTIMER_2_BASE:
            return TINT2;
        case AM335x_DMTIMER_3_BASE:
            return TINT3;
        case AM335x_DMTIMER_4_BASE:
            return TINT4;
        case AM335x_DMTIMER_5_BASE:
            return TINT5;
        case AM335x_DMTIMER_6_BASE:
            return TINT6;
        case AM335x_DMTIMER_7_BASE:
            return TINT7;
        default:
            break;
        }

        return INT_NUM_MAX;
    }


    /**
     * @brief   Froze timer during debug
     * @param   emufree_val 'true' -debug suspend ignored
     *          'false' - frozen during debug;
     **/
    template <>
    void  hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::set_debug_EMUFREE(bool emufree_val) noexcept
    {
        // Set debug suspend ignored(0x1) or frozen during debug (0x0 default)in DMTimer module **/
        m_regs.TIOCP_CFG.b.EmuFree = emufree_val;
    }

    template <typename DMT>
    void  hwTimer<DMT>::set_debug_EMUFREE(bool emufree_val) noexcept
    {
        // Set debug suspend ignored(0x1) or frozen during debug (0x0 default)in DMTimer module **/
        m_regs.TIOCP_CFG.b.EMUFREE = emufree_val;
    }

    /**
     * @brief   Gets frozen state during debug
     * @return  true - debug suspend ignored
     *          false - frozen during debug;
     **/
    template <>
    bool  hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::get_debug_EMUFREE() noexcept
    {
        return static_cast<bool>( m_regs.TIOCP_CFG.b.EmuFree);
    }

    template <typename DMT>
    bool hwTimer<DMT>::get_debug_EMUFREE() noexcept
    {
        return static_cast<bool>( m_regs.TIOCP_CFG.b.EMUFREE);
    }

    void run_clk_interconnects() noexcept
    {
        using namespace REGS::PRCM;
        auto& per = *AM335x_CM_PER;

        /* Run interconnects busses clocking */
        per.L3S_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;
        while(per.L3S_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP){}

        per.L3_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;
        while(per.L3_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP){}

        per.L3_INSTR_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
        while(per.L3_INSTR_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE){}

        per.L3_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
        while(per.L3_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE){}

        per.OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;
        while(per.OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP){}

        per.L4LS_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;
        while(per.L4LS_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP){}

        per.L4LS_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
        while(per.L4LS_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE){}
    }

        void run_clk_DMTIMER(e_TIMER_NUM tmr_num) noexcept
        {
            using namespace REGS::DMTIMER;
            using namespace REGS::PRCM;
            auto& dpll = *AM335x_CM_DPLL;
            auto& per = *AM335x_CM_PER;

            switch(tmr_num)
            {
               case TIMER_5:
                    run_clk_DMTIMER_5();
                    return; // no need to run run_clk_interconnects() and other stuff below
               case TIMER_6:
                    run_clk_DMTIMER_6();
                    return; // no need to run run_clk_interconnects() and other stuff below
                default:
                    break;
            }

            run_clk_interconnects();

            switch(tmr_num)
            {
                case TIMER_2:
                        /* Select the clock source for the Timer2 instance. */
                        dpll.TIMER2_CLK.b.CLKSEL = 0x0;               // clear bitfield
                        dpll.TIMER2_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
                        while(dpll.TIMER2_CLK.b.CLKSEL != CLK_M_OSC){}

                        per.TIMER2_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
                        while(per.TIMER2_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE){}
                        while(per.TIMER2_CLKCTRL.b.IDLEST != IDLEST_FUNC){}
                    break;
                case TIMER_3:
                        /* Select the clock source for the Timer3 instance. */
                        dpll.TIMER3_CLK.b.CLKSEL = 0x0;               // clear bitfield
                        dpll.TIMER3_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
                        while(dpll.TIMER3_CLK.b.CLKSEL != CLK_M_OSC){}

                        per.TIMER3_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
                        while(per.TIMER3_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE){}
                        while(per.TIMER3_CLKCTRL.b.IDLEST != IDLEST_FUNC){}
                    break;
                case TIMER_4:
                        /* Select the clock source for the Timer4 instance. */
                        dpll.TIMER4_CLK.b.CLKSEL = 0x0;               // clear bitfield
                        dpll.TIMER4_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
                        while(dpll.TIMER4_CLK.b.CLKSEL != CLK_M_OSC){}

                        per.TIMER4_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
                        while(per.TIMER4_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE){}
                        while(per.TIMER4_CLKCTRL.b.IDLEST != IDLEST_FUNC){}
                    break;
                case TIMER_7:
                        /* Select the clock source for the Timer7 instance. */
                        dpll.TIMER7_CLK.b.CLKSEL = 0x0;               // clear bitfield
                        dpll.TIMER7_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
                        while(dpll.TIMER7_CLK.b.CLKSEL != CLK_M_OSC){}

                        per.TIMER7_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
                        while(per.TIMER7_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE){}
                        while(per.TIMER7_CLKCTRL.b.IDLEST != IDLEST_FUNC){}
                    break;
                default:
                  break;
            }

            while(!per.L3S_CLKSTCTRL.b.CLKACTIVITY_L3S_GCLK){}
            while(!per.L3_CLKSTCTRL.b.CLKACTIVITY_L3_GCLK){}

            while((per.OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L3_GCLK |
                   per.OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L4_GCLK) == false){}

            switch(tmr_num)
            {
                case TIMER_2:
                        while((per.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK |
                        per.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER2_GCLK) == false){}
                    break;
                case TIMER_3:
                        while((per.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK |
                        per.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER3_GCLK) == false){}
                    break;
                case TIMER_4:
                        while((per.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK |
                        per.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER4_GCLK) == false){}
                    break;
                case TIMER_7:
                        while((per.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK |
                        per.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER7_GCLK) == false){}
                    break;
                default:
                  break;
            }
        }

        void run_clk_DMTIMER_1ms(REGS::PRCM::e_TIMER1MS_CLKSEL clk_sel) noexcept
        {
            using namespace REGS::PRCM;
            using namespace REGS::RTC;
            auto& rtc = *AM335X_RTC;

            e_TIMER1MS_CLKSEL clksel_copy = clk_sel;

            // disable write protect RTC registers
            rtc.KICK0R.reg = REGS::RTC::KICK0R_KEY_DIS;
            rtc.KICK1R.reg = REGS::RTC::KICK1R_KEY_DIS;

            switch(clksel_copy)
            {
                /// it is also necessary to allow use of external or internal oscillator 32768 in RTC module ///
                case MS1_32768HZ:
                    // if RTC running
                    if(rtc.RTC_CTRL.b.STOP_RTC &&
                       !rtc.RTC_CTRL.b.RTC_DISABLE)
                    {
                        // if RTC running and clock source is internal, we cannot supply an external source
                        if(!rtc.RTC_OSC.b.SEL_32KCLK_SRC)
                        {
                            // external source used, just activate the remaining clocks
                            clksel_copy = MS1_32KHZ;
                            break;
                        }

                    }
                    // use external source
                    rtc.RTC_OSC.b.SEL_32KCLK_SRC = 0x0;
                    rtc.RTC_OSC.b.SEL_32KCLK_SRC = 0x1;
                    rtc.RTC_OSC.reg &= ~REGS::RTC::OSC_OSC32K_GZ_MSK;
                    rtc.RTC_OSC.b.OSC32K_GZ = 0x0;
                    break;
                case MS1_32KHZ:
                    // if RTC running
                    if(rtc.RTC_CTRL.b.STOP_RTC &&
                       !rtc.RTC_CTRL.b.RTC_DISABLE)
                    {
                        // if RTC running and clock source is external, we cannot supply an internal source
                        if(rtc.RTC_OSC.b.SEL_32KCLK_SRC)
                        {
                            // external source used, just activate the remaining clocks
                            clksel_copy = MS1_32768HZ;
                            break;
                        }
                    }

                    //  just use internal source
                    rtc.RTC_OSC.b.SEL_32KCLK_SRC = 0x0;
                    rtc.RTC_OSC.b.SEL_32KCLK_SRC = 0x0;
                    break;
                default:
                    break;
            }

            // enable write protect RTC registers
            rtc.KICK0R.reg = KICK0_KICK0_KEY_EN;
            rtc.KICK1R.reg = KICK1_KICK1_KEY_EN;

            auto& dpll = *AM335x_CM_DPLL;

            // Select the clock source for the Timer1ms instance.
            dpll.TIMER1MS_CLK.b.CLKSEL = 0x0;
            while(dpll.TIMER1MS_CLK.b.CLKSEL != 0x0){}

            dpll.TIMER1MS_CLK.b.CLKSEL = clksel_copy;    // select clock source
            while(dpll.TIMER1MS_CLK.b.CLKSEL != clksel_copy){}

            auto& wkup = *AM335x_CM_WKUP;

            // Configuring registers related to Wake-Up region.
            wkup.CONTROL_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;           // Writing to MODULEMODE field of CM_WKUP_CONTROL_CLKCTRL register.
            while(wkup.CONTROL_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE){}   // Waiting for MODULEMODE field to reflect the written value.

            wkup.CLKSTCTRL.b.CLKTRCTRL = NO_SLEEP;                           // Writing to CLKTRCTRL field of CM_PER_L3S_CLKSTCTRL register.
            while(wkup.CLKSTCTRL.b.CLKTRCTRL != NO_SLEEP){}                   // Waiting for CLKTRCTRL field to reflect the written value.

            wkup.L3_AON_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;                     // Writing to CLKTRCTRL field of CM_L3_AON_CLKSTCTRL register.
            while(wkup.L3_AON_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP){}             // Waiting for CLKTRCTRL field to reflect the written value.

            wkup.TIMER1_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(wkup.TIMER1_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE){}
            while(wkup.TIMER1_CLKCTRL.b.IDLEST != IDLEST_FUNC){}
        }

        void run_clk_DMTIMER_5() noexcept
        {
            using namespace REGS::PRCM;
            auto& dpll = *AM335x_CM_DPLL;
            auto& per = *AM335x_CM_PER;

            /* Select the clock source for the Timer5 instance. */
            dpll.TIMER5_CLK.b.CLKSEL = 0x0;               // clear bitfield
            dpll.TIMER5_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
            while(dpll.TIMER5_CLK.b.CLKSEL != CLK_M_OSC){}

            per.TIMER5_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(per.TIMER5_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE){}

            while((per.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK |
            per.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER5_GCLK) == false){}
        }

        void run_clk_DMTIMER_6() noexcept
        {
            using namespace REGS::PRCM;
            auto& dpll = *AM335x_CM_DPLL;
            auto& per = *AM335x_CM_PER;

            /* Select the clock source for the Timer6 instance. */
            dpll.TIMER6_CLK.b.CLKSEL = 0x0;               // clear bitfield
            dpll.TIMER6_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
            while(dpll.TIMER6_CLK.b.CLKSEL != CLK_M_OSC){}

            per.TIMER6_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(per.TIMER6_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE){}

            while((per.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK |
            per.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER6_GCLK) == false){}
        }

    // dmtimer template instantiating
    template class hwTimer<AM335x_DMTIMER_Type>;                             // for DMTimer 0,2,3,4,5,6,7
    template class hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>;        // for DMTimer_1ms

    hwTimer<> dm_timer_0(AM335X_DMTIMER_0);
    hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type> dm_timer_1ms(REGS::DMTIMER1MS::AM335X_DMTIMER_1MS);
          hwTimer<> dm_timer_2(AM335X_DMTIMER_2);
    //      hwTimer<> dm_timer_3(AM335X_DMTIMER_3);
    //      hwTimer<> dm_timer_4(AM335X_DMTIMER_4);
    //      hwTimer<> dm_timer_5(AM335X_DMTIMER_5);
    //      hwTimer<> dm_timer_6(AM335X_DMTIMER_6);
    //      hwTimer<> dm_timer_7(AM335X_DMTIMER_7);
}