#include <stdint.h>
#include "am3358zcz_pins.hpp"
#include "pin.h"
#include "utils.h"

#define ever (;;)

#define USR_LED_0        (PINS::gpmc_a5)    // PINS::e_GPMC_A5::gpio1_21
#define USR_LED_1        (PINS::gpmc_a6)    // PINS::e_GPMC_A6::gpio1_22
#define USR_LED_2        (PINS::gpmc_a7)    // PINS::e_GPMC_A7::gpio1_23
#define USR_LED_3        (PINS::gpmc_a8)    // PINS::e_GPMC_A8::gpio1_24

am335x_gpio gpio0(REGS::GPIO::AM335x_GPIO_0);
am335x_gpio gpio1(REGS::GPIO::AM335x_GPIO_1);
am335x_gpio gpio2(REGS::GPIO::AM335x_GPIO_2);

int main()
{   
    gpio1.init();     
    USR_LED_0.sel_pinmode(PINS::e_GPMC_A5::gpio1_21);
    USR_LED_0.dir_set(REGS::GPIO::GPIO_OUTPUT);    
    USR_LED_1.sel_pinmode(PINS::e_GPMC_A6::gpio1_22);
    USR_LED_1.dir_set(REGS::GPIO::GPIO_OUTPUT);    
    USR_LED_2.sel_pinmode(PINS::e_GPMC_A7::gpio1_23);
    USR_LED_2.dir_set(REGS::GPIO::GPIO_OUTPUT);    
    USR_LED_3.sel_pinmode(PINS::e_GPMC_A8::gpio1_24);
    USR_LED_3.dir_set(REGS::GPIO::GPIO_OUTPUT);
    
    for ever
    {
        delay_100us(200);
        USR_LED_3.toggle();
    }
    
    return 0;
} 

/******************************* End of file *********************************/
