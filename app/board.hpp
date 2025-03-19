#ifndef __BOARD_H
#define __BOARD_H

#include "am3358zcz_pins.hpp"
#include "pin.h"

/********************************************************************************************************************/  

/********************************************** beaglebone black board pins ***********************************************/ 
    
/********************************************************************************************************************/

#define USR_LED_0        (PINS::gpmc_a5)    // PINS::e_GPMC_A5::gpio1_21
#define USR_LED_1        (PINS::gpmc_a6)    // PINS::e_GPMC_A6::gpio1_22
#define USR_LED_2        (PINS::gpmc_a7)    // PINS::e_GPMC_A7::gpio1_23
#define USR_LED_3        (PINS::gpmc_a8)    // PINS::e_GPMC_A8::gpio1_24

#define UART0_TX         (PINS::uart0_txd)  // PINS::e_UART0_TXD::gpio1_11
#define UART0_RX         (PINS::uart0_rxd)  // PINS::e_UART0_RXD::gpio1_10

#endif  //__BOARD_H

