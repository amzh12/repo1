#ifndef _RGB_H_
#define _RGB_H_
#include "stm32f10x.h"

#define R_LED(x) x?(GPIO_ResetBits(GPIOA,GPIO_Pin_8)):(GPIO_SetBits(GPIOA,GPIO_Pin_8))
#define G_LED(x) x?(GPIO_ResetBits(GPIOA,GPIO_Pin_7)):(GPIO_SetBits(GPIOA,GPIO_Pin_7))
#define B_LED(x) x?(GPIO_ResetBits(GPIOA,GPIO_Pin_6)):(GPIO_SetBits(GPIOA,GPIO_Pin_6))


void Init_RGB(void);
void rgb_task(void * prg);
#endif

