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
#include "prcm_.h"
#include "control.h"
#include "emif.h"
#include "EMIF.hpp"
#include "MMCHS.hpp"
#include "serial.hpp"
#include "common.h"

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

serial serial_uart_0(REGS::UART::AM335X_UART_0);

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

void input_callback(char c) 
{
    // echo input back out
    serial_uart_0.putc(c);
}

void init_board(void)
{ 
    copy_vector_table();
    
    mpu_pll_init();
    core_pll_init();
    per_pll_init();
    ddr_pll_init();
    interface_clocks_init();
           
    intc.init();                       //Initializing the ARM Interrupt Controller.
    intc.master_IRQ_enable();
    
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

    serial_uart_0.init(input_callback);
    
    USR_LED_0.set();    

    serial_uart_0.puts((char *)"bootloader started... \r\n");
    serial_uart_0.puts((char *)"UART initialized... \r\n"); 
    
    serial_uart_0.hexdump(0x01234567);
    serial_uart_0.puts((char *)"\n\r");
    serial_uart_0.hexdump(0x89ABCDEF);
    serial_uart_0.puts((char *)"\n\r");
    
     // initialize DDR3L, values hardcoded for D2516EC4BXGGB 
    ddr_init();
  
    if (REG(EMIF0_STATUS) & 0x4) 
    {
        serial_uart_0.puts((char *)"DDR3L initialized\n\r");
    } 
    else 
    {
        serial_uart_0.puts((char *)"DDR3L initialization failed...\n\r");
        return;
    }
    
    // check reading and writing to external DRAM before continuing */
    if (!ddr_check()) 
    {
        serial_uart_0.puts((char *)"DDR3L read/write check passed\n\r");
    } 
    else 
    {
        serial_uart_0.puts((char *)"DDR3L read/write check failed...\n\r");
        return;
    }        
}


// MPU PLL Configuration based on AM335x TRM 8.1.6.9.1 
// 1GHz clock based on AM335x datasheet table 3.1 AM3358BZCZ100 
void mpu_pll_init(void) 
{
  uint32_t x;
  
  // Switch PLL to bypass mode
  x = REG(CM_CLKMODE_DPLL_MPU);
  x &= ~0x7;
  x |= 0x4;
  REG(CM_CLKMODE_DPLL_MPU) = x;
  
  // wait for bypass status 
  while (!(REG(CM_IDLEST_DPLL_MPU) & 0x100)) {}

  // configure divider and multipler 
  // DPLL_MULT = 1000, DPLL_DIV = 23 (actual division factor is N+1) 
  // 24MHz*1000/24 = 1GHz 
  REG(CM_CLKSEL_DPLL_MPU) = (1000 << 8) | (23);

  // Set M2 Divider 
  REG(CM_DIV_M2_DPLL_MPU) &= ~0x1F;
  REG(CM_DIV_M2_DPLL_MPU) |= 1;

  // Enable, locking PLL 
  x = REG(CM_CLKMODE_DPLL_MPU);
  x |= 0x7;
  REG(CM_CLKMODE_DPLL_MPU) = x;
  
  // wait for locking to finish 
  while (!(REG(CM_IDLEST_DPLL_MPU) & 0x1)) {}
}

// Core PLL Configuration based on AM335x TRM 8.1.6.7.1 
// All values based on AM335x TRM Table 8-22 Core PLL Typical Frequencies OPP100 
// clock source is 24MHz crystal on OSC0-IN (BBB schematic page 3) 
void core_pll_init(void) 
{
  uint32_t x;
  
  // Switch PLL to bypass mode 
  x = REG(CM_CLKMODE_DPLL_CORE);
  x &= ~0x7;
  x |= 0x4;
  REG(CM_CLKMODE_DPLL_CORE) = x;
  
  // wait for bypass status 
  while (!(REG(CM_IDLEST_DPLL_CORE) & 0x100)) {}

  // configure divider and multipler 
  // DPLL_MULT = 1000, DPLL_DIV = 23 (actual division factor is N+1) 
  // 24MHz*1000/24 = 1GHz 
  REG(CM_CLKSEL_DPLL_CORE) = (500 << 8) | (23);

  // Set M4 Divider 
  REG(CM_DIV_M4_DPLL_CORE) &= ~0x1F;
  REG(CM_DIV_M4_DPLL_CORE) |= 10;

  // Set the M5 Divider 
  REG(CM_DIV_M5_DPLL_CORE) &= ~0x1F;
  REG(CM_DIV_M5_DPLL_CORE) |= 8;

  // Set the M6 Divider 
  REG(CM_DIV_M6_DPLL_CORE) &= ~0x1F;
  REG(CM_DIV_M6_DPLL_CORE) |= 4;

  // Enable, locking PLL 
  x = REG(CM_CLKMODE_DPLL_CORE);
  x |= 0x7;
  REG(CM_CLKMODE_DPLL_CORE) = x;
  
  // wait for locking to finish 
  while (!(REG(CM_IDLEST_DPLL_CORE) & 0x1)) {}
}

