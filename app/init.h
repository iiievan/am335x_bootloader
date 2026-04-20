#ifndef INIT_H
#define INIT_H

#include "stdint.h"
#ifdef __cplusplus
extern "C" {
#endif

bool init_board(void);
void delay_100us(uint32_t delay);

#ifdef __cplusplus
}
#endif

#endif /* INIT_H */