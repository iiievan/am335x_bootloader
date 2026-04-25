#ifndef _PIN_HPP
#define _PIN_HPP

#include "regs/REGS.hpp"

namespace HAL::PINS
{
        inline void run_clk_GPIO0()
        {
            using namespace REGS::PRCM;
            auto& wkup = *AM335x_CM_WKUP;
            static bool initialized = false;
            if (initialized) return;

            wkup.GPIO0_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(wkup.GPIO0_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE) {}
            wkup.GPIO0_CLKCTRL.b.OPTFCLKEN_GPIO0_GDBCLK = 0x1;
            while(wkup.GPIO0_CLKCTRL.b.OPTFCLKEN_GPIO0_GDBCLK != 0x1) {}

            /* Verifying if the other bits are set to required settings. */
            while(wkup.CONTROL_CLKCTRL.b.IDLEST != IDLEST_FUNC) {}
            while(wkup.L3_AON_CLKSTCTRL.b.CLKACTIVITY_L3_AON_GCLK != 0x1) {}
            while(wkup.L4WKUP_CLKCTRL.b.IDLEST != IDLEST_FUNC) {}
            while(wkup.CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_GCLK != CLK_ACT) {}
            while(wkup.L4_WKUP_AON_CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_AON_GCLK != 0x1) {}
            while(wkup.GPIO0_CLKCTRL.b.IDLEST != IDLEST_FUNC) {}
            while(wkup.CLKSTCTRL.b.CLKACTIVITY_GPIO0_GDBCLK != CLK_ACT) {}

            initialized = true;
        }

        inline void run_clk_GPIO1()
        {
            using namespace REGS::PRCM;
            auto& per = *AM335x_CM_PER;
            static bool initialized = false;
            if (initialized) return;

            per.GPIO1_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(per.GPIO1_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE) {}
            per.GPIO1_CLKCTRL.b.OPTFCLKEN_GPIO_1_GDBCLK = 0x1;
            while(per.GPIO1_CLKCTRL.b.OPTFCLKEN_GPIO_1_GDBCLK != 0x1) {}
            while(per.GPIO1_CLKCTRL.b.IDLEST != IDLEST_FUNC) {}
            while(per.L4LS_CLKSTCTRL.b.CLKACTIVITY_GPIO_1_GDBCLK != CLK_ACT) {}

            initialized = true;
        }

        inline void run_clk_GPIO2()
        {
            using namespace REGS::PRCM;
            auto& per = *AM335x_CM_PER;
            static bool initialized = false;
            if (initialized) return;

            per.GPIO2_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(per.GPIO2_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE) {}
            per.GPIO2_CLKCTRL.b.OPTFCLKEN_GPIO_2_GDBCLK = 0x1;
            while(per.GPIO2_CLKCTRL.b.OPTFCLKEN_GPIO_2_GDBCLK != 0x1) {}
            while(per.GPIO2_CLKCTRL.b.IDLEST != IDLEST_FUNC) {}
            while(per.L4LS_CLKSTCTRL.b.CLKACTIVITY_GPIO_2_GDBCLK != CLK_ACT) {}

            initialized = true;
        }

        inline void run_clk_GPIO3()
        {
            using namespace REGS::PRCM;
            auto& per = *AM335x_CM_PER;
            static bool initialized = false;
            if (initialized) return;

            per.GPIO3_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(per.GPIO3_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE) {}
            per.GPIO3_CLKCTRL.b.OPTFCLKEN_GPIO_3_GDBCLK = 0x1;
            while(per.GPIO3_CLKCTRL.b.OPTFCLKEN_GPIO_3_GDBCLK != 0x1) {}
            while(per.GPIO3_CLKCTRL.b.IDLEST != IDLEST_FUNC) {}
            while(per.L4LS_CLKSTCTRL.b.CLKACTIVITY_GPIO_3_GDBCLK != CLK_ACT) {}

            initialized = true;
        }

