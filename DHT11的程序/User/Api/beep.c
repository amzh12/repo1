#include "beep.h"

//��Դ������
//BEEP----PC0
//����ֻ��Ҫ�� PC0 ��һ���ߵ�ƽ �������ͻ���
//�� �͵�ƽ��  �Ͳ���
/*
	��������
			��Դ������--�ڲ��и�ʱ��Դ--����
				��ֻ��Ҫͨ����Դ�������ͻ���
			��Դ������
				�ڲ�û��ʱ��Դ��������Ҫ��Ϊ�ĸ����ṩһ��PWM����
				��ô�������ռ�ձȲ�ͬ�첻ͬ������
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
