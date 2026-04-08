#include <stdarg.h>
#include "string.h"
#include <stdint.h>
#include <stdlib.h>
#include "rtt_log.h"
#include "SEGGER_RTT.h"


#define _RTT_LOG_COLOR(clr) "\033[0;" clr "m"
#define _RTT_LOG_COLOR_RESET "\033[0m"

#define _RTT_LOG_COLOR_BLACK    "30"
#define _RTT_LOG_COLOR_RED      "31"
#define _RTT_LOG_COLOR_GREEN    "32"
#define _RTT_LOG_COLOR_BROWN    "33"
#define _RTT_LOG_COLOR_BLUE     "34"
#define _RTT_LOG_COLOR_PURPLE   "35"

#define _RTT_LOG_COLOR_E _RTT_LOG_COLOR(_RTT_LOG_COLOR_RED)
#define _RTT_LOG_COLOR_W _RTT_LOG_COLOR(_RTT_LOG_COLOR_BROWN)
#define _RTT_LOG_COLOR_I _RTT_LOG_COLOR(_RTT_LOG_COLOR_GREEN)
#define _RTT_LOG_COLOR_D _RTT_LOG_COLOR(_RTT_LOG_COLOR_BLUE)
#define _RTT_LOG_COLOR_T _RTT_LOG_COLOR(_RTT_LOG_COLOR_PURPLE)

#define RTT_LOG_LEVEL_DEFAULT RTTLogLevelDebug

#ifndef MAX_TAG_COUNT
#    define MAX_TAG_COUNT 32
#endif

#ifndef MAX_TAG_LENGTH
#    define MAX_TAG_LENGTH 16
#endif

static rtt_log_level_t m_log_level = RTT_LOG_LEVEL_DEFAULT;
static char*           m_exclude_tag[MAX_TAG_COUNT];

void rtt_log_init(void)
{
    SEGGER_RTT_Init();
}

void rtt_log_print_format(rtt_log_level_t level, const char* tag, const char* format, ...)
{
    if (level > m_log_level)
        return;

    for (int i = 0; i < MAX_TAG_COUNT; i++)
    {
        if (m_exclude_tag[i] != NULL && strcmp(m_exclude_tag[i], tag) == 0)
        {
            return;
        }
    }

    const char* color      = _RTT_LOG_COLOR_RESET;
    const char* log_letter = " ";
    switch (level)
    {
    case RTTLogLevelError:
        color      = _RTT_LOG_COLOR_E;
        log_letter = "E";
        break;
    case RTTLogLevelWarn:
        color      = _RTT_LOG_COLOR_W;
        log_letter = "W";
        break;
    case RTTLogLevelInfo:
        color      = _RTT_LOG_COLOR_I;
        log_letter = "I";
        break;
    case RTTLogLevelDebug:
        color      = _RTT_LOG_COLOR_D;
        log_letter = "D";
        break;
    case RTTLogLevelTrace:
        color      = _RTT_LOG_COLOR_T;
        log_letter = "T";
        break;
    default:
        break;
    }

    const uint32_t rtt_get_tick = 12345;

    SEGGER_RTT_printf(0, "%s%d:\t[%s][%s]:\t", color, rtt_get_tick, log_letter, tag);
    va_list ParamList;
    va_start(ParamList, format);
    SEGGER_RTT_vprintf(0, format, &ParamList);
    va_end(ParamList);
    SEGGER_RTT_printf(0, "%s\n", _RTT_LOG_COLOR_RESET);
}

void rtt_log_exclude_tag(char* tag)
{
    //rtt_assert(tag);
    for (uint8_t i = 0; i < MAX_TAG_COUNT; i++)
    {
        if (m_exclude_tag[i] == NULL)
        {
            m_exclude_tag[i] = malloc(MAX_TAG_LENGTH);
            strncpy(m_exclude_tag[i], tag, MAX_TAG_LENGTH);
            return;
        }
    }
}

void rtt_log_unexclude_tag(char* tag)
{
    //rtt_assert(tag);
    for (uint8_t i = 0; i < MAX_TAG_COUNT; i++)
    {
        if ((m_exclude_tag[i] != NULL) && (strcmp(m_exclude_tag[i], tag) == 0))
        {
            free(m_exclude_tag[i]);
            m_exclude_tag[i] = NULL;
            return;
        }
    }
}

void rtt_log_set_level(rtt_log_level_t level)
{
    //rtt_assert(level <= RHSLogLevelTrace);

    if (level == RTTLogLevelDefault)
    {
        level = RTT_LOG_LEVEL_DEFAULT;
    }
    m_log_level = level;
}

rtt_log_level_t rtt_log_get_level(void)
{
    return m_log_level;
}
