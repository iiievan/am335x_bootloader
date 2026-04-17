#include "INTController.hpp"
#include "cpu.h"
#include "cp15.h"

INTController_t intc;

isr_handler_t* interrupt_vectors = nullptr;

using namespace REGS::INTC;

static void int_def_hndlr(void *p_obj)
{
    p_obj = p_obj;
}

void  INTController_t::init (void)
{ 
    interrupt_vectors = &m_interrupt_vectors[0];
    
    // Reset the ARM interrupt controller 
    m_INTC_regs.SYSCONFIG.b.SoftReset = 0x1;
 
    // Wait for the reset to complete  
    while(m_INTC_regs.SYSSTATUS.b.ResetDone != 0x1);
    
    // Enable any interrupt generation by setting priority threshold 0xFF 
    m_INTC_regs.THRESHOLD.b.PriorityThreshold = PRIORITY_THRESHOLD;
    
    // Disable all pending interrupts */
    m_INTC_regs.ISR_CLEAR0.reg = 0xFF;
    m_INTC_regs.ISR_CLEAR1.reg = 0xFF;
    m_INTC_regs.ISR_CLEAR2.reg = 0xFF;
    m_INTC_regs.ISR_CLEAR3.reg = 0xFF;

    for (uint32_t int_id = 0; int_id < INT_NUM_MAX; int_id++)
    {
        register_handler((e_INT_ID)int_id,(isr_handler_t)int_def_hndlr);
    }
    
    m_INTC_regs.CONTROL.b.NewIRQAgr = 0x1; //Reset IRQ output and enable new IRQ generation
    m_INTC_regs.CONTROL.b.NewFIQAgr = 0x1; //Reset FIQ output and enable new FIQ generation
} 

void  INTController_t::register_handler(e_INT_ID  int_id, isr_handler_t isr_fnct)
{
    if (int_id > INT_NUM_MAX)
        return;

    // assign ISR
    m_interrupt_vectors[int_id] = isr_fnct;
}

void  INTController_t::unregister_handler(e_INT_ID int_id)
{   
    if (int_id > INT_NUM_MAX)
        return;

    m_interrupt_vectors[int_id] = int_def_hndlr;
}

void  INTController_t::interface_clk_set(bool mode)
{    
    if(mode)
    {
        //Internal OCP clock gating strategy - autoClkGate.
        m_INTC_regs.SYSCONFIG.b.Autoidle = 0x1;
    }
    else
    {
        //Internal OCP clock gating strategy - clkfree.
        m_INTC_regs.SYSCONFIG.b.Autoidle = 0x0;
    }
}

void  INTController_t::protection_enable(bool mode)
{
    if(mode)
        m_INTC_regs.PROTECTION.b.Protection = 0x1;
    else
        m_INTC_regs.PROTECTION.b.Protection = 0x0;
}

void  INTController_t::low_power_turbo(bool mode)
{
    if(mode)
    {
        // clock is auto-gated
        m_INTC_regs.IDLE.b.Turbo = 0x1;
    }
    else
    {
        // is free running (default),
        m_INTC_regs.IDLE.b.Turbo = 0x0;
    }
}

void  INTController_t::low_power_funcidle(bool mode)
{
    if(mode)
    {
        //functional clock gating strategy is applied.
        m_INTC_regs.IDLE.b.FuncIdle = 0x1;
    }
    else
    {
        //functional clock is free running
        m_INTC_regs.IDLE.b.FuncIdle = 0x0;
    }
}

void  INTController_t::priority_threshold_set(uint8_t threshold)
{
    m_INTC_regs.THRESHOLD.b.PriorityThreshold = threshold;
}

void  INTController_t::software_int_set(e_INT_ID int_id)
{    
    if (int_id > INT_NUM_MAX)
        return;
    
    // Enable the software interrupt in the corresponding ISR_SET register
    ISR_SET_reg_t *s_isr_set = get_ISR_SET_reference(int_id);
    s_isr_set->b.IsrSet |= BIT(int_id % 32);
}

void  INTController_t::software_int_clear(e_INT_ID int_id)
{
    if (int_id > INT_NUM_MAX)
        return;
    
    // Disable the software interrupt in the corresponding ISR_CLEAR register 
    ISR_CLEAR_reg_t *s_isr_clear = get_ISR_CLEAR_reference(int_id);
    s_isr_clear->b.IsrClear |= BIT(int_id % 32);
}

void  INTController_t::master_IRQ_enable(void)
{
    // Enable IRQ in CPSR
    CPUirqe();
}

