#ifndef _DELAY_H_
#define _DELAY_H_
#include "stm32f10x.h"
extern u16 rgb_run[2];
void Delay_1us(void);
void Delay_ms(u32 time);
void Delay_us(u32 time);
#endif
