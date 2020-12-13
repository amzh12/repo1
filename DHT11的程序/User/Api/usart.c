#include "usart.h"
#include "stdio.h"


//PA9 -- TX
//PA10 -- RX
void init_USART(u32 brr)
{
	//打开时钟
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2:GPIO口的初始化	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3:USART的初始化
	
	USART_InitStruct.USART_BaudRate=brr;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_InitStruct);
	
	USART_Cmd(USART1,ENABLE);//打开USART1的开关
	
}

//发送一个数据
void Send_data(u8 data)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0);
	USART_SendData(USART1,data);
}
/*
	"hello"  实际占用6个字节
	最后一个字节叫做结束符 '\0' == 0
*/
// "hello"
void Send_str(char * str)
{
	while(* str != 0)//有没有达到程序的末尾
	{
		Send_data(* str);
		str++;
	}
}

//printf函数内部实际上是打开一个叫做
//  stdout 的文件
//pintf实际上会调用fput
//fput每次智能发送一个字符
//printf函数 打印一个"hello"
//就会调用 6 次fput
//我们只需要把 fputc代码改一下
//那么printf函数的输出方向也会随之发生变化

/*
	C语言内部函数 
	函数写完之后不声明不调用
*/
int fputc(int c ,FILE *Stream)
{
	Send_data(c);
	return c;
}






