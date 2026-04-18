#include "HAL/INTC.hpp"
#include "cpu.h"
#include "cp15.h"

namespace HAL::INTC
{
    using namespace REGS::INTC;

    /**
     * Do not rename, symbol 'interrupt_vectors' used in exceptionhandlers.s of startup as a pointer!!!!!
     */
    static isr_handler_t s_interrupt_vectors[INT_NUM_MAX + 1];
    extern "C" isr_handler_t* const interrupt_vectors = s_interrupt_vectors;

    static void default_handler(void*) noexcept { }

    /**
      * @brief   This API is used to initialize the interrupt controller. This API
      *          shall be called before using the interrupt controller.
    **/
    void  init() noexcept
    {
        auto &ic = *AM335x_INTC;

        // Reset the ARM interrupt controller and wait to complete
        ic.SYSCONFIG.b.SoftReset = 0x1;
        while(ic.SYSSTATUS.b.ResetDone != 0x1){ }

        // Enable any interrupt generation by setting priority threshold 0xFF
        ic.THRESHOLD.b.PriorityThreshold = PRIORITY_THRESHOLD;

        // Disable all pending interrupts */
        ic.ISR_CLEAR0.reg = 0xFF;
        ic.ISR_CLEAR1.reg = 0xFF;
        ic.ISR_CLEAR2.reg = 0xFF;
        ic.ISR_CLEAR3.reg = 0xFF;

        for (uint32_t i = 0; i <= INT_NUM_MAX; ++i)
            interrupt_vectors[i] = default_handler;

        ic.CONTROL.b.NewIRQAgr = 0x1; //Reset IRQ output and enable new IRQ generation
        ic.CONTROL.b.NewFIQAgr = 0x1; //Reset FIQ output and enable new FIQ generation
    }

    /**
     * @brief    Registers an interrupt Handler in the interrupt vector table for
     *           system interrupts.
     * @param    int_id - Interrupt Number
     * @param    isr_fnct - Function pointer to the ISR
     *
     *           Note: When the interrupt occurs for the sytem interrupt number indicated,
     *           the control goes to the ISR given as the parameter.
     **/
    void  register_handler(e_INT_ID  int_id, isr_handler_t isr_fnct) noexcept
    {
        if (int_id > INT_NUM_MAX)
            return;

        interrupt_vectors[int_id] = isr_fnct;
    }

    /**
    * @brief   Unregisters an interrupt
    * @param   int_id - Interrupt Number
    *
    *          Note: Once an interrupt is unregistered it will enter infinite loop once
    *          an interrupt occurs
    **/
    void  unregister_handler(e_INT_ID int_id) noexcept
    {
        if (int_id > INT_NUM_MAX)
            return;

        interrupt_vectors[int_id] = default_handler;
    }

    /**
    * @brief   Sets the interface clock to be free running
    * @param  mode 'true' - automatic clock gating strategy is applied
    *                       based on the interface bus activity.
    *              'false' - clk freerun set
    **/
    void  interface_clk_set(bool mode) noexcept
    {
        auto &ic = *AM335x_INTC;

        if(mode)
            ic.SYSCONFIG.b.Autoidle = 0x1;
        else
            ic.SYSCONFIG.b.Autoidle = 0x0;
    }

    /**
    * @brief   Enables protection mode for the interrupt controller register access.
    * @param   mode 'true' - When the protection is enabled, the registers will be accessible only
    *                        in privileged mode of the CPU.
    *               'false' - When the protection is disabled, the registers will be accessible
    *                         in both unprivileged and privileged mode of the CPU.
    **/
    void  protection_enable(bool mode) noexcept
    {
        auto &ic = *AM335x_INTC;
        if(mode)
            ic.PROTECTION.b.Protection = 0x1;
        else
            ic.PROTECTION.b.Protection = 0x0;
    }

    /**
     * @brief   Enables input synchronizer clock
     * @param   mode 'true' - Input synchronizer clock is auto-gated
     *               'false' - Input synchronizer clock is free run
    **/
    void  low_power_turbo(bool mode) noexcept
    {
        auto &ic = *AM335x_INTC;

        if(mode)
            ic.IDLE.b.Turbo = 0x1;
        else
            ic.IDLE.b.Turbo = 0x0;
    }

    /**
     * @brief   Enables of functional clock
     * @param  mode 'false' - functional clock is free running.
     *              'true' - functional clock gating strategy is applied.
    **/
    void  low_power_funcidle(bool mode) noexcept
    {
        auto &ic = *AM335x_INTC;
        if(mode)
            ic.IDLE.b.FuncIdle = 0x1;
        else
            ic.IDLE.b.FuncIdle = 0x0;
    }

