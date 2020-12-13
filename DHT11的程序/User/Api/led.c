#include "led.h"
#include "delay.h"

#define KU_FLAG  1
#define Register_FLAG 0



void Init_LED(void)
{
	/******************************************************************
						寄存器点灯
	********************************************************************/
#if Register_FLAG
	//1:打开E端口的时钟
	RCC->APB2ENR |=(0x01<<6);
	
	//2：配置IO口为推挽输出
	//点灯对速度没要求  通信才会有要求
	GPIOE->CRL &=~(0x0F<<8);//把8 9 10 11清零
	GPIOE->CRL |=(0x01<<8);//把第8位置1
	
	GPIOE->CRL &=~(0x0F<<12);//把12 13 14 15清零
	GPIOE->CRL |=(0x01<<12);//把第12位置1
	
	GPIOE->CRL &=~(0x0F<<16);//把12 13 14 15清零
	GPIOE->CRL |=(0x01<<16);//把第12位置1
	
	GPIOE->CRL &=~(0x0F<<20);//把12 13 14 15清零
	GPIOE->CRL |=(0x01<<20);//把第12位置1
	
	//3：输出点亮LED灯的电平（低电平）
	GPIOE->ODR &=~(0x03<<2);//PE2和PE3输出低电平
#endif
#if  KU_FLAG	
/********************************************************
				库函数点灯
*********************************************************/
	GPIO_InitTypeDef GPIO_InitStruct;
//1：开时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
//2：配置GPIO引脚的工作模式
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;//第二个引脚
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;//速度为2MHZ
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出工作模式
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;//第三个引脚
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;//第四个引脚
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;//第四个引脚
	GPIO_Init(GPIOE,&GPIO_InitStruct);
//3：给GPIO口一个高电平/低电平
	
#endif
	
}




