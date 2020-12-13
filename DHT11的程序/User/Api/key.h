#ifndef _KEY_H_
#define _KEY_H_
#include "stm32f10x.h"

void Init_Key(void);
void Scanf_Key1(void);
u8 Scanf_Key_2(void);

void Key_task(void * tmp);
#endif
