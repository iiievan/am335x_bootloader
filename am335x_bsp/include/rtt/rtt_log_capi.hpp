#ifndef __RTT_LOG_CAPI_H
#define __RTT_LOG_CAPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


uint64_t rtt_get_system_time_ms(void);
void rtt_time_init(void);

#ifdef __cplusplus
}
#endif


#endif //__BOOT_RTT_LOG_CAPI_H