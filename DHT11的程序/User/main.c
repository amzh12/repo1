#include "stm32f10x.h"
#include "stdio.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "beep.h"
#include "usart.h"
#include "rgb.h"
#include "lcd.h"
#include "dht11.h"
//�ر�JTAG���ܣ���SWD����
inline void JTAG_SWD_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
}
extern unsigned char gImage_gou_pic[153600];
int main(void)
{
	extern u8 dht11_buf[5];
	u8 led_flag=0;
	JTAG_SWD_Config();
	SysTick_Config(72000);
	Init_LED();//��ʼ��LED��
	Init_Key();//��ʼ������
	Init_Beep();//��ʼ��������
	Init_RGB();//��ʼ��RGB��
	init_USART(921600);//��ʼ������
	printf("��ʼ���ɹ�\n");
	Init_LCD();
	Init_DHT11_GPIO();
//	Draw_Pic(240,320,(u16 *)gImage_gou_pic);
	Show_Sting(50,200,0xF800,0x1F,"�����й�������12Mandht11_buf[0]\r\n");
	while(1)
	{
		if(rgb_run[0]>rgb_run[1])
		{
			rgb_run[0]=0;
			rgb_task(NULL);
			led_flag=!led_flag;
			LED1(led_flag);LED2(led_flag);LED3(led_flag);LED4(led_flag);
		}
		Delay_ms(2000);
		Get_DHT11_Value();
		
	}
}





