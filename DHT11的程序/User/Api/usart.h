#ifndef _USART_H_
#define _USART_H_
#include "stm32f10x.h"


void init_USART(u32 brr);
void Send_str(char * str);
void USART_Ctrl_LED_Task(void *prg);
#endif