// PER PLL Configuration based on AM335x TRM 8.1.6.8.1 
// All values based on AM335x TRM Table 8-24 PER PLL Typical Frequencies OPP100 
// clock source is 24MHz crystal on OSC0-IN (BBB schematic page 3) 
void per_pll_init(void) 
{
  uint32_t x;
  
  // Switch PLL to bypass mode 
  x = REG(CM_CLKMODE_DPLL_PER);
  x &= ~0x7;
  x |= 0x4;
  REG(CM_CLKMODE_DPLL_PER) = x;
  
  // wait for bypass status 
  while (!(REG(CM_IDLEST_DPLL_PER) & 0x100)) {}

  // configure divider and multipler 
  // DPLL_MULT = 960, DPLL_DIV = 23 (actual division factor is N+1) 
  // 24MHz*960/24 = 960MHz 
  REG(CM_CLKSEL_DPLL_PER) = (960 << 8) | (23);

  // Set M2 Divider 
  REG(CM_DIV_M2_DPLL_PER) &= ~0x7F;
  REG(CM_DIV_M2_DPLL_PER) |= 5;

  // Enable, locking PLL 
  x = REG(CM_CLKMODE_DPLL_PER);
  x |= 0x7;
  REG(CM_CLKMODE_DPLL_PER) = x;
  
  // wait for locking to finish 
  while (!(REG(CM_IDLEST_DPLL_PER) & 0x1)) {}
}

// DDR PLL Configuration based on AM335x TRM 8.1.6.11.1 
// 400MHz based on Table 5-5 of AM335x datasheet DDR3L max frequency 
// clock source is 24MHz crystal on OSC0-IN (BBB schematic page 3) 
void ddr_pll_init(void) 
{
  uint32_t x;
  
  // Switch PLL to bypass mode 
  x = REG(CM_CLKMODE_DPLL_DDR);
  x &= ~0x7;
  x |= 0x4;
  REG(CM_CLKMODE_DPLL_DDR) = x;
  
  // wait for bypass status 
  while (!(REG(CM_IDLEST_DPLL_DDR) & 0x100)) {}

  // configure divider and multipler 
  // DPLL_MULT = 400, DPLL_DIV = 23 (actual division factor is N+1) 
  // 24MHz*400/24 = 400MHz 
  REG(CM_CLKSEL_DPLL_DDR) = (400 << 8) | (23);

  // Set M2 Divider 
  REG(CM_DIV_M2_DPLL_DDR) &= ~0x1F;
  REG(CM_DIV_M2_DPLL_DDR) |= 1;

  // Enable, locking PLL 
  x = REG(CM_CLKMODE_DPLL_DDR);
  x |= 0x7;
  REG(CM_CLKMODE_DPLL_DDR) = x;
  
  // wait for locking to finish 
  while (!(REG(CM_IDLEST_DPLL_DDR) & 0x1)) {}
}

// initialize all the interface clocks and prcm domains we will be using 
void interface_clocks_init(void) 
{
  // WKUP domain enable 
  REG(CM_WKUP_CONTROL_CLKCTRL) = 0x2;
  
  // PER domain enable 
  REG(CM_PER_L4LS_CLKCTRL) = 0x2;
  
  // L3 interconnect clocks enable 
  REG(CM_PER_L3_CLKCTRL) = 0x2;

  // WKUP domain force wakeup 
  REG(CM_WKUP_CLKSTCTRL) = 0x2;
  
  // PER domain force wakeup 
  REG(CM_PER_L4LS_CLKSTCTRL) = 0x2;
  
  // L3 interconnect force wakeup 
  REG(CM_PER_L3_CLKSTCTRL) = 0x2;
}

