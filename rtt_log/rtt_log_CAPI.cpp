#include "rtt_log_CAPI.hpp"
#include "HAL/sysTimer.hpp"

extern "C" {

    uint64_t rtt_get_system_time_ms(void)
    {
        return HAL::TIMERS::sys_time.get_ms();
    }

    void rtt_time_init(void)
    {
        // Таймер уже инициализируется в init.cpp
        // Эта функция оставлена для симметрии
    }

}
