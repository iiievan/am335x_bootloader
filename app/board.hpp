#ifndef __BOARD_HPP
#define __BOARD_HPP

#include "pins/am3358zcz_pins.hpp"

namespace Board
{
    // User LEDs BeagleBone Black
    inline auto& USR0 = HAL::PINS::gpmc_a5;   // GPIO1_21
    inline auto& USR1 = HAL::PINS::gpmc_a6;   // GPIO1_22
    inline auto& USR2 = HAL::PINS::gpmc_a7;   // GPIO1_23
    inline auto& USR3 = HAL::PINS::gpmc_a8;   // GPIO1_24

    inline auto& UART0_TX = HAL::PINS::uart0_txd;
    inline auto& UART0_RX = HAL::PINS::uart0_rxd;

    inline void init_user_leds()
    {
        USR0.configure_as_gpio_output(HAL::PINS::e_GPMC_A5::gpio1_21);
        USR1.configure_as_gpio_output(HAL::PINS::e_GPMC_A6::gpio1_22);
        USR2.configure_as_gpio_output(HAL::PINS::e_GPMC_A7::gpio1_23);
        USR3.configure_as_gpio_output(HAL::PINS::e_GPMC_A8::gpio1_24);
    }
}

#endif //__BOARD_HPP