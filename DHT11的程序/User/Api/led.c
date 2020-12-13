#include "led.h"
#include "delay.h"

#define KU_FLAG  1
#define Register_FLAG 0



void Init_LED(void)
{
	/******************************************************************
						�Ĵ������
	********************************************************************/
#if Register_FLAG
	//1:��E�˿ڵ�ʱ��
	RCC->APB2ENR |=(0x01<<6);
	
	//2������IO��Ϊ�������
	//��ƶ��ٶ�ûҪ��  ͨ�ŲŻ���Ҫ��
	GPIOE->CRL &=~(0x0F<<8);//��8 9 10 11����
	GPIOE->CRL |=(0x01<<8);//�ѵ�8λ��1
	
	GPIOE->CRL &=~(0x0F<<12);//��12 13 14 15����
	GPIOE->CRL |=(0x01<<12);//�ѵ�12λ��1
	
	GPIOE->CRL &=~(0x0F<<16);//��12 13 14 15����
	GPIOE->CRL |=(0x01<<16);//�ѵ�12λ��1
	
	GPIOE->CRL &=~(0x0F<<20);//��12 13 14 15����
	GPIOE->CRL |=(0x01<<20);//�ѵ�12λ��1
	
	//3���������LED�Ƶĵ�ƽ���͵�ƽ��
	GPIOE->ODR &=~(0x03<<2);//PE2��PE3����͵�ƽ
#endif
#if  KU_FLAG	
/********************************************************
				�⺯�����
*********************************************************/
	GPIO_InitTypeDef GPIO_InitStruct;
//1����ʱ��	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
//2������GPIO���ŵĹ���ģʽ
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;//�ڶ�������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;//�ٶ�Ϊ2MHZ
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//�����������ģʽ
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;//����������
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;//���ĸ�����
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;//���ĸ�����
	GPIO_Init(GPIOE,&GPIO_InitStruct);
//3����GPIO��һ���ߵ�ƽ/�͵�ƽ
	
#endif
	
}




