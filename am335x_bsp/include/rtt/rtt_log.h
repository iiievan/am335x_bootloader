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

#define RTT_LOG_E(tag, format, ...) rtt_log_print_format(RTTLogLevelError, tag, format, ##__VA_ARGS__)  // RED
#define RTT_LOG_W(tag, format, ...) rtt_log_print_format(RTTLogLevelWarn, tag, format, ##__VA_ARGS__)   // BROWN
#define RTT_LOG_I(tag, format, ...) rtt_log_print_format(RTTLogLevelInfo, tag, format, ##__VA_ARGS__)   // GREEN
#define RTT_LOG_D(tag, format, ...) rtt_log_print_format(RTTLogLevelDebug, tag, format, ##__VA_ARGS__)  // BLUE
#define RTT_LOG_T(tag, format, ...) rtt_log_print_format(RTTLogLevelTrace, tag, format, ##__VA_ARGS__)  // PURPLE

/**
 * @brief macros for printing register content through Segger RTT
 * @param level - debug level for color in log E,W,I,D,T
 * @param module_name - string name of module which rgister belong
 * @param reg_name - string of register name
 * @param reg_value - register itself
 *
 * RTT_LOG_REG(D,CM_WKUP, CONTROL_CLKCTRL, wkup.CONTROL_CLKCTRL.reg); // print register before modification (BLUE)
 * RTT_LOG_REG(E,CM_WKUP, CONTROL_CLKCTRL, wkup.CONTROL_CLKCTRL.reg); // print register after modification (RED)
 */
#define RTT_LOG_REG(level, module_name, reg_name, reg_value) \
    RTT_LOG_##level(#module_name,"%s = 0x%08X",#reg_name, (unsigned int)(reg_value))

#define RTT_CHECK_MODULE_SIZE(module_type, last_reg_offset) \
do { \
const size_t expected_size = (last_reg_offset) + 4; \
const size_t actual_size = sizeof(module_type); \
if(actual_size != expected_size) { \
RTT_LOG_E("module_size", "%s size mismatch! Expected: 0x%08X, Actual: 0x%08X (diff: %d bytes)", \
 #module_type, (unsigned int)expected_size, (unsigned int)actual_size, \
(int)(actual_size - expected_size)); \
} else { \
RTT_LOG_D("module_size", "%s size OK: 0x%08X", #module_type, (unsigned int)actual_size); \
} \
} while(0)

#ifdef NDEBUG
#define RTT_LOG_ASSERT(expr) ((void)0)
#else
#define RTT_LOG_ASSERT(expr) \
do { \
if (!(expr)) { \
rtt_log_print_format(RTTLogLevelError, "ASSERT", \
"Assertion failed: %s, file %s, line %d", \
#expr, __FILE__, __LINE__); \
while(1); /* или __asm("bkpt 1) для отладчика */ \
} \
} while(0)
#endif

#ifdef __cplusplus
}
#endif

#endif //__RTT_LOG_H