    #define CTRLMREG(x)                              \
    (*((REGS::CONTROL_MODULE::conf_module_pin_reg_t *)(REGS::CONTROL_MODULE::AM335x_CONTROL_MODULE_BASE + x)))

#if BSP_VOLATILE_OVERLOADS
    #define BSP_VOLATILE volatile
#else
    #define BSP_VOLATILE
#endif

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    class pin
    {
    private:

                       REGS::GPIO::AM335x_GPIO_Type &m_gpio_regs;
                                    const uint32_t  m_gpio_regs_adr;
        REGS::CONTROL_MODULE::conf_module_pin_reg_t &m_cntrmdl_reg;
                                           uint32_t  m_pinnum;
                                           uint32_t  m_pinbitmsk;
    public:   
                 explicit pin(REGS::GPIO::AM335x_GPIO_Type *gpio_module) noexcept
                   : m_gpio_regs(*gpio_module),
                    m_gpio_regs_adr((uint32_t)gpio_module),
                     m_cntrmdl_reg(CTRLMREG(ctrlm_reg)),
                     m_pinnum(pinnum)
                { m_pinbitmsk = (1 << m_pinnum); }

                ~pin()= default;

                void  gpio_module_init() BSP_VOLATILE noexcept
                {
                    using namespace REGS::GPIO;
                    static bool module_initialized = false;
                    if (module_initialized) return;

                    //check whether the module is hardware initialized or not.
                    if (m_gpio_regs.SYSSTATUS.b.RESETDONE &&
                        m_gpio_regs.CTRL.b.DISABLEMODULE == 0x0)
                    {
                        module_initialized = true;
                        return;
                    }

                    switch(m_gpio_regs_adr)
                    {
                    case AM335x_GPIO_0_BASE:
                        run_clk_GPIO0();
                        break;
                    case AM335x_GPIO_1_BASE:
                        run_clk_GPIO1();
                        break;
                    case AM335x_GPIO_2_BASE:
                        run_clk_GPIO2();
                        break;
                    case AM335x_GPIO_3_BASE:
                        run_clk_GPIO3();
                        break;
                    default:
                        return;
                    }

                    gpio_module_enable();
                    gpio_module_reset();

                    module_initialized = true;
                }

                void  gpio_module_enable() BSP_VOLATILE noexcept { m_gpio_regs.CTRL.b.DISABLEMODULE = 0x0; }
                void  gpio_module_disable() BSP_VOLATILE noexcept { m_gpio_regs.CTRL.b.DISABLEMODULE = 0x1; }

                void  gpio_module_reset() BSP_VOLATILE noexcept
                {
                    m_gpio_regs.SYSCONFIG.b.SOFTRESET = 0x1;
                    while(!m_gpio_regs.SYSSTATUS.b.RESETDONE);
                }

                /**
                 * @brief Удобная настройка пина как GPIO Output в один вызов
                 * @param gpio_mode  нужный mux-режим (например e_GPMC_A5::gpio1_21)
                 */
                void configure_as_gpio_output(T gpio_mode) BSP_VOLATILE noexcept
                {
                    gpio_module_init();
                    sel_pinmode(gpio_mode);
                    dir_set(REGS::GPIO::GPIO_OUTPUT);
                    // pull-up disabled by default
                    pullup_enable(false);
                }

                /**
                 * @brief Удобная настройка пина как GPIO Input в один вызов
                 * @param gpio_mode  нужный mux-режим
                 */
                void configure_as_gpio_input(T gpio_mode) BSP_VOLATILE noexcept
                {
                    gpio_module_init();
                    sel_pinmode(gpio_mode);
                    dir_set(REGS::GPIO::GPIO_INPUT);
                    pullup_enable(false);
                }

                /**
                * @brief  This API configures the periph mode of the pin.
                * @param  pinmode     The enum pinmode of the pin 0..7 see datasheet
                **/
                void  sel_pinmode(T pinmode) BSP_VOLATILE noexcept
                {
                    m_cntrmdl_reg.b.mode = (uint8_t)(pinmode);
                }

                /**
                * @brief  This API enables pullup of the pin.
                * @param  pull_en enables or disables pullup of the pin
                *
                *  'pull_en' can take one of the following values:
                *  - true - enables the pullup.
                *  - false - disable the pullup.
                **/
                void  pullup_enable(bool pull_en) BSP_VOLATILE noexcept
                {
                    if(pull_en)
                        m_cntrmdl_reg.b.puden = REGS::CONTROL_MODULE::PULL_ENABLED;
                    else
                        m_cntrmdl_reg.b.puden = REGS::CONTROL_MODULE::PULL_DISABLED;
                }

                /**
                * @brief  This API select pull type of the pin
                * @param  putypesel - type of the pull.
                *
                *  'putypesel' can take one of the following values:
                *  - REGS::GPIO::PULL_DOWN - pin pulled down
                *  - REGS::GPIO::PULL_UP - pin pulled up
                **/
                void  sel_pull_type(REGS::CONTROL_MODULE::e_PUTYPESEL putypesel) BSP_VOLATILE noexcept { m_cntrmdl_reg.b.putypesel = putypesel; }

                /**
                * @brief  This API enables input function of the pin
                * @param  rxactive enables or disables input function of the pin
                *
                *  'rxactive' can take one of the following values:
                *  - REGS::GPIO::INPUT_DISABLE - pin as a input
                *  - REGS::GPIO::INPUT_ENABLE - pin as a output
                **/
                void  sel_rxactive(REGS::CONTROL_MODULE::e_RXACTIVE rxactive) BSP_VOLATILE noexcept { m_cntrmdl_reg.b.rxactive = rxactive; }

                /**
                * @brief  This API select slew rate of the pin
                * @param  slewctrl selsect the slew rate of the pin
                *
                *  'slewctrl' can take one of the following values:
                *  - REGS::GPIO::FAST - fast slew rate
                *  - REGS::GPIO::SLOW - slow slew rate
                **/
                void  sel_slewrate(REGS::CONTROL_MODULE::e_SLEWCTRL slewctrl) BSP_VOLATILE noexcept { m_cntrmdl_reg.b.slewctrl = slewctrl; }

                /**
                * @brief  This API configures the direction of a specified GPIO pin as being
                *         either input or output.
                * @param  pindir  The required direction for the GPIO pin
                *
                *   'pindir' can take one of the following values:
                *  - REGS::GPIO::GPIO_INPUT - pindir configure the pin as an input pin\n
                *  - REGS::GPIO::GPIO_OUTPUT - to configure the pin as an output pin\n
                */
                void  dir_set(REGS::GPIO::e_PINDIR pindir) BSP_VOLATILE noexcept
                {
                    if(REGS::GPIO::GPIO_INPUT == pindir)
                    {
                        m_gpio_regs.OE.reg |= m_pinbitmsk; // config as input
                        m_cntrmdl_reg.b.rxactive = REGS::CONTROL_MODULE::INPUT_ENABLE;
                    }
                    else
                    {
                        m_gpio_regs.OE.reg &= ~m_pinbitmsk; // config as output
                        m_cntrmdl_reg.b.rxactive = REGS::CONTROL_MODULE::INPUT_DISABLE;
                    }
                }

                /**
                * @brief   This API determines the direction of a specified GPIO pin.
                *
                * @return  The direction of the specified pin. This returns one of the
                *          following two values:
                *          - REGS::GPIO::GPIO_DIR_INPUT - signifying that the pin is an input pin\n
                *          - REGS::GPIO::GPIO_DIR_OUTPUT - signifying that the pin is an output pin\n
                *
                */
                REGS::GPIO::e_PINDIR  dir_get() BSP_VOLATILE noexcept
                {
                    REGS::GPIO::e_PINDIR result = REGS::GPIO::GPIO_INPUT;

                    if(!(m_gpio_regs.OE.reg & m_pinbitmsk))
                        result = REGS::GPIO::GPIO_OUTPUT;

                    return result;
                }

                /**
                * @brief  This API drives an output GPIO pin to a logic HIGH state.
                **/
                void  set() BSP_VOLATILE noexcept { m_gpio_regs.SETDATAOUT.reg = m_pinbitmsk; }

                /**
                * @brief  This API drives an output GPIO pin to a logic LOW state.
                **/
                void  clear() BSP_VOLATILE noexcept { m_gpio_regs.CLEARDATAOUT.reg = m_pinbitmsk; }

                /**
                * @brief  This API toggle state an output GPIO pin .
                **/
                void  toggle() BSP_VOLATILE noexcept
                {
                    if(m_gpio_regs.DATAOUT.reg & m_pinbitmsk)
                        m_gpio_regs.CLEARDATAOUT.reg = m_pinbitmsk;
                    else
                        m_gpio_regs.SETDATAOUT.reg = m_pinbitmsk;
                }

                /**
                 * @brief  This API drives an output GPIO pin to a logic HIGH or a logic LOW
                 *         state.
                 * @param  value    This specifies whether a logic HIGH or a logic LOW
                 *                     should be driven on the output pin
                 *
                 *   'value' can take one of the following values:
                 *  - false - indicating to drive a logic LOW(logic 0) on the pin.
                 *  - true - indicating to drive a logic HIGH(logic 1) on the pin.
                 */
                void  write(bool value) BSP_VOLATILE noexcept
                {
                    if(value)
                        m_gpio_regs.SETDATAOUT.reg = m_pinbitmsk;
                    else
                        m_gpio_regs.CLEARDATAOUT.reg = m_pinbitmsk;
                }

                /**
                * @brief   This API determines the logic level(value) on a specified
                *          GPIO pin configured as INPUT.
                *
                * @return  The pin value of the specified pin configured as input
                *  - false - indicating a logic LOW(logic 0) on the pin.
                *  - true  - indicating a logic HIGH(logic 1) on the pin.
                */
         inline bool  read_input() const BSP_VOLATILE noexcept { return (bool)(m_gpio_regs.DATAIN.reg & m_pinbitmsk); }

                /**
                * @brief   This API determines the logic level(value) on a specified
                *          GPIO pin configured as OUTPUT.
                *
                * @return  The pin value of the specified pin configured as input
                *  - false - indicating a logic LOW(logic 0) on the pin.
                *  - true  - indicating a logic HIGH(logic 1) on the pin.
                */
         inline bool  read_output() const  BSP_VOLATILE noexcept { return (bool)(m_gpio_regs.DATAOUT.reg & m_pinbitmsk); }


                /**
                 * @brief  This API enables debouncing feature for a specified input
                 *         GPIO pin.Debounce time configured in the corresponding GPIO module
                 *         see debounce_time_config(uint32_t debounce_time).
                 */
                void  debounce_enable() BSP_VOLATILE noexcept
                {
                    m_gpio_regs.DEBOUNCENABLE.reg &= ~m_pinbitmsk;  // clear bit in register
                    m_gpio_regs.DEBOUNCENABLE.reg |= m_pinbitmsk;   // program bit in register
                }

                /**
                 * @brief  This API disables debouncing feature for a specified input
                 *         GPIO pin. Debounce time configured in the corresponding GPIO module
                 *         see debounce_time_config(uint32_t debounce_time).
                 */
                void  debounce_disable() BSP_VOLATILE noexcept
                {
                    m_gpio_regs.DEBOUNCENABLE.reg &= ~m_pinbitmsk;  // clear bit in register
                    m_gpio_regs.DEBOUNCENABLE.reg &= ~m_pinbitmsk;  // program bit in register
                }

                /**
                 * @brief  This API enables the configured interrupt event on a specified input
                 *         GPIO pin to trigger an interrupt request.
                 * @param  intline     This specifies the interrupt request line on which the
                 *                     interrupt request due to the transitions on a specified
                 *                     pin be propagated
                 *
                 *   'intline' can take one of the following two values:
                 *  - REGS::GPIO::GPIO_INT_LINE_1 - interrupt request be propagated over interrupt line 1\n
                 *  - REGS::GPIO::GPIO_INT_LINE_2 - interrupt request be propagated over interrupt line 2\n
                 */
                void  int_enable(uint32_t intline) BSP_VOLATILE noexcept
                {
                    if(REGS::GPIO::INT_LINE_1 == intline)
                        m_gpio_regs.IRQSTATUS_SET_0.reg = m_pinbitmsk;
                    else
                        m_gpio_regs.IRQSTATUS_SET_1.reg = m_pinbitmsk;
                }

                /**
                 * @brief  This API disables interrupt generation due to the detection
                 *         of any event on a specified input GPIO pin.
                 *
                 *   'intline' can take one of the following two values:
                 *  - REGS::GPIO::GPIO_INT_LINE_1 - signifying that the Interrupt Line 1 be disabled to
                 *    transmit interrupt requests due to transitions on specified pin\n
                 *  - REGS::GPIO::GPIO_INT_LINE_2 - signifying that the Interrupt Line 2 be disabled to
                 *    transmit interrupt requests due to transitions on specified pin\n
                 */
                void  int_disable(uint32_t intline) BSP_VOLATILE noexcept
                {
                    if(REGS::GPIO::INT_LINE_1 == intline)
                        m_gpio_regs.IRQSTATUS_CLR_0.reg = m_pinbitmsk;
                    else
                        m_gpio_regs.IRQSTATUS_CLR_1.reg = m_pinbitmsk;
                }

                /**
                 * @brief  This API configures the event type for a specified input GPIO pin.
                 *         Whenever the selected event occurs on that GPIO pin and if interrupt
                 *         generation is enabled for that pin, the GPIO module will send an
                 *         interrupt to CPU.
                 * @param  evnt_type  This specifies the event type on whose detection,
                 *                    the GPIO module will send an interrupt to CPU,
                 *                    provided interrupt generation for that pin is enabled.
                 *
                 *   'evnt_type' can take one of the following values:
                 *  - INT_TYPE_NO_LEVEL - no interrupt request on occurence of either a
                 *    logic LOW or a logic HIGH on the input GPIO pin\n
                 *  - INT_TYPE_LEVEL_LOW - interrupt request on occurence of a LOW level
                 *    (logic 0) on the input GPIO pin\n
                 *  - INT_TYPE_LEVEL_HIGH - interrupt request on occurence of a HIGH level
                 *    (logic 1) on the input GPIO pin\n
                 *  - INT_TYPE_BOTH_LEVEL - interrupt request on the occurence of both the
                 *    LOW level and HIGH level on the input GPIO pin\n
                 *  - INT_TYPE_NO_EDGE -  no interrupt request on either rising or
                 *    falling edges on the pin\n
                 *  - INT_TYPE_RISE_EDGE - interrupt request on occurence of a rising edge
                 *    on the input GPIO pin\n
                 *  - INT_TYPE_FALL_EDGE - interrupt request on occurence of a falling edge
                 *    on the input GPIO pin\n
                 *  - INT_TYPE_BOTH_EDGE - interrupt request on occurence of both a rising
                 *    and a falling edge on the pin\n
                 *
                 * @note  A typical use case of this API is explained below:
                 *        If it is initially required that interrupt should be generated on a
                 *        LOW level only, then this API can be called with
                 *        'INT_TYPE_LEVEL_LOW' as the parameter.
                 *        At a later point of time, if logic HIGH level only should be made as
                 *        the interrupt generating event, then this API has to be first called
                 *        with 'INT_TYPE_NO_LEVEL' as the parameter and later with
                 *        'INT_TYPE_LEVEL_HIGH' as the parameter. Doing this ensures that
                 *        logic LOW level trigger for interrupts is disabled.
                 */
                void  int_type_set(REGS::GPIO::e_INT_TYPE evnt_type) BSP_VOLATILE noexcept
                {
                    switch(evnt_type)
                    {
                        case REGS::GPIO::INT_TYPE_NO_LEVEL:
                            // Disabling logic LOW level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT0.reg &= ~m_pinbitmsk;
                            // Disabling logic HIGH level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT1.reg &= ~m_pinbitmsk;

                            break;
                        case REGS::GPIO::INT_TYPE_LEVEL_LOW:
                            // Enabling logic LOW level detect interrupt geenration.
                            m_gpio_regs.LEVELDETECT0.reg  |=  m_pinbitmsk;
                            // Disabling logic HIGH level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT1.reg  &= ~m_pinbitmsk;
                            // Disabling rising edge detect interrupt generation.
                            m_gpio_regs.RISINGDETECT.reg  &= ~m_pinbitmsk;
                            // Disabling falling edge detect interrupt generation.
                            m_gpio_regs.FALLINGDETECT.reg &= ~m_pinbitmsk;

                            break;
                        case REGS::GPIO::INT_TYPE_LEVEL_HIGH:
                            // Disabling logic LOW level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT0.reg  &=  ~m_pinbitmsk;
                            // Enabling logic HIGH level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT1.reg  |=  m_pinbitmsk;
                            // Disabling rising edge detect interrupt generation.
                            m_gpio_regs.RISINGDETECT.reg  &= ~m_pinbitmsk;
                            // Disabling falling edge detect interrupt generation.
                            m_gpio_regs.FALLINGDETECT.reg &= ~m_pinbitmsk;

                            break;
                        case REGS::GPIO::INT_TYPE_BOTH_LEVEL:
                            // Enabling logic LOW level detect interrupt geenration.
                            m_gpio_regs.LEVELDETECT0.reg  |=  m_pinbitmsk;
                            // Enabling logic HIGH level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT1.reg  |=  m_pinbitmsk;
                            // Disabling rising edge detect interrupt generation.
                            m_gpio_regs.RISINGDETECT.reg  &= ~m_pinbitmsk;
                            // Disabling falling edge detect interrupt generation.
                            m_gpio_regs.FALLINGDETECT.reg &= ~m_pinbitmsk;

                            break;
                        case REGS::GPIO::INT_TYPE_NO_EDGE:
                            // Disabling rising edge detect interrupt generation.
                            m_gpio_regs.RISINGDETECT.reg  &= ~m_pinbitmsk;
                            // Disabling falling edge detect interrupt generation.
                            m_gpio_regs.FALLINGDETECT.reg &= ~m_pinbitmsk;

                            break;
                        case REGS::GPIO::INT_TYPE_RISE_EDGE:
                            // Enabling rising edge detect interrupt generation.
                            m_gpio_regs.RISINGDETECT.reg  |=  m_pinbitmsk;
                            // Disabling falling edge detect interrupt generation.
                            m_gpio_regs.FALLINGDETECT.reg &= ~m_pinbitmsk;
                            // Disabling logic LOW level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT0.reg  &= ~m_pinbitmsk;
                            // Disabling logic HIGH level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT1.reg  &= ~m_pinbitmsk;

                            break;
                        case REGS::GPIO::INT_TYPE_FALL_EDGE:
                            // Disabling rising edge detect interrupt generation.
                            m_gpio_regs.RISINGDETECT.reg  &= ~m_pinbitmsk;
                            // Enabling falling edge detect interrupt generation.
                            m_gpio_regs.FALLINGDETECT.reg |=  m_pinbitmsk;
                            // Disabling logic LOW level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT0.reg  &= ~m_pinbitmsk;
                            // Disabling logic HIGH level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT1.reg  &= ~m_pinbitmsk;

                            break;
                        case REGS::GPIO::INT_TYPE_BOTH_EDGE:
                            // Enabling rising edge detect interrupt generation.
                            m_gpio_regs.RISINGDETECT.reg  |=  m_pinbitmsk;
                            // Enabling falling edge detect interrupt generation.
                            m_gpio_regs.FALLINGDETECT.reg |=  m_pinbitmsk;
                            // Disabling logic LOW level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT0.reg  &= ~m_pinbitmsk;
                            // Disabling logic HIGH level detect interrupt generation.
                            m_gpio_regs.LEVELDETECT1.reg  &= ~m_pinbitmsk;

                            break;
                        default:
                            break;
                    }
                }

                /**
                 * @brief  This API determines the programmed interrupt event type for a
                 *         specified input GPIO pin.
                 * @param  pinnum  The number of the pin in the GPIO instance
                 *
                 * @return This returns one or a combination of the following values:
                 * - INT_TYPE_NO_LEVEL - level trigger for interrupt request is disabled\n
                 * - INT_TYPE_LEVEL_LOW - logic LOW level event for interrupt request is
                 *   enabled\n
                 * - INT_TYPE_LEVEL_HIGH - logic HIGH level event for interrupt request is
                 *   enabled\n
                 * - INT_TYPE_BOTH_LEVEL - both logic LOW and logic HIGH level events
                 *   for interrupt request are enabled\n
                 * - INT_TYPE_NO_EDGE - edge trigger for interrupt request is disabled\n
                 * - INT_TYPE_RISE_EDGE - rising edge event for interrupt request is
                 *   enabled\n
                 * - INT_TYPE_FALL_EDGE - falling edge event for interrupt request
                 *   is enabled\n
                 * - INT_TYPE_BOTH_EDGE - both rising and falling edge events for
                 *   interrupt request are enabled\n
                 */
                uint32_t  int_type_get() BSP_VOLATILE noexcept
                {
                    uint32_t int_event = (REGS::GPIO::INT_TYPE_NO_LEVEL |
                                          REGS::GPIO::INT_TYPE_NO_EDGE);

                    // Checking if logic LOW level trigger interrupt is enabled.
                    if(m_gpio_regs.LEVELDETECT0.reg & m_pinbitmsk)
                    {
                        int_event &= ~(REGS::GPIO::INT_TYPE_NO_LEVEL);
                        int_event |=  REGS::GPIO::INT_TYPE_LEVEL_LOW;
                    }

                    // Checking if logic HIGH level trigger interrupt is enabled.
                    if(m_gpio_regs.LEVELDETECT1.reg & m_pinbitmsk)
                    {
                        int_event &= ~(REGS::GPIO::INT_TYPE_NO_LEVEL);
                        int_event |=  REGS::GPIO::INT_TYPE_LEVEL_HIGH;
                    }

                    // Checking if rising edge trigger interrupt is enabled.
                    if(m_gpio_regs.RISINGDETECT.reg & m_pinbitmsk)
                    {
                        int_event &= ~(REGS::GPIO::INT_TYPE_NO_EDGE);
                        int_event |=  REGS::GPIO::INT_TYPE_RISE_EDGE;
                    }

                    // Checking if falling edge trigger interrupt is enabled.
                    if(m_gpio_regs.FALLINGDETECT.reg & m_pinbitmsk)
                    {
                        int_event &= ~(REGS::GPIO::INT_TYPE_NO_EDGE);
                        int_event |=  REGS::GPIO::INT_TYPE_FALL_EDGE;
                    }

                    return int_event;
                }

                /**
                 * @brief  This API determines the enabled interrupt status of a specified pin.
                 * @param  intline    This specifies the interrupt line whose corresponding
                 *                    enabled interrupt status register has to be accessed.
                 *                    The status of the specified pin is returned in this API.
                 *
                 *  'intline' can take one of the following two values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to read the enabled interrupt status register
                 *   corresponding to interrupt line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to read the enabled interrupt status register
                 *   corresponding to interrupt line 2\n
                 *
                 * @return The enabled interrupt status of the pin on the specified interrupt
                 *         line. This could either be a non-zero or a zero value.
                 */
                bool  int_status(uint32_t intline) BSP_VOLATILE noexcept
                {
                    bool int_sts = false;

                    if(REGS::GPIO::INT_LINE_1 == intline)
                        int_sts = (m_gpio_regs.IRQSTATUS_0.reg & m_pinbitmsk);
                    else
                        int_sts = (m_gpio_regs.IRQSTATUS_1.reg & m_pinbitmsk);

                    return int_sts;
                }

                /**
                 * @brief  This API determines the raw interrupt status of the specified GPIO
                 *         pins in the instance corresponding to the specified interrupt line.
                 * @param  intline    This specifies the interrupt line whose corresponding
                 *                    raw interrupt status register has to be read.
                 *
                 *  'intline' can take one of the following two values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to read the raw interrupt status register corresponding
                 *   to interrupt line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to read the raw interrupt status register corresponding
                 *   to interrupt line 2\n
                 *
                 * @return  The raw interrupt status of the specified pins of the GPIO instance
                 *          corresponding to a specified interrupt line.
                 */
                bool  raw_int_status(uint32_t intline) BSP_VOLATILE noexcept
                {
                    bool int_sts = false;

                    if(REGS::GPIO::INT_LINE_1 == intline)
                        int_sts = (m_gpio_regs.IRQSTATUS_RAW_0.reg & m_pinbitmsk);
                    else
                        int_sts = (m_gpio_regs.IRQSTATUS_RAW_1.reg & m_pinbitmsk);

                    return int_sts;
                }

                /**
                 * @brief  This API clears the enabled interrupt status of a specified GPIO
                 *         pin.
                 * @param  intline    This specifies the interrupt line whose corresponding
                 *                    enabled interrupt status register has to be accessed.
                 *                    The status of the specified bit in it is cleared in this
                 *                    API.
                 *
                 *  'intline' can take one of the following two values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to access the enabled interrupt status register
                 *   corresponding to interrupt line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to access the enabled interrupt status register
                 *   corresponding to interrupt line 2\n *
                */
                void  int_clear(uint32_t intline) BSP_VOLATILE noexcept
                {
                    if(REGS::GPIO::INT_LINE_1 == intline)
                        m_gpio_regs.IRQSTATUS_0.reg = m_pinbitmsk;
                    else
                        m_gpio_regs.IRQSTATUS_1.reg = m_pinbitmsk;
                }

                /**
                 * @brief  This API manually triggers an interrupt request due to a specified
                 *         GPIO pin.
                 * @param  intline    This specifies the interrupt line over which the
                 *                    manually triggered interrupt request has to be
                 *                    propogated
                 *
                 *  'intline' can take one of the following values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to propogate the interrupt request over interrupt
                 *   line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to propogate the interrupt request over interrupt
                 *   line 2\n
                 *
                 * @note  Here an interrupt request is manually triggered by writing to a
                 *        specified bit in the Raw Interrupt Status register. As a
                 *        pre-requisite, the interrupt generation should be enabled for the
                 *        GPIO pin.
                 */
                void  trigger_int(uint32_t intline) BSP_VOLATILE noexcept
                {
                    if(REGS::GPIO::INT_LINE_1 == intline)
                        m_gpio_regs.IRQSTATUS_RAW_0.reg = m_pinbitmsk;
                    else
                        m_gpio_regs.IRQSTATUS_RAW_1.reg = m_pinbitmsk;
                }

                /**
                 * @brief  This API enables the feature for the specified Input GPIO Pin
                 *         (Interrupt Request Source) to generate an asynchronous wakeup
                 *         signal to the CPU.
                 * @param  intline This specifies the Smart Wakeup Interrupt Line over
                 *         which the asynchrounous wakeup signal has to be
                 *         propogated due to the specified Input GPIO pin.
                 *
                 *  'intline' can take one of the following values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to propogate the wakeup request over Smart
                 *   Wakeup Interrupt Line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to propagate the wakeup request over Smart
                 *   Wakeup Interrupt Line 2\n
                 * @note  1> Make sure that the GPIO instance in context is allowed to generate
                 *           Wakeup interrupts to the CPU. If allowed, then enable Wakeup
                 *           interrupt generation feature for that GPIO instance in the Interrupt
                 *           Controller.\n
                 *        2> Usually an Input GPIO Pin acts as an Interrupt Request(IRQ) Source.
                 *           An expected transition on an Input GPIO Pin can generate a Wakeup
                 *           request.\n
                 */
                void  int_wakeup_enable(uint32_t intline) BSP_VOLATILE noexcept
                {
                    if(REGS::GPIO::INT_LINE_1 == intline)
                        m_gpio_regs.IRQWAKEN_0.reg |= m_pinbitmsk;
                    else
                        m_gpio_regs.IRQWAKEN_1.reg |= m_pinbitmsk;
                }

                /**
                 * @brief  This API disables the feature for the specified Input GPIO Pin
                 *         (Interrupt Request Source) to generate an asynchronous wakeup
                 *         signal to the CPU.
                 * @param  intline This specifies the Smart Wakeup Interupt Line which has
                 *                     to be disabled to propogate any asynchrounous wakeup
                 *                     signal due to the specified input GPIO Pin.
                 *
                 *  'intline' can take one of the following values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to propogate the wakeup request over Smart
                 *   Wakeup Interrupt Line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to propagate the wakeup request over Smart
                 *   Wakeup Interrupt Line 2\n
                 */
                void  int_wakeup_disable(uint32_t intline) BSP_VOLATILE noexcept
                {
                    if(REGS::GPIO::INT_LINE_1 == intline)
                        m_gpio_regs.IRQWAKEN_0.reg &= ~m_pinbitmsk;
                    else
                        m_gpio_regs.IRQWAKEN_1.reg &= ~m_pinbitmsk;
                }

    };

}  // namespace HAL::PINS

#endif // _PIN_HPP