    /**
     * @brief   Sets the given priority threshold value.
     * @param   threshold - Priority threshold value
     *          'threshold' can take any value from 0x00 to 0x7F. To disable
     *          priority threshold, write 0xFF.
    **/
    void  priority_threshold_set(uint8_t threshold) noexcept
    {
        auto &ic = *AM335x_INTC;
        ic.THRESHOLD.b.PriorityThreshold = threshold;
    }

    /**
     * @brief   Sets software interrupt for the given interrupt number.
     * @param   int_id - the system interrupt number, for which software interrupt
     *                    to be generated
    **/
    void  software_int_set(e_INT_ID int_id) noexcept
    {
        if (int_id > INT_NUM_MAX)
            return;

        // Enable the software interrupt in the corresponding ISR_SET register
        ISR_SET_reg_t *s_isr_set = get_ISR_SET_reference(int_id);
        s_isr_set->b.IsrSet |= BIT(int_id % 32);
    }

    /**
     * @brief   Clears the software interrupt for the given interrupt number.
     * @param   int_id - the system interrupt number, for which software interrupt
     *                    to be cleared.
    **/
    void  software_int_clear(e_INT_ID int_id) noexcept
    {
        if (int_id > INT_NUM_MAX)
            return;

        // Disable the software interrupt in the corresponding ISR_CLEAR register
        ISR_CLEAR_reg_t *s_isr_clear = get_ISR_CLEAR_reference(int_id);
        s_isr_clear->b.IsrClear |= BIT(int_id % 32);
    }

    /**
     * @brief  Enables the processor IRQ only in CPSR. Makes the processor to
     *         respond to IRQs.  This does not affect the set of interrupts
     *         enabled/disabled in the AINTC.
     *
     *         Note: This function call shall be done only in previleged mode of ARM
    **/
    void  master_IRQ_enable() noexcept {  CPUirqe(); }

    /**
     * @brief  Disables the processor IRQ only in CPSR.Prevents the processor to
     *         respond to IRQs.  This does not affect the set of interrupts
     *         enabled/disabled in the AINTC.
     *
     *         Note: This function call shall be done only in previleged mode of ARM
    **/
    void  master_IRQ_disable() noexcept { CPUirqd(); }

    /**
     * @brief  Enables the processor FIQ only in CPSR. Makes the processor to
     *         respond to FIQs.  This does not affect the set of interrupts
     *         enabled/disabled in the AINTC.
     *
     *         Note: This function call shall be done only in previleged mode of ARM
    **/
    void  master_FIQ_enable() noexcept { CPUfiqe(); }

    /**
     * @brief  Disables the processor FIQ only in CPSR.Prevents the processor to
     *         respond to FIQs.  This does not affect the set of interrupts
     *         enabled/disabled in the AINTC.
     *
     *         Note: This function call shall be done only in previleged mode of ARM
    **/
    void  master_FIQ_disable() noexcept { CPUfiqd(); }

    /**
     * @brief    Returns the status of the interrupts FIQ and IRQ.
     * @return   Status of interrupt as in CPSR.
     *
     *           Note: This function call shall be done only in privileged mode of ARM
    **/
    uint32_t  master_status_get() noexcept { return CPUIntStatus(); }

    /**
     * @brief   This API enables the system interrupt in AINTC. However, for
     *          the interrupt generation, make sure that the interrupt is
     *          enabled at the peripheral level also.
     * @param   int_id  - Interrupt number
    **/
    void  unmask_interrupt(e_INT_ID int_id) noexcept
    {
        if (int_id > INT_NUM_MAX)
            return;

        cp15_DSB_barrier();

        // Disable the system interrupt in the corresponding MIR_CLEAR register
        MIR_CLEAR_reg_t *s_mir_clear = get_MIR_CLEAR_reference(int_id);
        s_mir_clear->b.MirClear = BIT(int_id % 32);
    }

    /**
     * @brief   This API disables the system interrupt in INTC.
     * @param   int_id  - Interrupt number
    **/
    void  mask_interrupt(e_INT_ID int_id) noexcept
    {
        if (int_id > INT_NUM_MAX)
            return;

        cp15_DSB_barrier();

        // Enable the system interrupt in the corresponding MIR_SET register
        MIR_SET_reg_t *s_mir_set = get_MIR_SET_reference(int_id);
        s_mir_set->b.MirSet = BIT(int_id % 32);
    }

    /**
     * @brief   Restore the processor IRQ only status. This does not affect
     *          the set of interrupts enabled/disabled in the INTC.
     * @param   status returned by the IntDisable fundtion.
     *
     *          Note: This function call shall be done only in previleged mode of ARM
    **/
    void  sys_enable(uint8_t  status) noexcept
    {
        if((status & 0x80) == 0) { master_IRQ_enable(); }
    }

