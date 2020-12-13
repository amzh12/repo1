
#include "delay.h"

u32 sys_time =0;//��¼ϵͳʱ��
u16 rgb_run[2]={0,500};
//ϵͳ�δ�����ľ�׼��ʱ
void Delay_ms(u32 time)
{
	sys_time=0;
	while(time>sys_time);
}
//�жϷ�����  1ms����һ��
void SysTick_Handler(void)
{
	sys_time++;
	rgb_run[0]++;
}
// 1us����ʱ
void Delay_1us(void)
{
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
	
}

void Delay_us(uint32_t time)
{
	while(time--)
	{
			Delay_1us();
	}
}
