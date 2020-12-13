#include "key.h"
#include "delay.h"
#include "led.h"
#include "beep.h"

//�����������ű������ģʽ
//��������
//KEY-- PA0
void Init_Key(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//1:��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//2:���ð�������λ��������
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}

//���ܰ��� ����
//ֻҪ���ɿ� ��������

//  ��������һ�ε���
//	�����ٰ���һ�ε���
#define KEY1 (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))

#define KEY2 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4))
#define KEY3 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5))
#define KEY4 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6))
void Scanf_Key1(void)
{
	static u8 led_flag=0; // �ֲ�����
	//�ֲ�����  ����һ������ �ռ��ͷ�
	//ÿ�ν��뺯�� �������������¸�ֵ
	if(KEY1==1) //�ܽ���if
	{
		Delay_ms(5);//�����жϼ���ʱ����
		if(KEY1==1) //�ܽ���if
		{
			while(KEY1==1)//���Ծ��ܽ���while
			{
				//�ɿ���������ѭ��
				;
			}
			//�� ����   0��1  1��0
			led_flag=!led_flag;
			BEEP(led_flag);
		}			
		
	}
}


/*
	��������
			���� 1  ������1����
				 2  ������2����
				 3  ������3���¡�
				 4  ������4����
*/
u8 Scanf_Key_2(void)
{
	static u8 unstck1 = 1;//�����ɿ���
	
	static u8 unstck2 = 1;//�����ɿ���
	static u8 unstck3 = 1;//�����ɿ���
	static u8 unstck4 = 1;//�����ɿ���
	
	
	if(KEY1==1&&unstck1==1)
	{
		unstck1 = 0;
		return 1;
	}else if(KEY1==0)
	{
		unstck1=1;
	}
	
	if(KEY2==0&&unstck2==1)
	{
		unstck2 = 0;
		return 2;
	}else if(KEY2==1)
	{
		unstck2=1;
	}
	
	if(KEY3==0&&unstck3==1)
	{
		unstck3 = 0;
		return 3;
	}else if(KEY3==1)
	{
		unstck3=1;
	}
	
	if(KEY4==0&&unstck4==1)
	{
		unstck4 = 0;
		return 4;
	}else if(KEY4==1)
	{
		unstck4=1;
	}
	return 0xFF;
}

void Key_task(void * tmp)
{
	u8 key_flag=0;
	u8 led1flag=0;
	u8 led2flag=0;
	u8 led3flag=0;
	u8 led4flag=0;
	while(1)
	{
		key_flag=Scanf_Key_2();
		if(key_flag == 1)//����������
		{
			led1flag=!led1flag;
			
			LED1(led1flag);
		}else if(key_flag == 2)
		{
			led2flag=!led2flag;
			LED2(led2flag);
		}else if(key_flag == 3)
		{
			led3flag=!led3flag;
			LED3(led3flag);
		}else if(key_flag == 4)
		{
			led4flag=!led4flag;
			LED4(led4flag);
		}
		Delay_ms(10);
	}
}

