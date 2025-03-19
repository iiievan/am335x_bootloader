#include "stdint.h"

#include "init.h"
#include "board.hpp"
#include "cp15.h"
#include "am335x_intc.h"
#include "am335x_dmtimer.h"
#include "am335x_gpio.h"
#include "pin.h"
#include "sys_timer.h"
#include "PRCM.h"
#include "DMTIMER1MS.h"

extern "C" void Entry(void);
extern "C" void UndefInstHandler(void);
extern "C" void SVC_Handler(void);
extern "C" void AbortHandler(void);
extern "C" void IRQHandler(void);
extern "C" void FIQHandler(void);

// precision 1ms system timer for system time
sys_timer<SYST_t> sys_time(SYST_TIMER_ptr);
am335x_gpio gpio0(REGS::GPIO::AM335x_GPIO_0);
am335x_gpio gpio1(REGS::GPIO::AM335x_GPIO_1);
am335x_gpio gpio2(REGS::GPIO::AM335x_GPIO_2);
//am335x_gpio gpio3(REGS::GPIO::AM335x_GPIO_3);

static uint32_t const vec_tbl[14]=
{
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF014,    /* Opcode for loading PC with the contents of [PC + 0x14] */
    0xE24FF008,    /* Opcode for loading PC with (PC - 8) (eq. to while(1)) */
    0xE59FF010,    /* Opcode for loading PC with the contents of [PC + 0x10] */
    0xE59FF010,    /* Opcode for loading PC with the contents of [PC + 0x10] */
    (uint32_t)Entry,
    (uint32_t)UndefInstHandler,
    (uint32_t)SVC_Handler,
    (uint32_t)AbortHandler,
    (uint32_t)IRQHandler,
    (uint32_t)FIQHandler
};

static void copy_vector_table(void)
{
    uint32_t *dest = (uint32_t *)AM335X_VECTOR_BASE;
    uint32_t *src  = (uint32_t *)vec_tbl;
    uint32_t count;
  
    CP15VectorBaseAddrSet(AM335X_VECTOR_BASE);

    for(count = 0; count < sizeof(vec_tbl)/sizeof(vec_tbl[0]); count++)
    {
        dest[count] = src[count];
    }
}

void init_board(void)
{ 
    copy_vector_table();
           
    intc.init();                       //Initializing the ARM Interrupt Controller.
    
    // setup system timer for 1ms interrupt 
    sys_time.init();
    
    gpio1.init();     
    USR_LED_0.sel_pinmode(PINS::e_GPMC_A5::gpio1_21);
    USR_LED_0.dir_set(REGS::GPIO::GPIO_OUTPUT);    
    USR_LED_1.sel_pinmode(PINS::e_GPMC_A6::gpio1_22);
    USR_LED_1.dir_set(REGS::GPIO::GPIO_OUTPUT);    
    USR_LED_2.sel_pinmode(PINS::e_GPMC_A7::gpio1_23);
    USR_LED_2.dir_set(REGS::GPIO::GPIO_OUTPUT);    
    USR_LED_3.sel_pinmode(PINS::e_GPMC_A8::gpio1_24);
    USR_LED_3.dir_set(REGS::GPIO::GPIO_OUTPUT);
    
    intc.master_IRQ_enable();    
}