    /**
     * @brief    Read and save the stasus and Disables the processor IRQ .
     *           Prevents the processor to respond to IRQs.
     * @return   Current status of IRQ
     *
     *           Note: This function call shall be done only in previleged mode of ARM
    **/
    uint8_t  sys_disable() noexcept
    {
        uint8_t status = (master_status_get() & 0xFF);

        master_IRQ_disable();

        return status;
    }

    /**
     * @brief   This API assigns a priority to an interrupt and routes it to
     *          either IRQ or to FIQ. Priority 0 is the highest priority level
     *          Among the host interrupts, FIQ has more priority than IRQ.
     * @param   int_id   - Interrupt number
     * @param   priority - Interrupt priority level
     *
     *          'priority' can take any value from 0 to 127, 0 being the highest and
     *          127(0x7F) being the lowest priority.
     *
     *          'host_int_route' can take one of the following values \n
     *          REGS::INTC::HOSTINT_ROUTE_IRQ - To route the interrupt to IRQ \n
     *          REGS::INTC::HOSTINT_ROUTE_FIQQ - To route the interrupt to FIQ
    **/
    void  priority_set(e_INT_ID int_id, uint32_t priority, uint32_t route) noexcept
    {
        INTC_ILR_reg_t *sILR = get_ILR_reference(int_id);
        sILR->b.Priority = priority;

        // by defualt to IRQ - 0x0 ,for am335x SoCs
        sILR->b.FIQnIRQ  = route;

    }

    /**
     * @brief   Returns the priority threshold.
     * @return  Priority threshold value.
    **/
    uint8_t  priority_threshold_get() noexcept
    {
        auto &ic = *AM335x_INTC;
        return ic.THRESHOLD.b.PriorityThreshold;
    }

    /**
     * @brief   Returns the raw interrupt status before masking.
     * @param   int_id - the system interrupt number.
     * @return  true - if the raw status is set \n
     *          false - if the raw status is not set.
    **/
    bool  raw_status_get(e_INT_ID int_id) noexcept
    {
        ITR_reg_t *s_raw_sts = get_ITR_reference(int_id);

        if(s_raw_sts->b.Itr & BIT(int_id % 32))
            return true;

        return false;
    }

    /**
     * @brief   Reads the active IRQ number.
     * @return  Active IRQ number.
    **/
    uint32_t  active_IRQ_num_get() noexcept
    {
        auto &ic = *AM335x_INTC;
        return   ic.SIR_IRQ.b.ActiveIRQ;
    }

    /**
     * @brief   Reads the spurious IRQ Flag. Spurious IRQ flag is reflected in both
     *          SIR_IRQ and IRQ_PRIORITY registers of the interrupt controller.
     * @return  Spurious(masked) IRQ Flag.
    **/
    uint32_t  spur_IRQ_flag_get() noexcept
    {
        auto &ic = *AM335x_INTC;
        return   ic.SIR_IRQ.b.SpuriousIRQ;
    }

    /**
     * @brief   Returns the currently active IRQ priority level.
     * @return  Current IRQ priority
    **/
    uint32_t  curr_IRQ_priorigty_get() noexcept
    {
        auto &ic = *AM335x_INTC;
        return ic.IRQ_PRIORITY.b.IRQPriority;
    }

    /**
     * @brief   Returns the IRQ status after masking.
     * @param   int_id - the system interrupt number
     * @return  true - if interrupt is pending \n
     *          false - in no interrupt is pending
    **/
    bool  pending_IRQ_masked_status_get(e_INT_ID int_id) noexcept
    {
        PENDING_IRQ_reg_t *s_pending = get_pending_IRQ_reference(int_id);

        if(s_pending->b.PendingIRQ & BIT(int_id % 32))
            return true;

        return false;
    }

    #if !defined(am335x)
    /** not for am335x SoCs **/

    uint32_t  active_FIQ_num_get() noexcept
    {
        auto &ic = *AM335x_INTC;
        return   ic.SIR_FIQ.b.ActiveFIQ;
    }

    uint32_t  curr_FIQ_priority_get() noexcept
    {
        auto &ic = *AM335x_INTC;
        return ic.FIQ_PRIORITY.b.FIQPriority;
    }

    uint32_t  spur_FIQ_flag_get() noexcept
    {
        auto &ic = *AM335x_INTC;
        return   ic.SIR_FIQ.b.SpuriousFIQ;
    }

    bool  pending_FIQ_masked_status_get(e_INT_ID int_id) noexcept
    {
        PENDING_FIQ_reg_t *&s_pending = get_pending_FIQ_reference(int_id);

        if(s_pending->b.PendingFIQ & BIT(int_id % 32))
            return true;

        return false;
    }
    #endif
}




