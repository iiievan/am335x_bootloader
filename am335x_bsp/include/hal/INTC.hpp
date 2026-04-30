#ifndef __HAL_INTC_H_
#define __HAL_INTC_H_

#include "regs/REGS.hpp"


namespace HAL::INTC
{
    using isr_handler_t = void (*)(void* param);
    extern "C" isr_handler_t* const interrupt_vectors;

    void  init() noexcept;
    void  register_handler(REGS::INTC::e_INT_ID  int_id,  isr_handler_t isr_fnct) noexcept;
    void  unregister_handler(REGS::INTC::e_INT_ID int_id) noexcept;

    void  interface_clk_set(bool mode) noexcept;
    void  protection_enable(bool mode) noexcept;
    void  low_power_turbo(bool mode) noexcept;
    void  low_power_funcidle(bool mode) noexcept;
    void  priority_threshold_set(uint8_t threshold) noexcept;

    void  software_int_set(REGS::INTC::e_INT_ID int_id) noexcept;
    void  software_int_clear(REGS::INTC::e_INT_ID int_id) noexcept;

    void  master_IRQ_enable() noexcept;
    void  master_IRQ_disable() noexcept;
    void  master_FIQ_enable() noexcept;
    void  master_FIQ_disable() noexcept;
uint32_t  master_status_get() noexcept;

    void  unmask_interrupt(REGS::INTC::e_INT_ID int_id) noexcept;
    void  mask_interrupt(REGS::INTC::e_INT_ID int_id) noexcept;

    void  sys_enable(uint8_t  status) noexcept;
 uint8_t  sys_disable() noexcept;

    void  priority_set(REGS::INTC::e_INT_ID int_id, uint32_t priority, uint32_t route = REGS::INTC::HOSTINT_ROUTE_IRQ) noexcept;


 uint8_t  priority_threshold_get() noexcept;
    bool  raw_status_get(REGS::INTC::e_INT_ID int_id) noexcept;

uint32_t  active_IRQ_num_get() noexcept;
uint32_t  spur_IRQ_flag_get() noexcept;
uint32_t  curr_IRQ_priorigty_get() noexcept;
    bool  pending_IRQ_masked_status_get(REGS::INTC::e_INT_ID int_id) noexcept;

#if !defined(am335x)
        uint32_t  active_FIQ_num_get() noexcept;
        uint32_t  curr_FIQ_priority_get() noexcept;
        uint32_t  spur_FIQ_flag_get() noexcept;
            bool  pending_FIQ_masked_status_get(REGS::INTC::e_INT_ID int_id) noexcept;
#endif
};


#endif //__HAL_INTC_H_
