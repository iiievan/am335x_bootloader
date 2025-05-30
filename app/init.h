#ifndef __INIT_H
#define __INIT_H

void init_board(void);

void mpu_pll_init(void);
void core_pll_init(void); 
void per_pll_init(void);
void ddr_pll_init(void);
void interface_clocks_init(void);

void ddr_init(void);
uint8_t ddr_check(void);

#endif  //__INIT_H

