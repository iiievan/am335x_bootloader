#ifndef _COMMON_H
#define _COMMON_H

#ifndef NULL
#define NULL ((void*) 0)
#endif

#define REG(addr) (*((volatile uint32_t*)(addr)))

#endif /* _COMMON_H */