void ddr_init(void) 
{
  // enable functional clock PD_PER_EMIF_GCLK 
  REG(CM_PER_EMIF_CLKCTRL) = 0x2;
  REG(CM_PER_EMIF_FW_CLKCTRL) = 0x2;

  // wait for clocks to be enabled 
  while (!((REG(CM_PER_L3_CLKSTCTRL) & 0x4) && (REG(CM_PER_L3_CLKSTCTRL) & 0x8))) {}

  // Note beaglebone black does not have VTT termination 
  // initialize virtual temperature process compensation 
  REG(CONTROL_MODULE_VTP_CTRL) |= 0x40;
  REG(CONTROL_MODULE_VTP_CTRL) &= ~0x1;
  REG(CONTROL_MODULE_VTP_CTRL) |= 0x1;

  while (!(REG(CONTROL_MODULE_VTP_CTRL) & 0x20)) {}

  // PHY CONFIG CMD 
  REG(CMD0_REG_PHY_CTRL_SLAVE_RATIO_0) = DDR3_CMD_SLAVE_RATIO;
  REG(CMD0_REG_PHY_INVERT_CLKOUT_0) = DDR3_CMD_INVERT_CLKOUT;

  REG(CMD1_REG_PHY_CTRL_SLAVE_RATIO_0) = DDR3_CMD_SLAVE_RATIO;
  REG(CMD1_REG_PHY_INVERT_CLKOUT_0) = DDR3_CMD_INVERT_CLKOUT;

  REG(CMD2_REG_PHY_CTRL_SLAVE_RATIO_0) = DDR3_CMD_SLAVE_RATIO;
  REG(CMD2_REG_PHY_INVERT_CLKOUT_0) = DDR3_CMD_INVERT_CLKOUT;
  
  // PHY CONFIG DATA 
  REG(DATA0_REG_PHY_RD_DQS_SLAVE_RATIO_0) = DDR3_DATA0_RD_DQS_SLAVE_RATIO;
  REG(DATA0_REG_PHY_WR_DQS_SLAVE_RATIO_0) = DDR3_DATA0_WR_DQS_SLAVE_RATIO;
  REG(DATA0_REG_PHY_FIFO_WE_SLAVE_RATIO_0) = DDR3_DATA0_FIFO_WE_SLAVE_RATIO;
  REG(DATA0_REG_PHY_WR_DATA_SLAVE_RATIO_0) = DDR3_DATA0_WR_DATA_SLAVE_RATIO;

  REG(DATA1_REG_PHY_RD_DQS_SLAVE_RATIO_0) = DDR3_DATA0_RD_DQS_SLAVE_RATIO;
  REG(DATA1_REG_PHY_WR_DQS_SLAVE_RATIO_0) = DDR3_DATA0_WR_DQS_SLAVE_RATIO;
  REG(DATA1_REG_PHY_FIFO_WE_SLAVE_RATIO_0) = DDR3_DATA0_FIFO_WE_SLAVE_RATIO;
  REG(DATA1_REG_PHY_WR_DATA_SLAVE_RATIO_0) = DDR3_DATA0_WR_DATA_SLAVE_RATIO;

  // IO CONTROL REGISTERS 
  REG(CONTROL_MODULE_DDR_CMD0_IOCTRL) = DDR3_IOCTRL_VALUE;
  REG(CONTROL_MODULE_DDR_CMD1_IOCTRL) = DDR3_IOCTRL_VALUE;
  REG(CONTROL_MODULE_DDR_CMD2_IOCTRL) = DDR3_IOCTRL_VALUE;
  REG(CONTROL_MODULE_DDR_DATA0_IOCTRL) = DDR3_IOCTRL_VALUE;
  REG(CONTROL_MODULE_DDR_DATA1_IOCTRL) = DDR3_IOCTRL_VALUE;

  // IO to work for DDR3 
  REG(CONTROL_MODULE_DDR_IO_CTRL) &= ~0x10000000;
  REG(CONTROL_MODULE_DDR_CKE_CTRL) |= 0x1;

  // EMIF TIMING CONFIG 
  REG(EMIF0_DDR_PHY_CTRL_1) = DDR3_READ_LATENCY;
  REG(EMIF0_DDR_PHY_CTRL_1_SHDW) = DDR3_READ_LATENCY;
  REG(EMIF0_DDR_PHY_CTRL_2) = DDR3_READ_LATENCY;

  REG(EMIF0_SDRAM_TIM_1) = DDR3_SDRAM_TIMING1;
  REG(EMIF0_SDRAM_TIM_1_SHDW) = DDR3_SDRAM_TIMING1;

  REG(EMIF0_SDRAM_TIM_2) = DDR3_SDRAM_TIMING2;
  REG(EMIF0_SDRAM_TIM_2_SHDW) = DDR3_SDRAM_TIMING2;

  REG(EMIF0_SDRAM_TIM_3) = DDR3_SDRAM_TIMING3;
  REG(EMIF0_SDRAM_TIM_3_SHDW) = DDR3_SDRAM_TIMING3;

  REG(EMIF0_SDRAM_REF_CTRL) = DDR3_REF_CTRL;
  REG(EMIF0_SDRAM_REF_CTRL_SHDW) = DDR3_REF_CTRL;
  REG(EMIF0_ZQ_CONFIG) = DDR3_ZQ_CONFIG;
  REG(EMIF0_SDRAM_CONFIG) = DDR3_SDRAM_CONFIG;
}

// read and write to some addresses in DDR, returns 0 on sucess 
uint8_t ddr_check(void) 
{
    uint32_t i;
    
    // write to a bunch of addresses 
    for (i = 0; i < 0x20000000; i += 0x2000) 
    {
        REG(DDR_START + i) = i;
    }
    
    // read from the same addresses and compare with expected value
    for (i = 0; i < 0x20000000; i += 0x2000) 
    {
      if (REG(DDR_START + i) != i) 
      {
        return 1;
      }
    }
    
    return 0;
}