void  INTController_t::master_IRQ_disable(void)
{
    // Disable IRQ in CPSR
    CPUirqd();
}

void  INTController_t::master_FIQ_enable(void)
{
    // Enable FIQ in CPSR.
    CPUfiqe();
}

void  INTController_t::master_FIQ_disable(void)
{
    // Disable FIQ in CPSR
    CPUfiqd();
}

void  INTController_t::unmask_interrupt(e_INT_ID int_id)
{
    if (int_id > INT_NUM_MAX)
        return;
    
    cp15_DSB_barrier();
    // Disable the system interrupt in the corresponding MIR_CLEAR register
    MIR_CLEAR_reg_t *s_mir_clear = get_MIR_CLEAR_reference(int_id);
    s_mir_clear->b.MirClear = BIT(int_id % 32);
}

void  INTController_t::mask_interrupt(e_INT_ID int_id)
{
    if (int_id > INT_NUM_MAX)
        return;
    
    cp15_DSB_barrier();
    // Enable the system interrupt in the corresponding MIR_SET register
    MIR_SET_reg_t *s_mir_set = get_MIR_SET_reference(int_id);
    s_mir_set->b.MirSet = BIT(int_id % 32);   
}

void  INTController_t::sys_enable(uint8_t  status)
{
    if((status & 0x80) == 0) 
        master_IRQ_enable();
}

uint8_t  INTController_t::sys_disable(void)
{
    // Reads the current status.
    uint8_t status = (master_status_get() & 0xFF);

    // Disable the Interrupts.
    master_IRQ_disable();

    return status;
}

#if defined(am335x) 
void  INTController_t::priority_set(e_INT_ID int_id, uint32_t priority)
{
    INTC_ILR_reg_t *sILR = get_ILR_reference(int_id);
    sILR->b.Priority = priority;

    // by defualt to IRQ - 0x0 ,for am335x SoCs
    sILR->b.FIQnIRQ  = HOSTINT_ROUTE_IRQ;

}
#else
void  INTController_t::priority_set(e_INT_ID int_id, uint32_t priority, uint32_t host_int_route)
{
    INTC_ILR_reg_t *&sILR = get_ILR_reference(int_id);
    sILR->b.Priority = priority;    

    sILR->b.FIQnIRQ  = host_int_route;
}
#endif

uint32_t  INTController_t::master_status_get(void)
{
    return CPUIntStatus();
}

uint32_t  INTController_t::active_IRQ_num_get(void)
{
    return   m_INTC_regs.SIR_IRQ.b.ActiveIRQ;
}

#if !defined(am335x)
uint32_t  INTController_t::active_FIQ_num_get(void)
{
    return   m_INTC_regs.SIR_FIQ.b.ActiveFIQ;
}
#endif

uint32_t  INTController_t::spur_IRQ_flag_get(void)
{
             // return sputious(masked) interrupt
    return   m_INTC_regs.SIR_IRQ.b.SpuriousIRQ;
}

#if !defined(am335x)
uint32_t  INTController_t::spur_FIQ_flag_get(void)
{
    return   m_INTC_regs.SIR_FIQ.b.SpuriousFIQ;
}
#endif

uint32_t  INTController_t::curr_IRQ_priorigty_get(void)
{
    return m_INTC_regs.IRQ_PRIORITY.b.IRQPriority;
}

#if !defined(am335x)
uint32_t  INTController_t::curr_FIQ_priority_get(void)
{
    return m_INTC_regs.FIQ_PRIORITY.b.FIQPriority;
}
#endif

uint8_t  INTController_t::priority_threshold_get(void)
{
    return m_INTC_regs.THRESHOLD.b.PriorityThreshold;
}

bool  INTController_t::raw_status_get(e_INT_ID int_id)
{
    ITR_reg_t *s_raw_sts = get_ITR_reference(int_id);
    
    if(s_raw_sts->b.Itr & BIT(int_id % 32))
        return true;

    return false;
}

bool  INTController_t::pending_IRQ_masked_status_get(e_INT_ID int_id)
{
    PENDING_IRQ_reg_t *s_pending = get_pending_IRQ_reference(int_id);
    
    if(s_pending->b.PendingIRQ & BIT(int_id % 32))
        return true;

    return false;
}

#if !defined(am335x)
bool  am335x_intc::pending_FIQ_masked_status_get(e_INT_ID int_id)
{
    PENDING_FIQ_reg_t *&s_pending = get_pending_FIQ_reference(int_id);
    
    if(s_pending->b.PendingFIQ & BIT(int_id % 32))
        return true;
    else
        return false;
} 
#endif
