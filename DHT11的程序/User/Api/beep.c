#include "beep.h"

//有源蜂鸣器
//BEEP----PC0
//我们只需要把 PC0 给一个高电平 蜂鸣器就会响
//给 低电平的  就不响
/*
	蜂鸣器：
			有源蜂鸣器--内部有个时钟源--方波
				你只需要通电有源蜂鸣器就会响
			无源蜂鸣器
				内部没有时钟源，所以需要人为的给他提供一个PWM方波
				那么他会根据占空比不同响不同的声音
*/

void Init_Beep(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
}
