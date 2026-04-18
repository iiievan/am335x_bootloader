#ifndef __AM335X_REGISTERS_H
#define __AM335X_REGISTERS_H

#define     __R     volatile const       // 'read only' register
#define     __W     volatile             // 'write only' register
#define     __RW    volatile             // 'read / write' register

#define BIT(x) (1u << (x))

#include "PRCM.hpp"
#include "CONTROL_MODULE.hpp"
#include "EMIF.hpp"
#include "INTC.hpp"
#include "DMTIMER.hpp"
#include "DMTIMER1MS.hpp"
#include "WDT.hpp"
#include "RTC.hpp"
#include "UART.hpp"
#include "MMCHS.hpp"

#endif //__AM335X_REGISTERS_H