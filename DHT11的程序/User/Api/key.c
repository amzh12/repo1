#include "key.h"
#include "delay.h"
#include "led.h"
#include "beep.h"

//按键连接引脚编程输入模式
//浮空输入
//KEY-- PA0
void Init_Key(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//1:开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//2:配置按键引脚位浮空输入
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}

//功能按下 灯亮
//只要你松开 灯立刻灭

//  按键按下一次灯亮
//	按键再按下一次灯亮
#define KEY1 (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))

#define KEY2 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4))
#define KEY3 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5))
#define KEY4 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6))
void Scanf_Key1(void)
{
	static u8 led_flag=0; // 局部变量
	//局部变量  函数一旦结束 空间释放
	//每次进入函数 重新生成且重新赋值
	if(KEY1==1) //能进入if
	{
		Delay_ms(5);//二次判断加延时消抖
		if(KEY1==1) //能进入if
		{
			while(KEY1==1)//绝对就能进入while
			{
				//松开按键跳出循环
				;
			}
			//！ ：非   0变1  1变0
			led_flag=!led_flag;
			BEEP(led_flag);
		}			
		
	}
}


/*
	按键按下
			返回 1  代表按键1按下
				 2  代表按键2按下
				 3  代表按键3按下、
				 4  代表按键4按下
*/
u8 Scanf_Key_2(void)
{
	static u8 unstck1 = 1;//按键松开的
	
	static u8 unstck2 = 1;//按键松开的
	static u8 unstck3 = 1;//按键松开的
	static u8 unstck4 = 1;//按键松开的
	
	
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
		if(key_flag == 1)//按键按下了
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

