#ifndef __AM335x_DMTIMER_H
#define __AM335x_DMTIMER_H

#include <cstdint>
#include "regs/REGS.hpp"

namespace HAL::TIMERS
{
    template <typename DMT = REGS::DMTIMER::AM335x_DMTIMER_Type> // and REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type
    class hwTimer
    {
        DMT  &m_regs;     // hwTimer registers

    public:
        typedef struct
        {
            uint32_t tldr;
            uint32_t tmar;
            uint32_t irqenableset;
            uint32_t tcrr;
            uint32_t tclr;
        } dmtimer_context_t;

    protected:
        volatile uint64_t m_time; // the timer time
        bool  m_is_paused { true };

    private:

        dmtimer_context_t  m_context;  // dmtimer context for rebooting
        void  m_wait_for_write(REGS::DMTIMER::e_TWPS_flags twps_mask) noexcept;

    public:
        explicit hwTimer(DMT *p_tmr_regs) noexcept;
        ~hwTimer() = default;

        void  enable() noexcept;
        void  disable() noexcept;

        void  mode_configure(REGS::DMTIMER::e_DMTIMER_mode mode) noexcept;
        void  prescaler_clk_enable(REGS::DMTIMER::e_PRSC ptv) noexcept;
        void  prescaler_clk_disable() noexcept;

        void  set_1ms_block(int32_t pos = 232000, int32_t neg = (-768000)) noexcept;
        void  counter_set(uint32_t counter) noexcept;
        uint32_t  counter_get() noexcept;

        void  reload_set(uint32_t reload) noexcept;
        uint32_t  reload_get() noexcept;

        void  GPO_configure(bool gpo_cfg) noexcept;
        void  compare_set(uint32_t compare_val) noexcept;
        uint32_t  compare_get() noexcept;

        void  IRQ_raw_set(REGS::DMTIMER::e_IRQ_flags int_flags) noexcept;
        uint32_t  IRQ_raw_get() noexcept;
        uint32_t  IRQ_get() noexcept;
        void  IRQ_clear(REGS::DMTIMER::e_IRQ_flags int_flags) noexcept;
        void  IRQ_enable(REGS::DMTIMER::e_IRQ_flags int_flags) noexcept;
        void  IRQ_disable(REGS::DMTIMER::e_IRQ_flags int_flags) noexcept;

        void  trigger_set() noexcept;
        uint32_t  IRQ_enable_get() noexcept;

        void  reset_configure(bool rst_option) noexcept;
        void  reset() noexcept;

        void  posted_mode_config(bool post_mode) noexcept;
        bool  posted_status_get() noexcept;

        void  context_save() noexcept;
        void  context_restore() noexcept;

        REGS::DMTIMER::e_TIMER_NUM  get_DMTIMER_number() noexcept;
        REGS::INTC::e_INT_ID get_DMTIMER_sys_interrupt() noexcept;

        void  set_debug_EMUFREE(bool emufree_val = false) noexcept;
        bool  get_debug_EMUFREE() noexcept;
        /**
         * @brief   Check if timer is enbled
         * @return  true - timer is enabled
         *          false - timer is disabled
         **/
        [[nodiscard]] bool  check_busy() const noexcept { return m_is_paused; }

    };

    extern void dmtimer_irqhandler(void *p_obj) noexcept;

    void run_clk_interconnects() noexcept;
    void run_clk_DMTIMER(REGS::DMTIMER::e_TIMER_NUM tmr_num) noexcept;
    void run_clk_DMTIMER_1ms(REGS::PRCM::e_TIMER1MS_CLKSEL clk_sel) noexcept;
    void run_clk_DMTIMER_5() noexcept;
    void run_clk_DMTIMER_6() noexcept;

    extern hwTimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_0;
    extern hwTimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type> dm_timer_1ms;
    extern hwTimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_2;
    extern hwTimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_3;
    extern hwTimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_4;
    extern hwTimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_5;
    extern hwTimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_6;
    extern hwTimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_7;
}
#endif //__DM_TIMER_H