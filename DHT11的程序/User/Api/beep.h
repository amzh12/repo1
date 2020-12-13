#ifndef _BEEP_H_
#define _BEEP_H_
#include "stm32f10x.h"
#define BEEP(x) x?(GPIO_SetBits(GPIOC,GPIO_Pin_0)):(GPIO_ResetBits(GPIOC,GPIO_Pin_0))
void Init_Beep(void);
#endif

