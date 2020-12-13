#include "usart.h"
#include "stdio.h"


//PA9 -- TX
//PA10 -- RX
void init_USART(u32 brr)
{
	//��ʱ��
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2:GPIO�ڵĳ�ʼ��	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//�����������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3:USART�ĳ�ʼ��
	
	USART_InitStruct.USART_BaudRate=brr;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_InitStruct);
	
	USART_Cmd(USART1,ENABLE);//��USART1�Ŀ���
	
}

//����һ������
void Send_data(u8 data)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0);
	USART_SendData(USART1,data);
}
/*
	"hello"  ʵ��ռ��6���ֽ�
	���һ���ֽڽ��������� '\0' == 0
*/
// "hello"
void Send_str(char * str)
{
	while(* str != 0)//��û�дﵽ�����ĩβ
	{
		Send_data(* str);
		str++;
	}
}

//printf�����ڲ�ʵ�����Ǵ�һ������
//  stdout ���ļ�
//pintfʵ���ϻ����fput
//fputÿ�����ܷ���һ���ַ�
//printf���� ��ӡһ��"hello"
//�ͻ���� 6 ��fput
//����ֻ��Ҫ�� fputc�����һ��
//��ôprintf�������������Ҳ����֮�����仯

/*
	C�����ڲ����� 
	����д��֮������������
*/
int fputc(int c ,FILE *Stream)
{
	Send_data(c);
	return c;
}






