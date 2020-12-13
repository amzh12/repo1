#include "rgb.h"

/*
	R -- PA8
	G -- PA7
	B -- PA6
*/



void Init_RGB(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
//1����ʱ��	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//2������GPIO���ŵĹ���ģʽ
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;//�ڶ�������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;//�ٶ�Ϊ2MHZ
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//�����������ģʽ
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	R_LED(0);G_LED(0);B_LED(0);


}


/*	
	001
	010
	011
	100
	101
	110
	111
*/

#include "usart.h"
#include "stdio.h"

void rgb_task(void * prg)
{
	u8 rgb_flag[7][3]=
{
		0,0,1,
		0,1,0,
		0,1,1,
		1,0,0,
		1,0,1,
		1,1,0,
		1,1,1
};
	static u8 i = 0;
	R_LED(rgb_flag[i][0]);G_LED(rgb_flag[i][1]);B_LED(rgb_flag[i][2]);
	i++;
	if(i==7)
	{
		i=0;
	}
}




