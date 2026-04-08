#ifndef __RTT_LOG_H
#define __RTT_LOG_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    RTTLogLevelDefault = 0,
    RTTLogLevelNone    = 1,
    RTTLogLevelError   = 2,
    RTTLogLevelWarn    = 3,
    RTTLogLevelInfo    = 4,
    RTTLogLevelDebug   = 5,
    RTTLogLevelTrace   = 6,
} rtt_log_level_t;

void rtt_log_init(void);

void rtt_log_print_format(rtt_log_level_t level, const char* tag, const char* format, ...)
    __attribute__((__format__(__printf__, 3, 4)));

void rtt_log_set_level(rtt_log_level_t level);

rtt_log_level_t rtt_log_get_level(void);

void rtt_log_exclude_tag(char* tag);

void rtt_log_unexclude_tag(char* tag);

#define RTT_LOG_E(tag, format, ...) rtt_log_print_format(RTTLogLevelError, tag, format, ##__VA_ARGS__)
#define RTT_LOG_W(tag, format, ...) rtt_log_print_format(RTTLogLevelWarn, tag, format, ##__VA_ARGS__)
#define RTT_LOG_I(tag, format, ...) rtt_log_print_format(RTTLogLevelInfo, tag, format, ##__VA_ARGS__)
#define RTT_LOG_D(tag, format, ...) rtt_log_print_format(RTTLogLevelDebug, tag, format, ##__VA_ARGS__)
#define RTT_LOG_T(tag, format, ...) rtt_log_print_format(RTTLogLevelTrace, tag, format, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif //__RTT_LOG_H


